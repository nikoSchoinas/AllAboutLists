#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
/*This program find all odd and prime numbers from 1 to 59.
Then creates a set for each category and does some set operations.*/

#define max_size 59       // set's max size

typedef enum {
    FALSE, TRUE
} boolean;

/*an array with booleans. */
typedef boolean setType[max_size+1];
/*Every set's elements is an integer but it's been declares as setElement.*/
typedef int setElement;

void Create(setType set);
void Universal(setType set);
void Union(setType s1, setType s2, setType uni);
void Intersect(setType s1, setType s2, setType inter);
void Difference(setType s1, setType s2, setType diff);
boolean IsMebmer(setElement stoixeio, setType set);
void displayset(setType set);
boolean IsPrime (int n);
void  Complement (setType set1,setType set2);

main()
{
    setType universal_set,prime_set,odd_set,intersect,union_set,difference,supplement;

    int i;
    Create(universal_set);
    Create(prime_set);
    Create(odd_set);
    Universal(universal_set);

    for ( i=1;i<=max_size;i+=2)
        odd_set[i]=TRUE;
    printf("Odd numbers from 1 to 59: \n");
    displayset(odd_set);
    printf("\n");

    for(i=1;i<=max_size;i++)
    {
         if(IsPrime(i))
           prime_set[i]=TRUE;
    }
    printf("Prime numbers from 1 to 59: \n");
    displayset(prime_set);
    printf("\n");
    Intersect(odd_set,prime_set,intersect);
    printf("Intersect between prime and odd numbers: \n");
    displayset(intersect);
    printf("\n");
    Union(odd_set,prime_set,union_set);
    printf("Union between prime and odd numbers: \n");
    displayset(union_set);
    printf("\n");
    Difference(odd_set,prime_set,difference);
    printf("Difference between prime and odd numbers: \n");
    displayset(difference);
    printf("\n");
    Complement(prime_set,supplement);
    printf("Complement of prime numbers: \n");
    displayset(supplement);
    printf("\n");

}

void displayset(setType set)
/*It takes a set and display it's elements*/
{
	setElement i;

	for (i=1;i <= max_size;i++)
	{
		if((set[i]))
			printf(" %d",i);
	}
	printf("\n");
}

void Create(setType set)
/*Creates an empty set.*/

{
    setElement i;

    for (i = 1; i <= max_size; i++)
        set[i] = FALSE;
}

void Universal(setType set)
/*It takes a set and makes every position true (from 1 to 59).*/
{
    setElement i;

    for (i = 1; i <= max_size; i++)
        set[i] = TRUE;
}
boolean IsMebmer(setElement element, setType set)
/*Arguments: a set and an element
Checks if that element belongs to set.
Returns true if exists in set. Else returns false.*/
{
    return set[element];
}

void Union(setType s1, setType s2, setType uni)
/*Arguments: Two sets.
Creates a new set that is the union of those sets.
Returns the new set.*/
{
    setElement i;

    for (i = 1; i <= max_size; i++)
        uni[i] = IsMebmer(i, s1) || IsMebmer(i, s2);
}

void Intersect(setType s1, setType s2, setType inter)
/*Arguments: Two sets.
Creates a new set that is the intersect of those sets.
Returns the new set.*/
{
    setElement i;

    for (i = 1; i <= max_size; i++)
        inter[i] = IsMebmer(i, s1) && IsMebmer(i, s2);
}

void Difference(setType s1, setType s2, setType diff)
/*Arguments: Two sets.
Creates a new set that is the difference of those sets.
Returns the new set.*/
{
    setElement i;

    for (i = 1; i <= max_size; i++)
        diff[i] = IsMebmer(i, s1) && (!IsMebmer(i, s2));
}

boolean IsPrime (int n)
/*Checks if integer n is prime or not.
Returns true if it's prime, else returns false.*/
{
    int i,limit;
    if (n<=1) return FALSE;
    if (n==2) return TRUE;
    if (n%2==0) return FALSE;
    limit=sqrt(n) +1;
    for (i=3;i<=limit;i+=2)
    {
        if(n%i==0) return FALSE;

    }
    return TRUE;
}

void  Complement (setType set1,setType set2)
/*Takes a set and returns its complement.
The complement is the universal set except from those numbers that exist in prime set.*/

{
    int i;

    Create(set2);
    for (i=1;i<=max_size;i++)
    {
        if (!set1[i])
            set2[i]=TRUE;
    }
}
