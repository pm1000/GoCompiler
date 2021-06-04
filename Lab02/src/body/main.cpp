// See https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Top-Level.html
#include <iostream>
#include "../header/IOController.h"

using namespace std;


int main (int argc, char *argv[])
{
    IOController* controller = new IOController("../inputFiles/", "../outputFiles/created/");
    controller->start();
    delete controller;
    return 0;
}

