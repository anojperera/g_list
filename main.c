/* testing genering collection class
   Sat Jul 24 18:27:43 BST 2010 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alist.h"

static int Display(void* data, unsigned int ix)
{
    /* print data */
    printf ("%s-index%d\n",(char*) data, ix);
    return 0;
}


int main(int argc, char** argv)
{
    int flg = 0;
    if(argc > 1)
	flg = atoi(argv[1]);
    else
	flg = 0;
    
    aNode* first = aList_New();
    
    /* aNode* first = NULL; */
	
    char ch1[] = "Test 1";
    char ch2[] = "Test 2";
    char ch3[] = "Test 3";
    char ch4[] = "This is awesom";
    char ch5[] = "Working fine\n and !";

    aList_Add(&first, ch1, strlen(ch1)+1);
    aList_Add(&first, ch2, strlen(ch2)+1);
    aList_Add(&first, ch3, strlen(ch3)+1);
    aList_Add(&first, ch4, strlen(ch4)+1);
    aList_Add(&first, ch5, strlen(ch5)+1);
	
    int i = 0;
    int MAX = aList_Count(&first);
    aNode* tmp;

    for(i=0; i<MAX; i++)
	{
	    tmp = aList_Item(&first, i);
	    /* printf("%s %i\n", (char*) tmp->data, i); */
	}

    aList_Display(&first, flg, Display);

    aList_Clear(&first);
    return 0;
}



