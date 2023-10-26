#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
    std::map<std::string, int> counts;
    std::string inputFile = "input.txt";
    std::string outputFile = "statisctic.txt";
    std::ifstream input(inputFile);
    if (!input) {
        std::cerr << "error while openning inStream" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(input, line)) {
        counts[line]++;
    }
    input.close();
    std::ofstream output(outputFile);
    if (!output) {
        std::cerr << "error while openning outStream" << std::endl;
        return 1;
    }
    for (const auto& pair : counts) {
        output << pair.first << ": " << pair.second << std::endl;
    }
    output.close();
    return 0;
}
