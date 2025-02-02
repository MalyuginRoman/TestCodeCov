#include <thread>
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

void eventloop::start(SafeQueue<ICommand *> *cmds)
{
    bool stop = false;
    int ic = 0;
    SafeQueue<ICommand*> cmds_1;
    EmptyCommand *cmd_empty = new EmptyCommand();
    HardStopCommand *cmd_hard = new HardStopCommand();
    SoftStopCommand *cmd_soft = new SoftStopCommand();
    
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);
    
    std::thread t1(
                [&cmds, &stop, &ic, &cmd_empty, &cmd_hard, &cmd_soft, &ex, &handler, &cmds_1](){
        try {
              while(!stop)
              {
                  ic += 1;
                  ICommand* cmd = cmds->front();
                  std::cout << "Start execute ";
                  cmd->execute();
                  std::cout << std::endl;
                  cmds->pop();
                  if(cmd == cmd_hard)
                  {
                      stop = true;
                      std::cout << "in queue after HardStop : " << std::endl;
                      while(!cmds->empty())
                      {
                          ICommand* cmdh = cmds->front();
                          cmdh->execute();
                          cmds->pop();
                          if(cmds->size() > 0)
                              std::cout << ", ";
                      }
                      std::cout << std::endl;
                  }
                  if(cmd == cmd_soft)
                  {
                      stop = true;
                      std::cout << "in queue after SoftStop : " << std::endl;
                      while(!cmds->empty())
                      {
                          ICommand* cmdss = cmds->front();
                          cmds_1.push(cmdss);
                          cmds->pop();
                      }
                      while(!cmds_1.empty())
                      {
                          ICommand* cmds = cmds_1.front();
                          cmds->execute();
                          cmds_1.pop();
                          if(cmds_1.size() > 0)
                              std::cout << ", ";
                      }
                      std::cout << std::endl;
                  }
                  if(cmds->empty())
                      stop = true;
              }
        } catch( std::exception ex) {
            handler->executeRepeat(handler, cmds, ex);
        }
    });
    t1.join();
}

void eventloop::execute(ICommand *cmd)
{
    std::cout << "Start execute ";
    cmd->execute();
    std::cout << std::endl;
}

void eventloop::addCommand(ICommand *cmd)
{
    this->imp->cmds->push(cmd);
}
