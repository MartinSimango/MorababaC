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
typedef struct LinkedList CoordsList;


//LIST FUNCTIONS
void init__CoordsList(CoordsList *list);
int CoordsList__isEmpty(const CoordsList * list);
int CoordsList__itemExits(const CoordsList* list, struct Coords data);
int CoordsList__addItem(CoordsList*list, struct Coords * data);
COORD_PTR CoordsList__getCoord(const CoordsList *list, struct Point point);
int CoordsList__removeItem(CoordsList *list, struct Coords data);
COORD_PTR CoordsList__getElementAt(const CoordsList *list, int pos);
void CoordsList__printList(CoordsList *list);
