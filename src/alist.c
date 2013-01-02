
/* implementation of generic linked list class
   Fri Jul 23 09:58:26 GMTDT 2010 */

#include "alist.h"

/* indext counter declared static */
/* unsigned int ix_counter = 0; */

/* constructor */
aNode* aList_New()
{
    return NULL;
}

/* adds a node to the collection */
void aList_Add(aNode** obj, void* data,
	       unsigned int sz)
{

    
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

    if(*obj != NULL)
	{
	    (*obj)->previous = temp; 	/* set previous to current node */
	    temp->last = (*obj)->last;

	    if((*obj)->ix_counter == 1)
		temp->last = *obj;

	    temp->ix_counter = (*obj)->ix_counter;
	}
    else
	temp->ix_counter = 0;

    temp->ix = temp->ix_counter++;	 	/* increment index counter */
    
    temp->next = *obj;

    *obj = temp;

    return;
}

inline void aList_Add2(aNode** obj,				/* link list item */
			   void* data,				/* data pointer */
			   unsigned int sz,			/* object size */
			   void* usr_obj,			/* user object */
			   int (*callback_add)(void*, void*))	/* callback function to be call to complete the add */
{
    /* call add method */
    aList_Add(obj, data, sz);
    /* if function pointer was passed call function pointer */
    if(callback_add)
	callback_add((*obj)->data, (usr_obj? usr_obj : NULL));
}

/* Add3 method doesn't copy the contents internally. */
inline void aList_Add3(aNode** obj,				/* link list item */
		       void* data,				/* data pointer */
		       void* usr_obj,				/* user object, passed to second argument of callback */
		       int (*callback)(void*, void*))		/* (data pointer, user object) */
{
    aNode* _tmp = NULL;						/* temporary node */

    /* create pointer */
    _tmp = (aNode*) malloc(sizeof(aNode));
    _tmp->data = data;						/* set data */
    _tmp->previous = NULL;
    if(*obj != NULL)
	{
	    (*obj)->previous = _tmp;				/* set previous to current node */
	    _tmp->last = (*obj)->last;
	    if((*obj)->ix_counter == 1)
		_tmp->last = *obj;
	    _tmp->ix_counter = (*obj)->ix_counter;
	}
    else
	_tmp->ix_counter = 0;

    _tmp->ix = _tmp->ix_counter++;				/* increment index counter */
    _tmp->next = *obj;
    *obj = _tmp;
    if(callback)						/* call function pointer if assigned */
	callback((*obj)->data, (usr_obj? usr_obj : NULL));
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

	    del_node->data = NULL;
	    free(del_node);
	    del_node = NULL;
	}

    /* *obj = NULL; */
    return;
}

/* Second clear function calls a function pointer deallocating memory */
inline void aList_Clear2(aNode** obj, int (*callback) (void* obj, unsigned int))
{
    if(!obj)
	return;

    aNode* current = *obj;
    aNode* del_node;
    while(current != NULL)
	{
	    del_node = current;

	    /* check if callback function assigned */
	    if(callback)
		callback(del_node->data, del_node->ix);

	    del_node->data = NULL;
	    current = current->next;
	    free(del_node);
	    del_node = NULL;
	}
	    
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
    aNode* tmp = NULL;

    /* depengind on the start flag
       iterate from last or first */
    if(s_flg)
	tmp = (*obj)->last;
    else
	tmp = *obj;

    int i = 0;
    while(tmp != NULL)
	{
	    if(callback(tmp->data, tmp->ix))
		break;
	    
	    if(s_flg)
		tmp = tmp->previous;
	    else
		tmp = tmp->next;
	    i++;
	}

    return 1;
    
}

/* Display Function 2 */
int aList_Display2(aNode** obj,
		       int s_flg,
			   int (*callback) (void*, void*, unsigned int),
		       void* c_obj)
{
    /* check for pointers */
    if(!obj || !(*obj) || !callback)
	return 0;

    /* declare temporary node */
    aNode* tmp = NULL;
    
   /* depengind on the start flag
       iterate from last or first */
    if(s_flg)
	tmp = (*obj)->last;
    else
	tmp = *obj;

    int i = 0;

    while(tmp != NULL)
	{
	    if(callback(c_obj, tmp->data, tmp->ix))
		return 0;
	    
	    if(s_flg)
		tmp = tmp->previous;
	    else
		tmp = tmp->next;

	    i++;
	}

    return i;
}

/* returns the data held in list and increments */
int aList_Next(aNode** obj, void* val)
{
    if(!obj || !(*obj))
	{
	    val = NULL;
	    return 0;
	}

    val = (*obj)->data;

    /* increment */
    (*obj) = (*obj)->next;

    return 1;
	
}

/* int aList_Previous(aNode** obj, void* val) */
/* { */
/*     if(!obj || !(*obj)) */
/* 	{ */
/* 	    val = NULL; */
/* 	    return 0; */
/* 	} */

/*     val = (*obj)->data; */
    
/*     (*obj) = (*obj)->previous; */
/* } */
