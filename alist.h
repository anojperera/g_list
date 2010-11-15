/* generic linked list class
   Fri Jul 23 09:32:47 GMTDT 2010 */

#ifndef __ALIST__
#define __ALIST__

/* c++ compaitiblity */
#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

    /* node structure */    
    typedef struct node
    {
		unsigned int ix;
		void* data;
		struct node* next;
    } aNode;


    /* add a node to list */
    void aList_Add(aNode** obj,
						  void* data,
						  unsigned int sz);

	/* add a node from back */
	void aList_AddB(aNode** obj,
				   void* data,
				   unsigned int sz);

    /* return the count of list */
    unsigned int  aList_Count(aNode** obj);

    /* clear list */
    void aList_Clear(aNode** obj);

    /* retrieved an item from list */
    aNode* aList_Item(aNode** obj, unsigned int ix);

    
/* c++ compatibility */
#ifdef __cplusplus
}
#endif
    

#endif /* __ALIST__ */
