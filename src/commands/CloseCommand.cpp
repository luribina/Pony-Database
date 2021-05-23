#include "commands/CloseCommand.h"

void CloseCommand::execute() {
    if (!database->is_open()) {
        interface->writeln_line("No database to close");
    } else {
        database->close_db();
        interface->writeln_line("Closed database");
    }
}

CloseCommand::CloseCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &anInterface) : ICommand(database, anInterface,
                                                                                        'c', "Close DB (Will save all changes)") {}
