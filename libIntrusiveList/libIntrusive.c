#include "libIntrusive.h"
#include<stdio.h>

void addNode(doubleLinkedList *l,intrusiveNode *node){
    if(l->head==NULL){
        l->head=node;
        node->left=NULL;
        node->right=NULL;
        return;
    }
    l->head->left=node;
    node->right=l->head;
    l->head=node;
}

void iterateList(doubleLinkedList *l,void (*work)(intrusiveNode *,int)){
    intrusiveNode*curr=l->head;
    while(curr!=NULL){
        work(curr,l->offset);
        curr=curr->right;
    }
}

void removeNode(doubleLinkedList *l,intrusiveNode *n){
    if(n==l->head){
        if(l->head->left!=NULL){
            l->head->left=NULL;
        }
        l->head=l->head->right;
        n->right=NULL;
        return;
    }
    if(n->left!=NULL){
        n->left->right=n->right;
    }
    if(n->right!=NULL){
        n->right->left=n->left;
    }
}