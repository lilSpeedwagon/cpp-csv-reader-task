#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "csv_reader.hpp"


void CompareRows(const csv::Row& lhs, const csv::Row& rhs) {
    REQUIRE(lhs.size() == rhs.size());
    for (size_t i = 0; i < lhs.size(); i++) {
        REQUIRE(lhs[i] == rhs[i]);
    }
}


TEST_CASE("empty input") {
    std::stringstream stream;

    csv::CsvReader reader(stream);
    const auto rows = reader.Read();

    REQUIRE(rows.empty());
}

TEST_CASE("simple row") {
    std::stringstream stream;
    stream << "value1,value2,value3";

    csv::CsvReader reader(stream);
    const auto rows = reader.Read();

    csv::Row expected_row = {
        "value1", "value2", "value3",
    };
    REQUIRE(rows.size() == 1);
    CompareRows(expected_row, rows.front());
}

TEST_CASE("empty values") {
    std::stringstream stream;
    stream << ",,";

    csv::CsvReader reader(stream);
    const auto rows = reader.Read();

    csv::Row expected_row = {
        "", "", "",
    };
    REQUIRE(rows.size() == 1);
    CompareRows(expected_row, rows.front());
}

TEST_CASE("two rows") {
    std::stringstream stream;
    stream << "value11,value12\n";
    stream << "value21,value22";

    csv::CsvReader reader(stream);
    const auto rows = reader.Read();

    std::vector<csv::Row> expected_rows = {
        {"value11", "value12"},
        {"value21", "value22"},
    };

    REQUIRE(rows.size() == expected_rows.size());
    for (size_t i = 0; i < rows.size(); i++) {
        CompareRows(expected_rows[i], rows[i]);
    }
}

TEST_CASE("missing lines") {
    std::stringstream stream;
    stream << "\n";
    stream << "value11,value12\n";
    stream << "\n";
    stream << "value21,value22";

    csv::CsvReader reader(stream);
    const auto rows = reader.Read();

    std::vector<csv::Row> expected_rows = {
        {"value11", "value12"},
        {"value21", "value22"},
    };

    REQUIRE(rows.size() == expected_rows.size());
    for (size_t i = 0; i < rows.size(); i++) {
        CompareRows(expected_rows[i], rows[i]);
    }
}

TEST_CASE("wrong delimiter") {
    std::stringstream stream;
    stream << "value1;value2";

    csv::CsvReader reader(stream);
    const auto rows = reader.Read();

    csv::Row expected_row = {
        "value1;value2",
    };
    REQUIRE(rows.size() == 1);
    CompareRows(expected_row, rows.front());
}

TEST_CASE("different column sizes") {
    std::stringstream stream;
    stream << "value11,value12\n";
    stream << "value21,value22,extra";

    csv::CsvReader reader(stream);
    REQUIRE_THROWS_MATCHES(reader.Read(), csv::CsvParsingError,
        Catch::Matchers::Message("invalid columns count on line 2"));
}