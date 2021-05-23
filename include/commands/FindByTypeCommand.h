#ifndef LAB2_FINDBYTYPECOMMAND_H
#define LAB2_FINDBYTYPECOMMAND_H

#include "ICommand.h"

class FindByTypeCommand : public ICommand {
public:
    FindByTypeCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &interface);

    void execute() override;
};


#endif //LAB2_FINDBYTYPECOMMAND_H
