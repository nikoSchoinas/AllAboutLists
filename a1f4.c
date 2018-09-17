#include <stdio.h>
#include <stdlib.h>
/*This*/

/*The size of the linked list. In this program equals to 10*/
#define NumberOfNodes 10
/*A value that indicates the end of the linked list*/
#define NilValue 0

/*Every element of the list it will be that data type*/
typedef int ListElementType;

typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer  Next;
} NodeType;


typedef enum {
    FALSE, TRUE
} boolean;


void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateLList(ListPointer *List);
boolean EmptyLList(ListPointer List);
boolean FullLList(ListPointer List);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);
void menu(int *choice);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);
void Search(ListPointer FreePtr, ListPointer List, NodeType Node[NumberOfNodes], ListElementType Item,
boolean *found, ListPointer *PredPtr);

main()
{
    ListPointer AList;
    NodeType Node[NumberOfNodes+1];
    ListPointer FreePtr,PredPtr;

    ListElementType AnItem;
    boolean *found;

   int choice, i;
   char ch;

   InitializeStoragePool(Node, &FreePtr);
   printAll(AList, FreePtr, Node);
   do
   {
   	menu(&choice);
      switch(choice)
      {
      	  case 1: CreateLList(&AList);          //DHMIOYRGIA LISTAS
      	             break;
          case 2:	do
                    {
   	                    printf("FreePtr=%d\n",FreePtr);
                        printf("Give a number to be inserted into the list: ");
                        scanf("%d", &AnItem);
                        /*The insertion is taking place at the start of the list.*/
                        PredPtr=NilValue;
                        Insert(&AList, Node,&FreePtr, PredPtr, AnItem);
                        printf("AList=%d\n",AList);
                        printf("\nContinue Y/N: ");
                        do
                        {
      	                     scanf("%c", &ch);
                        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
                    } while (toupper(ch)!='N');
                    printAll(AList, FreePtr, Node);
                    break;
          case 3:	printf("FreePtr=%d\n",FreePtr);
                    TraverseLinked(AList, Node);      //list traversal
         			break;
          case 4:   if (EmptyLList(AList))
      	                 printf("Empty List\n");
      	            else

      	            {
                        printAll(AList, FreePtr, Node);
                        printf("Give the position of the previous element for deletion: ");
                        scanf("%d", &PredPtr);
                        Delete(&AList, Node, &FreePtr, PredPtr);  //delete the element
                        printAll(AList, FreePtr, Node);
                    }
         			break;
          case 5:   if (EmptyLList(AList))
      	                 printf("Empty List\n");
      	            else printf("Not an Empty List\n");
      	            break;
      	case 6:   if (FullLList(FreePtr))
      	                 printf("Full List\n");
      	            else printf("Not a Full List\n");
      	            break;
      	 case 7:	printAll(AList, FreePtr, Node);     //show STORAGE POOL
         			break;
         case 8:    printf("Give number to search: ");
                    scanf("%d",&AnItem);
                    Search(FreePtr,AList,Node,AnItem,found,&PredPtr);
                    if(*found)
                        printf("\n this element has a previous element in position %d",PredPtr);
                    else
                        printf("no element found");
                    break;




	  }
   } while (choice!=9);

	return 0;






}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)
/*Arguments: the Node array and the FreePtr that points to the next free node
Initialize Node array as a linked list by linking the array's elements together. Also initialize FreePtr pointer
Returns the new Node array and the FreePtr pointer of the first free node.*/

{
   int i;

    for (i=1; i<NumberOfNodes;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data=-1;
    }
    Node[NumberOfNodes].Next=0;
    Node[NumberOfNodes].Data=0;
    *FreePtr=1;
}

void CreateLList(ListPointer *List)
/*Creates an empty linked list. Returns a non zero pointer that points to that list*/

{
  *List=NilValue;
}

boolean EmptyLList(ListPointer List)
/*Arguments: a pointer that point to a linked list.
Checks if a linked list is empty.
Returns true if the linked list is empty. False if not.*/
{
  return (List==NilValue);
}

