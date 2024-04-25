#include <iostream>
#include <thread>
#include <chrono>
#include "win.h"
#include "string"

using namespace std;

void victorysettlement()
{
    system("printf \"\\033c\"");
    string content = R"(*****************************************************************************
*                                                                           *                  
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                               victory                                     *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*****************************************************************************)";
    std::cout<< content << std::endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("printf \"\\033c\"");
    return;
}


