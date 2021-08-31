#include <iostream>

#include "csv_reader.hpp"


int main() {
    std::cout << "reading csv\n";
    std::fstream fs{};
    
    csv::CsvReader reader(fs);
    try {
        const auto rows = reader.Read();
        for (const auto& row : rows) {
            for (const auto& cell : row) {
                std::cout << cell << ',';
            }
            std::cout << '\n';
        }
        std::cout << "done\n";
    } catch (const csv::CsvParsingError& e) {
        std::cout << e.what();
    }
    
    return 0;
}