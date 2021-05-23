
#include "commands/UpdateCommand.h"

void UpdateCommand::execute() {
    if (!database->is_open()) {
        interface->writeln_line("Database is not opened");
        return;
    }
    unsigned long id = interface->read_id();
    if (database->id_exists(id)) {
        auto pony = interface->read_object();
        pony.set_id(id);
        database->update_by_id(std::move(pony));
        interface->writeln_line("Updated pony");
    } else {
        interface->writeln_line("No pony to update");
    }
}

UpdateCommand::UpdateCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface)
        : ICommand(database, interface, 'u', "Update by ID") {}
