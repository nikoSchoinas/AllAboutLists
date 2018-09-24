#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
/*This program creates a binary tree from file.
File's name should be I13F5.txt (can change in BuildBST function) 
and the records should be "Surname Name Code" (without "" or commas ,) (see I13F5.txt file).
Code should be between 1 to 3.
1--> office employee
2--> labor
3--> representative
There is a menu to handle binary tree operations.*/

/*Every tree's element consists of two char arrays and an integer.*/
typedef struct{
    char surname[20];
    char name[20];
    int code;
}BinTreeElementType;

/*A pointer that points to a BinTreeNode*/
typedef struct BinTreeNode *BinTreePointer;

/*Every tree's node consists of BinTreeElementType data and pointers to left and Right child.*/
 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTInorder(BinTreePointer Root);
void BuildBST(BinTreePointer *ARoot1,BinTreePointer *ARoot2, BinTreePointer *ARoot3);
void menu(int *choice);

main()
{
    BinTreePointer ARoot1,ARoot2,ARoot3,LockPtr;
    int choice, code;
    BinTreeElementType EmpRec;
    boolean Found;

    do
   {
   	menu(&choice);
      switch(choice)
      {
      	 case 1:	BuildBST(&ARoot1,&ARoot2,&ARoot3);
                    break;
         case 2:	printf("Give employee's surname: ");
                    scanf("%s", EmpRec.surname);
                    printf("Give employee's name: ");
                    scanf("%s",EmpRec.name);
                    printf("Give employee's code: ");
                    scanf("%d",&EmpRec.code);
                    if(EmpRec.code==1)
                        RecBSTInsert(&ARoot1,EmpRec);
                    else if(EmpRec.code==2)
                        RecBSTInsert(&ARoot2,EmpRec);
                    else if(EmpRec.code==3)
                        RecBSTInsert(&ARoot3,EmpRec);
                    break;

         case 3:    printf("Give employee's surname: ");
                    scanf("%s",EmpRec.surname);
                    printf("Give employee's code: ");
                    scanf("%d",&EmpRec.code);
                    if(EmpRec.code==1)
                        RecBSTSearch(ARoot1,EmpRec,&Found,&LockPtr);
                    else if(EmpRec.code==2)
                        RecBSTSearch(ARoot2,EmpRec,&Found,&LockPtr);
                    else if(EmpRec.code==3)
                        RecBSTSearch(ARoot3,EmpRec,&Found,&LockPtr);
                    if(Found)
                        {
                            printf("The employee exist:\n");
                            printf("< %s , %s, %d > \n",LockPtr->Data.surname,LockPtr->Data.name,LockPtr->Data.code);
                        }
                    else
                        printf("The employee does not exist: \n");
                    break;

        case 4:     printf("\nOffice Employees: \n");
                    RecBSTInorder(ARoot1);
                    printf("\nLabors: \n");
                    RecBSTInorder(ARoot2);
                    printf("\nRepresentatives: \n");
                    RecBSTInorder(ARoot3);
         			break;
		}
   } while (choice!=5);


}

void CreateBST(BinTreePointer *Root)
/*Creates an empty binary search tree.
Returns a null pointer that it will be the tree's root.*/
{
    *Root = NULL;
}

boolean BSTEmpty(BinTreePointer Root)
/*Arguments: A BST pointer that points to tree's root.
Checks if BST is empty.
If it is empty returns true. Else returns false.*/
{
    return (Root==NULL);
}

void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item)
/*Arguments: A BST pointer that point to tree's root and an element.
Inserts that element to tree.
Returns the modified BST.*/
{
    if (BSTEmpty(*Root)) {
        (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        strcpy((*Root) ->Data.surname,Item.surname);
        strcpy((*Root) ->Data.name,Item.name);
        (*Root) ->Data.code=Item.code;
        (*Root) ->LChild = NULL;
        (*Root) ->RChild = NULL;
    }
    else if (strcmp(Item.surname,(*Root) ->Data.surname)<0)
            RecBSTInsert(&(*Root) ->LChild,Item);
       else if (strcmp(Item.surname,(*Root) ->Data.surname)>0)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("Record exists in BST.\n");
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue,
                    boolean *Found, BinTreePointer *LocPtr)
/*Arguments: A BST pointer that points to tree's root and a key value.
Searches a tree node with that key value.
If that node is found then LocPtr pointer points to that node and variable *found is true.
If not, variable *found is false. */
{


    if (BSTEmpty(Root))
        *Found=FALSE;
    else
        if (strcmp(KeyValue.surname, Root->Data.surname)<0)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (strcmp(KeyValue.surname, Root->Data.surname)>0)
                RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
            else
                {
                    *Found = TRUE;
                    *LocPtr=Root;
                }
}



void RecBSTInorder(BinTreePointer Root)
/*Arguments: A BST pointer that points to tree's root.
It runs an in-order search so it process each node just once.
Prints the node's content.*/
{
    if (Root!=NULL) {
        RecBSTInorder(Root->LChild);
        printf("< %s , %s, %d > \n",Root->Data.surname,Root->Data.name,Root->Data.code);
        RecBSTInorder(Root->RChild);
    }

}




void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1. Create BST's from file\n");
    printf("2. Insert a new employee\n");
    printf("3. Search for an employee\n");
    printf("4. Print employees\n");
    printf("5. Quit\n");
    printf("\nChoice: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>4);
}

void BuildBST(BinTreePointer *ARoot1,BinTreePointer *ARoot2, BinTreePointer *ARoot3)
{
    FILE *fp;
    BinTreeElementType EmpRec;
    CreateBST(&(*ARoot1));
    CreateBST(&(*ARoot2));
    CreateBST(&(*ARoot3));
    fp=fopen("I13F5.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s",EmpRec.surname);
        fscanf(fp,"%s",EmpRec.name);
        fscanf(fp,"%d",&EmpRec.code);

        if(EmpRec.code==1)
            RecBSTInsert(ARoot1,EmpRec);
        else if (EmpRec.code==2)
            RecBSTInsert(ARoot2,EmpRec);
        else if (EmpRec.code==3)
            RecBSTInsert(ARoot3,EmpRec);
    }

    fclose(fp);

}
