#include "list.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

#define CHECK_LIST_VALID(h) \
    if (!h) \
{   \
    printf("Error: list invalid!"); \
    assert(0); \
    return -1; \
}

#define CHECK_NODE_VALID(n) \
    if (!n)                 \
{                           \
    printf("Error: memory is not enough!"); \
    assert(0);                          \
    return -1;                          \
}

static ListNode *__list_get_node(List head, uint32_t pos)
{
    assert(head);
    uint32_t length = list_length(head);
    assert(pos < length);
    if (pos >= length)
    {
        return NULL;
    }


    ListNode *node = head->next;

    int i;
    for (i = 0; i < pos; i++ )
    {
        node = node->next;
    }

    return node;
}

static void __list_print(List head)
{
    ListNode *node = head;

    uint32_t i = 0;
    while(node = node->next)
    {
        printf("List[%u] value[%d] next[%p]\n", i, node->item, node->next);
        i++;
    }
}

uint32_t list_length(List head)
{

    ListNode *node = head;

    uint32_t i = 0;
    while(node = node->next)
    {
        //printf("==> List[%u] value[%d] next[%p]", i, node->item, node->next);
        i++;
    }
    return i;
}

int list_create(List *head, uint32_t length, ListItem default_val)
{
    if (*head)
    {
        printf("Error: [head] is not NULL, maybe it's a exist list");
        assert(head == NULL);
        return -1;
    }

    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    CHECK_NODE_VALID(node);
    node->item = default_val;
    node->next = NULL;
    *head = node;

    int i;
    for (i = 0; i < length; i++)
    {
        ListNode *n = (ListNode *)malloc(sizeof(ListNode));
        CHECK_NODE_VALID(node);
        n->item = default_val;
        n->next = NULL;

        node->next = n;
        node = n;
    }

    return 0;
}


int list_push_item(List head, ListItem value)
{
    CHECK_LIST_VALID(head);

    ListNode *node = __list_get_node(head, list_length(head) - 1);

    ListNode *end = (ListNode *)malloc(sizeof(ListNode));
    CHECK_NODE_VALID(node);
    end->item = value;
    end->next = NULL;
    node->next = end;

    return 0;
}

int list_insert_item(List head, uint32_t pos, ListItem value)
{
    CHECK_LIST_VALID(head);
    int length = list_length(head);
    assert(pos <= pos);
    if (pos > length)
    {
        printf("Error: [pos] can't more than list length!");
        return -1;
    }

    if (pos == length)
    {
        return list_push_item(head, value);
    }

    if (pos == 0)
    {
        ListNode *node = (ListNode *)malloc(sizeof(ListNode));
        CHECK_NODE_VALID(node);
        node->item = value;
        node->next = __list_get_node(head, 0);
        head->next = node;
        return 0;
    }


    ListNode *prev = __list_get_node(head, pos);
    ListNode *next = __list_get_node(head, pos + 1);
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    CHECK_NODE_VALID(node);
    node->item = value;
    node->next = next;
    prev->next = node;

    return 0;

}

ListItem list_get_item(List head, uint32_t pos)
{
    ListNode *node = __list_get_node(head, pos);
    if (!node)
    {
        printf("Error: [pos] must less than list's length");
        assert(0);
        ListItem item;
        return item;
    }

    return node->item;
}


int list_replace_item(List head, uint32_t pos, ListItem value)
{
    ListNode *node = __list_get_node(head, pos);
    if (!node)
    {
        printf("Error: [pos] must less than list's length");
        assert(0);
        return -1;
    }

    node->item = value;
    return 0;
}

ListItem list_pop_item(List head)
{
    uint32_t length = list_length(head);
    ListItem ret = 0;
    if (length <= 1)
    {
        ListNode *node = __list_get_node(head, 0);
        CHECK_NODE_VALID(node);
        ret = node->item;
        free(node);
        node = NULL;
        head->next = NULL;
    }
    else
    {
        ListNode *node = __list_get_node(head, length - 1);
        ListNode *prev = __list_get_node(head, length - 2);
        if (!node || !prev)
        {
            printf("Error: [pos] must less than list's length");
            assert(0);
        }

        ret = node->item;
        free(node);
        node = NULL;
        prev->next = NULL;
    }

    return ret;
}

int list_destroy(List *head)
{
    if (head == NULL)
    {
        return 0;
    }

    if ((*head) == NULL)
    {
         free(*head);
         head = NULL;
         return 0;
    }

    CHECK_LIST_VALID(*head);
    ListNode *p, *q;
    p = (*head)->next;

    free (*head);
    *head = NULL;
    int i = 0;
    while(p)
    {
        int val = q->item;
        q = p->next;
        free(p);
        p = q;
        i++;
        printf ("release List[%d] value[%d]\n", i, val);
    }

    return 0;

}

void list_test()
{
    List list;
    printf("==> test create list, length:[%d] defalute_val[%d]\n", 10, 2);
    list_create(&list,10, 2 );
    __list_print(list);

    printf("\n");
    printf ("==> test list length, length:[%u]\n", list_length(list));
    __list_print(list);

    printf("\n");
    printf ("==> test push_item, length:[%u]\n", list_length(list));
    __list_print(list);
    list_push_item(list, 10000);
    printf("==> pushed value: [%d]\n", 100000);
    __list_print(list);

    printf("\n");
    ListItem item = list_get_item(list, 10);
    printf ("==> test get item , list[10] = [%d]\n", item);

    printf ("\n");
    printf ("==> test insert item, insert position:[%d] value:[%d] \n", 5, 12345);
    list_insert_item(list, 5, 12345);
    __list_print(list);

    printf ("\n");
    printf ("==> test insert to end, insert position:[%d] value:[%d] \n", 12, 98888);
    list_insert_item(list, 12, 98888);
    __list_print(list);

    printf ("\n");
    printf ("==> test insert to start, insert position:[%d] value:[%d] \n", 0, 6666111);
    list_insert_item(list, 0, 6666111);
    __list_print(list);


    printf ("\n");
    printf ("==> test replace: replace list[1] to 55555 \n");
    list_replace_item(list, 0, 55555);
    __list_print(list);

    printf ("\n");
    printf ("==> test pop item, item at end is:[%d]\n", list_pop_item(list));
    __list_print(list);

    printf("\n");
    __list_print(list);
    printf ("==> test destroy list\n" );
    list_destroy(&list);
    printf ("list addr: [%p]", list);
}

