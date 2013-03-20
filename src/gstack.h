/* Interface for a software stack.
 * Uses methods from blist.
 * Tue Mar 12 10:38:04 GMT 2013 */

#ifndef _GSTACK_H_
#define _GSTACK_H_

#include <blist.h>

/* typedef blist into gstack */
typedef blist gstack;

/* constructor and destructor */
#define gstack_new blist_new
#define gstack_delete blist_delete

#define gstack_push(obj, data)(blist_add_next((obj), blist_get_tail(obj), data))
inline __attribute__ ((always_inline)) static int gstack_pop(gstack* obj, void** data)
{
    return blist_remove(obj, blist_get_tail(obj), data);
}
#define gstack_peek(obj) ((obj)->_tail == NULL? NULL : obj->_tail->_data)
#define gstack_count blist_count

#endif /* _GSTACK_H_ */
