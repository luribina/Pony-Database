#ifndef LAB2_INVOKER_H
#define LAB2_INVOKER_H

#include <map>
#include <utility>
#include <vector>
#include <memory>

#include "commands/ICommand.h"
#include "Interface.h"


class Invoker {
public:
    explicit Invoker(std::shared_ptr<Interface> interface) : interface(std::move(interface)) {}

    ~Invoker() = default;

    void add_command(std::unique_ptr<ICommand> command);

    void add_description(char ch, const std::string& description);

    void execute_command(const std::string &line);

    void print_menu();

private:
    std::map<unsigned char, std::unique_ptr<ICommand>> commands{};
    std::vector<std::string> descriptions{};
    std::shared_ptr<Interface> interface;
};


#endif //LAB2_INVOKER_H
