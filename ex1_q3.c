// Course: Advanced C programming
// exercise 1, question 3
// file name: ex1_q3.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>

// --------------------------- //
//
//	Assigned by:
//		
//		netanel shalom 206990178
//
// --------------------------- //

// structs and function declarations section:
typedef struct rectangle {
	int xTopSmall;
	int yTopSmall;
	int xButtomRight;
	int yButtomRight;
}rectangle;

typedef struct recElement {
	rectangle Rect;
	struct recElement* next;
}recElement;

int validateRectangle(rectangle* rec);
rectangle scanRectangle();
recElement* createElement();
recElement* createRectList();
rectangle findSmallest(recElement* head);
void printRectangle(rectangle* rec);
void printList(recElement* head);
void freeList(recElement* head);

// --------------------------- //

int main()
{
	rectangle rec;
	recElement* head = NULL;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	head = createRectList();

	printf("\n\nRectangle list:\n");
	printList(head);

	rec = findSmallest(head);

	printf("\n\nFilling rectangle:\n");
	printRectangle(&rec);

	freeList(head);
	head = NULL;

	printf("\n\n");

	return 0;
}
// --------------------------- //


/// <summary>
/// Function gets an address of a rectangle and check validity.
/// </summary>
/// <param>Address of rectangle</param>
/// <returns>0- if rectangle is not valid, 1-if rectangle is a valid, 2-if rectangle is a point</returns>
int validateRectangle(rectangle* rec)
{
	// your code:
	/*int xTopSmall;
	int yTopSmall;
	int xButtomRight;
	int yButtomRight;*/
	if (rec->xTopSmall == rec->xButtomRight && 
		rec->yTopSmall == rec->yButtomRight)
		return 2;
	if (rec->xTopSmall < rec->xButtomRight &&
		rec->yTopSmall > rec->yButtomRight) {
		return 1;
	}
	else
		return 0;
}
// --------------------------- //



/// <summary>
/// Function scan a rectangle in the plane,
/// Used as auxiliary function for createElement.
/// </summary>
/// <param>None</param>
/// <returns>a newly scanned rectangle</returns>
rectangle scanRectangle()
{
	// your code:
	rectangle rq;
	do {
		printf("please enter xtopsmall");
		scanf("%d", &rq.xTopSmall);
		printf("please enter ytopsmall");
		scanf("%d", &rq.yTopSmall);
		printf("please enter xButtomRight");
		scanf("%d", &rq.xButtomRight);
		printf("please enter yButtomRight");
		scanf("%d", &rq.yButtomRight);
	} while (validateRectangle(&rq) == 0);
	return rq;
}
// --------------------------- //


/// <summary>
/// Function allocate a new recElement.
/// Calls scanRectangle during the process. 
/// if the scanned rectangle is a point, returns NULL.
/// </summary>
/// <returns>New allocated recElement or NULL if rectangle is a point</returns>
recElement* createElement()
{
	// your code:
	rectangle req = scanRectangle();
	if (validateRectangle(&req) == 2)
		return NULL;

	recElement* ptr = (recElement*)malloc(sizeof(recElement));
	ptr->Rect = req;
	ptr->next = NULL;

	return ptr;
}
// --------------------------- //


/// <summary>
/// Function creates a list of rectangles.
/// Calls function createElement in a loop.
/// Scan stops when createElement returns null.
/// </summary>
/// <param>None</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
recElement* createRectList()
{
	// your code:
	recElement* head = createElement();
	if (head == NULL)
		return NULL;
	
	recElement* prev = head, * curr = NULL;
	do {
		curr = createElement();
		prev->next = curr;
		prev = curr;
	} while (curr != NULL); // equal to NULL

	return head;
}
// --------------------------- //


/// <summary>
/// Function gets a list and returns the filling rectangle
/// </summary>
/// <param>recElement* head - the list of rectangles</param>
/// <returns>The filling rectangle. if the list is empty return rectangle with (0,0,0,0)</returns>
rectangle findSmallest(recElement* head)
{
	recElement *ptr=head;
	if (head == NULL) {//point 
		rectangle res = {0,0,0,0};
		return res;
	}

	int xtop = head->Rect.xTopSmall;
	int xbuttom=head->Rect.xButtomRight;
	int ytop=head->Rect.yTopSmall;
	int ybuttom=head->Rect.yButtomRight;
	while (ptr!=NULL)
	{
		if (xtop> ptr->Rect.xTopSmall)
			xtop = ptr->Rect.xTopSmall;// if next more small
		if (ytop < ptr->Rect.yTopSmall)
			ytop = ptr->Rect.yTopSmall;// if next more big
		if (xbuttom<ptr->Rect.xButtomRight)
			xbuttom = ptr->Rect.xButtomRight;// if next more small
		if (ybuttom >ptr->Rect.yButtomRight)
			ybuttom = ptr->Rect.yButtomRight;
	ptr = ptr->next;
	}

	rectangle res= {xtop,ytop, xbuttom, ybuttom};
	return res;
	// your code:
}
// --------------------------- //


/// <summary>
/// Function print rectangle cordinates on screen. (not drawing the rectangle!)
/// </summary>
/// <param>rectangle* rec - pointer to rectangle</param>
/// <returns>None</returns>
void printRectangle(rectangle* rec)
{
	printf("[(%d,%d)(%d,%d)]", rec->xTopSmall, rec->yTopSmall, rec->xButtomRight, rec->yButtomRight);
}
// --------------------------- //


/// <summary>
/// Function print list on screen.
/// </summary>
/// <param>recElement* head - list address</param>
/// <returns>None</returns>
void printList(recElement* head)
{
	// your code:
	recElement * curr = head;
	while (curr != NULL) {
		printRectangle(&(curr->Rect));
		curr = curr->next;
	}
}
// --------------------------- //


/// <summary>
/// Function free alocated memory of list 
/// </summary>
/// <param>recElement* head - pointer to head of the list</param>
/// <returns>None</returns>
void freeList(recElement* head)
{
	// your code:
	recElement* prev, * curr = head;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}
// --------------------------- //
