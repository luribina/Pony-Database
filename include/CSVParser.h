
#ifndef LAB2_CSVPARSER_H
#define LAB2_CSVPARSER_H

#include <vector>
#include <algorithm>
#include "FileReader.h"


class CSVParser {

public:

    explicit CSVParser(std::string &&name, std::size_t count) : file_reader_(std::move(name)), count_(count),
                                                                header_valid(false) {}

    CSVParser() = default;

    ~CSVParser() = default;

    CSVParser(const CSVParser &) = delete;

    CSVParser &operator=(const CSVParser &) = delete;

    CSVParser(CSVParser &&csv_parser) noexcept {
        swap(csv_parser);
    }

    CSVParser &operator=(CSVParser &&csv_parser) noexcept {
        if (this != &csv_parser) {
            swap(csv_parser);
        }
        return *this;
    }


    template<typename ... Columns>
    bool check_header(Columns &&... cols) {
        if (sizeof ...(Columns) != count_) return false;
        std::vector<std::string> col_names;
        fill_columns(col_names, std::forward<Columns>(cols)...);
        return read_header(col_names);
    }

    template<typename ...Args>
    bool read_row(Args &... args) {
        if (sizeof ...(Args) != count_) return false;
        std::string line = file_reader_.read_line();
        if (line.empty()) return false;
        return parse_row(line, 0, 1, args...);
    }

    template<typename Arg>
    bool read_col_value(Arg &arg, std::size_t col) {
        if (col < 1 || col > count_) return false;
        std::string line = file_reader_.read_line();
        if (line.empty()) return false;
        return parse_value(arg, line, col);
    }

    template<typename Arg>
    bool read_col_value_from_str(Arg &arg, std::string &line, std::size_t col) {
        if (col < 1 || col > count_) return false;
        return parse_value(arg, line, col);
    }

    FileReader &file_reader() {
        return file_reader_;
    }

private:
    FileReader file_reader_;
    std::size_t count_;
    bool header_valid;

    void swap(CSVParser &csv_parser) {
        std::swap(file_reader_, csv_parser.file_reader_);
        std::swap(count_, csv_parser.count_);
        std::swap(header_valid, csv_parser.header_valid);
    }

    template<typename ...Columns>
    void fill_columns(std::vector<std::string> &col_names, std::string &&column, Columns &&... cols) {
        col_names.emplace_back(column);
        fill_columns(col_names, std::forward<Columns>(cols)...);
    }

    void fill_columns(std::vector<std::string> &col_names) {}

    bool read_header(std::vector<std::string> &col_names) {
        std::string line = file_reader_.read_line();
        if (header_valid) return true;
        if (!line.empty()) {
            trim_line(line);
            std::size_t pos = 0;
            std::size_t next_pos;
            if (line.empty()) return false;
            for (std::size_t i = 0; i < count_; i++) {
                next_pos = line.find(',', pos);
                std::string value = line.substr(pos, next_pos - pos);
                trim_line(value);
                if (value != col_names[i]) {
                    header_valid = false;
                    return false;
                }
                pos = next_pos + 1;
            }
            header_valid = true;
            return true;
        }
        header_valid = false;
        return false;
    }

    void trim_line(std::string &line) {
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());
    }

    template<typename T, typename ...Args>
    bool parse_row(std::string &line, std::size_t pos, std::size_t col, T &value, Args &...args) {
        while (pos < line.size() && std::isspace(line[pos])) pos++;
        if (pos >= line.size()) return false;

        char del = ',';
        std::size_t next_pos;
        std::size_t tmp_pos;
        if (col == count_) next_pos = line.size();
        else next_pos = line.find(del, pos);
        tmp_pos = next_pos;

        if (line[pos] == '"') {
            pos++;
            next_pos = line.find('"', pos);
            tmp_pos = line.find(del, next_pos);
        } else {
            while (std::isspace(line[next_pos - 1])) next_pos--;
        }

        std::string string_value = line.substr(pos, next_pos - pos);
        next_pos = tmp_pos;
        if (!parse(string_value, value)) return false;
        else return parse_row(line, next_pos + 1, col + 1, args...);
    }

    bool parse_row(std::string &line, std::size_t pos, std::size_t col) {
        return true;
    }

    template<typename Arg>
    bool parse_value(Arg &arg, std::string &line, std::size_t col) {
        std::size_t pos = 0;
        std::size_t next_pos = -1;
        for (std::size_t i = 0; i < col; i++) {
            pos = ++next_pos;
            while (pos < line.size() && std::isspace(line[pos])) pos++;
            if (line[pos] == '"') {
                pos++;
                next_pos = line.find('"', pos);
            }
            if (i!=count_){
                next_pos = line.find(',', next_pos);
            } else {
                next_pos = line.size()-1;
            }
        }
        while (std::isspace(line[next_pos - 1])) next_pos--;
        if (line[next_pos - 1] == '"') next_pos--;
        std::string string_value = line.substr(pos, next_pos - pos);
        return parse(string_value, arg);
    }

    bool parse(std::string &string_value, std::string &value) {
        value = string_value;
        return true;
    }

    bool parse(std::string &string_value, int &value) {
        char *end;
        errno = 0;
        long tmp = std::strtol(string_value.c_str(), &end, 10);
        if (errno != 0 || *end != '\0' || end == string_value.c_str() || tmp > std::numeric_limits<int>::max() ||
            tmp < std::numeric_limits<int>::min())
            return false;
        value = tmp;
        return true;
    }

    bool parse(std::string &string_value, unsigned int &value) {
        char *end;
        errno = 0;
        value = std::strtoul(string_value.c_str(), &end, 10);
        return !(errno != 0 || *end != '\0' || end == string_value.c_str() ||
                 value > std::numeric_limits<unsigned int>::max());
    }

    bool parse(std::string &string_value, long &value) {
        char *end;
        errno = 0;
        value = std::strtol(string_value.c_str(), &end, 10);
        return !(errno != 0 || *end != '\0' || end == string_value.c_str());
    }

    bool parse(std::string &string_value, unsigned long &value) {
        char *end;
        errno = 0;
        value = std::strtoul(string_value.c_str(), &end, 10);
        return !(errno != 0 || *end != '\0' || end == string_value.c_str());
    }

    bool parse(std::string &string_value, double &value) {
        char *end;
        errno = 0;
        value = std::strtod(string_value.c_str(), &end);
        return !(errno != 0 || end == string_value.c_str() || *end != '\0');
    }


    template<typename T>
    bool parse(std::string &string_value, T &t) {
        return false;
    }

};

#endif //LAB2_CSVPARSER_H
