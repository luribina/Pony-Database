
#include "commands/RemoveByIdCommand.h"

void RemoveByIdCommand::execute() {
    if (!database->is_open()) {
        interface->writeln_line("Database is not opened");
        return;
    }
    unsigned long id = interface->read_id();
    if (database->delete_by_id(id)) {
        interface->write_line("Pony was deleted :(");
    } else {
        interface->write_line("No pony to remove");
    }
}

RemoveByIdCommand::RemoveByIdCommand(const std::shared_ptr<FileDatabase> &database,
                                     const std::shared_ptr<Interface> &interface) : ICommand(database, interface, 'r', "Remove by ID") {}
