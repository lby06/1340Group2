#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include "start_endpage.h"
using namespace std;

void clear_screen(){
#ifdef _WIN32
    system("CLS"); // 奇形怪状的bug
#elif __unix__
    system("clear"); // 正常
#endif
}

int print_file(const string filename, int wait_time, bool clean){
    ifstream file;
    string line;
    file.open(filename.c_str());
    if(file.fail()){
        cout << "error: file not found" << endl;
        exit(1);
    }
    if(clean) clear_screen();
    while(getline(file, line)){
        cout << line << endl;
    }
    file.close();
    this_thread::sleep_for(chrono::seconds(wait_time)); // windows 上无法运行, linux 上正常
    return line.size();
}

void new_game(){
    print_file("../../data/scripts/ascii_images/sith_code.txt", 8, true);
    print_file("../../data/scripts/ascii_images/script1.txt", 10, true);

    int choice;
    do{
        print_file("../../data/scripts/ascii_images/luke_skywalker.txt", 1, true);
        print_file("../../data/scripts/ascii_images/binks.txt", 0, false);
        cout << "Enter your choice ( 1 / 2 ): ";
        cin >> choice;

        switch(choice){
            case 1:
                print_file("../../data/scripts/ascii_images/script2.txt", 3, true);
                break;
            case 2:
                print_file("../../data/scripts/ascii_images/script3.txt", 3, true);
                break;
            default:
                cout << "invalid choice, please try again" << endl;
                break;
        }
    }while(choice != 1 && choice != 2);
    // main_game(choice);
    return;
}

void start_page(){
    int padding;
    string press_key = "Press any key to continue...";
    padding = 0.5*print_file("../../data/scripts/ascii_images/start1.txt", 0, true) - 0.5*press_key.size();
    cout << string(padding, ' ') << press_key;
    cin.ignore();
    
    int choice, slot;
    do{
        print_file("../../data/scripts/ascii_images/main_menu.txt", 0, true);
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                new_game();
                break;
            case 2:
                slot = save();
                break;
            case 3:
                //tutorial();
                break;
            case 4:
                end();
                break;
            default:
                cout << "invalid choice, please try again" << endl;
                break;
        }
    }while(choice != 4);
    return;
}

int rename_slot() {
    int slot;
    string new_name;
    bool valid = false;

    while(!valid){
        cout << "Enter the number of the slot you want to rename: ";
        cin >> slot;
        if (slot == 1 || slot == 2 || slot == 3){
            valid = true;
        }else{
            cout << "Invalid slot number.\n";
        }   
    }

    cout << "Enter a new name for the slot: ";
    cin.ignore();
    getline(cin, new_name);
    
    ifstream file_in("../../data/scripts/ascii_images/save.txt");
    vector<string> lines;
    string line;
    while (getline(file_in, line)) {
        lines.push_back(line);
    }
    file_in.close();
    lines[2*slot - 1] = "        " + new_name;
    
    ofstream file_out("../../data/scripts/ascii_images/save.txt");
    if(file_out.fail()){
        cout << "error: file not found" << endl;
    }
    for (const string& line : lines) {
        file_out << line << "\n";
    }
    file_out.close();
    
    return slot;
}
int save(){
    print_file("../../data/scripts/ascii_images/save.txt", 0, true);
    return rename_slot();
}

void end(){
    bool quit = true;
    cout << "       Are you sure ?  Enter 1 (Yes) / 0 (No):    " << endl;
    cin >> quit;
    if(!quit) return;
    print_file("../../data/scripts/ascii_images/end.txt", 3, true);
    exit(1);
}

// void save(){
//     return;
// }
// void tutorial(){
//     return;
// }
// void main_game(int choice)
