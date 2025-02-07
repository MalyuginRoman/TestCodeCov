#include <iostream>
#include "icommand.h"
using namespace std;
class SafeQueue;

class MacroCommandP
{
public:
    SafeQueue<ICommand*> cmds;

    MacroCommandP(SafeQueue<ICommand*> cmds) :
        cmds(cmds)
    {
    }
};

MacroCommand::MacroCommand(SafeQueue<ICommand*> cmds) :
    imp(new MacroCommandP(cmds))
{
}

MacroCommand::~MacroCommand() { delete imp;}

void MacroCommand::execute()
{
    cout << "Start execute of MacroCommand" << endl;
    if(imp->cmds.empty())
        throw runtime_error ("Сommand queue is empty");
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
    map<string, function<ICommand*()>> *m_map;
    map<string, string> *m_scope;

    RegisterCommandP(map<string, function<ICommand*()>> *m_map, map<string, string> *m_scope) :
        m_map(m_map),
        m_scope(m_scope)
    {
    }
};

RegisterCommand::RegisterCommand(map<string, function<ICommand*()>> *m_map, map<string, string> *m_scope) :
    imp(new RegisterCommandP(m_map, m_scope))
{
}

RegisterCommand::~RegisterCommand() { delete imp;}

void RegisterCommand::execute()
{
}

void RegisterCommand::registerType(string key_s, string key_f, function<ICommand*()> func)
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
    {}
};
