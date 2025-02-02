#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>
#include <map>
#include <functional>
#include <memory>

using namespace std;
namespace fs = filesystem;

class ICommand;

class Adapter
{
public:
    Adapter();
    void erase(list<string>& list1, list<string>& list2, list<string>& list11, list<string>& list12, list<string>& list13, list<string>& list14)
    {
        list1.erase(list1.begin());
        list2.erase(list2.begin());
        list11.erase(list11.begin());
        list12.erase(list12.begin());
        list13.erase(list13.begin());
        list14.erase(list14.begin());
    };
    void erase2(list<string>& list3, list<string>& list4, list<string>& list41, list<string>& list42, list<string>& list43, list<string>& list44)
    {
        list3.erase(list3.begin());
        list4.erase(list4.begin());
        list41.erase(list41.begin());
        list42.erase(list42.begin());
        list43.erase(list43.begin());
        list44.erase(list44.begin());
    };
    void generate()
    {
        fs::path current_path = fs::current_path();
        fs::path file_path(current_path);
        list<string> list1, list2, list11, list12, list13, list14,
                     list3, list4, list41, list42, list43, list44;

        // Рекурсивный обход директории
        cout << file_path.parent_path() << endl;
        for (auto &p : fs::recursive_directory_iterator(file_path.parent_path()))
        {
            if(p.path().extension() == ".h")
            {
                string current_file = p.path().filename().generic_string();
                string readFileName = p.path().parent_path().generic_string() + "/" +
                                      p.path().filename().generic_string();
                fstream readFile(readFileName);
                if (!readFile.is_open())
                {
                    cout << "File " << readFileName << " not be opened" << endl;
                }
                else
                {
                    if(current_file == "imoving.h")
                    {
                        string str;
                        while(readFile >> str)
                        {
                            if(str == "virtual")
                            {
                                readFile >> str;
                                list1.push_back(str);
                                readFile >> str;
                                list2.push_back(str);
                                readFile >> str;
                                readFile >> str;
                                list11.push_back(str);
                                readFile >> str;
                                list12.push_back(str);
                                readFile >> str;
                                list13.push_back(str);
                                readFile >> str;
                                list14.push_back(str);
                            }
                        }
                        string fileWriteName =
                                p.path().parent_path().generic_string() + "/" +
                                p.path().filename().replace_extension(".cpp").generic_string();
                        cout << fileWriteName << endl;
                        ofstream f;
                        f.open(fileWriteName, ios::out);
                        {
                            f << "#include \"object.h\"" << endl;
                            f << "#include \"imoving.h\"" << endl;
                            f << " " << endl;
                            f << "MovingAdapter::MovingAdapter(IocContainer<ICommand> ioc," << endl;
                            f << "                                 std::map<std::string, std::function<ICommand*()>> m_map," << endl;
                            f << "                                 std::map<std::string, std::string> m_scope," << endl;
                            f << "                                 object *obj) :" << endl;
                            f << "        ioc(ioc), m_map(m_map), m_scope(m_scope), obj(obj) {}" << endl;
                            size_t count = list1.size();
                            for(int i = 0; i < count; i++)
                            {
                                f << list1.front()  << " MovingAdapter::" << list2.front() << "("
                                  << list11.front() << " " << list12.front();
                                if(i % 2 == 0)
                                    f << " " << list13.front()  << " " << list14.front();
                                f << ")" << endl;
                                f << "{" << endl;
                                    if(list2.front() == "getPosition")
                                    {
                                        f << "  //ioc.resolve(\"Spaceship.Operations.IMovable:position.get\", m_map, m_scope, obj);" << endl;
                                        f << "  return 0;" << endl;
                                    }
                                    else if(list2.front() == "getVelocity")
                                    {
                                        f << "  //ioc.resolve(\"Spaceship.Operations.IMovable:velocity.get\", m_map, m_scope, obj);" << endl;
                                        f << "  return 0;" << endl;
                                    }
                                    else if(list2.front() == "setPosition")
                                    {
                                        f << "  //ioc.resolve(\"Spaceship.Operations.IMovable:position.set\", m_map, m_scope, obj," << endl;
                                        f << "  //newValue).Execute();" << endl;
                                        f << "  return 0;" << endl;
                                    }
                                    else if(list2.front() == "setVelocity")
                                    {
                                        f << "  return 0;" << endl;
                                    }
                                f << "}" << endl;
                                erase(list1, list2, list11, list12, list13, list14);
                            }
                        }
                        f.close();
                        cout << p.path().parent_path().generic_string() << endl;
                        cout << fileWriteName << endl;
                        //fs::remove(fileWriteName);
                    }
                    else if(current_file == "irotateble.h")
                    {
                        string str;
                        while(readFile >> str)
                        {
                            if(str == "virtual")
                            {
                                readFile >> str;
                                list3.push_back(str);
                                readFile >> str;
                                list4.push_back(str);
                                readFile >> str;
                                readFile >> str;
                                list41.push_back(str);
                                readFile >> str;
                                list42.push_back(str);
                                readFile >> str;
                                list43.push_back(str);
                                readFile >> str;
                                list44.push_back(str);
                            }
                        }
                        string fileWriteName =
                                p.path().parent_path().generic_string() + "/" +
                                p.path().filename().replace_extension(".cpp").generic_string();
                        cout << fileWriteName << endl;
                        ofstream f;
                        f.open(fileWriteName, ios::out);
                        {
                            f << "#include \"object.h\"" << endl;
                            f << "#include \"irotateble.h\"" << endl;
                            f << " " << endl;
                            f << "RotatingAdapter::RotatingAdapter(IocContainer<ICommand> ioc," << endl;
                            f << "                                 std::map<std::string, std::function<ICommand*()>> m_map," << endl;
                            f << "                                 std::map<std::string, std::string> m_scope," << endl;
                            f << "                                 object *obj) :" << endl;
                            f << "        ioc(ioc), m_map(m_map), m_scope(m_scope), obj(obj) {}" << endl;
                            size_t count = list3.size();
                            for(int i = 0; i < count; i++)
                            {
                                f << list3.front()  << " RotatingAdapter::" << list4.front() << "("
                                  << list41.front() << " " << list42.front();
                                if(i % 2 == 0)
                                    f << " " << list43.front()  << " " << list44.front();
                                f << ")" << endl;
                                f << "{" << endl;
                                    if(list4.front() == "getAngular")
                                    {
                                        f << "  //ioc.resolve(\"Spaceship.Operations.IRotateble:angular.get\", m_map, m_scope, obj);" << endl;
                                        f << "  return 0;" << endl;
                                    }
                                    else if(list4.front() == "getAngularVelocity")
                                    {
                                        f << "  //ioc.resolve(\"Spaceship.Operations.IRotateble:angular_velocity.get\", m_map, m_scope, obj);" << endl;
                                        f << "  return 0;" << endl;
                                    }
                                    else if(list4.front() == "setAngularVelocity")
                                    {
                                        f << "  //ioc.resolve(\"Spaceship.Operations.IRotateble:angular_velocity.set\", m_map, m_scope, obj," << endl;
                                        f << "  //newValue).Execute();" << endl;
                                        f << "  return 0;" << endl;
                                    }
                                    else if(list4.front() == "setAngular")
                                    {
                                        f << "  //ioc.resolve(\"Spaceship.Operations.IRotateble:angular.set\", m_map, m_scope, obj," << endl;
                                        f << "  //newValue).Execute();" << endl;
                                        f << "  return 0;" << endl;
                                    }
                                f << "}" << endl;
                                erase2(list3, list4, list41, list42, list43, list44);
                            }
                        }
                        f.close();
                        cout << fileWriteName << endl;
                        //fs::remove(fileWriteName);
                    }
                    else
                    {
                        cout << current_file << " - file not using" << endl;
                    }
                }
                readFile.close();
            }
        }
    };

    template<class T, typename... Argss>
    shared_ptr<T> resolved(string key_f, map<string, function<ICommand*()>> m_map,
                          map<string, string> m_scope, int newValue, Argss&&... arg)
    {
        if (m_map.find(key_f) == m_map.end())
            throw runtime_error ("Unknown key_f");

        int size = sizeof...(arg);
        cout << "Argument number in resolved " << size << endl;

        auto func = m_map[key_f];
        return shared_ptr<T>(func());
    }
};
