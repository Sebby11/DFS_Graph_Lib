//Sebastian Medina                      CruzID: Seamedin          Course: CSE 101
//October 26, 2019                         FIlename: List.h
//Description: List header file


#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// structs----------------------------------------------------------------

// doubly linked list 
typedef struct NodeObj{
  void* data;// CHANGED
  struct NodeObj* moveNext;
  struct NodeObj* movePrev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
  // like moveNext
  Node front;//first
  Node back;//Last
  Node cursor;
  int index;//
  int size;
}ListObj;


// Exported type
typedef struct ListObj* List;

// newList()
// returns reference to new empty List object
List newList(void);

// freeList()
// frees list memory in heap
void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
void* front(List L); // Returns front element of L. Pre: length()>0
void* back(List L); // Returns back element of L. Pre: length()>0
void* get(List L); // Returns cursor element of L. Pre: length()>0, 
//index()>=0

// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.

void moveFront(List L); // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.

void moveBack(List L); // If L is non-empty, sets cursor under the back element,
// otherwise does nothing.

void movePrev(List L); // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing

void moveNext(List L); // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing

void prepend(List L, void* data); // Insert new element into L. If L is non-empty,
// insertion takes place before front element.

void append(List L, void* data); // Insert new element into L. If L is non-empty,
// insertion takes place after back element.

void insertBefore(List L, void* data); // Insert new element before cursor.
// Pre: length()>0, index()>=0

void insertAfter(List L, void* data); // Insert new element before cursor.
// Pre: length()>0, index()>=0

void deleteFront(List L); // Delete the front element. Pre: length()>0

void deleteBack(List L); // Delete the back element. Pre: length()>0

void delete(List L); // Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); // Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.

#endif
