#include <iostream>
#include <thread>
#include <algorithm>
#include "producer.h"
#include "object.h"
#include "ioc.h"
#include "icommand.h"
#include "safequeue.h"
#include "exceptionhandler.h"
#include "eventloop.h"
#include "imessage.h"

void producer::start_game()
{
    int count = 2;
    std::cout << "Start create " << count << " objects." << std::endl;

    for(int i = 0; i < count; i++)
    {
        int id = i;
        coord place;
        react state;

        place.placeX = 0.;
        place.placeY = 0.;
        place.angular = 45 * i;

        state.velocity = 100;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector_obj.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector_obj.at(i)->id() << ":" << vector_obj.at(i)->state().velocity << "," << vector_obj.at(i)->state().angularVelocity << "," << vector_obj.at(i)->state().fuel
                       << "," << vector_obj.at(i)->place().placeX << "," << vector_obj.at(i)->place().placeY << "," << vector_obj.at(i)->place().angular << std::endl;
    }
}

void producer::read_message(vector<char> message)
{
    string am(message.begin(), message.end());
    size_t lm = message.size();
    int cur_num = 0;
    char* endptr;
    gameId_i = 0, objectId_i = 0, operationId_i = 0;
    for(int i = 0; i < lm; i++)
    {
        if(cur_num == 0 && message.at(i) != ' ')
        {
            gameId_s += message.at(i);
            if(gameId_i == 0)
                gameId_i = strtol(&message.at(i), &endptr, 10);
        }
        if(cur_num == 1 && message.at(i) != ' ')
        {
            objectId_s += message.at(i);
            if(objectId_i == 0)
                objectId_i = strtol(&message.at(i), &endptr, 10);
        }
        if(cur_num == 2 && message.at(i) != ' ')
        {
            operationId_s += message.at(i);
            if(operationId_i == 0)
                operationId_i = strtol(&message.at(i), &endptr, 10);
        }
        if(cur_num == 3 && message.at(i) != ' ')
            args += message.at(i);
        if(message.at(i) == ' ')
            cur_num += 1;
    }
}


void producer::test_game(vector <char> message)
{
    std::cout << "Start test internet command" << std::endl;

    read_message(message);

    IocContainer<ICommand> ioc;
    SafeQueue<ICommand*> queueCmds;

    // Scope2 with fuel
    // формируем макрокоманды

    InternetCommand<ICommand*> cmd_net;

    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);

    queueCmds.push(cmd_net.resolve(operationId_i));
    eventloop* gamequeue = new eventloop(&queueCmds);

    std::thread t1(
                [&ioc, &gamequeue, &queueCmds, &handler, &ex, &cmd_net](){
        try {
            gamequeue->start(&queueCmds);
        } catch( std::exception ex) {
            handler->executeRepeat(handler, &queueCmds, ex);
        }
    });
    t1.join();
}
