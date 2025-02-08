#include <iostream>
#include "icommand.h"

class MacroCommandP
{
public:
    std::vecror<ICommand*> cmds;

    MacroCommandP(std::vecror<ICommand*> cmds) :
        cmds(cmds)
    {
    }
};

MacroCommand::MacroCommand(std::vecror<ICommand*> cmds) :
    imp(new MacroCommandP(cmds))
{
}

MacroCommand::~MacroCommand() { delete imp;}

void MacroCommand::execute()
{
    std::cout << "Start execute of MacroCommand" << std::endl;
    if(imp->cmds.empty())
        throw std::runtime_error ("Сommand queue is empty");
    for(ICommand* i : imp->cmds)
    {
        try
        {
            i->execute();
        } catch (...) {
            throw std::runtime_error ("Pass the error up");
        }
    }
}
class RegisterCommandP
{
public:
    std::map<std::string, std::function<ICommand*()>> *m_map;
    std::map<std::string, std::string> *m_scope;

    RegisterCommandP(std::map<std::string, std::function<ICommand*()>> *m_map, std::map<std::string, std::string> *m_scope) :
        m_map(m_map),
        m_scope(m_scope)
    {
    }
};

RegisterCommand::RegisterCommand(std::map<std::string, std::function<ICommand*()>> *m_map, std::map<std::string, std::string> *m_scope) :
    imp(new RegisterCommandP(m_map, m_scope))
{
}

RegisterCommand::~RegisterCommand() { delete imp;}

void RegisterCommand::execute()
{
}

void RegisterCommand::registerType(std::string key_s, std::string key_f, std::function<ICommand*()> func)
{
    imp->m_scope->emplace(key_s, key_f);
    imp->m_map->emplace(key_f, func);
    std::cout << "Registre " << key_f << " in " << key_s << std::endl;
}

class CheckPositionCommandP
{
public:
    std::map<int, std::list<objectVector>> *p_map_o_a;
    std::map<int, std::pair<double, double>> *p_map_c_a;
    std::map<int, std::list<objectVector>> *p_map_o_b;
    std::map<int, std::pair<double, double>> *p_map_c_b;

    CheckPositionCommandP(std::map<int, std::list<objectVector>> *p_map_o_a,
                          std::map<int, std::pair<double, double>> *p_map_c_a,
                          std::map<int, std::list<objectVector>> *p_map_o_b,
                          std::map<int, std::pair<double, double>> *p_map_c_b) :
            p_map_o_a(p_map_o_a),
            p_map_c_a(p_map_c_a),
            p_map_o_b(p_map_o_b),
            p_map_c_b(p_map_c_b)
    {}
};
