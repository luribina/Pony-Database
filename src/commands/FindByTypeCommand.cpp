
#include "commands/FindByTypeCommand.h"

void FindByTypeCommand::execute() {
    if (!database->is_open()) {
        interface->writeln_line("Database is not opened");
        return;
    }
    Pony::Type type = interface->read_type();
    database->reset_state();
    while (!database->is_end()) {
        auto ponies = database->find_by_type(type);
        for (const auto &pony:ponies) {
            interface->write_pony(pony);
        }
    }
}

FindByTypeCommand::FindByTypeCommand(const std::shared_ptr<FileDatabase> &database,
                                     const std::shared_ptr<Interface> &interface) : ICommand(database, interface, 't', "Find by type") {}
