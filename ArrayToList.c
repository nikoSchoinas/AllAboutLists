#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define matrixElements 10
/*This program asks user to give a a word and place it in an array.
Then the array is turned into a list.
Finally prints the list's element and the word is displayed backwards.  */
//*List element type. It's a character actually.*/
typedef char ListElementType;
/*ListPointer points to a struct.*/
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
void FromArrayToList(ListPointer *AList,char str[]);


main()
{
    ListPointer AList;
    char str[matrixElements];
    int i;
    CreateList(&AList);
    printf("\nGive a string up to %d characters: ",matrixElements);
    scanf("%s",str);
    FromArrayToList(&AList,str);
    printf("\nThe elements from  matrix had passed to a list");
    printf("\nThe List has the following elements: ");
    LinkedTraverse(AList);

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
      	     printf("%c", CurrPtr->Data);
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
void FromArrayToList(ListPointer *AList,char str[])
/*This function places the array's characters into the list.
It starts from the first character. */
{
    int i;
    for(i=0;i<strlen(str);i++)
        LinkedInsert(AList,str[i],NULL);
}
