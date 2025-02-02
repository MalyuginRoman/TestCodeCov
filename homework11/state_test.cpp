#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "include/producer.h"

class state_test : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(state_test);
  CPPUNIT_TEST(test1);
  CPPUNIT_TEST(test2);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void test1(void)
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
    SafeQueue<ICommand*> queueCmds;
    SafeQueue<ICommand*> queueCmds_1;

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand();
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    EmptyCommand *cmd_empty = new EmptyCommand();
  
    queueCmds.push(cmd_check);
    queueCmds.push(cmd_move);
    queueCmds.push(cmd_burn);
    queueCmds.push(cmd_check);
    queueCmds.push(cmd_rotate);
    queueCmds.push(cmd_burn);

    StateStatus *sc = new StateStatus(new DefaultState(), cmd_empty);
    
    eventloop* producer = new eventloop(&queueCmds, sc);
    producer->start(&queueCmds, sc, 1);
    delete sc;
}

  void test2(void)
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
    SafeQueue<ICommand*> queueCmds;
    SafeQueue<ICommand*> queueCmds_1;

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand();
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    EmptyCommand *cmd_empty = new EmptyCommand();
  
    queueCmds.push(cmd_check);
    queueCmds.push(cmd_move);
    queueCmds.push(cmd_burn);
    queueCmds.push(cmd_check);
    queueCmds.push(cmd_rotate);
    queueCmds.push(cmd_burn);

    StateStatus *sc = new StateStatus(new DefaultState(), cmd_empty);
    
    eventloop* producer = new eventloop(&queueCmds, sc);
    producer->start(&queueCmds, sc, 2);
    delete sc;
}
};

CPPUNIT_TEST_SUITE_REGISTRATION(state_test);

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
}
