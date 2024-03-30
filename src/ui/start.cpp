#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

void clear_screen(){
#ifdef _WIN32
    system("CLS");
#elif __unix__
    system("clear");
#endif
}

int print_file(const string filename, int wait_time){
    ifstream file;
    string line;
    file.open(filename.c_str());
    if(file.fail()){
        cout << "error: file not found" << endl;
        exit(1);
    }
    //clear_screen();
    while(getline(file, line)){
        cout << line << endl;
    }
    file.close();
    this_thread::sleep_for(chrono::seconds(wait_time));
    return line.size();
}

void new_game(){
    print_file("../../data/scripts/ascii_images/sith_code.txt", 3);
    print_file("../../data/scripts/ascii_images/script1.txt", 3);

    int choice;
    do{
        print_file("../../data/scripts/ascii_images/luke_skywalker.txt", 0);
        print_file("../../data/scripts/ascii_images/darth_vader.txt", 0);
        cout << "Enter your choice ( 1 / 2 ): ";
        cin >> choice;

        switch(choice){
            case 1:
                print_file("../../data/scripts/ascii_images/script2.txt", 3);
                break;
            case 2:
                print_file("../../data/scripts/ascii_images/script3.txt", 3);
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
    padding = 0.5*print_file("../../data/scripts/ascii_images/start1.txt", 0) - 0.5*press_key.size();
    cout << string(padding, ' ') << press_key;
    cin.ignore();
    
    int choice;
    do{
        print_file("../../data/scripts/ascii_images/main_menu.txt", 0);
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                new_game();
                break;
            case 2:
                //save();
                break;
            case 3:
                //tutorial();
                break;
            case 4:
                //end();
                break;
            default:
                cout << "invalid choice, please try again" << endl;
                break;
        }
    }while(choice != 4);
    
    
}

// void save(){
//     return;
// }
// void tutorial(){
//     return;
// }
// void end(){
//     return;
// }
// void main_game(int choice)

int main(){
    start_page();
    return 0;
}