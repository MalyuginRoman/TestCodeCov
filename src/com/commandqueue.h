#pragma once
#include "icommand.h"
#include <queue>

template<class T>
class CommandQueue
{
public:
    CommandQueue();

    std::queue<T*> cmd;
    void add(T* cmd);
    void del();
    bool isEmpty();
    ICommand* front();
};
