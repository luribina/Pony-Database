
#ifndef LAB2_CLOSECOMMAND_H
#define LAB2_CLOSECOMMAND_H

#include "ICommand.h"

class CloseCommand : public ICommand {
public:

    CloseCommand(const std::shared_ptr<FileDatabase> &database, const std::shared_ptr<Interface> &anInterface);

    void execute() override;
};


#endif //LAB2_CLOSECOMMAND_H
