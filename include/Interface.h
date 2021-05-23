#ifndef LAB2_INTERFACE_H
#define LAB2_INTERFACE_H

#include <iostream>
#include "Pony.h"

class Interface {
public:
    Interface(std::istream &istream, std::ostream &ostream);

    std::string read_line();

    unsigned long read_id();

    unsigned int read_age();

    double read_height();

    Pony::Type read_type();

    std::string read_name();

    void write_line(std::string &&line);

    void writeln_line(std::string &&line);

    void write_line(std::string &line);

    void writeln_line(std::string &line);

    void write_pony(const Pony &pony);

    Pony read_object();

private:
    std::istream &istream;
    std::ostream &ostream;

    static std::string trim_line(std::string &line);

    static std::string type_format(std::string &line);
};


#endif //LAB2_INTERFACE_H
