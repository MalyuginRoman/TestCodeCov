#pragma once
#include "object.h"

class producer
{
public:
    void start_game();
    void test_game(std::vector <char> message);
    void read_message(std::vector <char> message);

    objectVector vector_obj;
    std::string gameId_s, objectId_s, operationId_s, args;
    int gameId_i, objectId_i, operationId_i;
};
