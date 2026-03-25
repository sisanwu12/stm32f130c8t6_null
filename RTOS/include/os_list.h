/**
 * @file os_list.h
 * @author Yukikaze
 * @brief RTOS 双向链表接口定义文件。
 * @version 0.1
 * @date 2026-03-25
 *
 * @copyright Copyright (c) 2026
 *
 * @note 本文件提供就绪链表、延时链表和等待链表共用的基础链表操作。
 */

#ifndef __OS_LIST_H__
#define __OS_LIST_H__

#include <stddef.h>
#include <stdint.h>

typedef struct list list_t; // 前向声明，供链表节点记录所属链表

typedef struct list_node {
    struct list_node *prev; // 前驱节点
    struct list_node *next; // 后继节点
    list_t           *owner; // 当前所属链表，NULL 表示未挂入任何链表
} list_node_t; // 通用双向链表节点

struct list {
    list_node_t *head;       // 头节点
    list_node_t *tail;       // 尾节点
    uint32_t     item_count; // 链表节点数量
}; // 通用双向链表

/*
 * 已知结构体成员指针 ptr、外层结构体类型 type 和成员名 member，
 * 通过减去 member 在 type 中的偏移量，反推出整个外层结构体的起始地址。
 */
#define LIST_CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

/*
 * 使用约定：
 * 1. 节点第一次使用前必须先调用 list_node_init()；
 * 2. 节点只有从原链表成功移除后，才能再次插入其他链表；
 * 3. 若节点已经挂在某条链表上，重复插入会直接失败。
 */
void list_node_init(list_node_t *node);
void list_init(list_t *list);
uint8_t list_insert_head(list_t *list, list_node_t *node);
uint8_t list_insert_tail(list_t *list, list_node_t *node);
uint8_t list_remove(list_t *list, list_node_t *node);
list_node_t *list_remove_head(list_t *list);
uint8_t list_is_empty(const list_t *list);

#endif /* __OS_LIST_H__ */
