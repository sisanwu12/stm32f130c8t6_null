/**
 * @file dri_ll_rcc.c
 * @author sisanwu12
 * @brief
 * @version 0.1
 * @date 2026-03-31
 *
 */

#include "dri_ll_rcc.h"
#include "dri_ll.h"

/* ========== 时钟源控制 ========== */

/**
 * @brief HSI 内部高速时钟控制使能
 *
 */
void ll_rcc_hsi_enable(void)
{
    ll_set_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                LL_RCC_CR_HSION_MASK); // 设置 HSION 位
}

/**
 * @brief HSI 内部高速时钟控制禁能
 *
 */
void ll_rcc_hsi_disable(void)
{
    ll_clear_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                  LL_RCC_CR_HSION_MASK); // 清除 HSION 位
}

/**
 * @brief HSI 内部高速时钟就绪状态检查
 *
 * @return isREADY
 *  READY: HSI 就绪
 *  NOT_READY: HSI 未就绪
 */
isREADY ll_rcc_hsi_is_ready(void)
{
    return (ll_read_reg(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET) & LL_RCC_CR_HSIRDY_MASK) !=
           0; // 检查 HSIRDY 位
}

/**
 * @brief HSE 外部高速时钟控制使能
 *
 */
void ll_rcc_hse_enable(void)
{
    ll_set_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                LL_RCC_CR_HSEON_MASK); // 设置 HSEON 位
}

/**
 * @brief HSE 外部高速时钟控制禁能
 *
 */
void ll_rcc_hse_disable(void)
{
    ll_clear_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                  LL_RCC_CR_HSEON_MASK); // 清除 HSEON 位
}

/**
 * @brief HSE 外部高速时钟就绪状态检查
 *
 * @return isREADY
 *  READY: HSE 就绪
 *  NOT_READY: HSE 未就绪
 */
isREADY ll_rcc_hse_is_ready(void)
{
    return (ll_read_reg(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET) & LL_RCC_CR_HSERDY_MASK) !=
           0; // 检查 HSERDY 位
}

/**
 * @brief PLL 锁相环控制使能
 *
 */
void ll_rcc_pll_enable(void)
{
    ll_set_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                LL_RCC_CR_PLLON_MASK); // 设置 PLLON 位
    ll_wait_bits_set(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                     LL_RCC_CR_PLLRDY_MASK); // 等待 PLL 稳定
}

/**
 * @brief PLL 锁相环控制禁能
 *
 */
void ll_rcc_pll_disable(void)
{
    ll_clear_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                  LL_RCC_CR_PLLON_MASK); // 清除 PLLON 位
    ll_wait_bits_clear(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                       LL_RCC_CR_PLLRDY_MASK); // 等待 PLL 关闭
}

/**
 * @brief PLL 锁相环就绪状态检查
 *
 * @return isREADY
 * READY: PLL 就绪
 * NOT_READY: PLL 未就绪
 */
isREADY ll_rcc_pll_is_ready(void)
{
    return (ll_read_reg(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET) & LL_RCC_CR_PLLRDY_MASK) !=
           0; // 检查 PLLRDY 位
}

/**
 * @brief HSE 外部高速时钟过渡使能
 *
 */
void ll_rcc_hse_bypass_enable(void)
{
    ll_set_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                LL_RCC_CR_HSEBYP_MASK); // 设置 HSEBYP 位
}

/**
 * @brief HSE 外部高速时钟过渡禁能
 *
 */
void ll_rcc_hse_bypass_disable(void)
{
    ll_clear_bits(LL_RCC_BASE_ADDR, LL_RCC_CR_OFFSET,
                  LL_RCC_CR_HSEBYP_MASK); // 清除 HSEBYP 位
}

/* ========== 系统时钟选择与预分频 ========== */

/* 系统时钟选择 */

/**
 * @brief 选择系统时钟源
 *
 * @param sysclk_source 系统时钟源
 *        0x00000000UL: HSI 作为系统时钟
 *        0x00000001UL: HSE 作为系统时钟
 *        0x00000002UL: PLL 作为系统时钟
 */
void ll_rcc_sysclk_select(ll_rcc_sysclk_source sysclk_source)
{
    ll_modify_reg(LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET, LL_RCC_CFGR_SW_MASK,
                  (((u32)sysclk_source << LL_RCC_CFGR_SW_POS) & LL_RCC_CFGR_SW_MASK)); // 设置 SW 位
}

/**
 * @brief AHB 总线预分频设置
 *
 * @param ahb_prescaler AHB 预分频系数
 */
