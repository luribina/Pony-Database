
#include "commands/CreateCommand.h"

void CreateCommand::execute() {
    if (!database->is_open()) {
        interface->writeln_line("Database is not opened");
        return;
    }
    database->create_object(interface->read_object());
    interface->writeln_line("Added new pony :з");
}

CreateCommand::CreateCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface)
        : ICommand(database, interface, 'n', "Create new object") {}
