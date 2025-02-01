#include "CommandQueue.h"

CommandQueue::CommandQueue()
{}

void CommandQueue::add(ICommand *c)
{
    cmd.push(c);
}

void CommandQueue::del()
{
    cmd.pop();
}

bool CommandQueue::isEmpty()
{
    return cmd.empty();
}

ICommand* CommandQueue::front()
{
    return cmd.front();
}
