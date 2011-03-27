/* testing genering collection class
   Sat Jul 24 18:27:43 BST 2010 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "alist.h"

static int Display(void* data, unsigned int ix)
{
    /* print data */
    printf ("%i-index%d\n",*((int*) data), ix);
    return 0;
}

int test1(int argc, char** argv);
int test2(int argc, char** argv);

int main(int argc, char** argv)
{
    return test2(argc, argv);
}

int test2(int argc, char** argv)
{
    time_t start_time, end_time;
    int cnt = 5, ix = 0;
    
    int i;
    if(argc > 1)
	cnt = atoi(argv[1]);
    else
	cnt = 5;

    if(argc > 2)
	ix = atoi(argv[2]);
    else
	ix = 0;
    

    aNode* first = aList_New();

    for(i=0; i<cnt; i++)
	{
	    aList_Add(&first, (void*) &i, sizeof(int));
	}

    aNode* sObj;
    time(&start_time);    
    if(ix < 0)
	{
	    time(&end_time);
	    aList_Display(&first, 1, Display);
	}
    else
	{
	    sObj = aList_Item(&first, ix);
	    time(&end_time);
	    if(sObj)
		printf ("%i-index%d\n",*((int*) sObj->data), ix);
	}

    double diff_time = difftime(end_time, start_time);
    printf("Array addimg time %.6lf\n", diff_time);

    aList_Clear(&first);
    return 0;
}



int test1(int argc, char** argv)
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

    char** buff = (char**) calloc(5, sizeof(char*));
    int i = 0;
    for(i=0; i<5; i++)
	{
	    switch(i)
		{
		case 0:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch1) + 1));
	    
		    strcpy(buff[i], ch1);
		    break;
		case 1:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch2) + 1));
	    
		    strcpy(buff[i], ch2);
		    break;
		case 2:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch3) + 1));
	    
		    strcpy(buff[i], ch3);
		    break;
		case 3:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch4) + 1));
	    
		    strcpy(buff[i], ch4);
		    break;
		case 4:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch5) + 1));
	    
		    strcpy(buff[i], ch5);
		    break;		    
		}
	    aList_Add(&first, buff[i], strlen(buff[i])+1);
	}

    for(i=0; i<5; i++)
    	{
    	    free(buff[i]);
    	    buff[i] = NULL;
    	}
    free(buff);
    /* aList_Add(&first, ch1, strlen(ch1)+1); */
    /* aList_Add(&first, ch2, strlen(ch2)+1); */
    /* aList_Add(&first, ch3, strlen(ch3)+1); */
    /* aList_Add(&first, ch4, strlen(ch4)+1); */
    /* aList_Add(&first, ch5, strlen(ch5)+1); */
	
    /* int i = 0; */
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

