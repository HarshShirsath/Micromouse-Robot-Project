#include <iostream>
#include <cstring>
#include <string>

#include "simulator/simulator.h"
#include "algorithm/algorithm.h"
/**
 * @brief This is the main function.
 *  It takes argument whether to follow right wall or left wall.
 *
 * @param argc argument count
 * @param argv argument vector
 * @return int returned integer
 */
int main(int argc, char **argv)
{
    // If argument count is not 2 throw error that argument is missing
    if (argc != 2)
    {
        std::cerr << "--- Missing argument ---" << std::endl;
        std::cerr << "--- Please specify whether you want to test left hand rule method or right hand rule method ---" << std::endl;
        std::cerr << "--- For left-hand method: left ---" << std::endl;
        std::cerr << "--- For right-hand method: right ---" << std::endl;
        return 1;
    }

    // If argument passed is not left or right throw error incorrect argument
    if (strcmp(argv[1], "left") && strcmp(argv[1], "right"))
    {
        std::cerr << "--- Incorrect argument ---" << std::endl;
        std::cerr << "--- For left-hand method provide:left ---" << std::endl;
        std::cerr << "--- For right-hand method provide:right ---" << std::endl;
        return 2;
    }

    // Create object of class Algorithm on heap and call the
    // respective function as per the given argument
    auto algo = std::make_unique<rwa2group22::Algorithm>();
    if (!strcmp(argv[1], "left"))
        algo->run_left();
    else
        algo->run_right();
}
