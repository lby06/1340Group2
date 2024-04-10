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
                save(save_file);
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

    double parameters[20];
    int cnt = 0;
    string username, line;
    while(getline(fin, line)){
        if(line.substr(0, 7) == "@slot " + to_string(slot)){
            cnt = -2;
        }
        if(cnt >= 0 && cnt < 20) parameters[cnt] = stod(line);
        if(cnt == 24) username = line;
        cnt++;
    }
    s.save_character.set(parameters);
    // s.save_maze
    s.slot_number = slot;
    s.username = username;
    fin.close();
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
    
    return slot;  
}

int delete_slot(){
    int slot;
    bool valid = false;

    while(!valid){
        cout << "Enter the number of the slot you want to delete: ";
        cin >> slot;
        if (slot == 1 || slot == 2 || slot == 3){
            valid = true;
        }else{
            cout << "Invalid slot number.\n";
        }   
    }

    ifstream file_in("../../data/scripts/ascii_images/save.txt");
    vector<string> lines;
    string line;
    while (getline(file_in, line)) {
        lines.push_back(line);
    }
    file_in.close();
    lines[2*slot - 1] = lines[2*slot - 1].substr(0, 11) + "Slot " + to_string(slot);
    
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

void save(save_file s){
    static save_file save_files[3];
    int slot;
    char command;
    
    print_file("../../data/scripts/ascii_images/save.txt", 0, true);
    cin.ignore();
    cout << "Enter \"s\" to save your game; enter \"d\" to erase existing slot: ";
    cin >> command;
    if(command == 's'){
        slot = rename_slot();
        save_files[slot - 1] = s;
    }else if(command == 'd'){
        slot = delete_slot();
    }
    
    double *save_parameters;
    // Map savemap;
    string username;
    save_parameters = s.save_character.save();
    // savemap = 
    slot = slot
    username = s.username;

    // input save file
    fstream fin;
    fin.open("../../data/savings/sav.txt");
    if(fin.fail()){
        cout << "error: file not found" << endl;
    }
    vector<string> lines;
    string line;
    while (getline(fin, line)) {
        lines.push_back(line);
    }
    fin.close();

    int init_position;
    if(slot == 1){
        init_position = 0;
    }else if(slot == 2){
        init_position = 27;
    }else if(slot == 3){
        init_position = 54;
    }
    // change content of the save file
    if(command == 'd'){
        for(int i = 0; i < 20; i++){
            lines[init_position + 2 + i] = "";
        }
        lines[init_position + 24] = "";
        lines[init_position + 26] = "";

        // rewrite save file
        ofstream fout("../../data/savings/sav.txt");
        if(fout.fail()){
            cout << "error: file not found" << endl;
        }
        for (const string& line : lines) {
            fout << line << "\n";
        }
        fout.close();

        return;
    }
    for(int i = 0; i < 20; i++){
        lines[init_position + 2 + i] = to_string(save_parameters[i]);
    }
    lines[init_position + 24] = to_string(slot);
    lines[init_position + 26] = username;

    // rewrite save file
    ofstream fout("../../data/savings/sav.txt");
    if(fout.fail()){
        cout << "error: file not found" << endl;
    }
    for (const string& line : lines) {
        fout << line << "\n";
    }
    fout.close();

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