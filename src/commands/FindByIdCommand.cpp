
#include "commands/FindByIdCommand.h"

void FindByIdCommand::execute() {
    if (!database->is_open()) {
        interface->writeln_line("Database is not opened");
        return;
    }
    unsigned long id = interface->read_id();
    auto pony = database->read_by_id(id);
    if (pony.get_id() != 0) {
        interface->write_pony(pony);
    } else {
        interface->writeln_line("No pony with this id");
    }
}

FindByIdCommand::FindByIdCommand(const std::shared_ptr<FileDatabase> &database,
                                 const std::shared_ptr<Interface> &interface) : ICommand(database, interface, 'i', "Find by ID") {}
