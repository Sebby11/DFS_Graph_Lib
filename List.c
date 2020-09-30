//Sebastian Medina         CruzID: Seamedin        Course: CSE 101
//October 26, 2019            Filename: List.c
//Description: List ADT

#include<stdio.h>
#include<stdlib.h>
#include "List.h"


// Constructors-Destructors -----------------------------------------------

// newNode()
// sets a new head pointing to an open list
Node newNode(void* x, Node previous, Node after){
  Node head = malloc(sizeof(NodeObj));
  head->moveNext = after;
  head->movePrev = previous;
  head->data = x;
  return(head);
}

// freeNode()
// Releases the memory allocated to heap from node
void freeNode(Node *pN){
  if (pN != NULL && *pN != NULL){
    free(*pN);
    *pN = NULL;
  }
}

// newList()
// Returns & initializes empty List reference
List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->back = L->front = NULL;
  L->size  = 0;
  L->cursor = NULL;//set to know if cursor is initialized or not
  L->index = -1;
  return(L);
}

// freeList()
// Frees the hep memory in which the list took up
void freeList(List *pL){
  if (pL != NULL && *pL != NULL){
    //node to be walked across
    Node N = (*pL)->front;
    //Cycle through each node, starting at front and free them all.
    while (N != NULL){
      Node x = N;//current node that will be freed
      N = N->moveNext;
      free(x);
    }

    //free List itself
    free(*pL);
    *pL = NULL;
  }
}

// Access functions --------------------------------------------------------

// length(List L)
// Returns the number of elements in L
int length(List L){
  if(L == NULL){
    printf("List Error: Cannot call length on an empty List\n");
    exit(EXIT_FAILURE);
  }

  return L->size;
}

// index(List L)
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
  if(L == NULL){
    printf("List Error: Cannot call index() on an NULL List\n");
    exit(EXIT_FAILURE);
  }

  if (L->cursor == NULL)
    return -1;
  else
    return L->index;// will return NULL if no cursor is established???
}

