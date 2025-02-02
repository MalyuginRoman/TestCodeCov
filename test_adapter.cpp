#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "ioc.h"
#include "icommand.h"
#include "object.h"
#include <thread>

class test_adapter : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(test_adapter);
  CPPUNIT_TEST(test1);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void test1(void)
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
        std::cout << gameItem.at(i)->id() << ":" << gameItem.at(i)->state().velocity << "," << gameItem.at(i)->state().angularVelocity << "," << gameItem.at(i)->state().fuel
                       << "," << gameItem.at(i)->place().placeX << "," << gameItem.at(i)->place().placeY << "," << gameItem.at(i)->place().angular << std::endl;
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
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_adapter);/**/

int main()
{
CPPUNIT_NS::TestResult controller;

CPPUNIT_NS::TestResultCollector result;
controller.addListener(&result);

CPPUNIT_NS::BriefTestProgressListener progress;
controller.addListener(&progress);

CPPUNIT_NS::TestRunner runner;
runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
runner.run(controller);

return result.wasSuccessful() ? 0 : 1;
/*  return 0;*/
}
