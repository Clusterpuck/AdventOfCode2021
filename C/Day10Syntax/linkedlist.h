#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedListNode
{
    void *data;
    struct LinkedListNode *next;
} LiLiNode;

typedef struct
{
    LiLiNode * head;
    int size;
    LiLiNode * tail;
} LinkedList;

typedef void (*listFunc)( void* data );

/*function declarations*/

LinkedList* createLinkedList();
void insertFirst( LinkedList *list, void *entry );
void *removeFirst( LinkedList *list );
void insertLast( LinkedList *list, void *entry );
void *removeLast( LinkedList *list );
void printMessage( void* data );
void freeJEntry( void *data );
void printLinkedList( LinkedList *list, listFunc funcPtr );
void freeLinkedList( LinkedList *list, listFunc funcPtr );



#endif