boolean FullLList(ListPointer List)
/*Arguments: A linked list
Checks if this linked list is full.
Returns true if linked list is full. Else returns false.*/
{
  return (List==NilValue);
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
/*Arguments: Node array and FreePtr pointer.
Gets a free node that pointer P can point.
Returns P pointer and the modified FreePrt pointer that now points to a free node */

{
  *P = *FreePtr;
  if (*FreePtr!=0)
    *FreePtr =Node[*FreePtr].Next;
}

void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr)
/*Arguments: Node array which is the storage pool of available nodes.
Now the storage pool knows in which node the TempPtr pointer points.
Returns the modified Node array and the FreePtr pointer.*/

{
  Node[P].Next =*FreePtr;
  Node[P].Data = -1;
  *FreePtr =P;
}

void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
/*This function inserts into the linked list, if it's not full, the element (Item) after the node that PredPrt points to.
Returns the modified linked list, Node array, FreePtr.
Prints a message if list is full.*/

{
  ListPointer TempPtr;
  GetNode(&TempPtr,FreePtr,Node);
  if (!FullLList(TempPtr)) {
    if (PredPtr==NilValue)
    {
        Node[TempPtr].Data =Item;
        Node[TempPtr].Next =*List;
        *List =TempPtr;
    }
    else
      {
        Node[TempPtr].Data =Item;
        Node[TempPtr].Next =Node[PredPtr].Next;
        Node[PredPtr].Next =TempPtr;
      }
}
  else
    printf("Full List ...\n");
}

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr)
/*PredPtr points to a node. This function deletes the previous node from the list if it's not empty.
Returns the modified list and FreePtr pointer.
Prints a message if list is empty.*/
{
  ListPointer TempPtr ;

  if (!EmptyLList(*List))
//    if (PredPtr==NilValue)
    if (PredPtr==(*List)-1)
    {
        TempPtr =*List;
        *List =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        Node[PredPtr].Next =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
      }
  else
    printf("Empty List ...\n");
}

void TraverseLinked(ListPointer List, NodeType Node[])
/*Arguments: a linked list.
Traverse the list , if it's not empty.
Prints the elements of list.*/
{
  ListPointer CurrPtr;

  if (!EmptyLList(List))
  {
      CurrPtr =List;
      while (CurrPtr != NilValue)
      {
          printf("(%d,%d,%d) ",CurrPtr,Node[CurrPtr].Data, Node[CurrPtr].Next);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}
void menu(int *choice)
{
    printf("                  MENU                  \n");
    printf("-------------------------------------------------\n");
    printf("1. Create List\n");
    printf("2. Insert an element to List\n");
    printf("3. Traverse List\n");
    printf("4. Delete an element from the List\n");
    printf("5. Check if List is empty\n");
    printf("6. Check if List is full\n");
    printf("7. Print storage pool\n");
    printf("8. Search an item\n");
    printf("9. End\n");
    printf("\nChoice 1-9: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>8);
}
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[])
{
    int i;
    printf("1ST ELEMENT OF THE LIST = %d, 1st FREE POSITION = %d\n", List, FreePtr);
    printf("STORAGE POOL HAT THE ABOVE ELEMENTS\n");
    for (i=1;i<=NumberOfNodes;i++)
        printf("(%d,%d,%d) ",i,Node[i].Data, Node[i].Next);
    printf("\n");
}
void Search(ListPointer FreePtr, ListPointer List, NodeType Node[NumberOfNodes], ListElementType Item,
boolean *found, ListPointer *PredPtr)
{
     ListPointer CurrPtr;
     boolean stop;
     stop=FALSE;

  if (!EmptyLList(List))
  {
      CurrPtr =List;
      *PredPtr=NilValue;
      while (CurrPtr != NilValue && !stop)
      {
          if(Node[CurrPtr].Data>=Item)
          {
              stop=TRUE;
              *found=(Node[CurrPtr].Data==Item);
          }
          else
          {
              *PredPtr=CurrPtr;
              CurrPtr=Node[CurrPtr].Next;
          }

       }

   }
   else *found=FALSE;

}

