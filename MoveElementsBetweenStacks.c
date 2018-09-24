#include<stdio.h>
#include<stdlib.h>
#define StackLimit 6
/*This program creates 3 stacks. First of all, adds to stack #1 some elements so they make the word "PASCAL".
Then those elements are moved to stack #2. Stack uses FIFO architecture, so the word "PASCAL" is now "LASCAP".
Then, those elements are moved to stack #3 and the word "PASCAL" is made again.
We use all the known functions for those operations: CreateStack,Pop,Push etc. */
typedef char StackElementType;

typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

main()
{
    StackType stack1,stack2,stack3;
    /* Create 3 stacks*/
    CreateStack(&stack1);
    CreateStack(&stack2);
    CreateStack(&stack3);

    /*Push every letter in Stack #1*/
    Push(&stack1,'P');
    Push(&stack1,'A');
    Push(&stack1,'S');
    Push(&stack1,'C');
    Push(&stack1,'A');
    Push(&stack1,'L');

    printf("\nstack1:");
    TraverseStack(stack1);

    /*Transfer element data from stack #1 to stack #2, so they will be traversed backwards.*/
    while(!EmptyStack(stack1))
    {
        Push(&stack2,stack1.Element[stack1.Top]);
        Pop(&stack1,&stack1.Element[stack1.Top]);
    }

    printf("\nstack2:");
    TraverseStack(stack2);

    /*Transfer element data from stack #2 to stack #3*/
    while(!EmptyStack(stack2))
    {
        Push(&stack3,stack2.Element[stack2.Top]);
        Pop(&stack2,&stack1.Element[stack2.Top]);
    }

    printf("\nstack3:");
    TraverseStack(stack3);

    while(!EmptyStack(stack3))
    {
        Push(&stack1,stack3.Element[stack3.Top]);
        Pop(&stack3,&stack3.Element[stack3.Top]);
    }

}

void CreateStack(StackType *Stack)
/*Creates an empty linked stack.
Returns a pointer to that stack.*/
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack)
/*Arguments: A linked stack.
Checks if stack is empty.
If it is empty returns true, then false.*/
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/*Arguments: A linked stack.
Checks if stack is full.
If it is full returns true, then false.*/
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
/*Arguments: a stack pointer that points to a stack and a stack's Item
Pushes the Item in the top.*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/*Pops the top Item. If stack is not empty.
If stack is empty a message is being displayed.*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

void TraverseStack(StackType Stack)
{
    /*Traverses and prints all stack's elements.*/
    int i;
    printf("\nNumber of stack elements: %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%c, ",Stack.Element[i]);
    }
    printf("\n");
}
