#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <memory>
#include "icommand.h"

using namespace std;

template<class T>
class IocContainer
{
public:
    template<typename... Args>
    shared_ptr<T> resolve(string key_f, map<string, function<ICommand*()>> m_map, map<string, string> m_scope, Args&&... arg)
    {
        if (m_map.find(key_f) == m_map.end())
            throw runtime_error ("Unknown key_f");

        int size = sizeof...(arg);
        cout << "Argument number in resolved " << size << endl;

        auto func = m_map[key_f];
        return shared_ptr<T>(func());
    }
};