void ll_rcc_ahb_prescaler_set(ll_rcc_ahb_prescaler ahb_prescaler)
{
    ll_modify_reg(
        LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET, LL_RCC_CFGR_HPRE_MASK,
        (((u32)ahb_prescaler << LL_RCC_CFGR_HPRE_POS) & LL_RCC_CFGR_HPRE_MASK)); // 设置 HPRE 位
}

/**
 * @brief APB1 总线预分频设置
 *
 * @param apb1_prescaler APB1 预分频系数
 */
void ll_rcc_apb1_prescaler_set(ll_rcc_apb_prescaler apb1_prescaler)
{
    ll_modify_reg(
        LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET, LL_RCC_CFGR_PPRE1_MASK,
        (((u32)apb1_prescaler << LL_RCC_CFGR_PPRE1_POS) & LL_RCC_CFGR_PPRE1_MASK)); // 设置 PPRE1 位
}

/**
 * @brief APB2 总线预分频设置
 *
 * @param apb2_prescaler APB2 预分频系数
 */
void ll_rcc_apb2_prescaler_set(ll_rcc_apb_prescaler apb2_prescaler)
{
    ll_modify_reg(
        LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET, LL_RCC_CFGR_PPRE2_MASK,
        (((u32)apb2_prescaler << LL_RCC_CFGR_PPRE2_POS) & LL_RCC_CFGR_PPRE2_MASK)); // 设置 PPRE2 位
}

/**
 * @brief 获取系统时钟源
 *
 * @return ll_rcc_sysclk_source 系统时钟源
 */
ll_rcc_sysclk_source ll_rcc_sysclk_source_get(void)
{
    return (ll_rcc_sysclk_source)ll_read_field(LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET,
                                               LL_RCC_CFGR_SW_MASK,
                                               LL_RCC_CFGR_SW_POS); // 获取 SW 字段
}

/**
 * @brief 获取系统时钟状态
 *
 * @return ll_rcc_sysclk_status 系统时钟状态
 */
ll_rcc_sysclk_status ll_rcc_sysclk_status_get(void)
{
    return (ll_rcc_sysclk_status)ll_read_field(LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET,
                                               LL_RCC_CFGR_SWS_MASK, LL_RCC_CFGR_SWS_POS);
}

/* ========== PLL 配置 ========== */

/**
 * @brief 设置 PLL 时钟源
 *
 * @param source
 *       0x00000000UL: (HSI / 2) 作为 PLL 时钟源
 *       0x00000001UL: HSE 作为 PLL 时钟源
 * @note 该函数会修改 CFGR 寄存器中的 PLLSRC 位,
 *      PLLSRC 位 仅能在 PLL 关闭时修改, 因此调用该函数前请确保 PLL 已关闭
 */
void ll_rcc_pll_source_set(ll_rcc_pll_source source)
{
    ll_modify_reg(
        LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET, LL_RCC_CFGR_PLLSRC_MASK,
        (((u32)source << LL_RCC_CFGR_PLLSRC_POS) & LL_RCC_CFGR_PLLSRC_MASK)); // 设置 PLLSRC 位
}

/**
 * @brief 设置 PLL 锁相环倍频
 *
 * @param value PLL 锁相环倍频系数
 */
void ll_rcc_pll_mul_set(ll_rcc_pll_mul value)
{
    ll_modify_reg(
        LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET, LL_RCC_CFGR_PLLMUL_MASK,
        (((u32)value << LL_RCC_CFGR_PLLMUL_POS) & LL_RCC_CFGR_PLLMUL_MASK)); // 设置 PLLMUL 位
}

/**
 * @brief 获取 PLL 时钟源
 *
 * @return ll_rcc_pll_source PLL 时钟源
 */
ll_rcc_pll_source ll_rcc_pll_source_get(void)
{
    return (ll_rcc_pll_source)ll_read_field(LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET,
                                            LL_RCC_CFGR_PLLSRC_MASK, LL_RCC_CFGR_PLLSRC_POS);
}

/**
 * @brief 获取 PLL 倍频
 *
 * @return ll_rcc_pll_mul PLL 倍频系数
 */
ll_rcc_pll_mul ll_rcc_pll_mul_get(void)
{
    return (ll_rcc_pll_mul)ll_read_field(LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET,
                                         LL_RCC_CFGR_PLLMUL_MASK, LL_RCC_CFGR_PLLMUL_POS);
}

