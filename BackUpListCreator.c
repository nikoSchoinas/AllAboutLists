#include <stdio.h>
#include <stdlib.h>
/*This program asks the user to give some numbers so that creates a list.
The program creates and a back up list.
Then prints the elements of every list. */

/*List element type. It's an Integer actually.*/
typedef int ListElementType;

/*ListNode struct represents every node (element) in the list.*/
typedef struct ListNode *ListPointer;
typedef struct ListNode
{
	ListElementType Data;
    ListPointer Next;
} ListNode;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void OrderedLimearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void BackupList(ListPointer Alist, ListPointer *BList);

main()
{
    ListPointer AList,BList;
    ListElementType Item;
    int i,num;
    CreateList(&AList);

    printf("Give the number of elements: ");
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        printf("Give Item to Insert in list:");
        scanf("%d",&Item);
        LinkedInsert(&AList,Item,NULL);
    }

    printf("\n The Original List has the following elements: ");
    LinkedTraverse(AList);
    CreateList(&BList);
    BackupList(AList,&BList);
    printf("\n The Backup list has the following elements: ");
    LinkedTraverse(BList);
    printf("\n");
    system("pause");

}

void CreateList(ListPointer *List)
/*Creates an empty linked list.
Returns the null pointer to that list.*/

{
	*List = NULL;
}

boolean EmptyList(ListPointer List)
/*Arguments: A pointer that points to the first node of the list.
Checks if the list is empty.
If it is returns true, else returns false.*/

{
	return (List==NULL);
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
/*Inserts a node that contains the Item value after the node that PredPtr points to.
If the list is empty, inserts the node at the beginning.
Returns the modified list.*/

{
	ListPointer TempPtr;

   TempPtr= (ListPointer)malloc(sizeof(struct ListNode));
   TempPtr->Data = Item;
	if (PredPtr==NULL) {
        TempPtr->Next = *List;
        *List = TempPtr;
    }
    else {
        TempPtr->Next = PredPtr->Next;
        PredPtr->Next = TempPtr;
    }
}

void LinkedDelete(ListPointer *List, ListPointer PredPtr)
/*PredPtr points to a node. This function deletes the previous node.
Or deletes the first node if the list has one node.
Prints a message if the list was empty. */

{
    ListPointer TempPtr;

    if (EmptyList(*List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    if (PredPtr==NULL)
        {
      	      TempPtr = *List;
              *List = TempPtr->Next;
        }
        else
        {
      	     TempPtr = PredPtr->Next;
             PredPtr->Next = TempPtr->Next;
        }
        free(TempPtr);
    }
}

void LinkedTraverse(ListPointer List)
/*Traverse the given list.*/

{
	ListPointer CurrPtr;

   if (EmptyList(List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    CurrPtr = List;
         while ( CurrPtr!=NULL )
        {
      	     printf(" %d", CurrPtr->Data);
             CurrPtr = CurrPtr->Next;
        }
   }
}

void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
/*Executes a linear search in the non-ordered linked list to find a node that contains the Item value.
If the search was successful CurrPtr points to the asked node and PredPtr points to the previous node. */

{
   ListPointer CurrPtr;
   boolean stop;

   CurrPtr = List;
   *PredPtr = NULL;
   stop= FALSE;
   while (!stop && CurrPtr!=NULL )
    {
         if (CurrPtr->Data==Item )
         	stop = TRUE;
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
	*Found=stop;
}

void OrderedLimearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
/*Executes a linear search in the ordered list to find the node that contains Item value or to find a free place
to add a node that will contain the Item value.
CurrPtr points to that node and PredPtr pointer to the previous one.*/
{
   ListPointer CurrPtr;
   boolean DoneSearching;

   CurrPtr = List;
   *PredPtr = NULL;
   DoneSearching = FALSE;
   *Found = FALSE;
   while (!DoneSearching && CurrPtr!=NULL )
    {
         if (CurrPtr->Data>=Item )
         {
         	DoneSearching = TRUE;
         	*Found = (CurrPtr->Data==Item);
         }
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
}
void BackupList(ListPointer AList, ListPointer *BList)
{
    if(!EmptyList(AList))
        *BList=AList;
    else
        printf("\nEmpty List...");
}
