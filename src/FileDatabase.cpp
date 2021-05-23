
#include "FileDatabase.h"
#include <filesystem>
#include <fstream>

bool FileDatabase::open_db(std::string &&name) {
    std::string full_name = name + ".csv";

    if (!std::filesystem::exists(full_name)) {
        std::ofstream tmp(full_name);
        tmp << "id,age,height,name,type\n";
        next_id++;
    }

    csvParser = CSVParser(std::move(full_name), 5);
    if (!(csvParser.file_reader().open_file() && check_file())) {
        return false;
    }
    return true;
}

void FileDatabase::close_db() {
    save_changes();
    next_id = 0;
    all_state = false;
    request_end = false;
    deleted_items.clear();
    updated_items.clear();
    created_items.clear();
    csvParser.file_reader().close_file();
}

bool FileDatabase::is_open() {
    return csvParser.file_reader().is_open();
}

bool FileDatabase::id_exists(unsigned long seek_id) {
    reset_state();
    unsigned long id;
    while (csvParser.read_col_value(id, 1)) {
        if (id == seek_id) return true;
    }
    for (const auto &pony: created_items) {
        if (pony.id == seek_id) return true;
    }
    return false;
}

Pony FileDatabase::read_by_id(unsigned long seek_id) {
    reset_state();
    unsigned long id;
    unsigned int age;
    double height;
    std::string name;
    std::string str_type;
    while (csvParser.read_row(id, age, height, name, str_type)) {
        if (id == seek_id) {
            if (updated_items.count(id)) return updated_items.at(id);
            return Pony(id, age, height, name, Pony::get_string_map().at(str_type));
        }
    }

    for (const auto &pony: created_items) {
        if (pony.id == seek_id) return pony;
    }

    return Pony();
}

bool FileDatabase::delete_by_id(unsigned long delete_id) {
    reset_state();
    if (deleted_items.count(delete_id)) return false;
    unsigned long id;
    while (csvParser.read_col_value(id, 1)) {
        if (id == delete_id) {
            if (updated_items.count(id)) updated_items.erase(id);
            else deleted_items.emplace(id);
            return true;
        }
    }
    for (auto pony = created_items.begin(); pony != created_items.end(); ++pony) {
        if (pony->id == delete_id) {
            created_items.erase(pony);
            return true;
        }
    }
    return false;
}

void FileDatabase::update_by_id(Pony &&pony) {
    updated_items.emplace(pony.id, pony);
}

void FileDatabase::create_object(Pony &&pony) {
    pony.id = next_id++;
    created_items.emplace_back(pony);
}

std::vector<Pony> FileDatabase::find_by_type(Pony::Type seek_type) {
    auto ponies = read_next();
    std::vector<Pony> filtered;
    for (const auto &pony:ponies) {
        if (pony.type == seek_type) filtered.emplace_back(pony);
    }
    return filtered;
}

std::vector<Pony> FileDatabase::list_all_objects() {
    return read_next();
}

bool FileDatabase::is_end() const {
    return request_end;
}

void FileDatabase::reset_state() {
    csvParser.file_reader().reset();
    csvParser.file_reader().read_line();
    all_state = false;
    request_end = false;
}

void FileDatabase::save_changes() {
    if (deleted_items.empty() && updated_items.empty() && created_items.empty()) return;
    reset_state();
    std::ofstream tmp_file("tmp");
    tmp_file.setf(std::ios::fixed, std::ios::floatfield);
    csvParser.file_reader().read_line();
    tmp_file << "id,age,height,name,type\n";
    save_to_file(tmp_file);
    csvParser.file_reader().close_file();
    std::remove(csvParser.file_reader().get_name().c_str());
    std::rename("tmp", csvParser.file_reader().get_name().c_str());
}

bool FileDatabase::check_file() {
    if (!csvParser.check_header("id", "age", "height", "name", "type")) return false;
    unsigned long id = 0;
    unsigned int age;
    double height;
    std::string name;
    std::string str_type;
    while (csvParser.read_row(id, age, height, name, str_type)) {}
    bool eof = csvParser.file_reader().is_eof();
    if (!eof) csvParser.file_reader().close_file();
    next_id = id+1;
    return eof;
}

std::vector<Pony> FileDatabase::read_next() {
    if (all_state) {
        all_state = false;
        request_end = true;
        return created_items;
    }
    std::vector<Pony> ponies{};
    int i = 0;
    unsigned long id;
    unsigned int age;
    double height;
    std::string name;
    std::string str_type;
    while (csvParser.read_row(id, age, height, name, str_type) && i < 100) {
        i++;
        if (!Pony::get_string_map().count(str_type)) {
            return std::vector<Pony>{};
        }
        if (deleted_items.count(id)) continue;
        if (updated_items.count(id)) {
            ponies.emplace_back(updated_items.at(id));
        } else {
            ponies.emplace_back(Pony(id, age, height, name, Pony::get_string_map().at(str_type)));
        }
    }
    if (csvParser.file_reader().is_eof()) {
        all_state = true;
        if (created_items.empty()) request_end = true;
    }
    return ponies;
}

void FileDatabase::save_to_file(std::ofstream &file) {
    unsigned long id;
    std::string line = csvParser.file_reader().read_line();
    while (csvParser.read_col_value_from_str(id, line, 1)) {
        if (deleted_items.count(id)) {
            line = csvParser.file_reader().read_line();
            continue;
        }
        if (updated_items.count(id)) {
            Pony &pony = updated_items.at(id);
            file << pony.id << "," << pony.age << "," << pony.height << "," << pony.name << ","
                 << Pony::get_type_map().at(pony.type) << std::endl;
        } else {
            file << line << std::endl;
        }
        line = csvParser.file_reader().read_line();
    }
    for (const auto &pony:created_items) {
        file << pony.id << "," << pony.age << "," << pony.height << "," << pony.name << ","
             << Pony::get_type_map().at(pony.type) << std::endl;
    }
}