/**
 * @brief 设置 PLL 锁相环时钟源为 HSE 外部高速时钟时的 HSE 外部高速时钟的分频系数
 *
 * @param div HSE 分频系数
 */
void ll_rcc_pll_hse_div_set(ll_rcc_pll_hse_div div)
{
    // HSE 分频设置仅在 PLL 时钟源为 HSE 时有效, 因此调用该函数前请确保 PLL 时钟源已设置为 HSE
    ll_modify_reg(LL_RCC_BASE_ADDR, LL_RCC_CFGR_OFFSET, LL_RCC_CFGR_PLLXTPRE_MASK,
                  (((u32)div << LL_RCC_CFGR_PLLXTPRE_POS) &
                   LL_RCC_CFGR_PLLXTPRE_MASK)); // 设置 PLLXTPRE 位中的分频部分
}

/* ========== 外设时钟门控 ========== */

/**
 * @brief 使能 AHB 外设时钟
 *
 * @param mask AHB 外设时钟使能位掩码
 */
void ll_rcc_ahb_enable(ll_rcc_ahbenr_bits mask)
{
    ll_set_bits(LL_RCC_BASE_ADDR, LL_RCC_AHBENR_OFFSET, mask);
}

/**
 * @brief 禁能 AHB 外设时钟
 *
 * @param mask AHB 外设时钟使能位掩码
 */
void ll_rcc_ahb_disable(ll_rcc_ahbenr_bits mask)
{
    ll_clear_bits(LL_RCC_BASE_ADDR, LL_RCC_AHBENR_OFFSET, mask);
}

/**
 * @brief 使能 APB1 外设时钟
 *
 * @param mask APB1 外设时钟使能位掩码
 */
void ll_rcc_apb1_enable(ll_rcc_apb1enr_bits mask)
{
    ll_set_bits(LL_RCC_BASE_ADDR, LL_RCC_APB1ENR_OFFSET, mask);
}

/**
 * @brief 禁能 APB1 外设时钟
 *
 * @param mask APB1 外设时钟使能位掩码
 */
void ll_rcc_apb1_disable(ll_rcc_apb1enr_bits mask)
{
    ll_clear_bits(LL_RCC_BASE_ADDR, LL_RCC_APB1ENR_OFFSET, mask);
}

/**
 * @brief 使能 APB2 外设时钟
 *
 * @param mask APB2 外设时钟使能位掩码
 */
void ll_rcc_apb2_enable(ll_rcc_apb2enr_bits mask)
{
    ll_set_bits(LL_RCC_BASE_ADDR, LL_RCC_APB2ENR_OFFSET, mask);
}

/**
 * @brief 禁能 APB2 外设时钟
 *
 * @param mask APB2 外设时钟使能位掩码
 */
void ll_rcc_apb2_disable(ll_rcc_apb2enr_bits mask)
{
    ll_clear_bits(LL_RCC_BASE_ADDR, LL_RCC_APB2ENR_OFFSET, mask);
}

/**
 * @brief 检查 AHB 外设时钟是否使能
 *
 * @param mask AHB 外设时钟使能位掩码
 * @return isENABLE
 *  ENABLE: 对应位掩码的外设时钟使能
 *  DISABLE: 对应位掩码的外设时钟未使能
 */
isENABLE ll_rcc_ahb_is_enabled(ll_rcc_ahbenr_bits mask)
{
    return (ll_read_reg(LL_RCC_BASE_ADDR, LL_RCC_AHBENR_OFFSET) & mask) != 0;
}

/**
 * @brief 检查 APB1 外设时钟是否使能
 *
 * @param mask APB1 外设时钟使能位掩码
 * @return isENABLE
 *  ENABLE: 对应位掩码的外设时钟使能
 *  DISABLE: 对应位掩码的外设时钟未使能
 */
isENABLE ll_rcc_apb1_is_enabled(ll_rcc_apb1enr_bits mask)
{
    return (ll_read_reg(LL_RCC_BASE_ADDR, LL_RCC_APB1ENR_OFFSET) & mask) != 0;
}

/**
 * @brief 检查 APB2 外设时钟是否使能
 *
 * @param mask APB2 外设时钟使能位掩码
 * @return isENABLE
 *  ENABLE: 对应位掩码的外设时钟使能
 *  DISABLE: 对应位掩码的外设时钟未使能
 */
isENABLE ll_rcc_apb2_is_enabled(ll_rcc_apb2enr_bits mask)
{
    return (ll_read_reg(LL_RCC_BASE_ADDR, LL_RCC_APB2ENR_OFFSET) & mask) != 0;
}
