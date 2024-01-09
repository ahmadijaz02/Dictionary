//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <iomanip>
//#include <windows.h>
//using namespace std;
//struct node
//{
//	string word;
//	string meaning;
//	node* next;
//};
//class login {
//private:
//	string id;
//	string user_password, user_name, user_email;
//public:
//	login()
//	{
//		id = "1234";
//		user_password = "abc";
//		user_email = "f223343@cfd.nu.edu.pk";
//		user_name = "22F-3414";
//		ofstream writeData("LoginClass.txt");
//		writeData << id << " " << user_password << " " << user_email << " " << user_name;
//		writeData.close();
//	}
//	~login() {};
//	bool check(string ad_id, string pass) {
//		ifstream getData("LoginClass.txt");
//		if (getData.is_open())
//			getData >> id >> user_password;
//		if ((user_password == pass) && (id == ad_id))
//			return true;
//		else
//			return false;
//	}
//};
//class Dictionary
//{
//public:
//	static const int size = 97;
//	node* arr[size];
//	Dictionary()
//	{
//		for (int i = 0; i < size; i++)
//		{
//			arr[i] = NULL;
//		}
//	}
//	node* createNode(string w, string m)
//	{
//		node* ptr = new node();
//		ptr->word = w;
//		ptr->meaning = m;
//		ptr->next = NULL;
//		return ptr;
//	}
//	node* createNode1(string w)
//	{
//		node* ptr = new node();
//		ptr->word = w;
//		ptr->next = NULL;
//		return ptr;
//	}
//	int hashIndex(int key)
//	{
//		return key % size;
//	}
//	void insertion(string w, string m) {
//		if (search(w) == true)
//		{
//			cout << setw(95) << "Word is already is dictionary" << endl;
//		}
//		else
//		{
//			insert(w, m);
//			updateFile();
//			cout << setw(95) << "Word inserted successfully." << endl;
//
//		}
//	}
//	void insert(string w, string m)
//	{
//		node* ptr = createNode(w, m);
//		int key = static_cast<int>(ptr->word[0]);
//		int i = hashIndex(key);
//
//		if (arr[i] == NULL || arr[i]->word >= ptr->word)
//		{
//			ptr->next = arr[i];
//			arr[i] = ptr;
//		}
//		else
//		{
//			node* newOne = arr[i];
//			while (newOne->next != NULL && newOne->next->word < ptr->word)
//			{
//				newOne = newOne->next;
//			}
//			ptr->next = newOne->next;
//			newOne->next = ptr;
//		}
//	}
//	bool search(string w)
//	{
//		int key = static_cast<int>(w[0]);
//		int i = hashIndex(key);
//		node* newnode = arr[i];
//		while (newnode != NULL)
//		{
//			if (newnode->word == w)
//			{
//
//				return true;
//
//			}
//			newnode = newnode->next;
//		}
//		return false;
//	}
//	void updateword(string w)
//	{
//		if (search(w))
//		{
//			cout << "word found" << endl;
//			string m;
//			cout << "enter new meaning of searched word:" << endl;
//			cin >> m;
//			deletion(w);
//			insertion(w, m);
//		}
//
//	}
//	bool deletion(string w)
//	{
//		int key = static_cast<int>(w[0]);
//		int i = hashIndex(key);
//		node* ptr = arr[i];
//		node* prev = NULL;
//
//		while (ptr != NULL && ptr->word != w) {
//			prev = ptr;
//			ptr = ptr->next;
//		}
//
//		if (ptr != NULL) {
//			if (prev != NULL) {
//				prev->next = ptr->next;
//			}
//			else {
//				arr[i] = ptr->next;
//			}
//
//			delete ptr;
//			updateFile();
//
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//
//	void updateFile() {
//		ifstream inputFile("Dictionary.txt");
//		ofstream outputFile("newDictionary.txt", ios::out);
//
//		for (int i = 0; i < size; i++)
//		{
//			node* current = arr[i];
//			while (current != NULL)
//			{
//				outputFile << current->word << "    " << current->meaning << " " << endl;;
//				current = current->next;
//			}
//		}
//		outputFile.close();
//		inputFile.close();
//		remove("Dictionary.txt");
//		rename("newDictionary.txt", "Dictionary.txt");
//	}
//	void loadDictionary()
//	{
//		string word, meaning;
//		ifstream file("Dictionary.txt");
//		if (!file.is_open())
//		{
//			cout << "Error: Could not open file Dictionary.txt" << endl;
//			return;
//		}
//		while (file >> word >> meaning)
//		{
//			insert(word, meaning);
//		}
//		cout << "Data loaded into chained hash table successfully." << endl;
//		file.close();
//	}
//	string meaning(string w)
//	{
//		int key = static_cast<int>(w[0]);
//		int i = hashIndex(key);
//		node* newnode = arr[i];
//		while (newnode != NULL)
//		{
//			if (newnode->word == w)
//			{
//
//				return newnode->meaning;
//
//			}
//			newnode = newnode->next;
//		}
//	}
//	string suggestion(string w)
//	{
//		int key = static_cast<int>(w[0]);
//		int i = hashIndex(key);
//		node* newOne = arr[i];
//		while (newOne != NULL && newOne->word < w)
//		{
//			newOne = newOne->next;
//		}
//
//		int count = 0;
//		string suggestions = "";
//
//		while (newOne != NULL && count < 10)
//		{
//			suggestions += newOne->word + "\n";
//			newOne = newOne->next;
//			count++;
//		}
//
//		return suggestions;
//	}
//
//
//};
//int main() {
//	system("color 85");
//	bool flag = false;
//	int count = 1;
//	char opt;
//	string pass, id;
//	login objLog;
//
//	cout << endl << endl;
//	cout << setw(70) << "Login to your account" << endl << endl;
//	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
//
//	do {
//		cout << endl;
//		cout << "Please Enter the Admin ID: ";
//		getline(cin, id);
//		cout << "Please Enter the Admin Password: ";
//		getline(cin, pass);
//		flag = objLog.check(id, pass);
//
//		if (!flag) {
//			cout << "Wrong username or password. You have " << 5 - count << " Attempts Remaining" << endl;
//			count++;
//
//			if (count > 5) {
//				cout << setw(70) << "Account is Locked Permanently :-(" << endl;
//				system("pause");
//				return 0;
//			}
//		}
//		else {
//			cout << "You Successfully Login" << endl;
//			Sleep(1000);
//			system("cls");
//
//			Dictionary dictionary;
//			cout << "Loading dictionary from file..." << endl;
//			dictionary.loadDictionary();
//			dictionary.updateFile();
//			Sleep(1000);
//			system("cls");
//
//			int choice, choice1;
//			string word, meaning;
//
//			do {
//				cout << setw(95) << "------ Dictionary Menu ------" << endl;
//				cout << setw(91) << "1. Insert a word" << endl;
//				cout << setw(95) << "2. Search for a word" << endl;
//				cout << setw(85) << "3. Log out" << endl;
//				cout << setw(91) << "Enter your choice: ";
//				cin >> choice;
//
//				switch (choice) {
//				case 1: {
//					Sleep(1000);
//					system("cls");
//					cout << setw(95) << "Enter the word to insert: ";
//					cin >> word;
//					cout << setw(91) << "Enter the meaning: ";
//					cin >> meaning;
//					dictionary.insertion(word, meaning);
//				}
//					  break;
//
//				case 2: {
//					Sleep(1000);
//					system("cls");
//					do {
//						cout << setw(95) << "1. Search for a word" << endl;
//						cout << setw(91) << "2. Delete a word" << endl;
//						cout << setw(91) << "3. Update a word" << endl;
//						cout << setw(94) << "4. Show suggestions" << endl;
//						cout << setw(85) << "5. Log out" << endl;
//						cout << setw(95) << "Enter your choice: ";
//						cin >> choice1;
//
//						switch (choice1) {
//						case 1: {
//							Sleep(1000);
//							system("cls");
//							cout << setw(95) << "Enter the word to search: ";
//							cin >> word;
//
//							if (dictionary.search(word)) {
//								cout << setw(85) << "Meaning: " << dictionary.meaning(word) << endl;
//							}
//							else {
//								cout << setw(95) << "Word not found." << endl;
//							}
//						}
//							  break;
//
//						case 2: {
//							Sleep(1000);
//							system("cls");
//							cout << setw(95) << "Enter the word to delete: ";
//							cin >> word;
//
//							if (dictionary.deletion(word)) {
//								cout << setw(95) << "Word is deleted." << endl;
//							}
//							else {
//								cout << setw(95) << "Word is not deleted." << endl;
//							}
//						}
//							  break;
//
//						case 3:
//						{
//							Sleep(1000);
//							system("cls");
//							string word;
//							cout << setw(95) << "Enter the word to update: ";
//							cin >> word;
//							dictionary.updateword(word);
//						}
//						break;
//
//						case 4:
//						{
//							Sleep(1000);
//							system("cls");
//							string w;
//							cout << setw(95) << "Enter word: ";
//							cin >> w;
//							string suggestions = dictionary.suggestion(w);
//
//							if (suggestions.empty()) {
//								cout << setw(95) << "No suggestions found." << endl;
//							}
//							else {
//								cout << "Suggestions:" << endl << suggestions << endl;
//							}
//						}
//						break;
//						case 5:
//						{
//							Sleep(1000);
//							system("cls");
//							cout << setw(55) << "Exiting the program." << endl;
//						}
//						break;
//						default:
//							cout << setw(55) << "Invalid choice. Please enter a valid option." << endl;
//							break;
//						}
//						cout << endl << endl;
//						cout << "Press Y to Return to Dashboard" << endl;
//						cin >> opt;
//						Sleep(250);
//						system("cls");
//					} while (opt == 'Y' || opt == 'y');
//
//				}
//					  break;
//
//				case 3:
//				{
//					Sleep(1000);
//					system("cls");
//					cout << setw(55) << "Exiting the program." << endl;
//				}
//				break;
//
//				default:
//					cout << setw(55) << "Invalid choice. Please enter a valid option." << endl;
//					break;
//				}
//				cout << endl << endl;
//				cout << "Press Y to Return to Dashboard" << endl;
//				cin >> opt;
//				Sleep(250);
//				system("cls");
//			} while (opt == 'Y' || opt == 'y');
//
//		}
//	} while (!(flag) && count <= 5);
//
//	system("pause");
//	return 0;
//}