#include "endpage.h"
#include "startpage.h"
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

void end(){
    bool quit;
    cout << "       Are you sure ?  Enter 1 (Yes) / 0 (No):    " << endl;
    if(!quit) return;
    print_file("../../data/scripts/ascii_images/end.txt", 3, true);
    exit(1);
}