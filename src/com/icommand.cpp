#include <iostream>
#include "icommand.h"
using namespace std;

class MacroCommandP
{
public:
    vector<ICommand*> cmds;

    MacroCommandP(vector<ICommand*> cmds) :
        cmds(cmds)
    {
    }
};

MacroCommand::MacroCommand(vector<ICommand*> cmds) :
    imp(new MacroCommandP(cmds))
{
}

MacroCommand::~MacroCommand() { delete imp;}

void MacroCommand::execute()
{
    cout << "Start execute of MacroCommand" << endl;
    if(imp->cmds.empty())
        throw runtime_error ("Сommand list is empty");
    for(ICommand* i : imp->cmds)
    {
        try
        {
            i->execute();
        } catch (...) {
            throw runtime_error ("Pass the error up");
        }
    }
}

class RegisterCommandP
{
public:
    std::map<std::string, std::function<ICommand*()>> *m_map;
    std::map<std::string, std::string> *m_scope;

    RegisterCommandP(std::map<std::string, std::function<ICommand*()>> *m_map,
                     std::map<std::string, std::string> *m_scope) :
        m_map(m_map),
        m_scope(m_scope)
    {
    }
};

RegisterCommand::RegisterCommand(std::map<std::string, std::function<ICommand*()>> *m_map,
                                 std::map<std::string, std::string> *m_scope) :
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
    cout << "Registre " << key_f << " in " << key_s << endl;
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
    {
    }
};
