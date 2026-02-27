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


#define OFFSET(structName,fieldName) \ 
    ((unsigned int)&(((structName*)0)->fieldName))

void addNode(doubleLinkedList *l,intrusiveNode *node);

void iterateList(doubleLinkedList *l,void (*work)(intrusiveNode *,int));

void removeNode(doubleLinkedList *l,intrusiveNode *n);

#endif