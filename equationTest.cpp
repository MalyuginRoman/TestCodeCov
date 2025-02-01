#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include "config.h"

class TestSolution : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(TestSolution);
  CPPUNIT_TEST(testEquationSolution);
  CPPUNIT_TEST(correctA);
  CPPUNIT_TEST(noRoot);
  CPPUNIT_TEST(oneRoot);
  CPPUNIT_TEST(twoRoot);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void testEquationSolution(void)
{
  root x = solve(1, 2, 1);
  double result = 1.;
  CPPUNIT_ASSERT((x.x1 - result) < e);
}
  void correctA()
{
  double a = 0.;
  double b = 0.;
  double c = 0.;
  CPPUNIT_ASSERT_MESSAGE(std::string("Уравнение не является квадратным"), abs(a) < e);
  root x = solve(a, b, c);
}
  void noRoot()
{
  double d = discr(1, 0, 1);
  CPPUNIT_ASSERT_MESSAGE(std::string("Вещественных корней нет"), d < 0);
}
  void oneRoot()
{
  double d = discr(1, 2, 1);
  CPPUNIT_ASSERT_MESSAGE(std::string("Один вещественный корень"), abs(d) < e);
}
  void twoRoot()
{
  double d = discr(1, 0, -1);
  CPPUNIT_ASSERT_MESSAGE(std::string("Два вещественных корня"), abs(d) > e);
}
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestSolution);

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
