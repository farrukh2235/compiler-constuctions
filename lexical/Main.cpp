#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>

using namespace std;

const int rows = 20;
const int cols = 25;

int Arrr_Tab[rows][cols];
int GerNext(int , char);
void display();
bool is_alpha(char );
bool is_digit(char );
bool is_operator(char );
void get_TransitionTable();
bool isKeyword(char *);
int GerNext(int , char );



int main()
{
    get_TransitionTable();
    //display();
    ifstream fin("input.txt");
    ofstream fout("Token.txt");
    ofstream error("Error.txt");

    if (!fin.is_open())
    {
        cout << "File Not Found.\n"
             << endl;
        exit(0);
    }
    
    char token[255];
    int token_index = 0;

    char ch;
    int currr_ind = 1, flag = 0;

    do
    {
        if (fin.eof())
            return 0;

        if (flag == 0)
            fin >> ch;
        else
            flag = 0;

        currr_ind = GerNext(currr_ind, ch);

        if (currr_ind == 2 || currr_ind == 4 || currr_ind == 5 || currr_ind == 6 || currr_ind == 8 || currr_ind == 9 || currr_ind == 10 || currr_ind == 11 || currr_ind == 12 || currr_ind == 13 || currr_ind == 14 || currr_ind == 15)
        {
            token[token_index] = ch;
            token_index++;
           
            token[token_index] = '\0';
            if (isKeyword(token))
            {
                fout << token << " is a <Keyword>" << endl;

                currr_ind = 1;
                token_index = 0;
            }
        }

        else if (currr_ind == 3)
        {

            token[token_index] = '\0';
            if (isKeyword(token))
                fout << token << " is a <Keyword>" << endl;

            else
                fout << token << " is a <Identifier>" << endl;

            currr_ind = 1;
            token_index = 0;
            flag = 1;
        }

        else if (currr_ind == 19)
        {
            token[token_index] = '\0';
            fout << token << " is a <Number>" << endl;
            currr_ind = 1;
            token_index = 0;
            flag = 1;
        }

        else if (currr_ind == 18)
        {
            token[token_index] = '\0';
            fout << token << " is a <Operator>" << endl;

            currr_ind = 1;
            token_index = 0;
            flag = 1;
        }

        else if (currr_ind == 17)
        {
            token[token_index] = ch;
            token[token_index + 1] = '\0';
            fout << token << " is a <Operator>" << endl;

            currr_ind = 1;
            token_index = 0;
        }
        else if (currr_ind == 16)
        {
            token[token_index] = ch;
            token[token_index + 1] = '\0';
            fout << token << " is a <Bracket>" << endl;

            currr_ind = 1;
            token_index = 0;
        }

        else
        {
            token[token_index] = ch;
            token[token_index + 1] = '\0';
            error << token << " is a <Invalid token>" << endl;
            currr_ind = 1;
            token_index = 0;
        }
    } while (!fin.eof());
    fin.close();
    fout.close();
    error.close();
    return 0;
}
void display()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << Arrr_Tab[i][j] << " ";
        }
        cout << endl;
    }
}



bool is_alpha(char ch)
{

    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
    {
        return true;
    }
    return false;
}



bool is_digit(char ch)
{
    char digit[] = {"0123456789"};

    for (int i = 0; i < strlen(digit); i++)
    {
        if (digit[i] == ch)
        {
            return true;
        }
    }
    return false;
}

bool is_operator(char ch)
{
    char op[] = {"+-=<>,/*&%#!:;|"};
    for (int i = 0; op[i] != '\0'; i++)
    {
        if (ch == op[i])
            return true;
    }
    return false;
}

void get_TransitionTable()
{
    ifstream fin("Table.txt");

    if (!fin.is_open())
    {
        cout << "File Not Found." << endl;
        exit(0);
    }

    char input[100];

    for (int i = 0; i < rows; i++)
    {
        fin.getline(input, 100);

        char *temp_str = NULL;

        temp_str = strtok(input, " ");

        Arrr_Tab[i][0] = atoi(temp_str);

        for (int j = 1; j < cols; j++)
        {
            temp_str = strtok(NULL, " ");

            Arrr_Tab[i][j] = atoi(temp_str);
        }
    }

    fin.close();
}



bool isKeyword(char *token)
{
    char keywords[32][10] = {"main", "else", "new", "bool", "endl", "true", "break",
                             "case", "false", "char", "float", "for", "return",
                             "const","short", "unsigned", "signed", "using", "if", "default", "void", "delete", "int",
                             "do", "long", "double", "switch", "while", "namespace", "std", "cin", "cout"};

    for (int i = 0; i < 32; i++)
    {
        if (strcmp(keywords[i], token) == 0)
            return true;
    }

    return false;
}

int GerNext(int currr_ind, char ch)
{
    if (is_alpha(ch))
        return Arrr_Tab[currr_ind][0];

    else if (is_digit(ch))
        return Arrr_Tab[currr_ind][1];

    else if (ch == '+')
        return Arrr_Tab[currr_ind][2];

    else if (ch == '-')
        return Arrr_Tab[currr_ind][3];

    else if (ch == '*')
        return Arrr_Tab[currr_ind][4];

    else if (ch == '/')
        return Arrr_Tab[currr_ind][5];

    else if (ch == '{')
        return Arrr_Tab[currr_ind][6];

    else if (ch == '}')
        return Arrr_Tab[currr_ind][7];

    else if (ch == '(')
        return Arrr_Tab[currr_ind][8];

    else if (ch == ')')
        return Arrr_Tab[currr_ind][9];

    else if (ch == '[')
        return Arrr_Tab[currr_ind][10];

    else if (ch == ']')
        return Arrr_Tab[currr_ind][11];

    else if (ch == '_')
        return Arrr_Tab[currr_ind][12];

    else if (ch == '.')
        return Arrr_Tab[currr_ind][13];

    else if (ch == '=')
        return Arrr_Tab[currr_ind][14];

    else if (ch == '>')
        return Arrr_Tab[currr_ind][15];

    else if (ch == '<')
        return Arrr_Tab[currr_ind][16];

    else if (ch == '&')
        return Arrr_Tab[currr_ind][17];

    else if (ch == '!')
        return Arrr_Tab[currr_ind][18];

    else if (ch == '|')
        return Arrr_Tab[currr_ind][19];

    else if (ch == ':')
        return Arrr_Tab[currr_ind][20];

    else if (ch == '%')
        return Arrr_Tab[currr_ind][21];

    else if (ch == ';')
        return Arrr_Tab[currr_ind][22];

    else if (ch == '#')
        return Arrr_Tab[currr_ind][23];

    else if (ch == ',')
        return Arrr_Tab[currr_ind][24];

    return 0;
}


