#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "src/sec/object.h"
#include "src/spe/ioc.h"
#include "src/com/icommand.h"
#include "src/sec/safequeue.h"
#include "src/spe/exceptionhandler.h"
#include "src/spe/eventloop.h"
#include "src/spe/imessage.h"
#include "src/spe/istate.h"
#include "src/sec/objposition.h"
#include "src/sec/producer.h"

class state_test : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(state_test);
  CPPUNIT_TEST(test1);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void test1(void)
{
// формируем системы окрестностей
    std::map<int, system_okr> p_map_c_a;
    std::map<int, system_okr> p_map_c_b;
    p_map_c_a = func_name(1);
    p_map_c_b = func_name(2);
// формируем объекты
    int count = 1;
    objectVector vector_obj;
    std::cout << std::endl;
    std::cout << "Start create " << count << " objects." << std::endl;

    for(int i = 0; i < count; i++)
    {
        int id = (i + 100);
        coord place;
        react state;

        place.placeX = 1. + 20. * i;
        if(place.placeX > 100.)
            place.placeX = 100. - (place.placeX - 100.);
        place.placeY = 1. + 25. * i;
        if(place.placeY > 100.)
            place.placeY = 100. - (place.placeY - 100.);
        place.angular = 45 * (i + 1);

        state.velocity = 40;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector_obj.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector_obj.at(i)->id() << ":" << vector_obj.at(i)->state().velocity << "," << vector_obj.at(i)->state().angularVelocity << "," << vector_obj.at(i)->state().fuel
                       << "," << vector_obj.at(i)->place().placeX << "," << vector_obj.at(i)->place().placeY << "," << vector_obj.at(i)->place().angular << std::endl;
    }
// помещаем объекты в системы окрестностей
    p_map_c_a = func_obj(p_map_c_a, &vector_obj);
    p_map_c_b = func_obj(p_map_c_b, &vector_obj);

    IocContainer<ICommand> ioc;
    SafeQueue<ICommand*> queueCmds;

    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand(&p_map_c_a, &p_map_c_b, vector_obj.at(0));
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
