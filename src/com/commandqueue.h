#pragma once
#include "icommand.h"
#include <queue>

class CommandQueue
{
public:
    CommandQueue();

    std::queue<ICommand*> cmd;
    void add(ICommand* cmd);
    void del();
    bool isEmpty();
    ICommand* front();
};
