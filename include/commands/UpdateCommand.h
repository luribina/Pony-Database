#ifndef LAB2_UPDATECOMMAND_H
#define LAB2_UPDATECOMMAND_H

#include "ICommand.h"

class UpdateCommand : public ICommand {
public:
    UpdateCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface);

    void execute() override;
};


#endif //LAB2_UPDATECOMMAND_H
