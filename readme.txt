I'm implementing First-Fit policy.
In the allocate function im using malloc to give the initial memory, 
and setting a bookkeeping structure for the initial case.

In mymalloc function, I first traverse the book structures and break from the
while loop whenever I find a free block of memory big enough to hold the 
requested char array. If there is no enough free space, curr becomes NULL
and my program returns NULL. If a free block is found, I set the book structure for
it and check if theres enough space if there enough space left for book structure
and atleast 1 free byte, I create the book struct for those bytes, else
i just allocate it to the previous block.

In myfree function, I first set the block as free and then check for contiguous
free block and merge them.

My book-keeping structure contains a bool value 'isFree' which if is 1 indicates
that its free and allocated otherwise. Then theres int 'nBytes' which stores the
number of bytes free/allocated. The last variable is a pointer to next book 
structure called 'nextBook'.

Got a better understanding of how memory management works in C.
And learnt how to debug huge chuncks of code.