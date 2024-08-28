// maximum_pages.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

int maximumPages(std::vector<int> &a) {
    int n = a.size();
    if (n < 2) {
        throw std::invalid_argument("At least two books are required");
    }
    int max1 = *std::max_element(a.begin(), a.end() - 1);
    return max1 + a[n - 1];
}

int main(int argc, char *argv[]) {
    try {
        int t = std::stoi(argv[1]);  // First argument is the number of test cases
        int argIndex = 2;

        while (t--) {
            int n = std::stoi(argv[argIndex++]);  // Next argument is the number of books
            if (n < 2) {
                std::cerr << "At least two books are required" << std::endl;
                return EXIT_FAILURE;
            }

            std::vector<int> a(n);
            for (int i = 0; i < n; i++) {
                a[i] = std::stoi(argv[argIndex++]);  // Fill the array with page numbers
            }

            int ans = maximumPages(a);
            std::cout << ans << "\n";
        }

        return EXIT_SUCCESS;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument" << std::endl;
        return EXIT_FAILURE;
    } catch (const std::out_of_range& e) {
        std::cerr << "Argument out of range" << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unexpected error" << std::endl;
        return EXIT_FAILURE;
    }
}
