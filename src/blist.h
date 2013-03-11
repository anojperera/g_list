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
struct _blist_elem
{
    void* _data;
    unsined int _ix;
    struct _blist_elm* _next;
    struct _blist_elm* _prev;
};


struct _blist
{
    sizt_t _elm_count;
    int (*_comp)(const void* key1, const void* key2);			/* function pointer for comparison */
    int (*_delete)(void* data);						/* function pointer for delete */
    struct _blist_elm* _head;						/* head element */
    struct _blist_elm* _tail;						/* tail element */
};

/* interface methods */
#ifdef __cplusplus
extern "C" {
#endif

    /* Constructor and destructor */
    /* Constructor takes one argument for destructor */
    int blist_new(blist* obj, void (*delete)(void* data));
    void blist_delete(blist* obj);

    int blist_add_next(blist* obj, blist_elm* element, const void* data);
    int blist_add_prev(blist* obj, blist_elm* elemetn, const void* data);

    int blist_remove(blist* obj, blist_elm* element, void** data);

    /* For each function, able to control direction */
    int blist_foreach(blist* obj, unsigned int dir, void* ext_obj, int (*foreach)(void* obj, void* data, unsined int ix));

    /* Convenient macros */
#define blist_count(obj)((obj)->_elm_count)
#define blist_get_head(obj)((obj)->_head)
#define blist_get_tail(obj)((obj)->_tail)
#define blist_is_head(elm)((elm)->_prev == NULL? 1 : 0)
#define blist_is_tail(elm)((elm)->_next == NULL? 1: 0)
#define blist_data(elm)((elm)->data)
#define blist_next(elm)((elm)->_next)
#define blist_prev(elm)((elm)->_prev)
    
#ifdef __cplusplus
}
#endif

#endif /* _BLIST_H_ */
