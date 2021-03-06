/* Interface for improved list. This list is able to insert
 * and remove items from any positions. Also able to store locally
 * or hold a pointer to the object.
 * Doubly linked lists use, so that iterations can be done in any
 * order.
 * Mon Mar 11 21:19:22 GMT 2013 */

#ifndef _BLIST_H_
#define _BLIST_H_

#include <stdlib.h>

/* type defs of list elements and class */
typedef struct _blist_elm blist_elm;
typedef	struct _blist blist;

/* Implementation of structs */
struct _blist_elm
{
    void* _data;
    unsigned int _ix;
    struct _blist_elm* _next;
    struct _blist_elm* _prev;
};


struct _blist
{
    size_t _elm_count;
    int (*_comp)(const void* key1, const void* key2);			/* function pointer for comparison */
    void (*_delete)(void* data);					/* function pointer for delete */
    void (*_delete2)(void* usr_obj, void* data);			/* optional callback pointer for delete */
    void* _usr_obj;							/* optional user object pointer */
    struct _blist_elm* _head;						/* head element */
    struct _blist_elm* _tail;						/* tail element */
};

/* interface methods */
#ifdef __cplusplus
extern "C" {
#endif

    /* Constructor and destructor */
    /* Constructor takes one argument for destructor */
    int blist_new(blist* obj, void (*delete_ptr)(void* data));
    void blist_delete(blist* obj);

    int blist_add_next(blist* obj, blist_elm* element, void* data);
    int blist_add_prev(blist* obj, blist_elm* elemetn, void* data);

    int blist_remove(blist* obj, blist_elm* element, void** data);

    /* For each function, able to control direction
     * ext_obj shall be passed to the first argument of the callback
     * Callback function must return 0 to continue */
    int blist_foreach(blist* obj, unsigned int dir, void* ext_obj, int (*foreach)(void* obj, void* data, unsigned int ix));

    /* Convenient macros */
#define blist_count(obj)((obj)->_elm_count)
#define blist_get_head(obj)((obj)->_head)
#define blist_get_tail(obj)((obj)->_tail)
#define blist_is_head(elm)((elm)->_prev == NULL? 1 : 0)
#define blist_is_tail(elm)((elm)->_next == NULL? 1: 0)
#define blist_data(elm)((elm)->_data)
#define blist_next(elm)((elm)->_next)
#define blist_prev(elm)((elm)->_prev)
#define blist_set_usr_obj(obj, usr_obj)((obj)->_usr_obj = usr_obj)
#define blist_set_option_del_callback(obj, callback_fn)((obj)->_delete2 = callback_fn)

    
    /* Wrapper functions for adding data to the list at each end.
     * They internally called above methods */
    inline __attribute__ ((always_inline)) static int blist_add_from_end(blist* obj, void* data)
    {
	blist_elm* _elm;
	/* check for object pointer */
	if(obj == NULL)
	    return -1;

	/* get head element */
	_elm = blist_get_tail(obj);

	/* call add next method */
	return blist_add_next(obj, _elm, data);
    }
    
#ifdef __cplusplus
}
#endif

#endif /* _BLIST_H_ */
