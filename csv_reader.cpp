#include "csv_reader.hpp"


namespace csv {

CsvParsingError::CsvParsingError(const std::string& msg) 
    : std::runtime_error(msg) {}

CsvReader::CsvReader(std::istream& stream) : stream_{stream} {}

CsvReader::~CsvReader() {}

std::vector<Row> CsvReader::Read() {
    if (!IsStreamOk()) {
        return {};
    }

    std::vector<Row> result;    
    bool is_columns_count_defined = false;
    size_t columns_count = 0;
    size_t row_index = 0;

    while (IsStreamOk()) {
        row_index++;
        auto row = ReadRow();
        if (row.empty()) {
            continue;
        }
        
        if (!is_columns_count_defined) {
            columns_count = row.size();
            is_columns_count_defined = true;
        } else if (row.size() != columns_count) {
            throw CsvParsingError(
                "invalid columns count on line " + std::to_string(row_index));
        }
        result.push_back(std::move(row));
    }

    return result;
}

Row CsvReader::ReadRow() {
    std::string line;
    std::getline(stream_, line);

    if (line.empty()) {
        return {};
    }

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
    result.emplace_back(begin_it, end_it);
    return result;
}

bool CsvReader::IsStreamOk() const {
    return !stream_.fail() && !stream_.eof();
}

bool CsvReader::IsDelimiter(const char c) {
    return c == kDelimiter;
}

} // namespace csv