/**
 * @file os_task.c
 * @author Yukikaze
 * @brief RTOS 任务管理与调度器实现文件。
 * @version 0.1
 * @date 2026-03-25
 *
 * @copyright Copyright (c) 2026
 *
 * @note 本文件实现任务生命周期管理、调度与延时处理逻辑。
 */

#include "os_task.h"

/**
 * @brief 判断优先级是否落在当前就绪队列支持的范围内。
 *
 * @param priority 待检查的任务优先级。
 *
 * @return uint8_t 非 0 表示优先级有效，0 表示优先级越界。
 */
static uint8_t ready_queue_priority_is_valid(uint8_t priority)
{
    return (uint8_t)(priority < OS_MAX_PRIORITIES);
}

/**
 * @brief 根据优先级生成对应的就绪位图掩码。
 *
 * @param priority 任务优先级，数值越小优先级越高。
 *
 * @return uint32_t 对应优先级的位图掩码。
 */
static uint32_t ready_queue_priority_mask(uint8_t priority)
{
    if (ready_queue_priority_is_valid(priority) == 0U)
    {
        return 0U;
    }

    return (uint32_t)(1UL << priority);
}

/**
 * @brief 初始化就绪队列。
 *
 * @param queue 待初始化的就绪队列。
 */
void ready_queue_init(ready_queue_t *queue)
{
    uint32_t priority = 0U;

    if (queue == NULL)
    {
        return;
    }

    queue->ready_bitmap = 0U;

    for (priority = 0U; priority < OS_MAX_PRIORITIES; priority++)
    {
        list_init(&queue->ready_lists[priority]);
    }
}

/**
 * @brief 将任务按尾插方式加入对应优先级的就绪链表。
 *
 * @param queue 目标就绪队列。
 * @param task 待加入的任务控制块。
 */
void ready_queue_insert_tail(ready_queue_t *queue, tcb_t *task)
{
    uint8_t priority = 0U;

    if ((queue == NULL) || (task == NULL))
    {
        return;
    }

    priority = task->priority;

    if (ready_queue_priority_is_valid(priority) == 0U)
    {
        return;
    }

    if (list_insert_tail(&queue->ready_lists[priority], &task->sched_node) == 0U)
    {
        return;
    }

    queue->ready_bitmap |= ready_queue_priority_mask(priority);
    task->state = TASK_READY;
}

/**
 * @brief 将任务从对应优先级的就绪链表中移除。
 *
 * @param queue 目标就绪队列。
 * @param task 待移除的任务控制块。
 */
void ready_queue_remove(ready_queue_t *queue, tcb_t *task)
{
    uint8_t priority = 0U;
    list_t *list     = NULL;

    if ((queue == NULL) || (task == NULL))
    {
        return;
    }

    priority = task->priority;

    if (ready_queue_priority_is_valid(priority) == 0U)
    {
        return;
    }

    list = &queue->ready_lists[priority];

    if (list_remove(list, &task->sched_node) == 0U)
    {
        return;
    }

    if (list_is_empty(list) != 0U)
    {
        queue->ready_bitmap &= ~ready_queue_priority_mask(priority);
    }
}

/**
 * @brief 获取当前最高优先级的非空就绪链表优先级值。
 *
 * @param queue 待查询的就绪队列。
 * @param priority 输出的最高优先级指针。
 *
 * @return uint8_t 非 0 表示查找成功，0 表示当前没有就绪任务。
 */
uint8_t ready_queue_get_highest_priority(const ready_queue_t *queue, uint8_t *priority)
{
    uint8_t current = 0U;

    if ((queue == NULL) || (queue->ready_bitmap == 0U))
    {
        return 0U;
    }

    for (current = 0U; current < OS_MAX_PRIORITIES; current++)
    {
        if ((queue->ready_bitmap & ready_queue_priority_mask(current)) != 0U)
        {
            if (priority != NULL)
            {
                *priority = current;
            }
            return 1U;
        }
    }

    return 0U;
}

/**
 * @brief 查看当前最高优先级的就绪任务，但不将其移出队列。
 *
 * @param queue 待查询的就绪队列。
 *
 * @return const tcb_t* 当前最高优先级的任务控制块只读指针；若队列为空则返回 NULL。
 */
const tcb_t *ready_queue_peek_highest(const ready_queue_t *queue)
{
    uint8_t priority   = 0U;
    const list_t *ready_list = NULL;

    if (ready_queue_get_highest_priority(queue, &priority) == 0U)
    {
        return NULL;
    }

    ready_list = &queue->ready_lists[priority];

    if (ready_list->head == NULL)
    {
        return NULL;
    }

    return LIST_CONTAINER_OF(ready_list->head, tcb_t, sched_node);
}

/**
 * @brief 对指定优先级的就绪链表执行一次时间片轮转。
 *
 * @param queue 目标就绪队列。
 * @param priority 需要轮转的优先级。
 */
void ready_queue_rotate(ready_queue_t *queue, uint8_t priority)
{
    list_t      *ready_list = NULL;
    list_node_t *node       = NULL;

    if (queue == NULL)
    {
        return;
    }

    if (ready_queue_priority_is_valid(priority) == 0U)
    {
        return;
    }

    ready_list = &queue->ready_lists[priority];

    if (ready_list->item_count <= 1U)
    {
        return;
    }

    node = list_remove_head(ready_list);

    if (node != NULL)
    {
        (void)list_insert_tail(ready_list, node);
    }
}

/**
 * @brief 判断整个就绪队列是否为空。
 *
 * @param queue 待判断的就绪队列。
 *
 * @return uint8_t 非 0 表示就绪队列为空，0 表示至少存在一个就绪任务。
 */
uint8_t ready_queue_is_empty(const ready_queue_t *queue)
{
    if (queue == NULL)
    {
        return 1U;
    }

    return (uint8_t)(queue->ready_bitmap == 0U);
}
