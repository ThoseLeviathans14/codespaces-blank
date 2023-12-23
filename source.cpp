#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

const string Reserved[6] = { "program", "var", "begin", "end.", "integer", "write" };//reserved words we will check "temp" against

void removeSpaces(vector<string>& lines)//part 1 of removing extra spaces
{
    string iterator;//placehold letter we will iterate through

    for (int x = 0; x < lines.size(); x++)
    {
        int spaces_end = 0;
        iterator = lines[x];//iterates thoughout the string we have passed to this function
        for (int y = 0; y < iterator.length(); y++)
        {
            if (iterator[y] != ' ') break;//skips this specific character
            else if (iterator[y] == ' ')//finds a space, then adds to the counter
            {
                spaces_end++;
            }
        }
        iterator.erase(0, spaces_end);//erases extra spaces from finalv1.txt based on counter
        lines[x] = iterator;//if a space is found, it gets deleted, and iterator moves on, and next character gets copied back into lines
    }
}

void removeComments(vector<string>& lines)
{
    string holder;//holds the string that gets passed into function
    for (int x = 0; x < lines.size(); x++)
    {
        holder = lines[x];
        int comm_pos = holder.find("(*");//find beginning of comment
        int comm_end = holder.find("*)");//finds end of comment
        if (comm_pos != -1 && comm_end == -1 || comm_pos == -1 && comm_end != -1)//means the entire line is a comment, so delete it all
        {
            holder.erase(holder.begin(), holder.end());
        }
        else if (comm_pos != -1 && comm_end != -1)//a comment exists in the line, since both beginning and the ends are found
        {
            holder.erase(comm_pos, comm_end + 2);//uses these positions to delete code, offset of 2 since it would begin at _*), instead of at the )
        }
        lines[x] = holder;//then it copies back into lines without the comments
    }
}

void killSpaces(vector<string>& lines)//to get rid of any remaining spaces
{
    string NewLine;
    string existLine;
    for (int x = 0; x < lines.size(); x++)
    {
        existLine = lines[x];
        NewLine.clear(); // in order to break the line each time and start on a new line
        unique_copy(existLine.begin(), existLine.end(), back_insert_iterator<string>(NewLine), [](char a, char b) { return isspace(a) && isspace(b); });//returns iterator values, only if they are unique, and distince from characters in front of them
        lines[x] = NewLine;//NewLine gets rid of all
    }
}

void fixFiles()//function that cleans up the file, essentially part 1 of the final project in form of a function
{
    vector<string> lines;//holds the contents finalv1.txt
    string placeholder;//iterator

    fstream file1;//holds finalv1.txt
    ofstream file2("finalv23.txt");//opens our new file, in order to write into it the contents of finalv1.txt after it is cleaned up
    file1.open("finalv1.txt", ios::in);
    if (!file1.is_open())
    {
        cout << "Something went wrong! :(";
    }
    while (getline(file1, placeholder))
    {
        lines.push_back(placeholder);//push the line into a vector of strings
    }
    file1.close();
    removeSpaces(lines);
    removeComments(lines);
    killSpaces(lines);
    //extra function added since some parts of file need an extra space in order to work properly
    for (int x = 0; x < lines.size(); x++)
    {
        if (lines[x] != "")
        {
            for (int y = 0; y < lines[x].length(); y++)
            {
                string placeholder = lines[x];
                if (placeholder[y] == ';' || placeholder[y] == ',')
                {
                    if (placeholder[y - 1] != ' ')
                    {
                        //inserts a space between tokens
                        //very dumb solution but it works, and I hate it
                        lines[x].insert(y, " ");
                    }
                }
            }
            file2 << lines[x] << "\n";

        }
    }
    file2.close();
}

bool checkReservedWord(string word)//flag to check for reserved words
{
    for (int x = 0; x < 6; x++)
    {
        if (word == Reserved[x]) return true;
    }
    return false;
}

int FindX_coord(string column)//columns of parsing table
{
    if (column == "program") return 0;
    else if (column == "var") return 1;
    else if (column == "begin") return 2;
    else if (column == "end.") return 3;
    else if (column == ":") return 4;
    else if (column == ",") return 5;
    else if (column == "integer") return 6;
    else if (column == "write") return 7;
    else if (column == "=") return 8;
    else if (column == "+") return 9;
    else if (column == "-") return 10;
    else if (column == "*") return 11;
    else if (column == "/") return 12;
    else if (column == "(") return 13;
    else if (column == ")") return 14;
    else if (column == "0") return 15;
    else if (column == "1") return 16;
    else if (column == "2") return 17;
    else if (column == "3") return 18;
    else if (column == "4") return 19;
    else if (column == "5") return 20;
    else if (column == "6") return 21;
    else if (column == "7") return 22;
    else if (column == "8") return 23;
    else if (column == "9") return 24;
    else if (column == "a") return 25;
    else if (column == "b") return 26;
    else if (column == "c") return 27;
    else if (column == "d") return 28;
    else if (column == "w") return 29;
    else if (column == "f") return 30;
    else if (column == "\"value=\"") return 31;
    else if (column == ";") return 32;
}

