/* testing genering collection class
   Sat Jul 24 18:27:43 BST 2010 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <alist.h>
#include "blist.h"
#include "gstack.h"

struct _test
{
    char* t_str;
    int val;
};

static int Display(void* data, unsigned int ix)
{
    /* print data */
    /* printf ("%i-index%d\n",*((int*) data), ix); */
    return 0;
}

/* blist delete method */
static void _blist_delete(void* data)
{
    /* check for NULL pointer and delete */
    if(data != NULL)
	free(data);
    return;
}

/* blsit foreach */
static int _blist_foreach(void* obj, void* data, unsigned int ix)
{
    char* _data;
    /* continue array if element was null */
    if(data == NULL)
	return 0;
    _data = (char*) data;
    fprintf(stdout, "%s - %i\n", _data, ix);
    return 0;
}

/* copy helper for test 3 */
static int _copy_helper(void* obj, void* usr_obj)
{
    struct _test* _obj;
    struct _test* _uobj;
    if(!obj || !usr_obj)
	return 0;

    _obj = (struct _test*) obj;
    _uobj = (struct _test*) usr_obj;
    _obj->t_str = (char*) malloc(sizeof(char) * (strlen(_uobj->t_str)+1));
    strcpy(_obj->t_str, _uobj->t_str);
    return 0;
}

/* delete helper for test 3 */
static int _delete_helper(void* obj, unsigned int ix)
{
    struct _test* _obj;
    if(!obj)
	return 0;
    _obj = (struct _test*) obj;
    if(_obj->t_str)
	free(_obj->t_str);
    _obj->t_str = NULL;
    free(_obj);
    return 0;
}

/* display helper function for test 3 */
static int _display_helper(void* obj, unsigned int ix)
{
    struct _test* _obj;
    if(!obj)
	return 0;

    _obj = (struct _test*) obj;
    printf("%s %i\n", _obj->t_str, _obj->val);
    return 0;
}

int test1(int argc, char** argv);
int test2(int argc, char** argv);
int test3(int argc, char** argv);
int test4(int argc, char** argv);
int test5(int argc, char** argv);
int test6(int argc, char** argv);

int main(int argc, char** argv)
{
    return test6(argc, argv);
}


int test3(int argc, char** argv)
{
    int i = 0, max = 2, s_flg = 0;
    struct _test objs;
    aNode* _node = aList_New();
    if(argc > 1)
	max = atoi(argv[1]);
    if(argc > 2)
	s_flg = atoi(argv[2]);

    objs.t_str = (char*) malloc(sizeof(char) * 16);
    for(i=0;i<max;i++)
	{
	    memset((void*) objs.t_str, 0, sizeof(char) * 16);
	    sprintf(objs.t_str, "ABC%i", i);
	    objs.val = i;
	    /* call to add to collection */
	    aList_Add2(&_node, (void*) &objs, sizeof(struct _test), (void*) &objs, _copy_helper);
	}

    aList_Display(&_node, s_flg, _display_helper);

    free(objs.t_str);
    aList_Clear2(&_node, _delete_helper);
    return 0;
}

int test2(int argc, char** argv)
{
    time_t start_time, end_time;
    int cnt = 5, ix = 0;

    int i;
    if(argc > 1)
	cnt = atoi(argv[1]);
    else
	cnt = 5;

    if(argc > 2)
	ix = atoi(argv[2]);
    else
	ix = 0;


    aNode* first = aList_New();

    for(i=0; i<cnt; i++)
	{
	    aList_Add(&first, (void*) &i, sizeof(int));
	}

    aNode* sObj;
    time(&start_time);
    if(ix < 0)
	{
	    time(&end_time);
	    aList_Display(&first, 1, Display);
	}
    else
	{
	    sObj = aList_Item(&first, ix);
	    time(&end_time);
	    if(sObj)
		printf ("%i-index%d\n",*((int*) sObj->data), ix);
	}

    double diff_time = difftime(end_time, start_time);
    printf("Array addimg time %.6lf\n", diff_time);

    aList_Clear(&first);
    return 0;
}



