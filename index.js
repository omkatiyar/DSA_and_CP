async function generateItinerary(zone, type, itinerary, iataData, durationData) {
    let generatedItinerary = { "itinerary": {} };

    async function mapSegment(segment, flightType, index, segmentType) {
        const departData = iataData[flightType].depart[0].data;
        const arriveData = iataData[flightType].arrive[0].data;

        const legs = [];
        for (let leg of segment.legs) {
            try {
                const op_carrierData = await MongoApiFindOne('airlines', { iata_code: leg.op_carrier.iata });
                leg.op_carrier.name = op_carrierData.data.name || '';
                leg.op_carrier.url = op_carrierData.data.logo_svg_url || '';

                const mk_carrierData = await MongoApiFindOne('airlines', { iata_code: leg.mk_carrier.iata });
                leg.mk_carrier.name = mk_carrierData.data.name || '';
                leg.mk_carrier.url = mk_carrierData.data.logo_svg_url || '';
            } catch (error) {
                // Handle error
            }

            const legDuration = calculateDuration(leg.depart.date, leg.depart.time, leg.arrive.date, leg.arrive.time);

            legs.push({
                "depart": {
                    "iata": leg.depart.iata,
                    "city": departData.translations[0].city.name,
                    "airport": departData.translations[0].name,
                    "terminal": leg.depart.terminal,
                    "date": leg.depart.date,
                    "time": leg.depart.time,
                    "geo": departData.coordinates,
                    "country": departData.translations[0].country.name,
                },
                "arrive": {
                    "iata": leg.arrive.iata,
                    "city": arriveData.translations[0].city.name,
                    "airport": arriveData.translations[0].name,
                    "terminal": leg.arrive.terminal,
                    "date": leg.arrive.date,
                    "time": leg.arrive.time,
                    "geo": arriveData.coordinates,
                    "country": arriveData.translations[0].country.name,
                },
                "id": leg.id,
                "type": segmentType || 'outbound',
                "op_carrier": leg.op_carrier,
                "mk_carrier": leg.mk_carrier,
                "aircraft": leg.aircraft,
                "cabin": leg.cabin,
                "rbd": leg.rbd,
                "meal": leg.meal,
                "layover": leg.layover,
                "baggage": leg.baggage,
                "duration": legDuration,
                "segment_ref_no": "",
                "group": 0,
                "linkavailability": false,
                "segmentindex": 0,
                "techstop": 0,
            });
        }

        return {
            "depart": {
                "iata": segment.depart.iata,
                "city": departData.translations[0].city.name,
                "country": departData.translations[0].country.name,
                "state": departData.translations[0].state?.name || "",
                "airport": departData.translations[0].name,
                "date": segment.depart.date,
                "time": segment.depart.time,
                "geo": departData.coordinates,
            },
            "arrive": {
                "iata": segment.arrive.iata,
                "city": arriveData.translations[0].city.name,
                "airport": arriveData.translations[0].name,
                "state": arriveData.translations[0].state?.name || "",
                "country": arriveData.translations[0].country.name,
                "date": segment.arrive.date,
                "time": segment.arrive.time,
                "geo": arriveData.coordinates,
            },
            "id": index + 1,
            "segdet": `${segment.depart.iata} - ${segment.arrive.iata}`,
            "stops": segment.stops,
            "duration": durationData[flightType].durationMinutes,
            "duration_seconds": durationData[flightType].durationseconds,
            "legs": legs
        };
    }

    function calculateDuration(departDate, departTime, arriveDate, arriveTime) {
        const departDateTime = new Date(`${departDate}T${departTime}`);
        const arriveDateTime = new Date(`${arriveDate}T${arriveTime}`);
        const durationMs = arriveDateTime - departDateTime;
        const durationHours = Math.floor(durationMs / (1000 * 60 * 60));
        const durationMinutes = Math.floor((durationMs % (1000 * 60 * 60)) / (1000 * 60));
        return `${durationHours}:${durationMinutes.toString().padStart(2, '0')}`;
    }

    if (zone === "domestic") {
        if (["one-way", "return", "multi-city"].includes(type)) {
            generatedItinerary.itinerary.flight1 = {
                "search_type": type,
                "segs": []
            };

            for (let i = 0; i < itinerary.flight1.segs.length; i++) {
                const segment = itinerary.flight1.segs[i];
                const segmentType = type === "return" && i === 0 ? 'outbound' : 'outbound';
                generatedItinerary.itinerary.flight1.segs.push(await mapSegment(segment, 'flight1', i, segmentType));
            }

            if (["return", "multi-city"].includes(type)) {
                generatedItinerary.itinerary.flight2 = {
                    "search_type": type,
                    "segs": []
                };

                for (let i = 0; i < itinerary.flight2.segs.length; i++) {
                    const segment = itinerary.flight2.segs[i];
                    const segmentType = type === "return" && i === 0 ? 'outbound' : 'inbound';
                    generatedItinerary.itinerary.flight2.segs.push(await mapSegment(segment, 'flight2', i, segmentType));
                }
            }
        }
    } else if (zone === "international") {
        generatedItinerary.itinerary.flight1 = {
            "search_type": type,
            "segs": []
        };

        const maxSegs = type === "return" ? 2 : (type === "multi-city" ? 6 : 1);
        for (let i = 0; i < Math.min(itinerary.flight1.segs.length, maxSegs); i++) {
            const segment = itinerary.flight1.segs[i];
            const segmentType = type === "return" && i === 1 ? 'inbound' : 'outbound';
            generatedItinerary.itinerary.flight1.segs.push(await mapSegment(segment, 'flight1', i, segmentType));
        }
    }

    return generatedItinerary;
}
