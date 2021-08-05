#include <iostream>
#include <string>
#include <fstream>

struct Tree
{
public:
    std::string data;
    Tree* left;
    Tree* right;

    Tree(std::string str)
        : data(str), left(nullptr), right(nullptr)
    {}

    void split(std::string newData, std::string leftData, std::string rightData)
    {
        data = newData;
        left = new Tree(leftData);
        right = new Tree(rightData);
    }

    void save(std::fstream& stream)
    {
        stream << data;
        if (left == nullptr)
        {
            stream << '*' << std::endl;;
        }
        else
        {
            stream << std::endl;
            left->save(stream);
            right->save(stream);
        }
    }

    Tree(std::fstream& stream) : left(nullptr), right(nullptr)
    {
        std::getline(stream, data);
        if (data.back() == '*')
        {
            data.pop_back();
        }
        else
        {
            left = new Tree(stream);
            right = new Tree(stream);
        }
    }
};

int main()
{
    std::fstream file("f.txt");
    if (!file.is_open()) std::cout << "file screwup!\n";
    Tree* treeHead = new Tree(file);
    file.close();
    std::string lastInput;
    do
    {
        Tree* treePtr = treeHead;
        std::cout << "Think of an animal and then press enter!\n";
        std::getline(std::cin, lastInput);
        
        do
        {
            std::cout << treePtr->data << std::endl;
            std::getline(std::cin, lastInput);
            treePtr = (tolower(lastInput[0]) == 'y') ? treePtr->left : treePtr->right;
        } while (treePtr->left != nullptr);

        std::cout << "Aha! Clearly the animal you thought of is the elusive...\n"
            + treePtr->data + "!\n" + "Amirite or am I right?\n";
        std::getline(std::cin, lastInput);
        if (tolower(lastInput[0]) == 'y')
        {
            std::cout << "In your human face!\n";
        }
        else
        {
            std::cout << "Well then what animal is it??!!!\n";
            std::getline(std::cin, lastInput);
            std::string correctAnimal = lastInput;

            std::cout << "What question would you ask to distinguish " +
                treePtr->data + " from " + correctAnimal + "?\n";
            std::getline(std::cin, lastInput);
            treePtr->split(lastInput, treePtr->data, correctAnimal);

            std::cout << "What would be the answer to your question for the animal you thought of?\n";
            std::getline(std::cin, lastInput);
            if (tolower(lastInput[0]) == 'y') std::swap(treePtr->left, treePtr->right);
            std::cout << "I will learn from this...\n";
        }

        std::cout << "Care to play again, human?\n";
        std::getline(std::cin, lastInput);
    } while (tolower(lastInput[0]) == 'y');

    file.open("History.txt");
    treeHead->save(file);
    file.close();
}