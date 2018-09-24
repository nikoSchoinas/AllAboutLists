#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
/*This program creates an index with students that uses Binary Tree Search data structure.
The records are inside students.txt file with the appropriate form.
It handles some BST operations*/

/*Every BST node consists of a code and a record number*/
typedef struct {
    int code;
    int recNo;
}BinTreeElementType;

/*Every student record consists of his/hers code,surname,name,sex,year,grade*/
typedef struct {
    int code;
    char surname[20];
    char name[20];
    char sex;
    int year;
    double grade;
}StudentT;

/*A BinTreePointer that points to a bin tree node. Consists of BinTreeElementType
and pointers that point to left and right child*/
typedef struct BinTreeNode *BinTreePointer;
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
void menu(int *choice);
int BuildBST(BinTreePointer *Root);
void PrintStudent(int recNum);
void PrintStudentWithGrade(double grade);

main()
{
    BinTreePointer Root,LockPtr;
    int recNum,size,code,choice;
    double grade;
    BinTreeElementType indexRec;
    boolean Found;
    FILE *infile;
    StudentT student;

    do
   {
   	menu(&choice);
      switch(choice)
      {
         case 1:	size=BuildBST(&Root);
                    break;
         case 2:	printf("Give Student's code: ");
                    scanf("%d",&indexRec.code);
                    RecBSTSearch(Root,indexRec,&Found,&LockPtr);
                    if(Found)
                        printf("student already exist\n");
                    else
                        {

                            printf("Give student's surname: ");
                            scanf("%s" ,student.surname);
                            printf("Give student's name: ");
                            scanf("%s" ,student.name);
                            printf("Give student's year: ");
                            scanf("%d" ,&student.year);
                            printf("Give student's sex: ");
                            scanf(" %c" ,&student.sex);
                            printf("Give student's grade: ");
                            scanf("%lf",&student.grade);
                            indexRec.recNo=size++;
                            RecBSTInsert(&Root,indexRec);
                            infile=fopen("students.txt","a");
                            fprintf(infile,"%d, %s, %s, %c, %d, %lf\n",indexRec.code,student.surname,student.name,student.sex,student.year,student.grade);
                            fclose(infile);

                        }
         			break;
         case 3:    printf("Give student's code: ");
                    scanf("%d",&indexRec.code);
                    RecBSTSearch(Root,indexRec,&Found,&LockPtr);
                    if(Found)
                        PrintStudent(LockPtr->Data.recNo);
                    else
                        printf("Student does not exist");
         			break;
        case 4:    RecBSTInorder(Root);
         			break;
        case 5:	    printf("Give a grade to see the student's that have higher grade: ");
                    scanf("%lf",&grade);
                    PrintStudentWithGrade(grade);
         			break;

		}
   } while (choice!=6);
}

void menu(int *choice)
{
    printf("\n                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1. Create index from file\n");
    printf("2. Insert new student\n");
    printf("3. Search for a Student\n");
    printf("4. Print index\n");
    printf("5. Print Students with higher grade\n");
    printf("6. Quit\n");
    printf("\nChoice: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>7);
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
/*Arguments: A BST pointer that point to tree's root and an Item.
Inserts that Item to tree.
Returns the modified BST.*/
{
    if (BSTEmpty(*Root)) {
        (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        (*Root) ->Data.code = Item.code;
        (*Root) ->Data.recNo=Item.recNo;
        (*Root) ->LChild = NULL;
        (*Root) ->RChild = NULL;
    }
    else
        if (Item.code < (*Root) ->Data.code)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item.code > (*Root) ->Data.code)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("Item %d is already in BST.\n", Item.code);
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
        if (KeyValue.code < Root->Data.code)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue.code > Root->Data.code)
                RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
            else
                {
                    *Found = TRUE;
                    *LocPtr=Root;
                }
}


void RecBSTInorder(BinTreePointer Root)
/*Arguments: A BST pointer that points to tree's root.
Executes an in-order traversal and process each node just once.
Prints node's context.*/
{
    if (Root!=NULL) {
        RecBSTInorder(Root->LChild);
        printf("<%d, %d > ",Root->Data.code,Root->Data.recNo);
        RecBSTInorder(Root->RChild);
    }
}

int BuildBST(BinTreePointer *Root)
/*Arguments: A BinTreePointer that points to tree's root.
Reads record from files, made the appropriate structs and inserts them into the BST.*/
{
    FILE *fp;
    int size,nscan;
    char termch;
    BinTreeElementType indexRec;
    StudentT studentRec;
    CreateBST(&(*Root));
    fp=fopen("students.txt","r");
    size=0;
    if(fp!=NULL)
    {
        while(TRUE)
        {
            nscan=fscanf(fp,"%d, %20[^,], %20[^,], %c, %d, %lf%c",&studentRec.code,studentRec.surname,studentRec.name,&studentRec.sex,&studentRec.year,&studentRec.grade,&termch);
            if(nscan==EOF) break;
            indexRec.code=studentRec.code;
            indexRec.recNo=size;

            RecBSTInsert(&(*Root),indexRec);
            size++;

        }

    }



    fclose(fp);
    fflush(stdin);
    return size;
}

void PrintStudent(int recNum)
/*Arguments: a student's record number.
Reads the file and search the student that has that record number.*/
{
    FILE *infile;
    int nscan,lines=0;
    char termch;
    StudentT studentRec;

    infile=fopen("students.txt","r");
    if(infile!=NULL)
    {
        while(lines<=recNum)
        {
            nscan=fscanf(infile,"%d, %20[^,], %20[^,], %c, %d, %lf%c",&studentRec.code,studentRec.surname,studentRec.name,&studentRec.sex,&studentRec.year,&studentRec.grade,&termch);
            if(nscan==EOF) break;
            lines++;
        }
    }

    printf("Student Exist\n");
    printf("< %d, %s, %s, %c, %d, %lf > ",studentRec.code,studentRec.surname,studentRec.name,studentRec.sex,studentRec.year,studentRec.grade);
    fclose(infile);
}

void PrintStudentWithGrade(double grade)
/*Arguments: a grade.
Reads the file and prints the students that have higher grade than the input grade.*/
{
    FILE *infile;
    int nscan;
    char termch;
    StudentT studentRec;

    infile=fopen("students.txt","r");
    if(infile!=NULL)
    {
        while(TRUE)
        {
            nscan=fscanf(infile,"%d, %20[^,], %20[^,], %c, %d, %lf%c",&studentRec.code,studentRec.surname,studentRec.name,&studentRec.sex,&studentRec.year,&studentRec.grade,&termch);
            if(nscan==EOF) break;
            if(studentRec.grade>=grade)
                printf("< %d, %s, %s, %c, %d, %lf >\n ",studentRec.code,studentRec.surname,studentRec.name,studentRec.sex,studentRec.year,studentRec.grade);

        }
    }

}



