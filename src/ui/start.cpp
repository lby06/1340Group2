#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

void clear_screen(){
#ifdef _WIN32
    system("CLS");
#elif __unix__
    system("clear");
#endif
}

int print_file(const string filename){
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
    return line.size();
}

void start_page(){
    int padding;
    string press_key = "Press any key to continue...";
    padding = 0.5*print_file("../../data/scripts/ascii_images/start1.txt") - 0.5*press_key.size();
    cout << string(padding, ' ') << press_key;
    cin.ignore();
    
    int choice;
    do{
        print_file("../../data/scripts/ascii_images/main_menu.txt");
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                //new_game();
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
// void new_game(){
//     return;
// }
// void save(){
//     return;
// }
// void tutorial(){
//     return;
// }
// void end(){
//     return;
// }

int main(){
    start_page();
    return 0;
}