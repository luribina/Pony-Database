#include "Interface.h"

#include <algorithm>
#include <limits>

Interface::Interface(std::istream &istream, std::ostream &ostream) : istream(istream), ostream(ostream) {
    ostream.setf(std::ios::fixed, std::ios::floatfield);
}

std::string Interface::read_line() {
    std::string line;
    std::getline(istream, line);
    return trim_line(line);
}

void Interface::write_line(std::string &&line) {
    ostream << line;
}

void Interface::writeln_line(std::string &&line) {
    ostream << line << "\n";
}

void Interface::write_line(std::string &line) {
    ostream << line;
}

void Interface::writeln_line(std::string &line) {
    ostream << line << "\n";
}

void Interface::write_pony(const Pony &pony) {
    ostream << pony;
}

unsigned long Interface::read_id() {
    write_line("Enter id: ");
    std::string line = read_line();
    char *end;
    errno = 0;
    unsigned long id = std::strtoul(line.c_str(), &end, 10);
    while (errno != 0 || *end != '\0' || end == line.c_str()) {
        errno = 0;
        writeln_line("Not a valid id");
        write_line("Enter id: ");
        line = read_line();
        id = std::strtoul(line.c_str(), &end, 10);
    }
    return id;
}

unsigned int Interface::read_age() {
    write_line("Enter age: ");
    std::string line = read_line();
    char *end;
    errno = 0;
    unsigned long ul_age = std::strtoul(line.c_str(), &end, 10);
    while (errno != 0 || *end != '\0' || end == line.c_str() || ul_age > std::numeric_limits<unsigned int>::max()) {
        errno = 0;
        writeln_line("Not a valid age");
        write_line("Enter age: ");
        line = read_line();
        ul_age = std::strtoul(line.c_str(), &end, 10);
    }
    return ul_age;
}

double Interface::read_height() {
    write_line("Enter height: ");
    std::string line = read_line();
    char *end;
    errno = 0;
    double height = std::strtod(line.c_str(), &end);
    while (line.length() > 17 || errno != 0 || end == line.c_str() || *end != '\0' || height <= 0) {
        errno = 0;
        writeln_line("Not a valid height");
        write_line("Enter height: ");
        line = read_line();
        height = std::strtod(line.c_str(), &end);
    }
    return height;
}

std::string Interface::read_name() {
    write_line("Enter pony name: ");
    std::string name = read_line();
    while (name.empty()) {
        writeln_line("Invalid name");
        write_line("Enter pony name: ");
        name = read_line();
    }
    return name;
}

Pony::Type Interface::read_type() {
    writeln_line("Enter pony type");
    write_line("Possible values are: ");
    for (const auto &i:Pony::get_string_map()) {
        write_line(i.first + " ");
    }

    writeln_line("");
    write_line("Type: ");
    std::string line = read_line();
    while (!Pony::get_string_map().count(type_format(line))) {
        write_line("Invalid type, enter again:");
        line = read_line();
    }
    return Pony::get_string_map().at(line);
}

Pony Interface::read_object() {
    unsigned long id = 0;
    std::string name = read_name();
    unsigned int age = read_age();
    double height = read_height();
    Pony::Type type = read_type();
    return Pony(id, age, height, name, type);
}

std::string Interface::trim_line(std::string &line) {
    std::string trimmed = line;
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), trimmed.end());
    return trimmed;
}

std::string Interface::type_format(std::string &line) {
    std::string formatted = line;
    std::transform(formatted.begin(), formatted.end(), formatted.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    formatted[0] = std::toupper(formatted[0]);
    return formatted;
}


