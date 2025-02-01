#include <iostream>

#include "object.h"
#include "config.h"

int main(int ac, char **av)
{
    objectVector vector;
    int count = 1;
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

    std::cout << vector.at(0)->id() << "," << vector.at(0)->state().velocity << "," << vector.at(0)->state().angularVelocity << "," << vector.at(0)->state().fuel
                   << "," << vector.at(0)->place().placeX << "," << vector.at(0)->place().placeY << "," << vector.at(0)->place().angular << std::endl;

    CommandQueue cmd;
    CommandFuelCheck *cmd_check = new CommandFuelCheck(vector.at(0));
    CommandMove *cmd_move = new CommandMove(vector.at(0));
    CommandRotate *cmd_rotate = new CommandRotate(vector.at(0));
    CommandFuelBurn *cmd_burn = new CommandFuelBurn(vector.at(0));
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);

    cmd.add(cmd_check);
    cmd.add(cmd_move);
    cmd.add(cmd_burn);
    cmd.add(cmd_rotate);
    cmd.add(cmd_burn);

    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            handler->executeRepeat(handler, &cmd, cmd.front(), ex);
        }
        cmd.del();
    }
    std::cout << std::endl;
}
