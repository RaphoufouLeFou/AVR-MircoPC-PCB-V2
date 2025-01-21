#include "include/OS.h"

int LaunchProgram(int argc, char **argv, int (*program)(int, char **))
{
    int res = program(argc, argv);
    while (1); // Avoid restarting
    return res;
}