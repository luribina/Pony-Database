
#ifndef LAB2_CREATECOMMAND_H
#define LAB2_CREATECOMMAND_H

#include "ICommand.h"

class CreateCommand : public ICommand {
public:
    CreateCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface);

    void execute() override;
};


#endif //LAB2_CREATECOMMAND_H
