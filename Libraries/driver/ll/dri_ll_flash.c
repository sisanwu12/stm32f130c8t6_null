/**
 * @file dri_ll_flash.c
 * @author sisanwu12
 * @brief
 * @version 0.1
 * @date 2026-04-05
 *
 */

#include "dri_ll_flash.h"
#include "dri_ll.h"

/* ---------- FLASH操作函数 ---------- */

/**
 * @brief 使能 FLASH 预取指
 * @retval None
 */
void ll_flash_prefetch_enable(void)
{
    ll_set_bits(LL_FLASH_BASE_ADDR, LL_FLASH_ACR_OFFSET, LL_FLASH_ACR_PRFTBE_MASK);
}

/**
 * @brief 禁用 FLASH 预取指
 * @retval None
 */
void ll_flash_prefetch_disable(void)
{
    ll_clear_bits(LL_FLASH_BASE_ADDR, LL_FLASH_ACR_OFFSET, LL_FLASH_ACR_PRFTBE_MASK);
}

/**
 * @brief 使能 FLASH 半周期访问
 * @retval None
 */
void ll_flash_halfcycle_enable(void)
{
    ll_set_bits(LL_FLASH_BASE_ADDR, LL_FLASH_ACR_OFFSET, LL_FLASH_ACR_HLFCYA_MASK);
}

/**
 * @brief 禁用 FLASH 半周期访问
 * @retval None
 */
void ll_flash_halfcycle_disable(void)
{
    ll_clear_bits(LL_FLASH_BASE_ADDR, LL_FLASH_ACR_OFFSET, LL_FLASH_ACR_HLFCYA_MASK);
}

/**
 * @brief 检查 FLASH 半周期访问是否使能
 * @retval isENABLE 如果使能返回 true，否则返回 false
 */
isENABLE ll_flash_halfcycle_is_enabled(void)
{
    return (ll_read_reg(LL_FLASH_BASE_ADDR, LL_FLASH_ACR_OFFSET) & LL_FLASH_ACR_HLFCYA_MASK) != 0U;
}

/**
 * @brief 设置 FLASH 延迟等级
 *
 * @param latency FLASH 延迟等级
 *        LL_FLASH_LATENCY_0: 0 等级 (0 < SYSCLK <= 24MHz)
 *        LL_FLASH_LATENCY_1: 1 等级 (24MHz < SYSCLK <= 48MHz)
 *        LL_FLASH_LATENCY_2: 2 等级 (48MHz < SYSCLK <= 72MHz)
 * @retval None
 */
void ll_flash_latency_set(ll_flash_latency latency)
{
    ll_modify_reg(LL_FLASH_BASE_ADDR, LL_FLASH_ACR_OFFSET, LL_FLASH_ACR_LATENCY_MASK,
                  ((u32)latency << LL_FLASH_ACR_LATENCY_POS) & LL_FLASH_ACR_LATENCY_MASK);
}

/**
 * @brief 获取当前 FLASH 延迟等级
 * @retval ll_flash_latency 当前 FLASH 延迟等级
 */
ll_flash_latency ll_flash_latency_get(void)
{
    return (ll_flash_latency)ll_read_field(LL_FLASH_BASE_ADDR, LL_FLASH_ACR_OFFSET,
                                           LL_FLASH_ACR_LATENCY_MASK, LL_FLASH_ACR_LATENCY_POS);
}