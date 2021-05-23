
#ifndef LAB2_FILEREADER_H
#define LAB2_FILEREADER_H

#include <string>
#include <filesystem>
#include <fstream>

class FileReader {
public:

    FileReader() : valid(false), opened(false), is_end(false) {};

    explicit FileReader(std::string &&name) : name(name), valid(check_file()), opened(false), is_end(false) {};

    FileReader(const FileReader &) = delete;

    FileReader &operator=(const FileReader &) = delete;

    FileReader(FileReader &&file_reader) noexcept;

    FileReader &operator=(FileReader &&file_reader) noexcept;

    ~FileReader() = default;

    bool open_file();

    void close_file();

    bool is_open() const;

    std::string read_line();

    bool check_file();

    void reset();

    bool is_eof() const;

    std::string get_name();

private:
    std::string name;
    std::ifstream file;
    bool valid;
    bool opened;
    bool is_end;

    void swap(FileReader &file_reader);
};

#endif //LAB2_FILEREADER_H
