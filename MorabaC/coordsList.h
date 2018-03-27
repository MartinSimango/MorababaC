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
int CoordsList__itemExits(const CoordsList* list, COORD_ data);
int CoordsList__addItem(CoordsList*list, COORD_PTR data);
COORD_PTR CoordsList__getCoord(const CoordsList *list, POINT_ point);
int CoordsList__removeItem(CoordsList *list, COORD_ data);
COORD_PTR CoordsList__getElementAt(const CoordsList *list, int pos);
CoordsList * CoordsList__FromCoordList(const CoordsList *list);
void CoordsList__printList(CoordsList *list);

