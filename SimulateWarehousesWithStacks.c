#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*This program stimulates the function of three warehouses that store containers.
Actually every warehouse is a stack. So if we add a lot of containers, the program stores them in a warehouse.*/

/*Every stack's element consists of an integer and an array with characters.*/
typedef struct
{
    int num;
    char date[12];
}StackElementType;

/*A pointer that point to a stack node.*/
typedef struct StackNode *StackPointer;

/*Every stack node consists of a StackElementType and a pointer that points to the next position.*/
typedef struct StackNode
{
	StackElementType Data;
    StackPointer Next;
} StackNode;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);
int StackSize(StackPointer Stack);
int IndexOfMin(StackPointer Stack1,StackPointer Stack2, StackPointer Stack3);
void TraverseStack(StackPointer Stack);

main()
{
    StackPointer Warehouse1,Warehouse2,Warehouse3;
    int i,n,min;
    StackElementType AnItem;
    CreateStack(&Warehouse1);
    CreateStack(&Warehouse2);
    CreateStack(&Warehouse3);
    printf("Number of containers: ");
    scanf("%d",&n);
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("Number of boxes inside container #%d: ",i+1);
        scanf("%d",&AnItem.num);
        printf("Expiration date of boxes in container #%d: ",i+1);
        scanf("%s",AnItem.date);
        min=IndexOfMin(Warehouse1,Warehouse2,Warehouse3);
        switch(min)
        {
            case 1: Push(&Warehouse1,AnItem);
                break;
            case 2: Push(&Warehouse2,AnItem);
                break;
            case 3: Push(&Warehouse3,AnItem);
                break;
        }
    }
    printf("\n********** Warehouse1 **********\n");
    TraverseStack(Warehouse1);
    printf("\n********** Warehouse2 **********\n");
    TraverseStack(Warehouse2);
    printf("\n********** Warehouse3 **********\n");
    TraverseStack(Warehouse3);

}

void CreateStack(StackPointer *Stack)
/*Creates an empty linked stack.
Returns a pointer to that stack. Initially NULL*/
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
    TempPtr->Data.num = Item.num;
    strcpy(TempPtr->Data.date,Item.date);
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
int StackSize(StackPointer Stack)
/*Returns the number of stack elements.*/
{
    StackPointer CurrPtr;
    int size=0;
    CurrPtr=Stack;
    while(CurrPtr!=NULL)
    {
        size+=CurrPtr->Data.num;
        CurrPtr=CurrPtr->Next;
    }
    return size;
}

int IndexOfMin(StackPointer Stack1,StackPointer Stack2, StackPointer Stack3)
/*Calculates which stack (warehouse) has less element and returns it's index*/
{
    if(StackSize(Stack1)<=StackSize(Stack2) && StackSize(Stack1)<=StackSize(Stack3))
        return 1;
    else if(StackSize(Stack2)<=StackSize(Stack1) && StackSize(Stack2)<=StackSize(Stack3))
        return 2;
    else
        return 3;
}
void TraverseStack(StackPointer Stack)
/*Traverses and prints stack's elements.*/
{
	StackPointer CurrPtr;

   if (EmptyStack(Stack))
   {
   	    printf("EMPTY Stack\n");
    }
   else
   {
   	    CurrPtr = Stack;
         while ( CurrPtr!=NULL )
        {
      	     printf("%d ", CurrPtr->Data);
      	     printf("%s\n",CurrPtr->Data.date);
             CurrPtr = CurrPtr->Next;
        }
   }
}
