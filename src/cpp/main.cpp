#include <iostream>
#include "../header/IOController.h"


int main() {
    IOController* controller = new IOController("../inputFiles/", "outputFiles");
    controller->start();
    delete controller;
    return 0;
}
