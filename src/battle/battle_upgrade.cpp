#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;


#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"

//clear screen
void clearScreen() {
    system("printf \"\\033c\"");
}

//append white spaces to complement a string to a target length
string appendspace(string line,int length)
{
    int len = line.length();
    if(len >= length)
    {
        return line;
    }
    else
    {
        int spacenumber = length - len;
        string output = line.append(spacenumber,' ');
        return output;
    }
}


//read char painting from a *.txt file and store as a vector
vector<string> getpaint(string filename,string target,int line_number,int length)
{
    ifstream ifs;
    ifs.open(filename.c_str());
    if(ifs.fail()){
        cout << "error: file not found" << endl;
        exit(1);
    }
    vector<string> output;
    string line;
    while(getline(ifs,line))
    {
        if(line == target)
        {
            for(int i = 0;i<line_number;i++)
            {
                getline(ifs,line);
                line = appendspace(line,length);
                output.push_back(line);

            }
            ifs.close();
            return output;
        }
    }
    ifs.close();
    return {"notfound"};
}



//given 4 vector<string> with same size, return a merged one that contain the non-whitespace chars of those
vector<string> merge(vector<vector<string>> vectors,int line_number,int length)
{
    string emptystring(length,' ');
    vector<string> output(line_number,emptystring);
    for(int row = 0;row<line_number;row++)
    {
        for(int col = 0; col < length; col++)
        {
            for (int e = 0; e< vectors.size();e++)
            {
                if(vectors[e][row][col] != ' ')
                {
                    output[row][col] = vectors[e][row][col];
                }
            }
        }
    }
    return output;
}


//given a certain position of a vector string, Change all positions on that line （except the tail） after this position to spaces.
vector<string> selectframe(vector<string> input, int line,int col)
{   
    vector<string> output = input;
    int length = input[0].length();
    for(int i = col;i<length-1;i++)
    {
        output[line][i] = ' ';
    }
    return output;
}

// given 4 vector strings, make them into a matrix and the second one(upgrading) will be selected frame first ( to make the animation)
vector<vector<string>>makematrix(vector<string> before, vector<string> upgrading, vector<string> upgraded, vector<string> after,int length,int line)
{
    vector<vector<string>> matrix;
    matrix.push_back(before);
    for(int i = 0;i<length;i++)
    {
        vector<string> keyframe = selectframe(upgrading,line,i);
        matrix.push_back(keyframe);
    }
    matrix.push_back(upgraded);
    matrix.push_back(after);
    return matrix;
    
}
//print out the vector line by line
void printvector(vector<string> vector)
{
    for(int i = 0; i < vector.size();i++)
    {
        cout << vector[i] << endl;
    }
}

