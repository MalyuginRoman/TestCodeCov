#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <memory>

using namespace std;

template<class T>
class IocContainer
{
public:
    using FuncType = function<T*()>;

    template<class ClassType>
    void registerType(string key_s, string key_f, FuncType func)
    {
        m_scope.emplace(key_s, key_f);
        m_map.emplace(key_f, func);
        cout << "   Registre " << key_f << " in " << key_s << endl;
    }

    template<typename... Args>
    shared_ptr<T> resolved(string key_f, Args&&... arg)
    {
        if (m_map.find(key_f) == m_map.end())
            throw runtime_error ("Unknown key_f");

        //int size = sizeof...(arg);
        //cout << "Argument number in resolved " << size << endl;

        auto func = m_map[key_f];
        return shared_ptr<T>(func());
    }

private:
    void resolve(string key_f, FuncType type)
    {
        m_map.emplace(key_f, type);
        cout << key_f << " for "<< endl;
    }

private:
    map<string, FuncType> m_map;
    map<string, string> m_scope;
};
