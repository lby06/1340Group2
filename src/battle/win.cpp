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
*                                    _                                      *
*                            (_)    | |                                     *                   
*                      __   ___  ___| |_ ___  _ __ _   _                    *
*                      \ \ / / |/ __| __/ _ \| '__| | | |                   *
*                       \ V /| | (__| || (_) | |  | |_| |                   *
*                        \_/ |_|\___|\__\___/|_|   \__, |                   *
*                                                   __/ |                   *
*                                                  |___/                    *
*                                                                           *
*                                                                           *
*                               experience  +12                             *
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

void diesettlement()
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
*                               you lose                                    *
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


