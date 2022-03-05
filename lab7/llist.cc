/************************************************************************
     This is the implementation file for the LList class which is a 
container based on a doubly linked list. The student is required to 
write the rearview function as well as the copy constructor. Note that 
the copy constructor will not be able to use the add function to produce 
a true copy because of the strange behavior of the add function, which 
treats all numbers divisible by five differently than other numbers.
	John Dolan		Ohio University		Spring 2018
************************************************************************/

//Hunter Stout - 3/4/2022

#include <iostream>
#include "llist.h"
using namespace std;

//################ Constructors & Big 3 ###############

//Node constructor
node::node(int d, node* p, node* n){
	data_field = d;
	nextptr = n;
	previousptr = p;
}

//Llist constructor
LList::LList(){
	head = tail = NULL;
	nodecount = 0;
}

//LList copy constructor
LList::LList(const LList& other) {
	if (other.head == NULL) { //For empty list.
		head = tail = NULL;
	}
	else { //Creates duplicate list.
		head = new node (other.head -> data(), other.head -> next(), other.head -> previous());
		tail = head;
		node *ph_cursor = other.head -> next();

		while (ph_cursor != NULL) {
			tail -> set_next(new node(ph_cursor -> data(), tail, NULL));
			tail = tail -> next();
			ph_cursor = ph_cursor -> next();
		}
	}
}

//Llist Deconstructor
LList::~LList(){
	node* rmptr;
	while(head != NULL){
		rmptr = head;
		head = head -> next();
		delete rmptr;
	}
}

//################## Llist functions ##################

void LList::frontview()const{
    node* cursor = head;
    while (cursor != NULL){
		cout << cursor -> data() << "  ";
		cursor = cursor -> next();
    }
	cout << endl;
}

//The student is required to write the implementation of this function
void LList::rearview()const{ //:D
    node* cursor = tail;
    while (cursor != NULL){
		cout << cursor -> data() << "  ";
		cursor = cursor -> previous();
    }
	cout << endl;
}


void LList::add_item(int item){
    if(head == NULL){
		head = tail = new node(item);
		nodecount++;
    }
    else if(item % 5 == 0 && nodecount > 3){
		int i = 0;
		node* cursor = head;
		while(i < nodecount / 2){
			cursor = cursor -> next();
			i++;
		}
		//Bad news:
		//cursor -> previous() -> set_next(new node(item, cursor -> next(), cursor -> previous()));

		//Update: new pointer, & try this again.
		node *yay = new node(item, cursor -> previous(), cursor); //:D
		cursor -> previous() -> set_next(yay);
		cursor -> set_previous(yay);

		nodecount++;
    }
    else{
		tail -> set_next(new node(item, tail));
		tail = tail -> next();
		nodecount++;
    }
}