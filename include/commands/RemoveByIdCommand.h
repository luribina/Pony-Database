
#ifndef LAB2_REMOVEBYIDCOMMAND_H
#define LAB2_REMOVEBYIDCOMMAND_H

#include "ICommand.h"

class RemoveByIdCommand : public ICommand {
public:
    RemoveByIdCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface);

    void execute() override;
};


#endif //LAB2_REMOVEBYIDCOMMAND_H
