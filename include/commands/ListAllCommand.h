#ifndef LAB2_LISTALLCOMMAND_H
#define LAB2_LISTALLCOMMAND_H

#include "ICommand.h"

class ListAllCommand : public ICommand {
public:
    ListAllCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface);

    void execute() override;
};


#endif //LAB2_LISTALLCOMMAND_H
