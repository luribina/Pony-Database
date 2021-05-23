
#include "Invoker.h"

void Invoker::execute_command(const std::string &line) {
    unsigned char ch = line[0];

    if (line.size() != 1 || !commands.count(ch)) {
        interface->writeln_line("Invalid command");
        return;
    }

    commands.at(ch).get()->execute();
}

void Invoker::print_menu() {
    interface->writeln_line("\n---Menu---");
    for (auto &description:descriptions) {
        interface->writeln_line(description);
    }
}

void Invoker::add_command(std::unique_ptr<ICommand> command) {
    add_description(command->get_command_name(), command->get_description());
    commands.emplace(command->get_command_name(), std::move(command));
}

void Invoker::add_description(char ch, const std::string& description) {
    descriptions.emplace_back(description+ " ["+ch+"]");
}


//Invoker::Invoker(std::shared_ptr<Interface> interface) {
//
//}
