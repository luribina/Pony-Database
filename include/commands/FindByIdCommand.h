
#ifndef LAB2_FINDBYIDCOMMAND_H
#define LAB2_FINDBYIDCOMMAND_H

#include "ICommand.h"

class FindByIdCommand : public ICommand {
public:
    FindByIdCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface);

    void execute() override;
};


#endif //LAB2_FINDBYIDCOMMAND_H
