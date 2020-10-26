#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "assignment_1.h"

#ifndef book1
#define book1

struct book
{
    bool isFree;
    int nBytes;
    struct book *nextBook;
} ;
typedef struct book book;

#endif

char *p;
int size;

//function to allocate memory for the global array p, n number of bytes long.
void allocate(int n)
{
    p = malloc(n*sizeof(char));
    size=n;
    book* b = (book*)p;
    b->isFree=1;
    b->nBytes=n-sizeof(book);
    b->nextBook=NULL;
}

//function to allocate a block of size "size" from p
void* mymalloc(int Size)
{
    book* temp;
    book* curr = (book*)p;
    book* next;
    while(curr!=NULL)
    {
        if(curr->isFree && curr->nBytes>=Size)
        {   
            break;
        }
        curr=curr->nextBook;
    }

    

    //Memory allocation
    if(curr!=NULL && curr->nBytes>=Size)
    {   
        int freeBytes=curr->nBytes;
        next=curr->nextBook;
        //setting book structure for allocated block
        temp=curr;
        *temp = (book){.isFree=0, .nBytes=Size, .nextBook=next};

        //if there enough space left for book structure and atleast 1 free byte, i create the book struct for those bytes
        if(freeBytes-Size>sizeof(book))
        {    
            curr+=size+sizeof(book);
            temp->nextBook=curr;
            curr->nBytes = freeBytes-Size-sizeof(book);
            curr->isFree=1;
            curr->nextBook=next;
        }
        //if no space left i just allocate it to the previous block
        else
        {
            temp->nBytes = freeBytes;
        }
    }
    else
    {
        return NULL;
    }

    return temp+sizeof(book);
}

//free the block pointed to by the parameter
void myfree(void *b)
{
    book* key = (book*)(b)-sizeof(book); //gets the location of book structure of the current block
    key->isFree=1; //sets the book variable as free
    
    book* curr=(book*)p;
    book* prev=NULL;
    
    while (curr!=key)
    {
        prev=curr;
        curr=curr->nextBook;
    }

    //if next block is free, merge it with the current block
    if(curr->nextBook!=NULL)
    {
        book* next=curr->nextBook;
        if(next->isFree)
        {
            curr->nBytes+=next->nBytes+sizeof(book);
            curr->nextBook=next->nextBook;
        }
    }

    //if prev block is free, merge it with the prev block
    if(prev!=NULL)
    {
        if(prev->isFree)
        {
            prev->nBytes+=key->nBytes+sizeof(book);
            prev->nextBook=key->nextBook;
        }
    }
}

// prints bytes used by the bookkeeping structure
void print_book()
{
    printf("%d",sizeof(book));
}

// prints the memory array p in given format
void display_mem_map()
{
    book* temp= (book*)p;
    int count=0;
    while (temp!=NULL)
    {
        printf("%d\t%d\tbook\n",count,sizeof(book));
        count+=sizeof(book);
        if(temp->isFree)
            printf("%d\t%d\tfree\n",count,temp->nBytes);
        else
            printf("%d\t%d\tallocated\n",count,temp->nBytes);
        count+=(temp->nBytes);
        temp=temp->nextBook;
    }
}