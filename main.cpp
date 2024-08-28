#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Flattened 2D array (3 rows and 4 columns)
    std::vector<int> data = {
        1, 2, 3, 4,   // row 0
        5, 6, 7, 8,   // row 1
        9, 10, 11, 12 // row 2
    };

    size_t numRows = 3;  // Number of rows in the flattened array
    size_t numCols = 4;  // Number of columns in the flattened array
    size_t colIndex = 2; // Index of the column to find max (0-based index)

    // Using a lambda function to get maximum in the specified column
    auto maxInColumn = std::max_element(
        data.begin() + colIndex, data.end(),              
        [numCols](int a, int b) { // Lambda to compare elements at column strides
            return a < b;
        }
    );

    // Display the maximum element found in the specified column
    if (maxInColumn != data.end()) {
        std::cout << "Maximum in column " << colIndex << " is: " << *maxInColumn << std::endl;
    } else {
        std::cout << "Column out of bounds" << std::endl;
    }

    return 0;
}
