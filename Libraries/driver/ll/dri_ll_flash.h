/**
 * @file dri_ll_flash.h
 * @author sisanwu12 (sisanwu12@outlook.com)
 * @brief
 * @version 0.1
 * @date 2026-04-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef __DRI_LL_FLASH_H__
#define __DRI_LL_FLASH_H__

#include "data_type.h"

/* ========== 数据定义 ==========*/

/* ---------- FLASH 地址定义层 ---------- */

/* FLASH 基地址 */
#define LL_FLASH_BASE_ADDR 0x40022000UL // FLASH寄存器基地址

/* FLASH 寄存器偏移地址*/
#define LL_FLASH_ACR_OFFSET     0x00UL // 访问控制寄存器
#define LL_FLASH_KEYR_OFFSET    0x04UL // 密钥寄存器
#define LL_FLASH_OPTKEYR_OFFSET 0x08UL // 选项密钥寄存器
#define LL_FLASH_SR_OFFSET      0x0CUL // 状态寄存器
#define LL_FLASH_CR_OFFSET      0x10UL // 控制寄存器
#define LL_FLASH_AR_OFFSET      0x14UL // 地址寄存器
#define LL_FLASH_OBR_OFFSET     0x1CUL // 选项字节寄存器
#define LL_FLASH_WRPR_OFFSET    0x20UL // 写保护寄存器

/* ---------- 寄存器位定义 ---------- */

/* FLASH_ACR 寄存器位位置 */
#define LL_FLASH_ACR_LATENCY_POS 0U // 延迟位位置
#define LL_FLASH_ACR_PRFTBE_POS  4U // 预取缓冲使能位位置
#define LL_FLASH_ACR_PRFTBS_POS  5U // 预取缓冲状态位位置
#define LL_FLASH_ACR_HLFCYA_POS  8U // 半周期访问使能位位置
#define LL_FLASH_ACR_HLFCYS_POS  9U // 半周期访问状态位位置

/* FLASH_ACR 寄存器位掩码 */
#define LL_FLASH_ACR_LATENCY_MASK (LL_MASK_2 << LL_FLASH_ACR_LATENCY_POS)
#define LL_FLASH_ACR_PRFTBE_MASK  (LL_MASK_1 << LL_FLASH_ACR_PRFTBE_POS)
#define LL_FLASH_ACR_PRFTBS_MASK  (LL_MASK_1 << LL_FLASH_ACR_PRFTBS_POS)
#define LL_FLASH_ACR_HLFCYA_MASK  (LL_MASK_1 << LL_FLASH_ACR_HLFCYA_POS)
#define LL_FLASH_ACR_HLFCYS_MASK  (LL_MASK_1 << LL_FLASH_ACR_HLFCYS_POS)

/* ---------- 参数 ---------- */

/* FLASH延迟等级设置 */
typedef enum
{
    LL_FLASH_LATENCY_0 = 0x00UL, // 0 等级 (0 < SYSCLK <= 24MHz)
    LL_FLASH_LATENCY_1 = 0x01UL, // 1 等级 (24MHz < SYSCLK <= 48MHz)
    LL_FLASH_LATENCY_2 = 0x02UL, // 2 等级 (48MHz < SYSCLK <= 72MHz)
} ll_flash_latency;
/* ========== 对外接口 ========== */

/* ---------- FLASH操作函数 ---------- */

/* FLASH预取指函数 */
void     ll_flash_prefetch_enable(void);
void     ll_flash_prefetch_disable(void);
isENABLE ll_flash_prefetch_is_enabled(void);

/* 半周期访问函数 */
void     ll_flash_halfcycle_enable(void);
void     ll_flash_halfcycle_disable(void);
isENABLE ll_flash_halfcycle_is_enabled(void);

/* FLASH延迟等级设置函数 */
void             ll_flash_latency_set(ll_flash_latency latency);
ll_flash_latency ll_flash_latency_get(void);

#endif /* __dri_LL_FLASH_H__ */