#include <stdio.h>
#include <stdlib.h>

/*This program prompts the user to make a stack with his own stack size and items.
Then prints that stack and moves all the elements to another stack.
Prints the second stack as well, but the elements are displayed backwards.
That's because Stack uses FIFO. */

/*Data type of stack's element. It's an Integer. */
typedef int StackElementType;
/*StackPointer points to a struct */
typedef struct StackNode *StackPointer;
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
void TraverseStack(StackPointer Stack);

main()
{
    StackPointer AStack1, AStack2;
    int Item,number,i;
    CreateStack(&AStack1);
    CreateStack(&AStack2);
    printf("Number of stack's elements: ");
    scanf("%d",&number);
    printf("\n");
    for(i=0;i<number;i++)
    {
        printf("Type element #%d: ",i+1);
        scanf("%d",&Item);
        Push(&AStack1,Item);
    }
    printf("\n********* First Stack *********");
    printf("\n");
    TraverseStack(AStack1);

    while(!EmptyStack(AStack1))
    {
        Pop(&AStack1,&Item);
        Push(&AStack2,Item);
    }

    printf("\n********* Second Stack *********");
    printf("\n");
    TraverseStack(AStack2);

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
void TraverseStack(StackPointer Stack)
/*Traverses and prints all stack's elements.*/
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
      	     printf("%d", CurrPtr->Data);
             CurrPtr = CurrPtr->Next;
        }
   }
}
