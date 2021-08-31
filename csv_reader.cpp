#include "csv_reader.hpp"


namespace csv {

CsvParsingError::CsvParsingError(const std::string& msg) 
    : std::runtime_error(msg) {}

CsvReader::CsvReader(std::fstream& stream) : stream_{stream} {}

CsvReader::~CsvReader() {}

std::vector<Row> CsvReader::Read() {
    if (!IsStreamOk()) {
        return {};
    }

    std::vector<Row> result;
    const auto first_row = ReadRow();
    const auto columns_count = first_row.size();
    size_t column_index = 1;
    
    while (IsStreamOk()) {
        const auto row = ReadRow();
        if (row.size() != columns_count) {
            throw CsvParsingError(
                "invalid columns count on line " + std::to_string(column_index));
        }
        result.push_back(std::move(row));
        column_index++;
    }

    return result;
}

Row CsvReader::ReadRow() {
    std::string line;
    std::getline(stream_, line);

    std::vector<std::string> result;
    auto begin_it = line.cbegin();
    auto end_it = line.cbegin();
    while (end_it != line.cend()) {
        if (IsDelimiter(*end_it)) {
            result.emplace_back(begin_it, end_it);
            begin_it = ++end_it;
        } else {
            ++end_it;
        }
    }
    return result;
}

bool CsvReader::IsStreamOk() const {
    return !stream_.fail() && !stream_.eof();
}

bool CsvReader::IsDelimiter(const char c) {
    return c == kDelimiter;
}

} // namespace csv