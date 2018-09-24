#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define ElementNumber 10
/*This program asks user to give a word to check if it's a cancer word.
A cancer word is a word that can be read backwards.
Adds the characters to a stack and a queue at the same time.
Stack has LIFO while queue has FIFO. So it pops the characters from every data structure and checks them.
If all characters are the same then the given word is a cancer word.*/

/*Data type of stack's element. It's a character. */
typedef char StackElementType;
/*StackPointer points to a struct */
typedef struct StackNode *StackPointer;
typedef struct StackNode
{
	StackElementType Data;
    StackPointer Next;
} StackNode;

/*Data type of queue's element. It's a character.*/
typedef char QueueElementType;
/*QueuePointer points to a struct.*/
typedef struct QueueNode *QueuePointer;

typedef struct QueueNode
{
	QueueElementType Data;
    QueuePointer Next;
} QueueNode;

typedef struct
{
    QueuePointer Front;
    QueuePointer Rear;
} QueueType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);
void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
void AddQ(QueueType *Queue, QueueElementType Item);
void RemoveQ(QueueType *Queue, QueueElementType *Item);

main()
{
    StackPointer AStack;
    QueueType AQueue;
    char str[ElementNumber],ch1,ch2;
    boolean flag;
    int i,counter;

    CreateStack(&AStack);
    CreateQ(&AQueue);
    printf("Give a word to find out if it is a CANCER word: ");
    scanf("%s",str);

    for(i=0;i<strlen(str);i++)
    {
        Push(&AStack,str[i]);
        AddQ(&AQueue,str[i]);
    }

    flag=TRUE;
    counter=0;

    while(flag && counter<strlen(str))
    {
        Pop(&AStack,&ch1);
        RemoveQ(&AQueue,&ch2);
        if(ch1!=ch2)
            flag=FALSE;
        counter++;
    }

    if(flag)
        printf("\nCANCER");
    else
        printf("\nNO CANCER");
}

void CreateStack(StackPointer *Stack)
/*Creates an empty linked stack.
Returns a pointer to that stack.*/

{
	*Stack = NULL;
}

boolean EmptyStack(StackPointer Stack)
/*Arguments: A linked stack.
Checks if stack is empty.
If it is empty returns true, then false.*/
{
	return (Stack==NULL);
}

void Push(StackPointer *Stack, StackElementType Item)
/*Arguments: a stack pointer that points to a stack and a stack's Item
Pushes the Item in the top.*/
{
	StackPointer TempPtr;

    TempPtr= (StackPointer)malloc(sizeof(struct StackNode));
    TempPtr->Data = Item;
    TempPtr->Next = *Stack;
    *Stack = TempPtr;
}

void Pop(StackPointer *Stack, StackElementType *Item)
/*Pops the top Item. If stack is not empty.
If stack is empty a message is being displayed.*/
{
    StackPointer TempPtr;

    if (EmptyStack(*Stack)) {
   	    printf("EMPTY Stack\n");
    }
   else
   {
        TempPtr = *Stack;
        *Item=TempPtr->Data;
        *Stack = TempPtr->Next;
        free(TempPtr);
    }
}
void CreateQ(QueueType *Queue)
/*Creates an empty queue.*/
{
	Queue->Front = NULL;
	Queue->Rear = NULL;
}

boolean EmptyQ(QueueType Queue)
/*Arguments: a queue.
Checks if queue is empty.
If it is empty returns true, else false.*/
{
	return (Queue.Front==NULL);
}

void AddQ(QueueType *Queue, QueueElementType Item)
/*Arguments: a pointer that points to a linked queue and an item.
Adds the item at the end of the queue.*/
{
	QueuePointer TempPtr;

    TempPtr= (QueuePointer)malloc(sizeof(struct QueueNode));
    TempPtr->Data = Item;
    TempPtr->Next = NULL;
    if (Queue->Front==NULL)
        Queue->Front=TempPtr;
    else
        Queue->Rear->Next = TempPtr;
    Queue->Rear=TempPtr;
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
/*Remove the item from the queue if it's not empty.
If queue is empty a message is being displayed.*/
{
    QueuePointer TempPtr;

    if (EmptyQ(*Queue)) {
   	    printf("EMPTY Queue\n");
    }
   else
   {
        TempPtr = Queue->Front;
        *Item=TempPtr->Data;
        Queue->Front = Queue->Front->Next;
        free(TempPtr);
        if (Queue->Front==NULL) Queue->Rear=NULL;
    }
}



