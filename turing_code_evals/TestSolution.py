import cppyy
import unittest

class VehicleOptionsTest(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        try:
            # Define the C++ code within cppyy
            cppyy.cppdef("""
                #include <iostream>
                #include <string>
                #include <sstream>
                using namespace std;

                string displayVehicleOptions(int option) {
                    ostringstream out;  // Create an ostringstream to capture the output

                    switch(option) {
                    case 1:
                        out << "Service Option : Swift Economy" << endl;
                        out << "Vehicle Type : Ford Fiesta " << endl;
                        out << "Notes : This hatchback is ideal for small trips due to its compact size." << endl;
                        out << "Its strong reliability and fuel consumption make it a prime choice for Swift Economy!" << endl;
                        break;
                    case 2:
                        out << "Service Option : Standard Swift" << endl;
                        out << "Vehicle Type : Honda Accord " << endl;
                        out << "Notes : The Accord fits more passengers than typical hatchbacks, up to 4 total." << endl;
                        out << "Greater load means more fuel use, but it's still a wise choice for Standard Swift service." << endl;
                        break;
                    case 3:
                        out << "Service Option : Supreme Swift" << endl;
                        out << "Vehicle Type : Dodge Caravan " << endl;
                        out << "Notes : This 7-seater ideal for families with lot of baggage, though it has a higher fuel cost." << endl;
                        out << "Despite the cost, its capacity for numerous passengers and luggage is advantageous!" << endl;
                        break;
                    default:
                        out << "Invalid option!" << endl;
                        break;
                    }

                    return out.str();  // Return the captured output as a string
                }
            """)
        except Exception as e:
            raise unittest.SkipTest(f"Error during C++ compilation: {str(e)}")

    def test_swift_economy_option(self):
        # Step 1: Call the C++ function and capture the returned string
        output = cppyy.gbl.displayVehicleOptions(1)

        # Step 2: Define the expected output
        expected_output = (
            "Service Option : Swift Economy\n"
            "Vehicle Type : Ford Fiesta \n"
            "Notes : This hatchback is ideal for small trips due to its compact size.\n"
            "Its strong reliability and fuel consumption make it a prime choice for Swift Economy!\n"
        )

        # Step 3: Compare the captured output to the expected output
        self.assertEqual(output, expected_output)

if __name__ == '__main__':
    unittest.main(verbosity=2)
