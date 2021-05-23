#include "Pony.h"

const std::map<Pony::Type, std::string> Pony::pony_to_string = {
        {Type::EARTHPONY, "Earthpony"},
        {Type::UNICORN,   "Unicorn"},
        {Type::PEGAS,     "Pegasus"},
        {Type::ALICORN,   "Alicorn"}
};

const std::map<std::string, Pony::Type> Pony::string_to_pony = {
        {"Earthpony", Type::EARTHPONY},
        {"Unicorn",   Type::UNICORN},
        {"Pegasus",   Type::PEGAS},
        {"Alicorn",   Type::ALICORN}
};

std::ostream &operator<<(std::ostream &os, const Pony &pony) {
    os << "id:" << pony.id << " ";
    os << "name:" << pony.name << " ";
    os << "type:" << Pony::pony_to_string.at(pony.type) << " ";
    os << "age:" << pony.age << " ";
    os << "height:" << pony.height << std::endl;
    return os;
}

const std::map<Pony::Type, std::string> &Pony::get_type_map() {
    return pony_to_string;
}

const std::map<std::string, Pony::Type> &Pony::get_string_map() {
    return string_to_pony;
}

unsigned long Pony::get_id() const {
    return id;
}

void Pony::set_id(unsigned long id) {
    this->id = id;
}
