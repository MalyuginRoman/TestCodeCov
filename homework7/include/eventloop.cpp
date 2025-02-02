#include "eventloop.h"
#include "exceptionhandler.h"

class eventloopP
{
public:
    SafeQueue<ICommand *> *cmds;
    eventloopP(SafeQueue<ICommand *> *cmds) :
        cmds(cmds)
    {
    }
};

eventloop::eventloop(SafeQueue<ICommand *> *cmds) :
    imp(new eventloopP(cmds))
{
}


eventloop::~eventloop() { delete imp; }

void eventloop::start(SafeQueue<ICommand *> *cmds, int variant)
{
    bool stop = false;
    int ic = 0;
    
    EmptyCommand *cmd_empty = new EmptyCommand();
    HardStopCommand *cmd_hard = new HardStopCommand();
    SoftStopCommand *cmd_soft = new SoftStopCommand();
    
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);
    
    std::thread t1(
                [&cmds, &stop, &ic, &variant, &cmd_empty, &cmd_hard, &cmd_soft, &ex, &handler](){
        try {
            while(!stop)
            {
                ic += 1;
                ICommand* cmd = cmds->front();
                cmd->execute();
                cmds->pop();
                if(cmd == cmd_hard)
                {
                    stop = true;
                }
                if(cmd == cmd_soft)
                {
                    stop = true;
                    while(!cmds->empty())
                    {
                        ICommand* cmd = cmds->front();
                        cmd->execute();
                        cmds->pop();
                    }
                }
                if(cmds->empty())
                    stop = true;
                if(ic == 2) cmds->push(cmd_empty);
                if(variant == 1 && ic == 3) cmds->push(cmd_soft);
                if(variant == 2) cmds->push(cmd_hard);
            }
        } catch( std::exception ex) {
            handler->executeRepeat(handler, cmds, ex);
        }
    });
    t1.join();
}
