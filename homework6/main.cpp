#include <iostream>
#include "include/ioc.h"
#include "include/icommand.h"
#include "include/object.h"
#include <thread>
using namespace std;

class MovingAdapter;

void thread1()
{
    objectVector gameItem;
    int count = 2;
    for(int i = 0; i < count; i++)
    {
        int id = i + 1;
        coord place;
        react state;

        place.placeX = 0.;
        place.placeY = 0.;
        place.angular = 45 * i;

        state.velocity = 100;
        state.angularVelocity = 20;
        state.fuel = 10;

        gameItem.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        cout << gameItem.at(i)->id() << ":" << gameItem.at(i)->state().velocity << "," << gameItem.at(i)->state().angularVelocity << "," << gameItem.at(i)->state().fuel
                       << "," << gameItem.at(i)->place().placeX << "," << gameItem.at(i)->place().placeY << "," << gameItem.at(i)->place().angular << endl;
    }

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand(gameItem.at(0));
    MoveCommand *cmd_move = new MoveCommand(gameItem.at(0));
    RotateCommand *cmd_rotate = new RotateCommand(gameItem.at(0));
    BurnCommand *cmd_burn = new BurnCommand(gameItem.at(0));
    list<ICommand*> cmd_list;
    cmd_list.push_back(cmd_check);
    cmd_list.push_back(cmd_move);
    cmd_list.push_back(cmd_burn);
    cmd_list.push_back(cmd_check);
    cmd_list.push_back(cmd_rotate);
    cmd_list.push_back(cmd_burn);

    IocContainer<ICommand> ioc;
    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;

    RegisterCommand *cmd_registr = new RegisterCommand(&m_map, &m_scope);

    cmd_registr->registerType(
                "Scope2",
                "Adapter",
                [&ioc, &gameItem, &m_map, &m_scope](){
                return new CreateAdaptor(ioc, m_map, m_scope, gameItem.at(0));
    });

    cmd_registr->registerType(
                "Scope2",
                "MacroCommand1",
                [&cmd_list]() { return new MacroCommand(cmd_list); });
    std::thread t1(
                [&ioc, &gameItem, m_map, m_scope](){
                    ioc.resolve("Adapter", m_map, m_scope, gameItem.at(0))->execute();
                    ioc.resolve("MacroCommand1", m_map, m_scope, gameItem.at(0))->execute();
    });
    t1.join();
}

void thread2()
{
    objectVector gameItem;
    int count = 2;
    for(int i = 0; i < count; i++)
    {
        int id = i + 1;
        coord place;
        react state;

        place.placeX = 0.;
        place.placeY = 0.;
        place.angular = 45 * i;

        state.velocity = 100;
        state.angularVelocity = 20;
        state.fuel = 10;

        gameItem.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        cout << gameItem.at(i)->id() << ":" << gameItem.at(i)->state().velocity << "," << gameItem.at(i)->state().angularVelocity << "," << gameItem.at(i)->state().fuel
                       << "," << gameItem.at(i)->place().placeX << "," << gameItem.at(i)->place().placeY << "," << gameItem.at(i)->place().angular << endl;
    }

    IocContainer<ICommand> ioc;

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand(gameItem.at(1));
    MoveCommand *cmd_move = new MoveCommand(gameItem.at(1));
    RotateCommand *cmd_rotate = new RotateCommand(gameItem.at(1));
    BurnCommand *cmd_burn = new BurnCommand(gameItem.at(1));
    list<ICommand*> cmd_list;

    //bool isOk = a12->getVelocity():

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
                [&ioc, &gameItem, m_map, m_scope](){
                    ioc.resolve("MacroCommand2", m_map, m_scope, gameItem.at(1))->execute();
    });
    t2.join();
}

int main(int ac, char **av)
{
    std::cout << std::endl;
    std::cout << "Testing thread methods..." << std::endl;
#ifdef test1
    thread1();
#endif
#ifdef test2
    thread2();
#endif

    return 0;
}