int test1(int argc, char** argv)
{
    int flg = 0;
    if(argc > 1)
	flg = atoi(argv[1]);
    else
	flg = 0;

    aNode* first = aList_New();

    /* aNode* first = NULL; */

    char ch1[] = "Test 1";
    char ch2[] = "Test 2";
    char ch3[] = "Test 3";
    char ch4[] = "This is awesom";
    char ch5[] = "Working fine\n and !";

    char** buff = (char**) calloc(5, sizeof(char*));
    int i = 0;
    for(i=0; i<5; i++)
	{
	    switch(i)
		{
		case 0:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch1) + 1));

		    strcpy(buff[i], ch1);
		    break;
		case 1:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch2) + 1));

		    strcpy(buff[i], ch2);
		    break;
		case 2:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch3) + 1));

		    strcpy(buff[i], ch3);
		    break;
		case 3:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch4) + 1));

		    strcpy(buff[i], ch4);
		    break;
		case 4:
		    buff[i] = (char*)
			malloc(sizeof(char) * (strlen(ch5) + 1));

		    strcpy(buff[i], ch5);
		    break;
		}
	    aList_Add(&first, buff[i], strlen(buff[i])+1);
	}

    for(i=0; i<5; i++)
    	{
    	    free(buff[i]);
    	    buff[i] = NULL;
    	}
    free(buff);
    /* aList_Add(&first, ch1, strlen(ch1)+1); */
    /* aList_Add(&first, ch2, strlen(ch2)+1); */
    /* aList_Add(&first, ch3, strlen(ch3)+1); */
    /* aList_Add(&first, ch4, strlen(ch4)+1); */
    /* aList_Add(&first, ch5, strlen(ch5)+1); */

    /* int i = 0; */
    int MAX = aList_Count(&first);
    aNode* tmp;

    for(i=0; i<MAX; i++)
	{
	    tmp = aList_Item(&first, i);
	    /* printf("%s %i\n", (char*) tmp->data, i); */
	}

    aList_Display(&first, flg, Display);

    aList_Clear(&first);
    return 0;
}

/* Test blist function */
int test4(int argc, char** argv)
{

    blist _list;
    int _flg;
    const char ch1[] = "Test 1";
    const char ch2[] = "Test 2";
    const char ch3[] = "Test 3";
    const char ch4[] = "This is awesom";
    const char ch5[] = "Working fine and !";

    if(argc > 1)
	_flg = atoi(argv[1]);
    else
	_flg = 0;

    /* initialise */
    if(blist_new(&_list, NULL))
	{
	    fprintf(stderr, "Error initialising\n");
	    return 0;
	}

    /* add to list */
    blist_add_from_end(&_list, (void*) ch1);
    blist_add_from_end(&_list, (void*) ch2);
    blist_add_from_end(&_list, (void*) ch3);
    blist_add_from_end(&_list, (void*) ch4);
    blist_add_from_end(&_list, (void*) ch5);

    /* display results */
    blist_foreach(&_list, _flg, NULL, _blist_foreach);

    /* delete list */
    blist_delete(&_list);
    return 0;
}

int test5(int argc, char** argv)
{
#define TEST5_NUM 5
#define TEST5_BUFF_SZ 32
    int i;
    blist _list;
    int _flg;
    const char ch1[] = "Test 1";
    const char ch2[] = "Test 2";
    const char ch3[] = "Test 3";
    const char ch4[] = "This is awesom";
    const char ch5[] = "Working fine and !";
    char* _buff[TEST5_NUM];
    if(argc > 1)
	_flg = atoi(argv[1]);
    else
	_flg = 0;

    /* initialise */
    if(blist_new(&_list, _blist_delete))
	{
	    fprintf(stderr, "Error initialising\n");
	    return 0;
	}

    /* copy to buffer */
    for(i=0; i<TEST5_NUM; i++)
	{
	    _buff[i] = (char*) malloc(TEST5_BUFF_SZ);
	    switch(i)
		{
		case 0:
		    strcpy(_buff[i], ch1);
		    break;
		case 1:
		    strcpy(_buff[i], ch2);
		    break;
		case 2:
		    strcpy(_buff[i], ch3);
		    break;
		case 3:
		    strcpy(_buff[i], ch4);
		    break;
		case 4:
		default:
		    strcpy(_buff[i], ch5);
		}
	    blist_add_from_end(&_list, (void*) _buff[i]);
	}

    /* display results */
    blist_foreach(&_list, _flg, NULL, _blist_foreach);

    /* delete list */
    blist_delete(&_list);
    return 0;
}

/* Test blist function */
int test6(int argc, char** argv)
{

    gstack _stack;
    gstack* _stack_ptr;
    int _flg;
    void* _data = NULL;
    void* _top = NULL;
    
    const char ch1[] = "Test 1";
    const char ch2[] = "Test 2";
    const char ch3[] = "Test 3";
    const char ch4[] = "This is awesom";
    const char ch5[] = "Working fine and !";

    if(argc > 1)
	_flg = atoi(argv[1]);
    else
	_flg = 0;

    /* initialise */
    if(gstack_new(&_stack, NULL))
	{
	    fprintf(stderr, "Error initialising\n");
	    return 0;
	}

    /* add to list */
    _stack_ptr = &_stack;
    gstack_push(_stack_ptr, (void*) ch1);
    gstack_push(_stack_ptr, (void*) ch2);
    gstack_push(_stack_ptr, (void*) ch3);
    gstack_push(_stack_ptr, (void*) ch4);
    gstack_push(_stack_ptr, (void*) ch5);

    /* display results */
    gstack_pop(&_stack, &_data);
    if(_data != NULL)
	fprintf(stdout, "%s\n", (char*) _data);

    gstack_pop(&_stack, &_data);
    if(_data != NULL)
	fprintf(stdout, "%s\n", (char*) _data);    

    /* get top */

    _top = gstack_peek(_stack_ptr);
    if(_top != NULL)
	fprintf(stdout, "%s\n", (char*) _top);
    /* delete list */
    gstack_delete(&_stack);
    return 0;
}
