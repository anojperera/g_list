/* Enhanced list for alist. */
/* The current date is: 20/12/2012 */
#ifndef __BLIST_H__
#define __BLIST_H__

#include <stdlib.h>

/* Forward declaration of struct */
typedef struct _blist_elm blist_elm;
typedef struct _blist blist;

struct _blist_elm
{
    unsigned int _ix;						/* index */
    void* _data;						/* data pointer */
    size_t _size;						/* size */
    struct _blist_elm* _prev;					/* previous element */
    struct _blist_elm* _next;					/* next element */
};

/* linked list struct */
struct _blist
{
    int _size;
    int _ix_counter;						/* counter */
    int (*compare)(const void* key1, const void* key2);		/* compare */
    void (*delete)(void* data, unsigned int ix);			/* destructor function pointer */
    int (*foreach)(void* obj, void* data, unsigned int ix);	/* for each function pointer */
    blist_elm* _head;						/* head */
    blist_elm* _tail;						/* tail */
    void* _s_obj;						/* external object */
};


/* Interface methods */

/* constructors */
blist* bList_New(blist* obj, void (*delete)(void* data, unsigned int ix));
blist* bList_New2(blist* obj);

/* destructor */
blist* bList_Delete(blist* obj);

/* Insert next. Pass NULL pointer to add */
int bList_Ins_Next(blist* obj, blist_elm* element, const void* data, size_t sz);
int bList_Ins_Prev(blist* obj, blist_elm* element, const void* data, size_t sz);
int bList_Remove(blist* obj, blist_elm* element);

/* iterations */
int bList_Display(blist* obj, int s_flg);
int bList_Display2(blist* obj, int s_flg, int (*foreach)(void* obj, void* data, unsigned int ix), void* s_obj);

/* helper macros */
#define bList_Size(blist) ((blist)->_size)
#define bList_Head(blist) ((blist)->_head)
#define bList_Tail(blist) ((blist)->_tail)
#define bList_Is_Head(element) ((element)->_prev == NULL? 1 : 0)
#define bList_Is_Tail(element) ((element)->_next == NULL? 1 : 0)
#define bList_Get_Data(element) ((element)->_data)
#define bList_Next(element) ((element)->_next)
#define bList_Previous(element) ((element)->_prev)

#endif /* __BLIST_H__ */
