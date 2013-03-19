/* Implementation of blist */
/* Mon Mar 11 21:48:00 GMT 2013 */

#include "blist.h"

#define BLIST_OBJ_CHK(obj) \
    if(obj==NULL) return -1

/* Constructor method */
int blist_new(blist* obj, void (*delete)(void* data))
{
    /* initialise the list */
    obj->_elm_count = 0;
    obj->_comp = NULL;
    obj->_delete = delete;
    obj->_head = NULL;
    obj->_tail = NULL;
    pthread_mutex_init(&obj->_mutex, NULL);
    return 0;
}

/* destroy list */
void blist_delete(blist* obj)
{
    void* _data;
    if(obj == NULL)
	return;
    /* iterate over the elements and remove */
    while(blist_count(obj) > 0)
	{
	    if(blist_remove(obj, blist_get_tail(obj), (void**) &_data) == 0)
		{
		    /* call function pointer for delete */
		    if(obj->_delete)
			obj->_delete(_data);
		}
	    
	}

    /* finally initialise struct to NULL */
    pthread_mutex_destroy(&obj->_mutex);
    obj->_comp = NULL;
    obj->_delete = NULL;
    obj->_head = NULL;
    obj->_tail = NULL;
    return;
}

/* Add next method */
int blist_add_next(blist* obj, blist_elm* element, void* data)
{
    blist_elm* _new_elm;			/* new element */
    BLIST_OBJ_CHK(obj);
    
    if(element == NULL && blist_count(obj) > 0)
	return -1;

    /* create new element */
    _new_elm = (blist_elm*) malloc(sizeof(blist_elm));
    if(_new_elm == NULL)
	return -1;
    _new_elm->_ix = 0;
    /* add data to new element */
    _new_elm->_data = (void*) data;

    /* if its the first element */
    if(blist_count(obj) == 0)
	{
	    obj->_head =  _new_elm;
	    obj->_head->_prev = NULL;
	    obj->_head->_next = NULL;
	    obj->_tail = _new_elm;
	}
    else
	{
	    _new_elm->_next = element->_next;
	    _new_elm->_prev = element;

	    /* if the next element of the new element is NULL, set it to
	     * to the tail */
	    if(_new_elm->_next == NULL)
		obj->_tail = _new_elm;
	    else
		element->_next->_prev = _new_elm;
	    element->_next = _new_elm;
	}

    /* increment counter */
    obj->_elm_count++;
    return 0;
}

/* Add previous */
int blist_add_prev(blist* obj, blist_elm* element, void* data)
{
    blist_elm* _new_elm;

    /* check object */
    BLIST_OBJ_CHK(obj);

    /* prevent null elements added if not the first */
    if(blist_count(obj) > 0 && element == NULL)
	return -1;

    /* create new element */
    _new_elm = (blist_elm*) malloc(sizeof(blist_elm));
    if(_new_elm == NULL)
	return -1;
    _new_elm->_ix = 0;


    /* set data */
    _new_elm->_data = data;

    /* if the first element */
    if(blist_count(obj) == 0)
	{
	    _new_elm->_next = NULL;
	    _new_elm->_prev = NULL;
	    obj->_head = _new_elm;
	    obj->_tail = _new_elm;
	}
    else
	{
	    _new_elm->_next = element;
	    _new_elm->_prev = element->_prev;
	    if(_new_elm->_next == NULL)
		obj->_head = _new_elm;
	    else
		element->_next->_prev = _new_elm;

	    element->_prev = _new_elm;
	}

    /* increase counter */
    obj->_elm_count++;
    return 0;
}

/* Remove method */
int blist_remove(blist* obj, blist_elm* element, void** data)
{
    BLIST_OBJ_CHK(obj);

    /* check for null element */
    if(blist_count(obj) == 0 || element == NULL)
	return -1;

    pthread_mutex_lock(&obj->_mutex);
    /* get a pointer to the data */
    *data = element->_data;
    
    /* compare pointers to determine if head */
    if(element == obj->_head)
	{
	    obj->_head = element->_next;
	    if(obj->_head == NULL)
		obj->_tail = NULL;
	    else
		element->_next->_prev = NULL;
	}
    else
	{
	    element->_prev->_next = element->_next;
	    if(element->_next == NULL)
		obj->_tail = element->_prev;
	    else
		element->_next->_prev = element->_prev;
	}

    element->_data = NULL;
    element->_next = NULL;
    element->_prev = NULL;
    free(element);

    /* decrement counter */
    obj->_elm_count--;
    pthread_mutex_unlock(&obj->_mutex);
    return 0;
}

int blist_foreach(blist* obj, unsigned int dir, void* ext_obj, int (*foreach)(void* obj, void* data, unsigned int ix))
{
    blist_elm* _elm;				/* temporary element */
    unsigned int _int_cnt = 0;			/* internal counter */
    
    /* object check */
    BLIST_OBJ_CHK(obj);

    _elm = (dir > 0? obj->_tail : obj->_head);
    _int_cnt = (dir > 0? obj->_elm_count : 0);
    /* if the direction is greater than 0, iterate from last */
    while(_elm) {
	
	/* call function pointer if assigned break if value was non zero */
	if(foreach((ext_obj? ext_obj : NULL), _elm->_data, _int_cnt))
	    break;
		
	_elm = (dir > 0? _elm->_prev : _elm->_next);
	if(dir > 0)
	    _int_cnt--;
	else
	    _int_cnt++;
    }

    return 0;
}
