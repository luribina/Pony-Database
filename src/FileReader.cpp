#include "FileReader.h"


bool FileReader::open_file() {
    if (opened) return true;
    valid = check_file();
    if (valid) {
        file.open(name);
        is_end = false;
        if (file.good()) {
            opened = true;
            return true;
        } else {
            file.close();
        }
    }
    opened = false;
    return false;
}

void FileReader::close_file() {
    if (opened) {
        reset();
//        file_.close();
        opened = false;
    }
}


std::string FileReader::read_line() {
    if (!opened) open_file();
    std::string line;
    if (!file.eof() && opened && valid) {
        std::getline(file, line);
    }
    is_end = file.eof();
    return line;
}

bool FileReader::check_file() {
    std::filesystem::path file_path(name);
    if (std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path)) {
        auto permissions = std::filesystem::status(file_path).permissions();
        auto read_write = std::filesystem::perms::owner_read | std::filesystem::perms::owner_write;
        return (permissions & read_write) == read_write;
    }
    return false;
}

void FileReader::reset() {
    file.clear();
    file.seekg(0);
    is_end = file.eof();
}

bool FileReader::is_eof() const {
    return is_end;
}

void FileReader::swap(FileReader &file_reader) {
    std::swap(name, file_reader.name);
    std::swap(file, file_reader.file);
    std::swap(valid, file_reader.valid);
    std::swap(opened, file_reader.opened);
    std::swap(is_end, file_reader.is_end);

}

FileReader &FileReader::operator=(FileReader &&file_reader) noexcept {
    if (this != &file_reader) {
        swap(file_reader);
    }
    return *this;
}

FileReader::FileReader(FileReader &&file_reader) noexcept {
    swap(file_reader);
}

bool FileReader::is_open() const {
    return opened;
}

std::string FileReader::get_name() {
    return name;
}
