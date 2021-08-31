#pragma once

#include <fstream>
#include <vector>
#include <string>


namespace csv {

class CsvParsingError : public std::runtime_error {
public:
    explicit CsvParsingError(const std::string& msg);
};

typedef std::vector<std::string> Row;

class CsvReader {
public:
    static constexpr char kDelimiter = ',';

    explicit CsvReader(std::fstream& stream);
    ~CsvReader();

    std::vector<Row> Read();

private:
    static bool IsDelimiter(const char c);

    Row ReadRow();
    bool IsStreamOk() const;

    std::fstream& stream_;
};

} // namespace::csv