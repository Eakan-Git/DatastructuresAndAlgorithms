#include <bits/stdc++.h>
using namespace std;

struct Node 
{
    string data;
    Node* yes_ans;
    Node* no_ans;
};
typedef Node* Tree;

void readFile(Tree& Game, fstream& file) 
{
    string input;
    getline(file, input);
    if (input != "#") 
    {
        Game = new Node;
        Game->data = input;
        readFile(Game->yes_ans, file);
        readFile(Game->no_ans, file);
    }
    else
        Game = NULL;
}

void writeFile(Tree& Game, fstream& file) 
{
    if (Game != NULL) 
    {
        file << Game->data << endl;
        writeFile(Game->yes_ans, file);
        writeFile(Game->no_ans, file);
    }
    else
        file << "#" << endl;
}

int menu() 
{
    int choice;
    system("cls");
    cout << "[1] Play game" << endl;
    cout << "[2] Exit game" << endl;
    do
    {
        cout << "Your choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 2);
    cin.ignore();
    system("cls");
    return choice;
}

void add(Tree& Game) 
{
    string input;

    cout << "Can you teach me about that animal? [y/n]: ";
    getline(cin, input);

    if (tolower(input[0]) == 'y') 
    {
        string new_animal, new_data;
        cout << "Enter a new animal follow the form:\ne.g., 'Is it a whale?':\n> ";
        getline(cin, new_animal);
        cout << "\nNow enter a question for which the answer is 'yes' for your new animal,\nand which does not contradict your previous answers:" << endl;
        cout << "e.g. 'Does it has horn on head?'\n";
        cout << "> ";
        getline(cin, new_data);


        Game->yes_ans = new Node;
        Game->yes_ans->no_ans = NULL;
        Game->yes_ans->yes_ans = NULL;

        Game->no_ans = new Node;
        Game->no_ans->no_ans = NULL;
        Game->no_ans->yes_ans = NULL;

        Game->no_ans->data = Game->data;
        
        Game->yes_ans->data = new_animal;  
        Game->data = new_data;

        cout << "\nThank you! I'd learned a lot!\n";
    }
    else
        cout << "Okay, please teach me later.\n";
}

void play(Tree& Game) 
{
    if (Game != NULL) 
    {
        string input;
        cout << Game->data << "[y/n]: ";
        cin.clear();
        getline(cin, input);
        if (tolower(input[0]) == 'y') 
        {
            if (Game->yes_ans == NULL)
                cout << "That was easy!" << endl;
            else
                play(Game->yes_ans);
        }
        else 
        {
            if (Game->no_ans == NULL) 
            {
                cout << "Well, I did not expect that!\n" << endl;
                add(Game);
            }
            else
                play(Game->no_ans);
        }
    }
}


int main() 
{
    Tree Game = NULL;
    fstream file;
    int input;
    do 
    {
        input = menu();
        if (input == 1) 
        {
            file.open("data.txt", ios::in);
            readFile(Game, file);
            file.close();

            play(Game);

            file.open("data.txt", ios::out);
            writeFile(Game, file);
            file.close();
        }
    } while (input == 1);
    return 0;
}