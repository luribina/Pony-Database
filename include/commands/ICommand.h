
#ifndef LAB2_ICOMMAND_H
#define LAB2_ICOMMAND_H

#include <utility>

#include "FileDatabase.h"
#include "Interface.h"

class ICommand {
public:

    ICommand(std::shared_ptr<FileDatabase> database, std::shared_ptr<Interface> anInterface,
             char commandName, std::string description) : database(std::move(database)), interface(std::move(anInterface)),
                                                                 command_name(commandName), description(std::move(description)) {}
    virtual void execute() = 0;

    virtual ~ICommand() = default;

    char get_command_name() const {
        return command_name;
    }

    const std::string &get_description() const {
        return description;
    }

protected:
    std::shared_ptr<FileDatabase> database;
    std::shared_ptr<Interface> interface;
    char command_name;
    std::string description;
};

#endif //LAB2_ICOMMAND_H
