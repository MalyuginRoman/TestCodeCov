#include <iostream>

#include "include/CommandQueue.h"
#include "include/CommandMove.h"
#include "include/CommandRotate.h"
#include "include/CommandLoger.h"
#include "include/CommandRepeat.h"
#include "include/ExceptionHandler.h"

int main(int ac, char **av)
{
    CommandQueue cmd;
    CommandMove *cmd_move = new CommandMove;
    CommandRotate *cmd_rotate = new CommandRotate;
    CommandLoger *cmd_loger = new CommandLoger;     //!п.4,5
    CommandRepeat *cmd_repeat = new CommandRepeat;  //!п.6,7
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);

#ifdef test1
    cmd.add(cmd_move);
    cmd.add(cmd_rotate);
    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            cmd_loger->execute(cmd.front());
        }
        cmd.del();
    }
#endif
#ifdef test2
    cmd.add(cmd_move);
    cmd.add(cmd_rotate);
    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            handler->executeLogerAfter(&cmd, ex);
        }
        cmd.del();
    }
#endif
#ifdef test3
    cmd.add(cmd_move);
    cmd.add(cmd_rotate);
    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            cmd_repeat->execute();
        }
        cmd.del();
    }
#endif
#ifdef test4
    cmd.add(cmd_move);
    cmd.add(cmd_rotate);
    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            handler->executeRepeatOnce(&cmd, ex);
        }
        cmd.del();
    }
#endif
#ifdef test5
    cmd.add(cmd_move);
    cmd.add(cmd_rotate);
    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            handler->executeRepeat(handler, &cmd, cmd.front(), ex);
        }
    }
#endif
    return 0;
}
