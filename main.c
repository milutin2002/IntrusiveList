#include<stdio.h>
#include<stdlib.h>
#include"libIntrusiveList/libIntrusive.h"
#include"string.h"

typedef struct demo
{
    char name[20];
    int a;
    intrusiveNode b;
}demo;

void iteration(intrusiveNode *n,int offset){
    demo *d=(demo *)((char *)n-offset);
    printf("%s %d\n",d->name,d->a);
}


int main(int argc,char *argv[]){
    demo *d1=(demo *)calloc(1,sizeof(demo));
    demo *d2=(demo *)calloc(1,sizeof(demo));
    demo *d3=(demo *)calloc(1,sizeof(demo));
    strcpy(d1->name,"efff");
    d1->a=4;
    strcpy(d2->name,"efdfdd");
    d2->a=5;
    strcpy(d3->name,"cddcdc");
    d3->a=7;
    doubleLinkedList *l=calloc(1,sizeof(doubleLinkedList));
    l->offset=OFFSET(demo,b);
    addNode(l,&d1->b);
    addNode(l,&d2->b);
    addNode(l,&d3->b);
    iterateList(l,iteration);
    removeNode(l,&d2->b);
    iterateList(l,iteration);
    return 0;
}