#include <iostream>
#include <memory>
#include "Interface.h"
#include "FileDatabase.h"
#include "Invoker.h"

#include "commands/OpenCommand.h"
#include "commands/CloseCommand.h"
#include "commands/CreateCommand.h"
#include "commands/FindByIdCommand.h"
#include "commands/FindByTypeCommand.h"
#include "commands/ListAllCommand.h"
#include "commands/RemoveByIdCommand.h"
#include "commands/UpdateCommand.h"


void fill_commands(Invoker &invoker, std::shared_ptr<FileDatabase> &database, std::shared_ptr<Interface> &interface);

int main() {
    auto database = std::make_shared<FileDatabase>();
    auto interface = std::make_shared<Interface>(std::cin, std::cout);
    Invoker invoker(interface);
    fill_commands(invoker, database, interface);
    invoker.print_menu();
    interface->write_line("\n>");
    std::string line;
    while ((line = interface->read_line()) != "q") {
        if (line == "m") invoker.print_menu();
        else if (!line.empty()) invoker.execute_command(line);
        interface->write_line("\n>");
    }
    return 0;
}

void fill_commands(Invoker &invoker, std::shared_ptr<FileDatabase> &database, std::shared_ptr<Interface> &interface) {
    invoker.add_command(std::make_unique<OpenCommand>(database, interface));
    invoker.add_command(std::make_unique<CloseCommand>(database, interface));
    invoker.add_command(std::make_unique<ListAllCommand>(database, interface));
    invoker.add_command(std::make_unique<FindByIdCommand>(database, interface));
    invoker.add_command(std::make_unique<FindByTypeCommand>(database, interface));
    invoker.add_command(std::make_unique<RemoveByIdCommand>(database, interface));
    invoker.add_command(std::make_unique<CreateCommand>(database, interface));
    invoker.add_command(std::make_unique<UpdateCommand>(database, interface));
    invoker.add_description('m', "Print menu");
    invoker.add_description('q',"Quit (All unsaved changes will be lost!!!)");
}
