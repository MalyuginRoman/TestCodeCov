#include <iostream>
#include "ioc.h"
#include "icommand.h"
#include "object.h"
#include "producer.h"

int main(int ac, char **av)
{
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

    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;

    RegisterCommand *cmd_registr = new RegisterCommand(&m_map, &m_scope);

    // Scope1 not fuel
    cmd_registr->registerType(
                "Scope1",
                "MoveCommand",
                []() { return new MoveCommand(); });
    cmd_registr->registerType(
                "Scope1",
                "RotateCommand",
                []() { return new RotateCommand(); });;

    ioc.resolve("MoveCommand", m_map, m_scope, vector.at(0))->execute();
    ioc.resolve("RotateCommand", m_map, m_scope, vector.at(0), vector.at(1))->execute();

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
    
    cmd_registr->registerType(
                "Scope2",
                "MacroCommand1",
                [&cmd_list]() { return new MacroCommand(cmd_list); });
    ioc.resolve("MacroCommand1", m_map, m_scope, vector.at(0))->execute();
    cmd_list.clear();


    cmd_list.push_back(cmd_check);
    cmd_list.push_back(cmd_rotate);
    cmd_list.push_back(cmd_burn);
    cmd_registr->registerType(
                "Scope2",
                "MacroCommand2",
                [&cmd_list]() { return new MacroCommand(cmd_list); });

    ioc.resolve("MacroCommand2", m_map, m_scope, vector.at(0), vector.at(1))->execute();

    return 0;
}
