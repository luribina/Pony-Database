#ifndef LAB2_PONY_H
#define LAB2_PONY_H

#include <string>
#include <map>
#include <iostream>
#include <utility>

class Pony {
    friend class FileDatabase;

public:
    enum class Type {
        EARTHPONY,
        UNICORN,
        PEGAS,
        ALICORN
    };

    Pony() = default;

    Pony(unsigned long id, unsigned int age, double height, std::string name, Type type) : id(id), age(age),
                                                                                           height(height),
                                                                                           name(std::move(name)),
                                                                                           type(type) {};

    ~Pony() = default;

    unsigned long get_id() const;

    void set_id(unsigned long id);

    friend std::ostream &operator<<(std::ostream &os, const Pony &pony);

    const static std::map<Type, std::string> &get_type_map();

    const static std::map<std::string, Type> &get_string_map();


private:
    unsigned long id;
    unsigned int age;
    double height;
    std::string name;
    Pony::Type type;
    const static std::map<Pony::Type, std::string> pony_to_string;
    const static std::map<std::string, Pony::Type> string_to_pony;
};


#endif //LAB2_PONY_H