// Returns front element of L. Pre: length()>0
void* front(List L){
  if(L == NULL){
    printf("List Error: Cannot call front() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  return L->front->data;
}

// Returns back element of L. Pre: length()>0
void* back(List L){
  if(L == NULL){
    printf("List Error: Cannot call back() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}


// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L){
  if(L == NULL){
    printf("List Error: Cannot call get() on a NULL List\n");
    exit(EXIT_FAILURE);
  }

  if (L->size <= 0){
    printf("List Error: Cannot call get() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  if (L->index < 0){
    printf("List Error: Cannot call get() when no cursor is present\n");
    exit(EXIT_FAILURE);
  }

  return L->cursor->data; 
}

// Manipulation procedures --------------------------------------------------

// Resets L to its original empty state.
void clear(List L){
  if(L == NULL){
    printf("List Error: Cannot call clear() when List is NULL\n");
    exit(EXIT_FAILURE);
  }

  Node clearAll = L->front;

  while (clearAll != NULL){
    Node tail = clearAll;
    clearAll = clearAll->moveNext;

    freeNode(&tail);
  }

  L->back = L->front = NULL;
  L->size  = 0;
  L->cursor = NULL;//set to know if cursor is initialized or not
  L->index = -1;
}

// If L is non-empty set the cursor to the front of the list
void moveFront(List L){
  if(L == NULL){
    printf("List Error: Cannot call moveFront() when List is NULL\n");
    exit(EXIT_FAILURE);
  }

  if (L->size >= 1){
    L->cursor = L->front;
    L->index = 0;
  }
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
  if(L == NULL){
    printf("List Error: Cannot call moveBack() List is NULL\n");
    exit(EXIT_FAILURE);
  }

  if (L->size >= 1){
    L->cursor = L->back;
    L->index = L->size - 1;
  }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
  if(L == NULL){
    printf("List Error: Cannot call movePrev() List is NULL\n");
    exit(EXIT_FAILURE);
  }

  if(L->index != -1 && L->index != 0){
    //move cursor one step toward the front of the List
    L->cursor = L->cursor->movePrev;
    L->index--;
  }
  else if (L->index != -1 && L->index == 0){
    L->cursor = NULL;
    L->index = -1;
  }
  else if (L->cursor == NULL){}
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
  if(L == NULL){
    printf("List Error: Cannot call moveNext() List is NULL\n");
    exit(EXIT_FAILURE);
  }

  if(L->index != -1 && L->index != (L->size - 1)){
    //move cursor one step toward the back of the List
    L->cursor = L->cursor->moveNext;
    L->index++;
  }
  else if (L->index != -1 && L->index == (L->size - 1)){
    L->cursor = NULL;
    L->index = -1;
  }
  else if (L->index == -1){}
}

// Insert new element to L. If L is non-empty, insertion takes
// place before front element.
void prepend(List L, void* data){
  if(L == NULL){
    printf("List Error: cannot call prepend() on NULL List\n");
    exit(EXIT_FAILURE);
  }

  if (L->size == 0){
    Node ins = newNode(data, NULL, NULL);
    L->front = ins;
    L->back = ins;
    L->size++;
  }
  else{
    Node ins = newNode(data, NULL, L->front);
    L->front->movePrev = ins;
    L->front = ins;
    L->size++;

    // account for cursor
    if(L->index != -1){
      L->index++;
    }
  }
}

// Insert new element into L. If L is non-empty, insertion 
// takes place after back element.
void append(List L, void* data){
  if(L == NULL){
    printf("List Error: cannot call append() on NULL List\n");
    exit(EXIT_FAILURE);
  }

  if (L->size == 0){
    Node ins = newNode(data, NULL, NULL);
    L->front = ins;
    L->back = ins;
  }
  else{
    Node ins = newNode(data, L->back, NULL);
    L->back->moveNext = ins;
    L->back = ins;

  }
  L->size++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* data){
  if(L == NULL){
    printf("List Error: cannot call insertBefore() on NULL List\n");
    exit(EXIT_FAILURE);
  }

  if(L->size < 1){
    printf("List Error: cannot call insertBefore() on an empty list\n");
    exit(EXIT_FAILURE);
  }

  if(L->index < 0){
    printf("List Error: cannot call insertBefore() when no cursor is initiated\n");
    exit(EXIT_FAILURE);
  }

  if(L->cursor == L->front){
    Node insBefore = newNode(data, NULL, L->cursor);
    L->front = insBefore;
    L->cursor->movePrev = insBefore;
    L->size++;
    L->index++;
  }
  else{
    Node insBefore = newNode(data, L->cursor->movePrev, L->cursor);
    L->cursor->movePrev->moveNext = insBefore;
    L->cursor->movePrev = insBefore;
    L->size++;
    L->index++;
  }

}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* data){
  if(L == NULL){
    printf("List Error: cannot call insertAfter() on NULL List\n");
    exit(EXIT_FAILURE);
  }

  if(L->size < 1){
    printf("List Error: cannot call insertAfter() on an empty list\n");
    exit(EXIT_FAILURE);
  }

  if(L->index < 0){
    printf("List Error: cannot call insertAfter() when no cursor is initiated\n");
    exit(EXIT_FAILURE);
  }

  if(L->cursor == L->back){
    Node insNext = newNode(data, L->cursor, NULL);
    L->back = insNext;
    L->cursor->moveNext = insNext;
    //L->size++;
  }
  else{
    Node insNext = newNode(data, L->cursor, L->cursor->moveNext);
    L->cursor->moveNext->movePrev = insNext;
    L->cursor->moveNext = insNext;
    //L->size++;
  }
  L->size++;


}


void deleteFront(List L){
  if(L== NULL){
    printf("List Error: cannot call deleteFront() on NULL List");
    exit(EXIT_FAILURE);
  }

  if(L->size <= 0){
    printf("List Error: cannot call deleteFront() on an empty List");
    exit(EXIT_FAILURE);
  }

  if (L->size == 1){
    clear(L);
    L->size = 0;
  }
  else{
    Node temp = L->front;
    L->front = L->front->moveNext;
    L->front->movePrev = NULL;

    freeNode(&temp);
    L->size--;
    L->index--;
  }

}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
  if(L== NULL){
    printf("List Error: cannot call deleteBack() on NULL List");
    exit(EXIT_FAILURE);
  }

  if(L->size <= 0){
    printf("List Error: cannot call deleteBack() on an empty List");
    exit(EXIT_FAILURE);
  }

  if (L->size == 1){
    clear(L);
    L->size = 0;
  }
  else{
    Node tmp = L->back;
    L->back = L->back->movePrev;
    L->back->moveNext = NULL;

    freeNode(&tmp);
    L->size--;
  }
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
  if(L == NULL){
    printf("List Error: cannot call delete() on NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(L->size < 1){
    printf("List Error: cannot call delete() on an empty list\n");
    exit(EXIT_FAILURE);
  }

  if(L->index < 0){
    printf("List Error: cannot call delete() with no index");
    exit(EXIT_FAILURE);
  }

  /*
   if(L->cursor == L->front){
   deleteFront(L);
   }
   else if (L->cursor == L->back){
   deleteBack(L);
   }
   else{
    Node N = L->cursor;
    L->cursor->movePrev->moveNext = L->cursor->moveNext;
    L->cursor->moveNext->movePrev = L->cursor->movePrev;

    
    freeNode(&N);
    N = NULL;
    L->size--;
   }
   L->index = -1;
  */

  if(L->cursor == L->back){
    deleteBack(L);
  }
  else if (L->cursor == L->front){
    deleteFront(L);
  }
  else{
    Node here = L->cursor;
    L->cursor->movePrev->moveNext = L->cursor->moveNext;
    L->cursor->moveNext->movePrev = L->cursor->movePrev;

    freeNode(&here);
    L->cursor = NULL;
    L->index = -1;
    L->size--;
  }
}


// Other Operations -----------------------------------------------------------

void printList(FILE* out, List L){
  Node toPrint = L->front;

  while(toPrint != NULL){
    fprintf(out, "%p ", toPrint->data);
    toPrint = toPrint->moveNext;
  }
}
