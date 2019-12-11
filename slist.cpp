#include "slist.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
// Initialize the lists management information
AirportList::AirportList() {
    this->length = 0;
    this->head = NULL;
}

// Clear the list management information and release all allocated Nodes
AirportList::~AirportList() {
   Node* current = this->head;
    while(current){
        this->head = current->next;
        this->length -= 1;
		delete current;
		current = this->head;
    }
    cout << "LIST DELETED: " << this->length << endl;
}

//Adds a new value to the end of this list.
void AirportList::add(Airport value){		
	Node* newNode = this->head;
	Node* beforeNode = this->head;
	bool isBeforeNode = false;
	while(newNode) {
		isBeforeNode = true;
		beforeNode = newNode;
		newNode = newNode->next;
	}
	if(isBeforeNode){
		newNode = new Node();
		newNode->airport = value;
		beforeNode->next = newNode;
	}
	else {
		this->head = new Node();
		this->head->airport = value;
	}
	this->length++;
};

//Removes all elements from this list.
void AirportList::clear(){
	Node* current = this->head;
	while(current){
		this->head = current->next;
		this->length -= 1;
		delete current;
		current = this->head;
	}
};			

//Returns true if the two lists contain the same elements in the same order.
bool AirportList::equals(AirportList list) {
	Node* thisCurrent = this->head;
	Node* thatCurrent = list.head;
	while(thisCurrent && thatCurrent) {
		if(thisCurrent==thatCurrent)
			continue;
		else
			return false;
	}
	return true;
}

//Returns the element at the specified index in this list.
Airport AirportList::get(int index) {
	int i = 0;
	Node* current = this->head;
	while(i < index) {
		current = current->next;
		i++;
	}
	return current->airport;
};

//Inserts the element into this list before the specified index.
void AirportList::insert(int index, Airport value) {
	Node* current = this->head->next;
	Node* beforeNode = this->head;
	int i = 1;
	while(i < index) {
		beforeNode = current;
		current = current->next;
		i++;
	}
	Node* newNode;
	newNode->airport = value;
	newNode->next = current;
	beforeNode->next = newNode;
};

//Switches the payload data of specified indexex.
void AirportList::exchg(int index1, int index2){
	int i = 0;
	Node* first = this->head;
	Node* second;
	if(!(index1 == index2)) {
		while(i < index1) {
			first = first->next;
			i++;
		}
		second = first;
		while(i < index2) {
			second = second->next;
			i++;
		}
		Airport temp = first->airport;
		first->airport = second->airport;
		second->airport = temp;
	}
};

//Swaps node located at index1 with node at index2
void AirportList::swap(int index1, int index2) {
	int i = 0;
	Node* beforeFirst = NULL;
	Node* beforeSecond;
	Node* first = this->head->next;
	Node* second;
	while(i < index1) {
		beforeFirst = first;
		first = first->next;
		i++;
	}
	second = first;
	while(i < index2) {
		beforeSecond = second;
		second = second->next;
		i++;
	}
	if(beforeFirst) {
		Node* temp = second;
		beforeFirst->next = second;
		second->next = first->next;
		beforeSecond->next = first;
		first->next = temp->next;
	}
	else{
		Node* temp = second;
		this->head = second;
		second->next = first->next;
		beforeSecond->next = first;
		first->next = temp->next;
	}
};

//Returns true if this list contains no elements.
bool AirportList::isEmpty() {
	if(this->head)
		return true;
	else
		return false;
};

void AirportList::remove(Airport airport) {
	Node* current = this->head;
	Node* previous;
	while(current) {
		previous = current;
		current = current->next;
		if(current->airport.code == airport.code) {
			Node* temp = current;
			current = current->next;
			previous->next = current;
			this->length--;
			delete temp;
			break;
		}
	}
};
//Removes the element at the specified index from this list.
void AirportList::remove(int index){		
	Node* current = this->head;
	if(index == 0) {
		this->head = current->next;
		delete current;
	}
	else {
		Node* beforeNode;
		int i = 0;
		while(i < index) {
			beforeNode = current;
			current = current->next;
			i++;
		}
		beforeNode->next = current->next;
		delete current;
	}
	
};

//Replaces the element at the specified index in this list with a new value.
void AirportList::set(int index, Airport value) {
	int i = 0;
	Node* current = this->head;
	while(i < index) {
		current = current->next;
		i++;
	}
	current->airport = value;
};

//Returns the number of elements in this list.
int AirportList::size() {
	int count = 0;
	Node* current = this->head;
	while(current) {
		current = current->next;
		count++;
	}
	return count;
};

//Returns a new list containing elements from a sub-range of this list.
AirportList AirportList::subList(int start, int length) {
	int i = 0;
	int counter = 0;
	Node* current = this->head;
	AirportList newList;
	while(i < start) {
		current = current->next;
		i++;
	}
	while(counter < length) {
		newList.add(current->airport);
		current = current->next;
		counter++;
	}
	return newList;
};

//Converts the list to a printable string representation.
string AirportList::toString() {
	Node* current = this->head->next;
	stringstream ss("");
	string output = "";
	while(current) {
		ss << current->airport.code << " lat: " << current->airport.latitude << " long: " << current->airport.longitude << endl;
		current = current->next;
	}
	output = ss.str();
	return output;
};