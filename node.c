//
// Created by Lizzy on 2020/1/13.
//

#include "node.h"
#include <stdio.h>
#include <stdlib.h>

//typedef struct _node {
//    int value;
//    struct _node *next;
//} Node;

// to help use functions
typedef struct _list {
    Node * head;
//    Node * tail;
} List;

void add(List* list, int number); // 1
void print(List* list); // 2
void search(List* list, int number); // 3
void delete(List* list, int number); // 4
void remove_all(List* list); // 5

int main(int argc, char const *argv[])
{
    List list;
    list.head = NULL;
    int number;
    do {
        scanf("%d", &number);
        if (number!=-1) {
            // add
            add(&list, number);
        }
    } while (number!=-1);

    // self-created way
//    printf("check the code above:\n");
//    Node *test;
//    test = list.head;
//    while(test) {
//        printf("%d ", test->value);
//        test = test->next;
//    }

    // traditional way
    print(&list);

    // search
//    int newNumber;
//    scanf("%d", &newNumber);
//    search(&list, newNumber);

    // delete
//    int delNumber;
//    scanf("%d", &delNumber);
//    delete(&list, delNumber);
//    printf("After deletion:\n");
//    print(&list);

    // remove all
    printf("Head: %d\n", list.head->value);
    remove_all(&list);
    printf("Head: %d\n", list.head->value);

    return 0;
}

void remove_all(List* list)
{
    Node *p, *q;
    for (p=list->head; p; p=q) {
        q=p->next;
        free(p);
    }
}

void delete(List* list, int number)
{
    Node *p, *q;
    for (q=NULL, p=list->head; p ;q=p, p=p->next) {
        if (p->value==number) {
            if (q) {
                q->next = p->next;
            } else {
                list->head = p->next;
            }
            free(p);
            break;
        }
    }
}

void search(List* list, int number) {
    Node *p;
    int isFound = 0;
    for ( p=list->head; p; p=p->next) {
        if (p->value==number) {
            isFound = 1;
            break;
        }
    }
    if (isFound) {
        printf("Yes.");
    } else {
        printf("No.");
    }
}

void print(List* list)
{
    Node *p;
    for (p=list->head; p; p=p->next) {
        printf("%d\t", p->value);
    }
    printf("\n");
}


void add(List* list, int number)
{
    // create the new node
    Node *p = (Node*)malloc(sizeof(Node));
    p->value = number;
    p->next = NULL;

    // attach to the link
    Node *last = list->head;
    if (last) {
        // find the last
        while (last->next) {
            last = last->next;
        }
        // attach
        last->next = p;
    } else {
        // attach to the head
        list->head = p; // watch out, last is a active pointer, change head
    }
}

/*
 1. 将创建新结点并且连接在链表上的过程单独分离开变为函数时，需要修改head，在函数内部修改不起作用。
 2. 可能的解决方法：
    - 返回Node* 类型的head, 并改变使用方式。
    - 传入的是指针的指针，即Node** pHead
    - 使用一个List来把Node指针包装进去，然后使用List的指针（推荐）
 */