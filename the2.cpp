#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "strutils.h"

#define LINES "---" //MACROS

using namespace std;

struct Node {
	string name;
	double itemPrice;
	double totalPrice;
	int quantity;
	Node* next = NULL;
	Node* previous = NULL;
	Node(string& itemname, double& price, int& itemnumber, double totalprice)
		:name(itemname), itemPrice(price), totalPrice(totalprice), quantity(itemnumber)
	{}
};

void printEmptyList();
void getItem(Node*& header, string& itemName, int& quantity, double& estimatedPrice);
void modifyString(string& text);

void Menu(string &choice) {
	string input;
	cout << "This program helps Alan with gathering the shopping list for his psychedelic breakfast." << endl;
	cout << LINES << endl << "MENU" << endl;
	cout << "1. Add item to the shopping list" << endl;
	cout << "2. Delete item from the shopping list" << endl;
	cout << "3. Print the shopping list" << endl;
	cout << "4. Print the shopping list in reverse order" << endl;
	cout << "5. Show total estimated cost of the list" << endl;
	cout << "6. Exit" << endl;
	cout << LINES << endl;
	
	cout << "Enter your choice: ";
	cin >> choice;
	cout << "---" << endl;
}

void InsertionSort(Node* &header, Node* &newnode,const int& itemcount) {
	Node* temp = header;
	Node* behind = header;
	if (newnode->totalPrice < header->totalPrice) {
		temp = header->next;
		newnode->next = temp;
		newnode->previous = header->previous;
		header = newnode;
	}
	int counter = 0;
	while (newnode->totalPrice > temp->totalPrice && counter < itemcount) {
		behind = temp;
		temp = temp->next;
		counter++;
	}
	if (counter >= itemcount) {
		Node* lastItem = header->previous;
		lastItem->next = newnode;
		header->previous = newnode;
		newnode->next = header;
		newnode->previous = lastItem;
	}
	else {
		behind->next = newnode;
		newnode->next = temp;
	}
	

}

////MAIN FUNCTIONS
void addItem(Node* &header,int &itemCount) {
	string itemName; int quantity; double estimatedPrice;
	if (header == NULL) { //FIRST ADD 
		getItem(header,itemName,quantity,estimatedPrice);
		header->next = header;
		
		header->previous = header;
		itemCount++;
	}
	else {
		Node* ptr = header;
		Node* newNode;
		cout << "Enter name for the item: ";
		cin.ignore();
		getline(cin, itemName);		ToUpper(itemName);
		modifyString(itemName);
		while (ptr->name != itemName && ptr->next != header) {
			ptr = ptr->next;
		}
		if (ptr->name == itemName) {
			//DONT ASK PRICE
			cout << "Enter quantity for the item: ";
			cin >> quantity;
			cout << LINES << endl;
			ptr->quantity += quantity;
			ptr->totalPrice += (ptr->itemPrice * quantity);
			cout << "The quantity of the item " << ptr->name << " is increased by " << quantity << ". The Final quantity is " << ptr->quantity << endl;
			cout << LINES << endl;
		}
		else {
			cout << "Enter quantity for the item: ";
			cin >> quantity;
			cout << "Enter the estimated price of the item: ";
			cin >> estimatedPrice;
			cout << LINES << endl;
			newNode = new Node(itemName, estimatedPrice, quantity, (quantity * estimatedPrice));
			itemCount++;
			InsertionSort(header, newNode, itemCount);
			cout << "The item " << itemName << " of quantity " << quantity << " is added to the list." << endl;
			cout << LINES << endl;
			
		}
	}
}


void getItem(Node* &header, string& itemName, int& quantity, double& estimatedPrice) {

	cout << "Enter name for the item: ";
	cin.ignore();
	getline(cin, itemName);		ToUpper(itemName);
	modifyString(itemName);
	cout << "Enter quantity for the item: ";
	cin >> quantity;
	cout << "Enter the estimated price of the item: ";
	cin >> estimatedPrice;
	cout << LINES << endl;
	header = new Node(itemName, estimatedPrice, quantity, (quantity * estimatedPrice));
	cout << "The item " << itemName << " of quantity " << quantity << " is added to the list." << endl;
	cout << LINES << endl;
	
}

