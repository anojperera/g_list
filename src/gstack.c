/* Implementation of stack */
#include "gstack.h"

/* Push object to stack */
int gstack_push(gstack* obj, void* data)
{
    return blist_add_next(obj, blist_get_tail(obj), data);
}

/* Pop object from stack */
int gstack_pop(gstack* obj, void** data)
{
    return blist_remove(obj, blist_get_tail(obj), data);
}