int FindY_coord(string row)//rows of parsing table
{
    if (row == "P") return 0;
    else if (row == "I") return 1;
    else if (row == "M") return 2;
    else if (row == "D") return 3;
    else if (row == "E") return 4;
    else if (row == "J") return 5;
    else if (row == "T") return 6;
    else if (row == "S") return 7;
    else if (row == "K") return 8;
    else if (row == "R") return 9;
    else if (row == "Q") return 10;
    else if (row == "W") return 11;
    else if (row == "A") return 12;
    else if (row == "F") return 13;
    else if (row == "O") return 14;
    else if (row == "U") return 15;
    else if (row == "H") return 16;
    else if (row == "G") return 17;
    else if (row == "N") return 18;
    else if (row == "Z") return 19;
    else if (row == "V") return 20;
    else if (row == "B") return 21;
    else if (row == "C") return 22;
}

int main() {
    //fix up the file
    fixFiles();
    //The Parsing Table
    //here, 100 = lambda
    string ParsingTable[23][33] =//23 rows, 33 columns
    { "program I; var D begin S end.", "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank",//0 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","CM","CM","CM", "CM", "CM","CM","blank","blank",//1 done
      "blank","blank","blank","blank","100","100","blank","blank","100","100","100","100","100","blank","100","BM","BM","BM","BM","BM","BM","BM","BM","BM","BM","CM","CM","CM","CM","CM","CM","blank","100",//2 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","E:T;","E:T;","E:T;","E:T;","E:T;","E:T;", "blank","blank",//3 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","IJ","IJ","IJ","IJ","IJ","IJ","blank","blank",//4 done
      "blank","blank","blank","blank","100",",E","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank",//5 done
      "blank","blank","blank","blank","blank","blank","integer","blank", "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank",//6 done
      "blank","blank","blank","blank","blank","blank","blank","RK","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","RK","RK","RK","RK","RK","RK","blank","blank",//7 done
      "blank","blank","blank","100","blank","blank","blank","S","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","S","S","S","S","S","S","blank","blank",// 8 done
      "blank","blank","blank","blank","blank","blank","blank","W","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","A","A","A","A","A","A","blank","blank", //9 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","100","100","100","100","100","100","\"value=\"","blank", //10 done
      "blank","blank","blank","blank","blank","blank","blank","write(QI);","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank", //11 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","I=F;","I=F;","I=F;","I=F;","I=F;","I=F;","blank","blank", //12 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","UO","UO","blank","blank","UO","blank","UO","UO","UO","UO","UO","UO","UO","UO","UO","UO","UO","UO","UO","UO","UO","UO","blank","blank",//13 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","+UO","-UO","blank","blank","blank","100","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","100",//14 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","GH","GH","blank","blank","GH","blank","GH","GH","GH","GH","GH","GH","GH","GH","GH","GH","GH","GH","GH","GH","GH","GH","blank","blank", //15  done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","100","100","*GH","/GH","blank","100","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","100",//16 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","N","N","blank","blank","(F)","blank","N","N","N","N","N","N","N","N","N","N","I","I","I","I","I","I","blank","blank",//17 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","VBZ","VBZ","blank","blank","blank","blank","VBZ","VBZ","VBZ","VBZ","VBZ","VBZ","VBZ","VBZ","VBZ","VBZ","blank","blank","blank","blank","blank","blank","blank","blank",//18 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","100","100","100","100","blank","100","BZ","BZ","BZ","BZ","BZ","BZ","BZ","BZ","BZ","BZ","blank","blank","blank","blank","blank","blank","blank","100",//19 done
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","+","-","blank","blank","blank","blank","100","100","100","100","100","100","100","100","100","100","blank","blank","blank","blank","blank","blank","blank","blank",//20
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","0","1","2","3","4","5","6","7","8","9","blank","blank","blank","blank","blank","blank","blank","blank",//21
      "blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","blank","a","b","c","d","w","f","blank","blank"//22
    };
    vector<string> Lines;//make each line contain one line of the file,
    
    stack<string> tempStack;//temp stack to use
   
    stack<string> check;//main checking stack
    int x = 0;///holds the position of the current word
    int Y_coordinate;
    int X_coordinate;

    string temp;//temp holds our result after inputting the coordinates we have read out
    bool reserved_check = false;
    bool matchcheck = false;
    fstream f;
    string content;//variable that passes the contents of our file, filev23.txt, into Lines
    f.open("finalv23.txt");
    //we create an array of each word in the file
    while (!f.eof()) {
        f >> content;
        Lines.push_back(content);
    }
    //Push in P, we begin here, it's our $E for our predictive parsing table
    check.push("P");
    do
    {
        string c = check.top();//once the loop repeats, we pop top of check's stack gets popped into "c"
        check.pop();
        if (c == Lines[x] && c == "end.") {
            cout << "EXPRESSION HAS NO ERRORS! :)"; return 0;//get out of the for loop
        }
        else if (c == Lines[x]) {
            //we found a match
            x++;//moves to next word
            reserved_check = false;
        }
        else
        {
            reserved_check = checkReservedWord(Lines[x]);
            if (reserved_check)//if it's true
            {
                //if the word is a reserved word use the entire word as an X_coordinate
                X_coordinate = FindX_coord(Lines[x]);//"x" is position in file
                Y_coordinate = FindY_coord(c);//c is current value in stack
                //I did my coordinates backwards by accident lol, whoops
                temp = ParsingTable[Y_coordinate][X_coordinate];
                if (temp == "blank") { cout << "ERROR\nSomething went wrong, check word " << Lines[x - 1] << endl; return 0; }
                //this method is very jank, try to find other way
                if (temp != "100") {
                    if (temp.find(Reserved[5]) == NULL) {
                        for (int x = temp.length() - 1; x >= 5; x--) {
                            string letters(1, temp[x]);//string "letters" creates a single string of length 1, it to break up words into individual characters
                            check.push(letters);
                        }
                        check.push("write");//here we are looking for the word write
                    }
                    else {
                        istringstream iss(temp);//splits the string "temp" holds into individual strings of 1 word
                        string temp2;//temp2 holds the individual strings, in order to push it into tempStack
                        while (iss >> temp2) {
                            tempStack.push(temp2);
                        }
                        while (!tempStack.empty()) {
                            if (checkReservedWord(tempStack.top())) {
                                check.push(tempStack.top());//if a reserved words is in our temp stack, we push into the main stack "check"
                                tempStack.pop();//removes reserved word from temp stack
                            }
                            else {
                                //If the word isn't a reserved word, then split it into it's smaller pieces
                                string placeholder = tempStack.top();//placeholder holds in the individual characters of the word as type string of length 1
                                tempStack.pop();
                                for (int a = placeholder.length() - 1; a >= 0; a--) {
                                    char b = placeholder[a];
                                    string letters(1, b);
                                    check.push(letters);//now the individual pieces get pushed into the main stack "check"
                                }
                            }
                        }
                    }
                }
                else
                {
                    //Do nothing, since we have arrived at a lambda lol
                }
            }
            //we could be dealing with "value=", which is not a reserved word, but must be used as a singluar string
            else if (Lines[x] == "\"value=\"")
            {
                X_coordinate = FindX_coord(Lines[x]);
                Y_coordinate = FindY_coord(c);
                temp = ParsingTable[Y_coordinate][X_coordinate];
                check.push(",");
                check.push(temp);
            }

            //we are no longer dealing with a reserved word
            else
            {
                //not a reserved word, check each letter
                for (auto p : Lines[x])//p is the iterator
                {
                    while (!matchcheck)
                    {
                        if (c[0] == p) {
                            //check.pop();
                            matchcheck = true;
                        }
                        else {
                            string letters(1, p);//string "letters" holds individual characters of the word we are breaking up, as type string of length 1
                            X_coordinate = FindX_coord(letters);
                            Y_coordinate = FindY_coord(c);
                            string XYAns = ParsingTable[Y_coordinate][X_coordinate];
                            if (XYAns == "blank") {
                                cout << "ERROR\nSomething went wrong, check word " << Lines[x - 1] << endl; return 0;
                                return 0;
                            }
                            else if (XYAns == "100") { c = check.top(); check.pop(); continue; } //pass by 100s, which here, represent lambda
                            else {
                                for (int x = XYAns.length() - 1; x >= 0; x--) {
                                    string help(1, XYAns[x]);//string "help" now holds individual characters of the word we are breaking up, as type string of length 1
                                    check.push(help);//pushes in the strings of length 1 into our main stack "check"
                                }
                                c = check.top();//stack has been filled by previous, function so "c" no holds most recent item in stack
                                check.pop();
                            }
                        }
                    }
                    c = check.top();//"c" matches the given input, so now we move onto next item in stack
                    matchcheck = false;//puts down flag for next run of the loop
                }
                x++;//move onto the next word
            }
        }
    } while (x < Lines.size());
    //check to see if the word is a reserved word

    cout << "NO ERRORS DETECTED :) \n";
    system("pause");
    return 0;
}

/*
 * We know write can only be possible if it is used in the correct manner
 * check the word, and see if write is a part of it
 * find the end point of the word write in the string
 * insert in reverse, going up into our found end point
 * push in write
 * */