void deleteItem(Node* &header, int &itemCount){
	string itemname;
	cout << "Enter an item name to delete from the list: ";
	cin.ignore();
	getline(cin, itemname);		ToUpper(itemname);
	modifyString(itemname);
	Node* temp = header;
	if (itemname == header->name) {
		if (itemCount == 1) {
			delete header;
			header = NULL;
			cout << itemname << " was succesfully deleted from the shopping cart!" << endl;
		}
		else {
			Node* head_prev = header->previous;
			header = header->next;
			delete temp;
			header->previous = head_prev;
			header->previous->next = header;
			cout << itemname << " was succesfully deleted from the shopping cart!" << endl;
	

		}
		
		itemCount--;
	}
	else if (itemname == header->previous->name) {
		Node* ptr = header->previous;
		Node* lastitem = ptr->previous;
		delete ptr;
		lastitem->next = header;
		header->previous = lastitem;
		cout << itemname << " was succesfully deleted from the shopping cart!" << endl;
		itemCount--;

	}
	
	else {
		Node* behind;
		do {
			behind = temp;
			temp = temp->next;
		} while (temp != header && temp->name != itemname);
		if (temp->name == itemname) {

			Node* nextone = temp->next;
			delete temp;
			cout << nextone->name << endl;
			behind->next = nextone;
			itemCount--;
			cout << itemname << " was sucessfully deleted from the shopping cart!" << endl;
		}
		else {
			cout << "There is no item name " << itemname << endl;
		}
	}
	
}
void displayList(Node* &header, const int &itemCount){
	if (itemCount == 0) {
		printEmptyList();
	}
	else {
		Node* temp = header;
	
		if (header->next == header) {
			cout << "Item: " << header->name << endl;
			cout << "Quantity: " << header->quantity << endl;
			cout << "Est.Price: " << header->itemPrice << endl;
			cout << LINES << endl;
		}
		else {
			do {
				cout << "Item: " << temp->name << endl;
				cout << "Quantity: " << temp->quantity << endl;
				cout << "Est.Price: " << temp->itemPrice << endl;
				cout << LINES << endl;
				temp = temp->next;
			}while (temp != header);

		}
	}
	
	
}
void displayReverse(vector<Node*> &myNodeList, Node* &header,const int &itemCount){
	if (itemCount == 0) {
		printEmptyList();
	}
	else {
		Node* temp = header;
		do {
			myNodeList.push_back(temp);
			temp = temp->next;
		} while (temp != header);
		for (int i = myNodeList.size() - 1; i >= 0; i--) {
			cout << "Item: " << myNodeList[i]->name << endl;
			cout << "Quantity: " << myNodeList[i]->quantity << endl;
			cout << "Est.Price: " << myNodeList[i]->itemPrice << endl;
			cout << LINES << endl;
		}
	}
}
string totalEstimatedCost(Node* &header,const int &itemCount){
	double result = 0;
	Node* temp = header;
	if (itemCount != 0) {
	do {
		result += temp->totalPrice;
		temp = temp->next;
	} while (temp != header);
	}

	string text = "The total estimated price of " + tostring(itemCount) + " kinds of item is: " + tostring(result) + "\n" + LINES + "\n";
	return text;
}
////


////OTHER FUNCTÝONS
void printEmptyList() {
	cout << "The shopping list is empty!" << endl;
	cout << LINES << endl;
}

void modifyString(string& text) {
	string splitedtext;
	istringstream splited(text);
	while (splited >> text) {
		splitedtext += (text + " ");
	}
	text = splitedtext.substr(0, splitedtext.length() - 1);
}



int main() {
	int itemCount = 0;
	Node* header = NULL;
	vector<Node*> myNodeList;
	string choice;
	Menu(choice);

	while (choice != "6") {

		//MAIN
		if (choice == "1") {  //add item
			addItem(header,itemCount);
		}
		else if (choice == "2") { // delete item
			deleteItem(header,itemCount);
		}
		else if (choice == "3") { // print the list
			displayList(header,itemCount);
		}
		else if (choice == "4") { // print the list in reverse order
			displayReverse(myNodeList,header,itemCount);
		}
		else if (choice == "5") { // print the total estimated cost
			string text = totalEstimatedCost(header,itemCount);
			cout << text;
		}
		else {
			cout << "This is not a valid option!" << endl;
			cout << LINES << endl;
		}
		Menu(choice);
	}
	cout << "Clearing the shopping list..." << endl;
	cout << "Exiting the program..." << endl;
	return 0;
}