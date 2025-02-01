#include <iostream>

#include "CommandQueue.h"
#include "CommandMove.h"
#include "CommandRotate.h"
#include "CommandLoger.h"
#include "CommandRepeat.h"
#include "ExceptionHandler.h"

int main(int ac, char **av)
{
    CommandQueue cmd;
    CommandMove *cmd_move = new CommandMove;
    CommandRotate *cmd_rotate = new CommandRotate;
    //CommandLoger *cmd_loger = new CommandLoger;     !п.4,5
    //CommandRepeat *cmd_repeat = new CommandRepeat;  !п.6,7
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);

    cmd.add(cmd_move);
    cmd.add(cmd_rotate);

    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            handler->executeRepeat(handler, &cmd, cmd.front(), ex);
            //cmd_loger->execute();                   !п.4
            //cmd.add(cmd_loger);                     !п.5
            //cmd_repeat->execute(&cmd, cmd.front()); !п.6
            //cmd.add(cmd_repeat);                    !п.7
        }
        //cmd.del();                                  !п.4-7
    }
    std::cout << std::endl;
}