//print out the vector line by line
void printvectorwithcolor(vector<string> vector, string color, string reset)
{
    for(int i = 0; i < vector.size();i++)
    {
        cout <<color<< vector[i] <<reset<< endl;
    }
}
//print out the matrix vector by vector, clear screen between to vectors in a certain speed
void printmatrix(vector<vector<string>> matrix, string color)
{
    for(int i = 0;i < matrix.size()-1;i++)
    {
        clearScreen();
        printvector(matrix[i]);
        if(i == 0 || i == (matrix.size()-1) || i == (matrix.size() - 2))
        {
            
            this_thread::sleep_for(chrono::seconds(1));
            
        }
        else
        {
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
    clearScreen();
    printvectorwithcolor(matrix[matrix.size()-1],color,RESET_COLOR);
    this_thread::sleep_for(chrono::seconds(1));
    cin.get();

}


vector<vector<string>> fromtoto (vector<vector<string>> generater, vector<string> toframe )
{
    vector<vector<string>> togenerater = generater;
    togenerater[generater.size()-1] = toframe;
    return togenerater;
}


vector<vector<string>> make (vector<vector<vector<string>>> generaters, vector<string> Upgraded, vector<string> Upgrading, vector<string> toframe, int level, int line_num, int col_num,int line__)
{
 
    vector<vector<string>> before_generater = generaters[level];
    vector<vector<string>> after_generater = generaters[level+1];
    vector<string> from = merge(before_generater,line_num,col_num);
    vector<string> to = merge(fromtoto(after_generater,toframe),line_num,col_num);
    vector<vector<string>> matrix = makematrix(from,Upgrading,Upgraded,to,col_num,line__);
    return matrix;
}
int main()
{
    // string target;
    // cin >> target;

    string filename = "./../../data/animations/paint.txt";
    string filename2 = "./../../data/animations/text.txt";
    string filename3 = "./../../data/animations/main_character.txt";

    int line_number = 23;
    int col_number = 77;
    int line__ = 16;

    vector<string> jedi = getpaint(filename2,"jedi",line_number,col_number);
    vector<string> frame = getpaint(filename,"frame",line_number,col_number);
    vector<string> toframe = getpaint(filename,"toframe",line_number,col_number);
    vector<string> mc1 = getpaint(filename3,"mc1",line_number,col_number);
    vector<string> mc2 = getpaint(filename3,"mc2",line_number,col_number);
    vector<string> mc3 = getpaint(filename3,"mc3",line_number,col_number);
    vector<string> mc4 = getpaint(filename3,"mc4",line_number,col_number);
    vector<string> trainee = getpaint(filename2,"trainee",line_number,col_number);
    vector<string> knight = getpaint(filename2,"knight",line_number,col_number);
    vector<string> master = getpaint(filename2,"master",line_number,col_number);
    vector<string> legendary = getpaint(filename2,"legendary",line_number,col_number);
    vector<string> upgrading = getpaint(filename,"upgrading",line_number,col_number);
    vector<string> upgraded = getpaint(filename,"upgraded",line_number,col_number);
    vector<string> blank = getpaint(filename,"blank",line_number,col_number);
    vector<string> one = getpaint(filename2,"one",line_number,col_number);
    vector<string> two = getpaint(filename2,"two",line_number,col_number);
    vector<string> three = getpaint(filename2,"three",line_number,col_number);

    // printvector(jedi);
    // printvector(frame);
    //printvector(mc1);
    // printvector(mc2);
    // printvector(mc3);
    // printvector(mc4);
    //printvector(trainee);
    // printvector(knight);
    // printvector(master);
    // printvector(legendary);
    // printvector(upgrading);
    // printvector(one);
    // printvector(two);
    // printvector(three);
    vector<vector<string>> LEVEL1_one_GENERATER = {mc1,jedi,trainee,one,frame};
    vector<vector<string>> LEVEL1_two_GENERATER = {mc1,jedi,trainee,two,frame};
    vector<vector<string>> LEVEL1_three_GENERATER = {mc1,jedi,trainee,three,frame};
    vector<vector<string>> LEVEL2_one_GENERATER = {mc2,jedi,knight,one,frame};
    vector<vector<string>> LEVEL2_two_GENERATER = {mc2,jedi,knight,two,frame};
    vector<vector<string>> LEVEL2_three_GENERATER = {mc2,jedi,knight,three,frame};
    vector<vector<string>> LEVEL3_one_GENERATER = {mc3,jedi,master,one,frame};
    vector<vector<string>> LEVEL3_two_GENERATER = {mc3,jedi,master,two,frame};
    vector<vector<string>> LEVEL3_three_GENERATER = {mc3,jedi,master,three,frame};
    // vector<vector<string>> toLEVEL2_GENERATER = fromtoto(LEVEL2_GENERATER,toframe);
    // vector<vector<string>> toLEVEL3_GENERATER = fromtoto(LEVEL3_GENERATER,toframe);
    vector<vector<string>> LEVEL4_GENERATER = {mc4,jedi,legendary,toframe};

    vector<vector<vector<string>>> generaters = {
        LEVEL1_one_GENERATER,
        LEVEL1_two_GENERATER,
        LEVEL1_three_GENERATER,
        LEVEL2_one_GENERATER,
        LEVEL2_two_GENERATER,
        LEVEL2_three_GENERATER,
        LEVEL3_one_GENERATER,
        LEVEL3_two_GENERATER,
        LEVEL3_three_GENERATER,
        LEVEL4_GENERATER,
    };
    // vector<string> fromLEVEL1 = merge(LEVEL1_GENERATER,line_number,col_number);
    // vector<string> fromLEVEL2 = merge(LEVEL2_GENERATER,line_number,col_number);
    // vector<string> fromLEVEL3 = merge(LEVEL3_GENERATER,line_number,col_number); 
    // vector<string> toLEVEL4 = merge(LEVEL4_GENERATER,line_number,col_number);
    // vector<string> toLEVEL2 = merge(toLEVEL2_GENERATER,line_number,col_number);
    // vector<string> toLEVEL3 = merge(toLEVEL3_GENERATER,line_number,col_number);

    vector<vector<string>> Upgraded_GENERATER = {upgraded,frame};
    vector<vector<string>> Upgrading_GENERATER = {upgrading,frame};

    vector<string> Upgraded = merge(Upgraded_GENERATER,line_number,col_number);
    vector<string> Upgrading = merge(Upgrading_GENERATER,line_number,col_number);

    //vector<vector<string>>  matrix1 = makematrix(fromLEVEL1,Upgrading,Upgraded,toLEVEL2,col_number,line__);// upgrading from trainee to knight
    //vector<vector<string>>  matrix2 = makematrix(fromLEVEL2,Upgrading,Upgraded,toLEVEL3,col_number,line__);// upgrading from knight to master
    //vector<vector<string>>  matrix3 = makematrix(fromLEVEL3,Upgrading,Upgraded,toLEVEL4,col_number,line__);// upgrading from knight to legendary
    // printmatrix(matrix1,BLUE_COLOR);
    // printmatrix(matrix2,RED_COLOR);
    // printmatrix(matrix3,GREEN_COLOR);
    cout << "which level you are?" << endl;
    int i;
    cin >> i;
    cout << "now you will upgrade to " << i+1 << "level" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    vector<vector<string>> matrix = make(generaters,Upgraded,Upgrading,toframe,i,line_number,col_number,line__);
    printmatrix(matrix,BLUE_COLOR);
 }
