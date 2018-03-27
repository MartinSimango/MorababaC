#include "stdafx.h"

void init__CoordsList(CoordsList *list) {
	
	list->head = 0;
	list->tail = 0;
	list->length = 0;
	
}
int CoordsList__isEmpty(const CoordsList * list) {
	
	return list->head == 0;

}

int CoordsList__itemExits(const CoordsList* list, COORD_ data) {

	for (Node *p = list->head; p != 0; p = p->next) {

		if (Coords__isEqual(data, *(p->data))) {
			
			return 1;
		}

	}
	return 0;

}

int CoordsList__addItem(CoordsList*list, COORD_PTR data) {

	if (CoordsList__itemExits(list, *data)) { //no duplicates
		
		return 0;
	}

	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = 0;
	
	if (list->head == 0) {
		
		list->head = newNode;
		list->tail = list->head;

	}
	else 
	{
		list->tail->next = newNode;
		list->tail = newNode;
	}

	list->length++;
	return 1;

}
COORD_PTR CoordsList__getCoord(const CoordsList *list, POINT_ point) {
	
	if (CoordsList__isEmpty(list)) {
		return 0;
	}

	for (Node *curr = list->head; curr != 0; curr = curr->next) {
		
		POINT_ currPoint = curr->data->pos;
		
		if (currPoint.let == point.let && currPoint.num == point.num) {
			
			return curr->data;
		}
	}
	return 0;

}
int CoordsList__removeItem(CoordsList *list, COORD_ data) {
	if (CoordsList__isEmpty(list)) {
		return 0;
	}
	Node *curr;
	Node *prev = 0;
	curr = list->head;

	while (curr != 0) {
		
		if (Coords__isEqual(*(curr->data), data)) {
			
			break;
		
		}
		else {
			
			prev = curr;
			curr = curr->next;

		}
	}

	if (curr == 0) {
		
		return 0;
	}

	if (curr == list->head) {
		
		list->head = list->head->next;

	}
	else if (prev != 0) {

		prev->next = curr->next;

	}

	list->length--;
	free(curr);  //delete the memory current is pointing to
	return 1;

}
COORD_PTR CoordsList__getElementAt(const CoordsList *list, int pos) {
	
	if (pos<0 || pos >= list->length)
		return 0;
	
	Node*curr = list->head;
	
	for (int i = 0; i<pos; i++) {
		
		curr = curr->next;

	}

	return curr->data;
}

CoordsList * CoordsList__FromCoordList(const CoordsList *list) {
	CoordsList *newList = malloc(sizeof(CoordsList));
	init__CoordsList(newList); //initialize head
	
	for (int i = 0; i < list->length; i++) {
		COORD_PTR coordToAdd = Coord__FromCoord(CoordsList__getElementAt(list, i));
		CoordsList__addItem(newList,coordToAdd);
	}
	return newList;

}

void CoordsList__printList(CoordsList *list){
  for(Node *p=list->head;p!=0;p=p->next){
 	printf("(%c,%d) , ",p->data->pos.let, p->data->pos.num);
}
  printf("\n");
 }
