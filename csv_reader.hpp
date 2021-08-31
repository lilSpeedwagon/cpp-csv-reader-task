#pragma once

#include <iostream>
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

    explicit CsvReader(std::istream& stream);
    ~CsvReader();

    std::vector<Row> Read();

private:
    static bool IsDelimiter(const char c);

    Row ReadRow();
    bool IsStreamOk() const;

    std::istream& stream_;
};

} // namespace::csv