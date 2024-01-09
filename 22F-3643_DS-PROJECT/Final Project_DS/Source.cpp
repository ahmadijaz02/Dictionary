#include <iostream>
#include <fstream>
#include<Windows.h>
#include<cstdio>
#include <algorithm>
#include<iomanip>
#include<string>

using namespace std;

class login 
{
private:
    string id;
    string user_password, user_name, user_email;
public:
    login()
    {
        id = "3623";
        user_password = "Ahmad_Ijaz";
        user_email = "f223643@cfd.nu.edu.pk";
        user_name = "Bisam Ahmad";
        ofstream writeData("LoginClass.txt");
        writeData << id << " " << user_password << " " << user_email << " " << user_name;
        writeData.close();
    }
    ~login() {};
    bool check(string ad_id, string pass) 
    {
        ifstream getData("LoginClass.txt");
        if (getData.is_open())
        {
            getData >> id >> user_password;
        }
            
        if ((user_password == pass) && (id == ad_id))
        {
            return true;
        }
           
        else
        {
            return false;
        }
            
    }
};


class AVLNode
{
public:
    string word;
    string meaning;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const string& word, const string& mean) : word(word), meaning(mean), left(NULL), right(NULL), height(1) {}
};

class AVLDictionary
{
private:
    AVLNode* root;
    bool found = false; // that control if the word is found or not! and use it in specific.
   // bool found1 = false;
public:
    int count = 1; // that stops bool to be true in insertion from file.
    int count1 = 1; // tha controlls suggestion count to be 10.
    AVLDictionary() : root(NULL) {}

    int getHeight(AVLNode* node)
    {
        return (node) ? node->height : 0;
    }

