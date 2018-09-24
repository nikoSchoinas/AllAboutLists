#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*The type of tree's element. It's an integer.*/
typedef int BinTreeElementType;

/*A pointer that points to tree's node*/
typedef struct BinTreeNode *BinTreePointer;

/*Every tree's node consists of BinTreeElementType data and pointers to left and Right child.*/
 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
};

typedef enum {
    FALSE, TRUE
} boolean;

/*Every stack's element is a pointer.*/
typedef BinTreePointer StackElementType;

/*StackPointer point to a stack's node*/
typedef struct StackNode *StackPointer;

/*Every stack node consists of StackElementType data and a pointer that points to next node.*/
typedef struct StackNode
{
	StackElementType Data;
    StackPointer Next;
} StackNode;

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);


void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType Item, boolean *Found,BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);

main()
{
    int choice ;
    char ch;
    BinTreePointer ARoot, LocPtr;
    BinTreeElementType AnItem;
    boolean Found;

    CreateBST(&ARoot);
    do
    {
        menu(&choice);
        switch(choice)
        {
            case 1:	do
            {
   	            printf("Enter a number for insertion in the Tree: ");
                scanf("%d", &AnItem);
                BSTInsert(&ARoot, AnItem);
                printf("\nContinue Y/N: ");
                do
                {
      	             scanf("%c", &ch);
                } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
            } while (toupper(ch)!='N');
            break;
            case 2:	if (EmptyBST(ARoot))
                        printf("Empty tree\n");
                    else
                        InorderTraversal(ARoot);
         			break;
            case 3:    if (EmptyBST(ARoot))
                        printf("Empty tree\n");
                    else
                    {
                        printf("Enter a number for searching in the Tree: ");
                        scanf("%d", &AnItem);
                        BSTSearch(ARoot, AnItem, &Found, &LocPtr);
         			    if (Found==FALSE)
         			        printf("Item %d not in tree \n",AnItem);
         			    else
         			        printf("Item %d is in tree \n",AnItem);
                    }
         			break;
            case 4:    if (EmptyBST(ARoot))
                        printf("Empty tree\n");
                    else
                    {
                        printf("Enter a number for deleting in the Tree: ");
                        scanf("%d", &AnItem);
                        BSTDelete(&ARoot, AnItem);
                    }
         			break;
		}
   } while (choice!=5);

	return 0;
}

void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1. Insert an element to Binary Tree\n");
    printf("2. In-oder traverse of Binary TreeA\n");
    printf("3. Search for a element in Binary Tree\n");
    printf("4. Delete an element of Binary Tree\n");
    printf("5. Quit\n");
    printf("\nChoice: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>4);
}

void CreateBST(BinTreePointer *Root)
/*Creates an empty binary search tree.
Returns a null pointer that it will be the tree's root.*/
{
    *Root = NULL;
}

boolean EmptyBST(BinTreePointer Root)
/*Arguments: A BST pointer that points to tree's root.
Checks if BST is empty.
If it is empty returns true. Else returns false.*/
{   return (Root==NULL);
}

void BSTInsert(BinTreePointer *Root, BinTreeElementType Item)
/*Arguments: A BST pointer that point to tree's root and an element.
Inserts that element to tree.
Returns the modified BST.*/
{
    BinTreePointer LocPtr, Parent;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (Item < LocPtr->Data)
            LocPtr = LocPtr ->LChild;
        else if (Item > LocPtr ->Data)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("Element %c is already in BST\n", Item);
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        LocPtr ->Data = Item;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (Item < Parent ->Data)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}

void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr)
/*Arguments: A BST pointer that points to tree's root and a key value.
Searches a tree node with that key value.
If that node is found then LocPtr pointer points to that node and variable *found is true.
If not, variable *found is false. */
{

    (*LocPtr) = Root;
    (*Found) = FALSE;
    while (!(*Found) && (*LocPtr) != NULL)
    {
        if (KeyValue < (*LocPtr)->Data)
            (*LocPtr) = (*LocPtr)->LChild;
        else
            if (KeyValue > (*LocPtr)->Data)
                (*LocPtr) = (*LocPtr)->RChild;
            else (*Found) = TRUE;
    }
}

void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
    BinTreePointer *LocPtr, BinTreePointer *Parent)
/*Same as BSTSearch with the difference that *Parent variable points to the parent of the selected node.*/
{
    *LocPtr = Root;
    *Parent=NULL;
    *Found = FALSE;
    while (!(*Found) && *LocPtr != NULL)
    {
        if (KeyValue < (*LocPtr)->Data) {
            *Parent=*LocPtr;
            *LocPtr = (*LocPtr)->LChild;
        }
        else
            if (KeyValue > (*LocPtr)->Data) {
                *Parent=*LocPtr;
                *LocPtr = (*LocPtr)->RChild;
            }
            else *Found = TRUE;
    }

}

void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
/*Arguments: A BinTreePointer that points to tree's root and a key-value for deletion.
Tries to find a node that contains that value.
If value is found, it's been deleted.
A modified tree is returned.*/

{

   BinTreePointer
   n,                   //points to the node that contains the key value. *)
   Parent,              // Father node of n's or nNext's
   nNext,               // In-order next node of n.
   SubTree;             // pointer of the subtree
   boolean Found;       // Is true if value is in BST *)

     BSTSearch2(*Root, KeyValue, &Found , &n, &Parent);
     if (!Found)
        printf("Element %d exist in BST\n", KeyValue);
     else {
          if (n->LChild != NULL && n->RChild != NULL)
          {  /*Node for deletion. Find in-order next and his father.*/
                 nNext = n->RChild;
                 Parent = n;
                 while (nNext->LChild !=NULL)  //Left traversal *)
                 {
                      Parent = nNext;
                      nNext = nNext->LChild;
                 }
                /*Copy context from nNext to n and change n so it points to the next node.*/

                n->Data = nNext->Data;
                n = nNext;
          } //Case: that node has only one child
          SubTree = n->LChild;
          if (SubTree == NULL)
             SubTree = n->RChild;
          if (Parent == NULL)                 //Root it will be deleted
             *Root = SubTree;
          else if (Parent->LChild == n)
                  Parent->LChild = SubTree;
               else
                   Parent->RChild = SubTree;
          free(n);
     }
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

void InorderTraversal(BinTreePointer Root)
/*A BST pointer that points to tree's root.
Executes an in-order traversal and process each node just once.
Prints node's context.*/

{
    StackPointer Stack;
    BinTreePointer CurrPtr;
    CurrPtr=Root;
    CreateStack(&Stack);
    do
    {
        while(CurrPtr!=NULL)
        {
            Push(&Stack,CurrPtr);
            CurrPtr=CurrPtr->LChild;
        }

        if(!EmptyStack(Stack))
        {
            Pop(&Stack,&CurrPtr);
            printf("%d ",CurrPtr->Data);
            CurrPtr=CurrPtr->RChild;
        }
    }
    while((!EmptyStack(Stack)) || CurrPtr!=NULL);
}
