
/* implementation of generic linked list class
   Fri Jul 23 09:58:26 GMTDT 2010 */

#include "alist.h"

/* constructor */
aNode* aList_New()
{
    /* aNode* tmp; */

    /* /\* create mem *\/ */
    /* tmp = (aNode*) malloc(sizeof(aNode)); */

    /* /\* check for NULL pointer *\/ */
    /* if(!tmp) */
    /* 	return NULL; */

    /* /\* initialise elements *\/ */
    /* tmp->ix = 0; */
    /* tmp->data = NULL; */
    /* tmp->next = NULL; */
    /* tmp->previous = NULL; */
    return NULL;
}

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

    temp->previous = NULL;

    if(ix_counter != 0)
	{
	    (*obj)->previous = temp; 	/* set previous to current node */
	    temp->last = (*obj)->last;

	    if(ix_counter == 1)
		temp->last = *obj;
	}
    
    temp->ix = ix_counter++;	 	/* increment index counter */
    
    temp->next = *obj;

    *obj = temp;

    return;
}

/* void aList_AddB(aNode** obj, void* data, */
/* 		unsigned int sz) */
/* { */
/*     /\* if first node call insert from front *\/ */
/*     if(*obj == NULL) */
/* 	{	 */
/* 	    aList_Add(obj, data, sz); */
/* 	    return; */
/* 	} */

/*     /\* if memory size was not assigned */
/*        return function *\/ */
/*     if(sz == 0) */
/* 	return; */
    
/*     aNode* temp;		/\* temporary node *\/ */

/*     /\* create pointer *\/ */
/*     temp = (aNode*) malloc(sizeof(aNode)); */
/*     temp = *obj; */
/*     while(temp->next != NULL) */
/* 	temp = temp->next; */


/*     aNode* last = (aNode*) malloc(sizeof(aNode)); */
	
/*     last->data = malloc(sz);	/\* create mem for data obj *\/ */
	
/*     /\* copy memory to new location *\/ */
/*     memcpy(last->data, data, sz); */
	
/*     last->next = NULL;			/\* set next pointer to NULL *\/ */
	
/*     last->ix++;					/\*index counter *\/ */
/*     if(temp) */
/* 	{ */
/* 	    temp->next = last; */
/* 	} */
/*     else */
/* 	{ */
/* 	    temp = last; */
/* 	} */
/*     return; */

/* } */


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

    /* *obj = NULL; */
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

/* display results */
int aList_Display(aNode** obj,
		  int s_flg,
		  int (*callback) (void* , unsigned int))
{
    /* check for NULL pointer */
    if(!obj || !(*obj))
	return 0;

    /* check function pointer */
    if(!callback)
	return 0;

    /* declare temporary node */
    aNode* tmp;

    /* depengind on the start flag
       iterate from last or first */
    if(s_flg)
	tmp = (*obj)->last;
    else
	tmp = *obj;

    int i = 0;
    while(tmp != NULL)
	{
	    callback(tmp->data, tmp->ix);
	    
	    if(s_flg)
		tmp = tmp->previous;
	    else
		tmp = tmp->next;
	    i++;
	}

    return 0;
    
}
