#include "commands/OpenCommand.h"

void OpenCommand::execute() {
    if (database->is_open()) {
        interface->writeln_line("Database is already opened");
        return;
    }
    interface->write_line("Enter database name(will be created if doesn't exist): ");
    if (database->open_db(interface->read_line())) {
        interface->writeln_line("Opened database");
    } else {
        interface->writeln_line("Can not open database");
    }
}

OpenCommand::OpenCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface)
        : ICommand(database, interface, 'o', "Open DB") {}
