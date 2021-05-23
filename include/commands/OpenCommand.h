
#ifndef LAB2_OPENCOMMAND_H
#define LAB2_OPENCOMMAND_H

#include "ICommand.h"

class OpenCommand : public ICommand {
public:
    OpenCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface);

    void execute() override;
};

#endif //LAB2_OPENCOMMAND_H