    int getBalanceFactor(AVLNode* node)
    {
        return (node) ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y)
    {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x)
    {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    AVLNode* insert(AVLNode* root, const string& word, const string& meaning)
    {
        if (root == NULL)
        {
            return new AVLNode(word, meaning);
        }

        if (word < root->word)
        {
            root->left = insert(root->left, word, meaning);
        }
        else if (word > root->word)
        {
            root->right = insert(root->right, word, meaning);
        }
        else
        {
            //cout << "Word already exists!" << endl;
            if (count != 1)
            {
                found = true;
            } 
            return root;
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);
        if (balance > 1 && word < root->left->word)
        {
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && word > root->right->word)
        {
            return rotateLeft(root);
        }

        // Left Right Case
        if (balance > 1 && word > root->left->word)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Left Case
        if (balance < -1 && word < root->right->word)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    AVLNode* search(AVLNode* root, const string& word)
    {
        if (root == NULL || root->word == word)
        {
            return root;
        }

        if (word < root->word)
        {
            return search(root->left, word);
        }

        return search(root->right, word);
    }

    AVLNode* minValueNode(AVLNode* node)
    {
        AVLNode* current = node;
        while (current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

    AVLNode* deleteNode(AVLNode* root, const string& word)
    {
        if (root == NULL)
        {
            return root;
        }

        if (word < root->word)
        {
            root->left = deleteNode(root->left, word);
        }
        else if (word > root->word)
        {
            root->right = deleteNode(root->right, word);
        }
        else
        {
            if (root->left == NULL || root->right == NULL)
            {
                AVLNode* temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                {
                    *root = *temp;
                }
                found = true;
                delete temp;
            }
            else
            {
                AVLNode* temp = minValueNode(root->right);
                root->word = temp->word;
                root->right = deleteNode(root->right, temp->word);
            }
        }

        if (root == NULL)
        {
            return root;
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
        {
            return rotateRight(root);
        }

        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
        {
            return rotateLeft(root);
        }

        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void loadDictionary(const string& filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening the file: " << filename << endl;
            return;
        }

        cout << "Dictionary is loading ";  Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ." << endl;

        string word, meaning;
        while (file >> word >> meaning)
        {
            root = insert(root, word, meaning);
        }
        cout << "Dictionary loaded successfully!" << endl; Sleep(1500);
        file.close();
    }

    void insert_word(const string& word, const string& meaning)
    {
        root = insert(root, word, meaning);
        cout << endl << endl;
        if (found)
        {
            cout << "Word already exists!" << endl << endl;
        }
        else
        {
            cout << "Inserting "; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ." << endl << endl;
            cout << "Word added successfully." << endl; Sleep(1500);
            cout << endl;
        }
        found = false;
        cout << endl;
    }

    void search_word(const string& word)
    {
        char ch;
        string meaning;
        AVLNode* result = search(root, word);
        cout << endl;
        cout << "Searching "; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ." << endl << endl;
        if (result)
        {
            cout << "Word Found:" << endl; Sleep(1000);
            cout << "Word = " << result->word << "  , Meaning = " << result->meaning << endl << endl;
        }
        else
        {
            cout << "Word not found in the dictionary." << endl << endl;
            Sleep(1500);
            cout << "Suggested Words:" << endl;
            suggestWords(word);
            cout << "Do you want to add " << word << " ? (y / n) = ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                cout << endl;
                cout << "Enter meaning = ";
                cin >> meaning;
                insert_word(word, meaning);
            }
        }
        cout << endl;
    }

    AVLNode* update_mean(AVLNode* root, string word1, string word2) 
    {
        if (root == NULL)
        {
            return root;
        }

        if (word1 < root->word)
        {
            root->left = update_mean(root->left, word1, word2);
        }    
        else if (word1 > root->word)
        {
            root->right = update_mean(root->right, word1, word2);
        }     
        else 
        {
            found = true;
            root->meaning = word2;
            root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        }

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
        {
            return rotateRight(root);
        }
        if (balance > 1 && getBalanceFactor(root->left) < 0) 
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) <= 0)
        {
            return rotateLeft(root);
        }
        if (balance < -1 && getBalanceFactor(root->right) > 0) 
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    AVLNode* update_word(AVLNode* root, string word1, string word2)
    {
        if (root == NULL)
        {
            return root;
        }

        if (word1 < root->word)
        {
            root->left = update_word(root->left, word1, word2);
        }
        else if (word1 > root->word)
        {
            root->right = update_word(root->right, word1, word2);
        }
        else
        {
            found = true;
            root->word = word2;
            root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        }

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
        {
            return rotateRight(root);
        }
        if (balance > 1 && getBalanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) <= 0)
        {
            return rotateLeft(root);
        }
        if (balance < -1 && getBalanceFactor(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void updateWord()
    {
        string word1 = " ", word2 = " ", meaning = " ";
        char choice = '0';
        char ch;

        cout << "To update Word Press -> 1" << endl;
        cout << "To update Meaning Press -> 2" << endl << endl;
        
        do
        {
            cout << "Enter choice = ";
            cin >> choice;
            if (choice != '1')
            {
                cout << "Invalid choice!" << endl << endl;
            }
            else if (choice != '2')
            {
                cout << "Invalid choice!" << endl << endl;
            }
        } while (choice != '1' && choice != '2');
        
        if (choice == '1')
        {
            cout << endl;
            cout << "Enter Word to Update = ";
            cin >> word1;
            cout << "Enter Word to update with = ";
            cin >> word2;
            root = update_word(root, word1, word2);
        }
        else if (choice == '2')
        {
            cout << endl;
            cout << "Enter Word to Update Meaning = ";
            cin >> word1;
            cout << "Enter Meaning to update with = ";
            cin >> word2;
            root = update_mean(root, word1, word2);
        }
        cout << endl;
        cout << "Searching "; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ." << endl << endl;
        if (found)
        {
            cout << "Word Found!"; Sleep(1500); cout << endl << endl;
            cout << "Updating "; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ." << endl << endl;
            cout << "Word Updated successfully." << endl; Sleep(1500);
        }
        else
        {
            cout << endl;
            cout << "Word not found in the dictionary." << endl << endl;
            Sleep(1500);
            cout << "Suggested Words:" << endl;
            suggestWords(word1);
            cout << "Do you want to add " << word1 << " ? (y / n) = ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                cout << endl;
                cout << "Enter meaning = ";
                cin >> meaning;
                insert_word(word1, meaning);
            }
        }
        found = false;
        cout << endl;
    }

    void delete_word(const string& word)
    {
        char ch;
        string meaning;
        root = deleteNode(root, word);
        cout << endl << endl;
        cout << "Searching "; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ." << endl << endl;
        if (found)
        {
            cout << "Word Found!"; Sleep(1500); cout << endl << endl;
            cout << "Deleting "; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ."; Sleep(650); cout << " ." << endl << endl;
            cout << "Word Deleted successfully." << endl; Sleep(1500);
        }
        else
        {
            cout << "Word not found in the dictionary." << endl << endl;
            Sleep(1500);
            cout << "Suggested Words:" << endl;
            suggestWords(word);
            cout << "Do you want to add " << word << " ? (y / n) = ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                cout << endl;
                cout << "Enter meaning = ";
                cin >> meaning;
                insert_word(word, meaning);
            }
        }
        found = false;
       
        cout << endl;
    }

    void inorder_traversal(AVLNode* root)
    {
        if (root != NULL)
        {
            inorder_traversal(root->left);
            cout << "Word = " << root->word << " \t\t Meaning = " << root->meaning << endl;
            inorder_traversal(root->right);
        }
    }

    void inorder_traversal()
    {
        inorder_traversal(root);
        cout << endl;
    }

    void destroy_tree(AVLNode* root)
    {
        if (root)
        {
            destroy_tree(root->left);
            destroy_tree(root->right);
            delete root;
        }
    }

    void update_file(AVLNode*& root)
    {
        ofstream outFile("updatedfile.txt", ios::app);
        if (!outFile)
        {
            cout << "Error opening the file for writing." << endl;
        }
        else if (root != NULL)
        {
            update_file(root->left);
            outFile << root->word << " \t\t " << root->meaning << endl;
            update_file(root->right);
        }
        outFile.close();
        remove("Dictionary.txt");
        rename("updatedfile.txt", "Dictionary.txt");
    }

    void update_file()
    {
        update_file(root);
        cout << endl;
    }

    void menu_box()
    {
        cout << setw(70) << "-----------------------------------------" << endl;
        cout << setw(30) << "|" << setw(40) << "|" << endl;
        cout << setw(30) << "|" << setw(40) << "|" << endl;
        cout << setw(30) << "|" << setw(5) << "\t   WELCOME TO FAST DICTIONARY" << setw(9) << "|" << endl;
        cout << setw(30) << "|" << setw(40) << "|" << endl;
        cout << setw(30) << "|" << setw(40) << "|" << endl;
        cout << setw(70) << "-----------------------------------------" << endl;
    }

    void displaySuggestions(AVLNode* node, string prefix)
    {
        if (node != NULL)
        {
            displaySuggestions(node->left, prefix);
            
            if (node->word.find(prefix) == 0) 
            {
                if (count1 <= 10)
                {
                    cout << count1 << "- " << node->word << endl;
                    count1++;
                }
                
            }

            displaySuggestions(node->right, prefix);
        }
    }

    void suggestWords(string prefix) 
    {
        displaySuggestions(root, prefix);
        count1 = 1;
    }

    ~AVLDictionary()
    {
        destroy_tree(root);
    }

};

int main()
{
    system("color F0");
    AVLDictionary obj;
    login objLog;
    bool flag = false;
    int count = 1;
    char opt;
    string pass, id;
    obj.menu_box();
    cout << endl;
    cout << "Please Login to your account!" << endl;
    cout << endl;
    do
    {
        cout << "Please Enter the Admin ID = ";
        getline(cin, id);
        cout << "Please Enter the Admin Password = ";
        getline(cin, pass);
        flag = objLog.check(id, pass);

        if (!flag) 
        {
            cout << "Wrong username or password. You have " << 5 - count << " Attempts Remaining" << endl;
            count++;

            if (count > 5) 
            {
                cout << "Account is Locked Permanently :) " << endl << endl;;
                system("pause");
                return 0;
            }
        }
        else
        {
            cout << "You Successfully Login" << endl;
            Sleep(1000);
            system("cls");

        }
    } while (!flag);
    

    
    obj.loadDictionary("Dictionary.txt");
    system("cls");
    obj.menu_box();
    cout << endl << endl;
    char choice;
    char ch;
    string word;
    string mean;
    obj.count = 2;
    do
    {
        system("cls");
        obj.menu_box();
        cout << endl << endl;
        cout << "Menu:" << endl;
        cout << "1. Add Word" << endl;
        cout << "2. Search Word" << endl;
        cout << "3. Delete Word" << endl;
        cout << "4. Update Word" << endl;
        cout << "5. Display" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice = ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            system("cls");
            obj.menu_box();
            cout << endl << endl;
            cout << "Add Word to Dictionary:" << endl << endl;
            cout << "Enter the name = ";
            cin >> word;
            cout << "Enter Meaning = ";
            cin >> mean;
            obj.insert_word(word, mean);
            cout << "To go to menu press 'y' = ";
            cin >> ch;
            break;
        case '2':
            system("cls");
            obj.menu_box();
            cout << endl << endl;
            cout << "Search Word in Dictionary:" << endl << endl;
            cout << "Enter the name = ";
            cin >> word;
            obj.search_word(word);
            cout << "To go to menu press 'y' = ";
            cin >> ch;
            break;
        case '3':
            system("cls");
            obj.menu_box();
            cout << endl << endl;
            cout << "Delete Word from Dictionary:" << endl << endl;
            cout << "Enter the name = ";
            cin >> word;
            obj.delete_word(word);
            cout << "To go to menu press 'y' = ";
            cin >> ch;
            break;
        case '4':
            system("cls");
            obj.menu_box();
            cout << endl << endl;
            cout << "Update Word in Dictionary:" << endl << endl;
            obj.updateWord();
            cout << "To go to menu press 'y' = ";
            cin >> ch;
            break;
        case '5':
            system("cls");
            obj.menu_box();
            cout << endl << endl;
            obj.inorder_traversal();
            cout << "To go to menu press 'y' = ";
            cin >> ch;
            break;
        case '6':
            system("cls");
            obj.menu_box();
            cout << endl << endl;
            obj.update_file();
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            Sleep(1000);
        }
        cout << endl;
    } while (choice != '6');

    system("pause");
    return 0;
}