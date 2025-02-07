#include <iostream>
#include "src/spe/ioc.h"
#include "src/com/icommand.h"
#include "src/sec/object.h"
#include "src/sec/producer.h"
#include "src/sec/safequeue.h"

int main(int ac, char **av)
{
    #ifdef test1
    std::cout << std::endl;
    std::cout << "Testing thread methods..." << std::endl;
    producer a1;
    a1.test_thread1();
    a2.test_thread2();
    #endif
    return 0;
}
