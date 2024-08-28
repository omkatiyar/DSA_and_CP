def resolve_type(type_key, basedict, typedefdict, pointerdict, structdict, constdict, arraydict):
    global current_struct_name
    print(f"resolve_type({type_key})")
    if type_key in basedict:
        return basedict[type_key].get("name"), basedict[type_key].get("byte_size")
    elif type_key in constdict:
        res = resolve_type(constdict[type_key], basedict, typedefdict, pointerdict, structdict, constdict, arraydict)
        if isinstance(res[0], str):
            return res[0], "const"
    elif type_key in arraydict:
        array_type = arraydict[type_key].get("type_key")
        array_bound = arraydict[type_key].get("upper_bound")
        array_type_name = None
        res = resolve_type(array_type, basedict, typedefdict, pointerdict, structdict, constdict, arraydict)
        if isinstance(res[0], str):
            array_type_name = res[0]
            return array_type_name + array_bound, "array"
        elif isinstance(res[0], dict):
            array_type_name = res[1]
            return array_type_name + array_bound, "array"
    elif type_key in pointerdict:
        pointer_data = pointerdict[type_key]
        if pointer_data['type_key'] is None:
            return pointer_data['name'], "pointer"
        else:
            res = resolve_type(pointer_data['type_key'], basedict, typedefdict, pointerdict, structdict, constdict, arraydict)
            if isinstance(res[0], str):
                return pointer_data['name'], "pointer"
            elif isinstance(res[0], dict):
                return res[0], "pointer"
    elif type_key in typedefdict:
        name = typedefdict[type_key]['name']
        current_struct_name.set_current_name(name)
        res = resolve_type(typedefdict[type_key]['type_key'], basedict, typedefdict, pointerdict, structdict, constdict, arraydict)
        if isinstance(res[0], dict):
            return res[0], name
        elif isinstance(res[0], str):
            if res[1] == "pointer":
                return res[0], True
            else:
                return name, True
        else:
            return name, False
    elif type_key in structdict:
        struct = structdict[type_key]
        struct_name = struct['name']
        if struct_name is None:
            struct_name = current_struct_name.current_name
        if current_struct_name.contains(struct_name):
            return struct_name, True
        else:
            current_struct_name.append(struct_name)
        resolved_struct = {}
        for member in struct['members']:
            member_name = member['name']
            member_type_key = member['type_key']
            member_offset = member['offset']
            if member_type_key in pointerdict:
                member_name = member_name + "*"
                print(f"member_name = {member_name} member_type_key = {member_type_key} pointerdict = {pointerdict}")
            res = resolve_type(member_type_key, basedict, typedefdict, pointerdict, structdict, constdict, arraydict)
            if isinstance(res[0], str):
                resolved_struct[member_name] = {"name": member_name, "offset": member_offset, "type": res[0]}
            elif isinstance(res[0], dict):
                resolved_struct[member_name] = {"name": member_name, "offset": member_offset, "members": res[0]}
        current_struct_name.pop()
        return resolved_struct, struct_name
    else:
        return None, False
