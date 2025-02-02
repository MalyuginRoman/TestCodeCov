#pragma once
#include <iostream>
#include <thread>
#include "icommand.h"
#include "safequeue.h"

class eventloop
{
public:
    eventloop(SafeQueue<ICommand *> *cmds);
    ~eventloop();

    SafeQueue<ICommand *> *cmds;

    void start(SafeQueue<ICommand *> *cmds, int variant);
private:
    class eventloopP* imp;
};
