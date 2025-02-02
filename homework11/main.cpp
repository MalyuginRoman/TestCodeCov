#include <iostream>
#include "include/ioc.h"
#include "include/icommand.h"
#include "include/object.h"
#include "include/producer.h"
#include "include/safequeue.h"

int main(int ac, char **av)
{
    std::cout << std::endl;
    std::cout << "Testing thread methods..." << std::endl;
    #ifdef test1
    test_thread1();
    //test_thread2();
    #endif
    return 0;
}
