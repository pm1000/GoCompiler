#include <iostream>
#include "../header/IOController.h"


int main() {
    IOController* controller = new IOController("../inputFiles/", "../outputFiles/created/");
    controller->start();
    delete controller;
    return 0;
}
