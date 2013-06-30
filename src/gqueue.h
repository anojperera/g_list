/* Defines interfaces for handling first in first out type queues */
/* Sun Jun 30 13:39:23 BST 2013 */

#ifndef _GQUEUE_H_
#define _GQUEUE_H_

#include <blist.h>

/* Type define blist into queue */
typedef blist gqueue;

#define gqueue_new blist_new
#define gqueue_delete blist_delete

/* Append to queue */
#define gqueue_in(queue, data)				\
    blist_add_next(queue, blist_get_tail(queue), data)
/* Remove from queue */
inline __attribute__ ((always_inline)) static int gqueue_out(gqueue* queue, void** data)
{
    return blist_remove(queue, NULL, data);
}

#define gqueue_count blist_count
#define gqueue_peek (queue) ((queue)->_head == NULL ? NULL : (queue)->_head->data)

#endif /* _GQUEUE_H_ */
