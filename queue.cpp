#include <iostream>
#include "include/ioc.h"
#include "include/icommand.h"
#include "include/object.h"
#include "include/producer.h"

int main(int ac, char **av)
{
    std::cout << std::endl;
    std::cout << "Testing thread methods..." << std::endl;
#ifdef test1
    test_thread1();
#endif
    return 0;
}
