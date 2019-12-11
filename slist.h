/*

Header file for single linked list class library

*/
#include <string>
class Airport {
public:
    char    code[5];
    double   longitude;
    double   latitude;
		bool operator == (Airport const &airport) {
			if(this->code != airport.code)
				return false;
			else if (this->longitude != airport.longitude)
				return false;
			else if (this->latitude != airport.latitude)
				return false;
			else
				return true;
		}
};

//Airport node for airport linked list
class Node {
	public:
    Node* next;
    Airport airport;
};

//Linked list for airports
class AirportList {
	public:
    int length;
    Node* head;
    AirportList();
    ~AirportList();
    void remove(Airport airport);
		void add(Airport value);				//Adds a new value to the end of this list.

		void clear();					//Removes all elements from this list.

		bool equals(AirportList list);				//Returns true if the two lists contain the same elements in the same order.

		Airport get(int index);				//Returns the element at the specified index in this list.

		void insert(int index, Airport value);		//Inserts the element into this list before the specified index.

		void exchg(int index1, int index2);		//Switches the payload data of specified indexex.

		void swap(int index1, int index2);		//Swaps node located at index1 with node at index2

		bool isEmpty();				//Returns true if this list contains no elements.

		void remove(int index);			//Removes the element at the specified index from this list.

		void set(int index, Airport value);		//Replaces the element at the specified index in this list with a new value.

		int size();					//Returns the number of elements in this list.

		AirportList subList(int start, int length);	//Returns a new list containing elements from a sub-range of this list.

		std::string toString();				//Converts the list to a printable string representation.
};