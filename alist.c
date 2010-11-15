
/* implementation of generic linked list class
   Fri Jul 23 09:58:26 GMTDT 2010 */

#include "alist.h"


/* adds a node to the collection */
void aList_Add(aNode** obj, void* data,
	       unsigned int sz)
{
    /* indext counter declared static */
    static unsigned int ix_counter = 0;
    
    /* if memory size was not assigned
       return function */
    if(sz == 0)
	return;
    
    aNode* temp;		/* temporary node */

    /* create pointer */
    temp = (aNode*) malloc(sizeof(aNode));
    
    temp->data = malloc(sz);	/* create mem for data obj */

    /* copy memory to new location */
    memcpy(temp->data, data, sz);
    
    temp->ix = ix_counter++;	/* increment index counter */
    
    temp->next = *obj;

    *obj = temp;

    return;
}

void aList_AddB(aNode** obj, void* data,
		unsigned int sz)
{
    /* if first node call insert from front */
    if(*obj == NULL)
	{	
	    aList_Add(obj, data, sz);
	    return;
	}

    /* if memory size was not assigned
       return function */
    if(sz == 0)
	return;
    
    aNode* temp;		/* temporary node */

    /* create pointer */
    temp = (aNode*) malloc(sizeof(aNode));
    temp = *obj;
    while(temp->next != NULL)
	temp = temp->next;


    aNode* last = (aNode*) malloc(sizeof(aNode));
	
    last->data = malloc(sz);	/* create mem for data obj */
	
    /* copy memory to new location */
    memcpy(last->data, data, sz);
	
    last->next = NULL;			/* set next pointer to NULL */
	
    last->ix++;					/*index counter */
    if(temp)
	{
	    temp->next = last;
	}
    else
	{
	    temp = last;
	}
    return;

}


/* return the count of objects */ 
unsigned int  aList_Count(aNode** obj)
{
    int counter = 0;
    if(!obj)
	return 0;

    aNode* tmp = *obj;

    while(tmp != NULL)
	{
	    counter++;
	    tmp = tmp->next;
	}
    return counter;
}

void aList_Clear(aNode** obj)
{
    /* if null pointer return */
    if(!obj)
	return;

    aNode* current = *obj;
    aNode* del_node;

    while(current != NULL)
	{
	    del_node = current;
	    current = current->next;

	    free(del_node);
	}

    return;
}


/* return the object with index number ix */
aNode* aList_Item(aNode** obj, unsigned int ix)
{
    aNode* temp = *obj;

    while(temp != NULL)
	{
	    /* if index is found return break
	       loop and return object */
	    if(temp->ix == ix)
		break;

	    temp = temp->next;
	}

    return temp;
}
