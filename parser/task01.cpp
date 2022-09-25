#include "functions.h"
int main()
{
    ifstream fin;
    fin.open("inputT.csv");
    if (!fin.is_open())
    {
        cout << "transitions inputT file is not found, Lexical Analyzer can't work. Exiting." << endl;
        exit(1);
    }
    char s[1000];
    int row = 0;

    while (fin.getline(s, 1000))
        row++;
    fin.clear();
    fin.seekg(0, ios::beg);
    fin.getline(s, 1000);
    const int cols = getCommaCount(s);
    // cout<<"rows are : "<<row<<endl;
    // cout<<"cols are : "<<cols<<endl;
    const int rows = row;
    char table[rows][cols + 1][10];
    fin.clear();
    fin.seekg(0, ios::beg);
    char *ptr;
    int c = 0, r = 0;
    while (fin >> s)
    {
        // cout<<s<<endl;
        ptr = strtok(s, ",");
        while (ptr != NULL)
        {
            // cout <<ptr<< " "; // print the string token
            strcpy(table[r][c], ptr);
            ptr = strtok(NULL, ",");
            c++;
        }
        c = 0;
        r++;
    }
    fin.close();
    // for (int x = 0; x < rows; ++x)
    // {
    //     for (int y = 0; y < cols; ++y)
    //         cout << table[x][y] << "\t";
    //     cout << endl;
    // }
    // File Reading is complete here.
    //this maps tell if found word is keyword or not.
    unordered_map<string, int> kw;
    kw["loop"] = 1;
    kw["agar"] = 1;
    kw["magar"] = 1;
    kw["asm"] = 1;
    kw["else"] = 1;
    kw["new"] = 1;
    kw["this"] = 1;
    kw["auto"] = 1;
    kw["enum"] = 1;
    kw["operator"] = 1;
    kw["throw"] = 1;
    kw["bool"] = 1;
    kw["explicit"] = 1;
    kw["private"] = 1;
    kw["true"] = 1;
    kw["break"] = 1;
    kw["export"] = 1;
    kw["protected"] = 1;
    kw["try"] = 1;
    kw["case"] = 1;
    kw["extern"] = 1;
    kw["public"] = 1;
    kw["typedef"] = 1;
    kw["catch"] = 1;
    kw["false"] = 1;
    kw["register"] = 1;
    kw["typeid"] = 1;
    kw["char"] = 1;
    kw["float"] = 1;
    kw["typename"] = 1;
    kw["class"] = 1;
    kw["for"] = 1;
    kw["return"] = 1;
    kw["union"] = 1;
    kw["const"] = 1;
    kw["friend"] = 1;
    kw["short"] = 1;
    kw["unsigned"] = 1;
    kw["goto"] = 1;
    kw["signed"] = 1;
    kw["using"] = 1;
    kw["continue"] = 1;
    kw["if"] = 1;
    kw["sizeof"] = 1;
    kw["virtual"] = 1;
    kw["default"] = 1;
    kw["inline"] = 1;
    kw["static"] = 1;
    kw["void"] = 1;
    kw["delete"] = 1;
    kw["int"] = 1;
    kw["volatile"] = 1;
    kw["do"] = 1;
    kw["long"] = 1;
    kw["struct"] = 1;
    kw["double"] = 1;
    kw["mutable"] = 1;
    kw["switch"] = 1;
    kw["while"] = 1;
    kw["namespace"] = 1;
    //Input Mapping array to Table, location is location-1 here as index.
    int map2table[128] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, 22, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, -1, -1, -1, -1, -1, 21, 8, -1, -1, -1, 11, 5, -1, -1, -1, 4, 2, -1, 7, 19, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, -1, 10, 1, 9, -1, -1, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 15, -1, 16, -1, 17, -1, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 13, 3, 14, -1, -1};
    //States Array tell if particular state is final. -sign denote that it need to -- file pointer.
    int states[50] = {0, 0, 0, 0, 0, 0, 0, 0, -8, 0, 10, -11, 0, 13, -14, 0, 0, 17, 18, 19, 20, 21, 0, 23, 0, -25, 26, 0, -28, 29, 30, 31, 32, 0, 34, 0, 36, 37, 0, -39, 40, 41, 42, 43, 44, 0, -46, 0};
    //this map tells at which final state which kind of token will be generated.
    unordered_map<int, string> types;
    types[-8] = "Number";
    types[10] = "++";
    types[-11] = "+";
    types[13] = "--";
    types[-14] = "-";
    types[17] = "=:=";
    types[18] = "==";
    types[19] = "=+";
    types[20] = "=>";
    types[21] = "=<";
    types[23] = "!=";
    types[-25] = ">";
    types[26] = ">>";
    types[-28] = "<";
    types[29] = "<<";
    types[30] = "<>";
    types[31] = "*";
    types[32] = "/";
    types[34] = "&&";
    types[36] = "||";
    types[37] = "%";
    types[-39] = ":";
    types[40] = "::";
    types[41] = "[";
    types[42] = "]";
    types[43] = "{";
    types[44] = "}";
    types[-46] = "ID";
    // all setup complete here. Time to read the sourcecode File

    int curState = 1;
    char curChar = 0;
    int curLine = 1;
    TokenList tokenlist;
    string input;
    fin.open("sourcecode.txt");
    ofstream fout("Error.txt");
    if (!fin.is_open())
    {
        cout << "sourcecode.txt is not found, termiating.";
        exit(0);
    }
    while (fin.get(curChar))
    {
        if ((curState == 7 || curState == 2) && (curChar == 'E' || curChar == 'e')) // Case for handling Exponential Numbers.
        {
            input += curChar;
            curState = 3;
            continue;
        }
        if (map2table[int(curChar) - 1] == -1) // Case for Handling Unknown Symbol Error.
        {
            fout << "Unknown symbol '" << curChar << "' is found on line : " << curLine << endl;
            curState = 1;
            input = "";
            continue;
        }
        curState = atoi(table[curState][map2table[int(curChar) - 1]]); // Getting New State from 2D List Created from CSV file.
        if (curChar != ' ' && curChar != '\n')
            input += curChar;
        if (curState < 0)
        {
            if (kw[input] == 1)
                tokenlist.insertToken(input, "KW");
            else
            {
                // input.pop_back();
                // fout<<input;
                printError(fout, curLine, input, curState);
                // fin.unget();
            }
            input = "";
            curState = 1;
        }
        if (states[curState]) // Checking if Current State is Final State.
        {
            if (states[curState] < 0) // checking if Need -- the file Pointer.
            {
                fin.unget();
                if (curChar != ' ')
                    input.pop_back();
            }
            tokenlist.insertToken(input, types[states[curState]]);
            curState = 1;
            input = "";
        }
        if (curChar == '\n')
            curLine++;
    }

    tokenlist.outList();
    fout.close();
}