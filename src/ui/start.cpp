#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include "start_endpage.h"
#include "../character/character.h"
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

string new_game(){
    print_file("../../data/scripts/ascii_images/sith_code.txt", 8, true);
    print_file("../../data/scripts/ascii_images/script1.txt", 10, true);

    string name;
    bool valid = false;
    do{
        print_file("../../data/scripts/ascii_images/computer.txt", 0, true);
        cin.ignore();
        cout << "Enter your name (no more than 10 chars): ";
        getline(cin, name);

        if(name.size() < 11){  
            valid = true   ;   
            ifstream file_in("../../data/scripts/ascii_images/script3.txt");
            vector<string> lines;
            string line;
            while (getline(file_in, line)) {
                lines.push_back(line);
            }
            file_in.close();
            lines[25] = "  \"" + name + ", my most unlikely servant. Your ";
    
            ofstream file_out("../../data/scripts/ascii_images/script3.txt");
            if(file_out.fail()){
                cout << "error: file not found" << endl;
            }
            for (const string& line : lines) {
                file_out << line << "\n";
            }
            file_out.close();

            ifstream fin("../../data/scripts/ascii_images/luke_skywalker.txt");
            vector<string> sec_lines;
            string sec_line;
            while (getline(fin, sec_line)) {
                sec_lines.push_back(sec_line);
            }
            fin.close();
            sec_lines[17] = "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⡿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀         ****  " + name + "  ****";
    
            ofstream fout("../../data/scripts/ascii_images/luke_skywalker.txt");
            if(fout.fail()){
                cout << "error: file not found" << endl;
            }
            for (const string& sec_line : sec_lines) {
                fout << sec_line << "\n";
            }
            fout.close();
        }
    }while(!valid);
    print_file("../../data/scripts/ascii_images/luke_skywalker.txt", 4, true);
    print_file("../../data/scripts/ascii_images/script3.txt", 6, true);
    // main_game(choice);
    return name;
}

void start_page(){
    int padding;
    string press_key = "Press any key to continue...";
    padding = 0.5*print_file("../../data/scripts/ascii_images/start1.txt", 0, true) - 0.5*press_key.size();
    cout << string(padding, ' ') << press_key;
    cin.ignore();
    
    int choice, slot;
    string name;
    do{
        print_file("../../data/scripts/ascii_images/main_menu.txt", 0, true);
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                continue_game();
            case 2:
                name = new_game();
                break;
            case 3:
                save();
                break;
            case 4:
                //tutorial();
                break;
            case 5:
                end();
                break;
            default:
                cout << "invalid choice, please try again" << endl;
                break;
        }
    }while(choice != 4);
    return;
}

void continue_game(){
    print_file("../../data/scripts/ascii_images/save.txt", 0, true);

    int slot;
    cin.ignore();
    cout << "Choose your game to continue: ";
    cin >> slot;

    save_file s;
    parse_file("../../data/savings/sav.txt", s, slot);
    main_game(s);
    return;
}

void parse_file(const string filename, save_file &s, int slot){
    ifstream fin;
    fin.open(filename.c_str());
    if(fin.fail()){
        cout << "error: file not found" << endl;
    }
    //
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
    lines[2*slot - 1] = lines[2*slot - 1].substr(0, 11) + new_name;
    
    ofstream file_out("../../data/scripts/ascii_images/save.txt");
    if(file_out.fail()){
        cout << "error: file not found" << endl;
    }
    for (const string& line : lines) {
        file_out << line << "\n";
    }
    file_out.close();
    
    return slot - 1;    // index of the real save_file vector
}
void save(save_file s){
    static save_file save_files[3];
    int slot;
    
    print_file("../../data/scripts/ascii_images/save.txt", 0, true);
    slot = rename_slot();
    save_files[slot] = s;
    return;
}

void end(){
    bool quit = true;
    cout << "       Are you sure ?  Enter 1 (Yes) / 0 (No):    " << endl;
    cin >> quit;
    if(!quit) return;
    print_file("../../data/scripts/ascii_images/end.txt", 3, true);
    exit(1);
}

void main_game(save_file s){
    //
    return;
}

// void save(){
//     return;
// }
// void tutorial(){
//     return;
// }
// void main_game(int choice)
int main(){ // for test
    start_page();
    return 0;
}