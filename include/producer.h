#pragma once
#include <iostream>
#include <thread>
#include "ioc.h"
#include "icommand.h"
#include "object.h"

void test_thread1()
{
    std::cout << "Start test_thread1" << std::endl;
    objectVector vector;
    int count = 2;
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

        vector.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector.at(i)->id() << ":" << vector.at(i)->state().velocity << "," << vector.at(i)->state().angularVelocity << "," << vector.at(i)->state().fuel
                       << "," << vector.at(i)->place().placeX << "," << vector.at(i)->place().placeY << "," << vector.at(i)->place().angular << std::endl;
    }

    IocContainer<ICommand> ioc;

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand();
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    list<ICommand*> cmd_list;
    cmd_list.push_back(cmd_check);
    cmd_list.push_back(cmd_move);
    cmd_list.push_back(cmd_burn);

    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;

    RegisterCommand *cmd_registr = new RegisterCommand(&m_map, &m_scope);
    cmd_registr->registerType(
                "Scope2",
                "MacroCommand1",
                [&cmd_list]() { return new MacroCommand(cmd_list); });
    std::thread t1(
                [&ioc, &vector, m_map, m_scope](){
                    ioc.resolve("MacroCommand1", m_map, m_scope, vector.at(0))->execute();
    });
    t1.join();
}

void test_thread2()
{
    std::cout << "Start test_thread2" << std::endl;
    objectVector vector;
    int count = 2;
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

        vector.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector.at(i)->id() << ":" << vector.at(i)->state().velocity << "," << vector.at(i)->state().angularVelocity << "," << vector.at(i)->state().fuel
                       << "," << vector.at(i)->place().placeX << "," << vector.at(i)->place().placeY << "," << vector.at(i)->place().angular << std::endl;
    }

    IocContainer<ICommand> ioc;

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand();
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    list<ICommand*> cmd_list;


    cmd_list.push_back(cmd_check);
    cmd_list.push_back(cmd_rotate);
    cmd_list.push_back(cmd_burn);

    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;

    RegisterCommand *cmd_registr = new RegisterCommand(&m_map, &m_scope);
    cmd_registr->registerType(
                "Scope2",
                "MacroCommand2",
                [&cmd_list]() { return new MacroCommand(cmd_list); });

    std::thread t2(
                [&ioc, &vector, m_map, m_scope](){
                    ioc.resolve("MacroCommand2", m_map, m_scope, vector.at(0))->execute();
    });
    t2.join();
}
