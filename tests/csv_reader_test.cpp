#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "csv_reader.hpp"


TEST_CASE("empty", "[csv_reader]") {
    std::fstream fs;

    csv::CsvReader reader(fs);
    const auto rows = reader.Read();

    REQUIRE(rows.empty());
}