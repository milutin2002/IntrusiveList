#ifndef INTRUSIVE_H
#define INTRUSIVE_H

typedef struct intrusiveNode
{
    struct intrusiveNode *left,*right;
    
} intrusiveNode;

typedef struct doubleLinkedList
{
    intrusiveNode *head;
    int (*key)(void *,void *);
    int (*comparison)(void *,void *);
    unsigned int offset;
}doubleLinkedList;


#endif