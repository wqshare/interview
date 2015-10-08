#ifndef LIST_H_
#define LIST_H_

#include "stdint.h"

//辅助面试题的链表
#define OUT

typedef int ListItem;
typedef struct _ListNode
{
    ListItem item;
    struct _ListNode *next;
} ListNode, *List;

//创建一个空的或指定长度带有默认值的链表
extern int list_create(List *head, uint32_t length, ListItem default_val );

//在链表的末尾push一个节点
extern int list_push_item(List head, ListItem value);

//将一个节点插入到链表的任意位置
extern int list_insert_item(List head, uint32_t pos, ListItem value);

//将链表末尾的节点弹出并返回
extern ListItem list_pop_item(List head);

//获取链表任意位置的节点
extern ListItem list_get_item(List head, uint32_t pos);

//改变链表任意位置的节点值
extern int list_replace_item(List head, uint32_t pos, ListItem value);

//删除链表
extern int list_destroy(List *head);

//取得链表的长度
extern uint32_t list_length(List head);

extern void list_test();
#endif
