#include <iostream>
#include <thread>
#include <algorithm>
#include "producer.h"
#include "object.h"
#include "../spe/ioc.h"
#include "../com/icommand.h"
#include "safequeue.h"
#include "../spe/exceptionhandler.h"
#include "../spe/eventloop.h"
#include "../spe/imessage.h"
#include "../spe/istate.h"
#include "objposition.h"

void producer::test_thread1()
{
// формируем системы окрестностей
    std::map<int, system_okr> p_map_c_a;
    std::map<int, system_okr> p_map_c_b;
    p_map_c_a = func_name(1);
    p_map_c_b = func_name(2);
// формируем объекты
    std::cout << "Start test_thread1" << std::endl;
    objectVector vector;
    int count = 1;
    for(int i = 0; i < count; i++)
    {
        int id = i;
        coord place;
        react state;

        place.placeX = 1. + 20. * i;
        if(place.placeX > 100.)
            place.placeX = 100. - (place.placeX - 100.);
        place.placeY = 1. + 25. * i;
        if(place.placeY > 100.)
            place.placeY = 100. - (place.placeY - 100.);
        place.angular = 45 * (i + 1);

        state.velocity = 40;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector.at(i)->id() << ":" << vector.at(i)->state().velocity << "," << vector.at(i)->state().angularVelocity << "," << vector.at(i)->state().fuel
                       << "," << vector.at(i)->place().placeX << "," << vector.at(i)->place().placeY << "," << vector.at(i)->place().angular << std::endl;
    }

// помещаем объекты в системы окрестностей
    p_map_c_a = func_obj(p_map_c_a, &vector);
    p_map_c_b = func_obj(p_map_c_b, &vector);

    IocContainer<ICommand> ioc;
    SafeQueue<ICommand*> queueCmds;

    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand(&p_map_c_a, &p_map_c_b, vector.at(0));
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    EmptyCommand *cmd_empty = new EmptyCommand();
  
    queueCmds.push(cmd_check);
    queueCmds.push(cmd_move);
    queueCmds.push(cmd_burn);
    queueCmds.push(cmd_check);
    queueCmds.push(cmd_rotate);
    queueCmds.push(cmd_burn);

    StateStatus *sc = new StateStatus(new DefaultState(), cmd_empty);
    
    eventloop* producer = new eventloop(&queueCmds, sc);
    producer->start(&queueCmds, sc, 1);
}

void producer::start_game()
{
    objectVector vector;
    int count = 1;
    std::cout << "Start create " << count << " objects." << std::endl;

    for(int i = 0; i < count; i++)
    {
        int id = i;
        coord place;
        react state;

        place.placeX = 1. + 20. * i;
        if(place.placeX > 100.)
            place.placeX = 100. - (place.placeX - 100.);
        place.placeY = 1. + 25. * i;
        if(place.placeY > 100.)
            place.placeY = 100. - (place.placeY - 100.);
        place.angular = 45 * (i + 1);

        state.velocity = 40;
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

    //InternetCommand<ICommand*> cmd_net;

    //std::exception ex;
    //ExceptionHandler* handler = new ExceptionHandler(0, ex);

    //queueCmds.push(cmd_net.resolve(operationId_i));
    //eventloop* gamequeue = new eventloop(&queueCmds);

    //std::thread t1(
    //            [&ioc, &gamequeue, &queueCmds, &handler, &ex, &cmd_net](){
    //    try {
    //        gamequeue->start(&queueCmds);
    //    } catch( std::exception ex) {
    //        handler->executeRepeat(handler, &queueCmds, ex);
    //    }
    //});
    //t1.join();
}
