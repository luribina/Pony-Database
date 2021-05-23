
#include "commands/ListAllCommand.h"
#include <vector>

void ListAllCommand::execute() {
    if (!database->is_open()) {
        interface->writeln_line("Database is not opened");
        return;
    }
    database->reset_state();
    while (!database->is_end()) {
        auto ponies = database->list_all_objects();
        for (const auto &pony:ponies) {
            interface->write_pony(pony);
        }
    }
}

ListAllCommand::ListAllCommand(const std::shared_ptr<FileDatabase> &database,
                               const std::shared_ptr<Interface> &interface) : ICommand(database, interface, 'l', "List all ponies") {}
