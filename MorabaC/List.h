#pragma once
//LINKED LIST STRUCTURE
#include "gameStructure.h"

struct Node {
	struct Node * next;
	struct Coords *data;
};
typedef struct Node Node;
struct LinkedList {
	Node * head;
	Node *tail;
	int length;
};
typedef struct LinkedList List;


//LIST FUNCTIONS
void initList(List *list);
int isEmpty(List * list);
int isEqual(struct Coords data, struct Coords dataToBeCompared);
int itemExits(List* list, struct Coords data);
int addItem(List*list, struct Coords * data);
struct Coords * getCoords(List *list, struct Point point);
int removeItem(List *list, struct Coords data);
struct Coords * getElementAt(List *list, int pos);
void printList(List *list);
