#pragma once
#include <iostream>
#include "icommand.h"
#include "safequeue.h"

class eventloop
{
public:
    eventloop(SafeQueue<ICommand *> *cmds);
    ~eventloop();

    SafeQueue<ICommand *> *cmds;

    void start(SafeQueue<ICommand *> *cmds);
    void execute(ICommand *cmd);
    void addCommand(ICommand *cmd);
private:
    class eventloopP* imp;
};
