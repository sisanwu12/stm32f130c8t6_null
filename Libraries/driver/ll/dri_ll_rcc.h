/**
 * @file dri_ll_rcc.h
 * @author sisanwu12
 * @brief STM32F103 RCC 底层寄存器接口
 * @version 0.1
 * @date 2026-03-24
 *
 */

#ifndef __DRI_LL_RCC_H__
#define __DRI_LL_RCC_H__

#include "data_type.h"

/* ========== 数据定义 ==========*/

/* ---------- RCC 地址定义层 ---------- */

/* RCC 基地址 */
#define LL_RCC_BASE_ADDR 0x40021000UL

/* RCC 寄存器偏移地址 */
#define LL_RCC_CR_OFFSET       0x00UL // 时钟控制寄存器
#define LL_RCC_CFGR_OFFSET     0x04UL // 时钟配置寄存器
#define LL_RCC_CIR_OFFSET      0x08UL // 时钟中断寄存器
#define LL_RCC_APB2RSTR_OFFSET 0x0CUL // APB2 外设复位寄存器
#define LL_RCC_APB1RSTR_OFFSET 0x10UL // APB1 外设复位寄存器
#define LL_RCC_AHBENR_OFFSET   0x14UL // AHB 外设时钟使能寄存器
#define LL_RCC_APB2ENR_OFFSET  0x18UL // APB2 外设时钟使能寄存器
#define LL_RCC_APB1ENR_OFFSET  0x1CUL // APB1 外设时钟使能寄存器
#define LL_RCC_BDCR_OFFSET     0x20UL // 备份域控制寄存器
#define LL_RCC_CSR_OFFSET      0x24UL // 控制/状态寄存器

/* ---------- RCC 寄存器位/字段定义 ---------- */

/* RCC_CR 位位置 */
#define LL_RCC_CR_HSION_POS  0U  // HSI 时钟使能位位置
#define LL_RCC_CR_HSIRDY_POS 1U  // HSI 就绪位位置
#define LL_RCC_CR_HSEON_POS  16U // HSE 时钟使能位位置
#define LL_RCC_CR_HSERDY_POS 17U // HSE 就绪位位置
#define LL_RCC_CR_HSEBYP_POS 18U // HSE 旁路位位置
#define LL_RCC_CR_CSSON_POS  19U // 时钟安全系统使能位位置
#define LL_RCC_CR_PLLON_POS  24U // PLL 时钟使能位位置
#define LL_RCC_CR_PLLRDY_POS 25U // PLL 就绪位位置

/* RCC_CR 位掩码 */
#define LL_RCC_CR_HSION_MASK  (LL_MASK_1 << LL_RCC_CR_HSION_POS)
#define LL_RCC_CR_HSIRDY_MASK (LL_MASK_1 << LL_RCC_CR_HSIRDY_POS)
#define LL_RCC_CR_HSEON_MASK  (LL_MASK_1 << LL_RCC_CR_HSEON_POS)
#define LL_RCC_CR_HSERDY_MASK (LL_MASK_1 << LL_RCC_CR_HSERDY_POS)
#define LL_RCC_CR_HSEBYP_MASK (LL_MASK_1 << LL_RCC_CR_HSEBYP_POS)
#define LL_RCC_CR_CSSON_MASK  (LL_MASK_1 << LL_RCC_CR_CSSON_POS)
#define LL_RCC_CR_PLLON_MASK  (LL_MASK_1 << LL_RCC_CR_PLLON_POS)
#define LL_RCC_CR_PLLRDY_MASK (LL_MASK_1 << LL_RCC_CR_PLLRDY_POS)

/* RCC_CFGR 字段位置 */
#define LL_RCC_CFGR_SW_POS       0U  // 系统时钟选择字段位置
#define LL_RCC_CFGR_SWS_POS      2U  // 系统时钟状态字段位置
#define LL_RCC_CFGR_HPRE_POS     4U  // AHB 预分频字段位置
#define LL_RCC_CFGR_PPRE1_POS    8U  // APB1 预分频字段位置
#define LL_RCC_CFGR_PPRE2_POS    11U // APB2 预分频字段位置
#define LL_RCC_CFGR_PLLSRC_POS   16U // PLL 时钟源字段位置
#define LL_RCC_CFGR_PLLXTPRE_POS 17U // HSE 送入 PLL 前分频字段位置
#define LL_RCC_CFGR_PLLMUL_POS   18U // PLL 倍频字段位置

/* RCC_CFGR 字段掩码 */
#define LL_RCC_CFGR_SW_MASK       (LL_MASK_2 << LL_RCC_CFGR_SW_POS)
#define LL_RCC_CFGR_SWS_MASK      (LL_MASK_2 << LL_RCC_CFGR_SWS_POS)
#define LL_RCC_CFGR_HPRE_MASK     (LL_MASK_4 << LL_RCC_CFGR_HPRE_POS)
#define LL_RCC_CFGR_PPRE1_MASK    (LL_MASK_3 << LL_RCC_CFGR_PPRE1_POS)
#define LL_RCC_CFGR_PPRE2_MASK    (LL_MASK_3 << LL_RCC_CFGR_PPRE2_POS)
#define LL_RCC_CFGR_PLLSRC_MASK   (LL_MASK_1 << LL_RCC_CFGR_PLLSRC_POS)
#define LL_RCC_CFGR_PLLXTPRE_MASK (LL_MASK_1 << LL_RCC_CFGR_PLLXTPRE_POS)
#define LL_RCC_CFGR_PLLMUL_MASK   (LL_MASK_4 << LL_RCC_CFGR_PLLMUL_POS)

/* AHB 外设时钟使能位类型 */
typedef u32 ll_rcc_ahbenr_bits;
/* AHB 外设时钟使能位位置 */
#define LL_RCC_AHB_DMA1_POS  0U  // DMA1 时钟使能位位置
#define LL_RCC_AHB_DMA2_POS  1U  // DMA2 时钟使能位位置
#define LL_RCC_AHB_SRAM_POS  2U  // SRAM 时钟使能位位置
#define LL_RCC_AHB_FLITF_POS 4U  // FLITF 时钟使能位位置
#define LL_RCC_AHB_CRC_POS   6U  // CRC 时钟使能位位置
#define LL_RCC_AHB_FSMC_POS  8U  // FSMC 时钟使能位位置
#define LL_RCC_AHB_SDIO_POS  10U // SDIO 时钟使能位位置

/* AHB 外设时钟使能位掩码 */
#define LL_RCC_AHB_DMA1_MASK  (LL_MASK_1 << LL_RCC_AHB_DMA1_POS)
#define LL_RCC_AHB_DMA2_MASK  (LL_MASK_1 << LL_RCC_AHB_DMA2_POS)
#define LL_RCC_AHB_SRAM_MASK  (LL_MASK_1 << LL_RCC_AHB_SRAM_POS)
#define LL_RCC_AHB_FLITF_MASK (LL_MASK_1 << LL_RCC_AHB_FLITF_POS)
#define LL_RCC_AHB_CRC_MASK   (LL_MASK_1 << LL_RCC_AHB_CRC_POS)
#define LL_RCC_AHB_FSMC_MASK  (LL_MASK_1 << LL_RCC_AHB_FSMC_POS)
#define LL_RCC_AHB_SDIO_MASK  (LL_MASK_1 << LL_RCC_AHB_SDIO_POS)

/* APB1 外设时钟使能位类型 */
typedef u32 ll_rcc_apb1enr_bits;
/* APB1 外设时钟使能位位置 */
#define LL_RCC_APB1_TIM2_POS   0U  // TIM2 时钟使能位位置
#define LL_RCC_APB1_TIM3_POS   1U  // TIM3 时钟使能位位置
#define LL_RCC_APB1_TIM4_POS   2U  // TIM4 时钟使能位位置
#define LL_RCC_APB1_WWDG_POS   11U // WWDG 时钟使能位位置
#define LL_RCC_APB1_SPI2_POS   14U // SPI2 时钟使能位位置
#define LL_RCC_APB1_SPI3_POS   15U // SPI3 时钟使能位位置
#define LL_RCC_APB1_USART2_POS 17U // USART2 时钟使能位位置
#define LL_RCC_APB1_USART3_POS 18U // USART3 时钟使能位位置
#define LL_RCC_APB1_I2C1_POS   21U // I2C1 时钟使能位位置
#define LL_RCC_APB1_I2C2_POS   22U // I2C2 时钟使能位位置
#define LL_RCC_APB1_USB_POS    23U // USB 时钟使能位位置
#define LL_RCC_APB1_CAN_POS    25U // CAN 时钟使能位位置
#define LL_RCC_APB1_BKP_POS    27U // BKP 时钟使能位位置
#define LL_RCC_APB1_PWR_POS    28U // PWR 时钟使能位位置
#define LL_RCC_APB1_DAC_POS    29U // DAC 时钟使能位位置

/* APB1 外设时钟使能位掩码 */
#define LL_RCC_APB1_TIM2_MASK   (LL_MASK_1 << LL_RCC_APB1_TIM2_POS)
#define LL_RCC_APB1_TIM3_MASK   (LL_MASK_1 << LL_RCC_APB1_TIM3_POS)
#define LL_RCC_APB1_TIM4_MASK   (LL_MASK_1 << LL_RCC_APB1_TIM4_POS)
#define LL_RCC_APB1_WWDG_MASK   (LL_MASK_1 << LL_RCC_APB1_WWDG_POS)
#define LL_RCC_APB1_SPI2_MASK   (LL_MASK_1 << LL_RCC_APB1_SPI2_POS)
#define LL_RCC_APB1_SPI3_MASK   (LL_MASK_1 << LL_RCC_APB1_SPI3_POS)
#define LL_RCC_APB1_USART2_MASK (LL_MASK_1 << LL_RCC_APB1_USART2_POS)
#define LL_RCC_APB1_USART3_MASK (LL_MASK_1 << LL_RCC_APB1_USART3_POS)
#define LL_RCC_APB1_I2C1_MASK   (LL_MASK_1 << LL_RCC_APB1_I2C1_POS)
#define LL_RCC_APB1_I2C2_MASK   (LL_MASK_1 << LL_RCC_APB1_I2C2_POS)
#define LL_RCC_APB1_USB_MASK    (LL_MASK_1 << LL_RCC_APB1_USB_POS)
#define LL_RCC_APB1_CAN_MASK    (LL_MASK_1 << LL_RCC_APB1_CAN_POS)
#define LL_RCC_APB1_BKP_MASK    (LL_MASK_1 << LL_RCC_APB1_BKP_POS)
#define LL_RCC_APB1_PWR_MASK    (LL_MASK_1 << LL_RCC_APB1_PWR_POS)
#define LL_RCC_APB1_DAC_MASK    (LL_MASK_1 << LL_RCC_APB1_DAC_POS)

/* APB2 外设时钟使能位类型 */
typedef u32 ll_rcc_apb2enr_bits;
/* APB2 外设时钟使能位位置 */
#define LL_RCC_APB2_AFIO_POS   0U  // AFIO 时钟使能位位置
#define LL_RCC_APB2_GPIOA_POS  2U  // GPIOA 时钟使能位位置
#define LL_RCC_APB2_GPIOB_POS  3U  // GPIOB 时钟使能位位置
#define LL_RCC_APB2_GPIOC_POS  4U  // GPIOC 时钟使能位位置
#define LL_RCC_APB2_GPIOD_POS  5U  // GPIOD 时钟使能位位置
#define LL_RCC_APB2_GPIOE_POS  6U  // GPIOE 时钟使能位位置
#define LL_RCC_APB2_ADC1_POS   9U  // ADC1 时钟使能位位置
#define LL_RCC_APB2_ADC2_POS   10U // ADC2 时钟使能位位置
#define LL_RCC_APB2_TIM1_POS   11U // TIM1 时钟使能位位置
#define LL_RCC_APB2_SPI1_POS   12U // SPI1 时钟使能位位置
#define LL_RCC_APB2_USART1_POS 14U // USART1 时钟使能位位置

/* APB2 外设时钟使能位掩码 */
#define LL_RCC_APB2_AFIO_MASK   (LL_MASK_1 << LL_RCC_APB2_AFIO_POS)
#define LL_RCC_APB2_GPIOA_MASK  (LL_MASK_1 << LL_RCC_APB2_GPIOA_POS)
#define LL_RCC_APB2_GPIOB_MASK  (LL_MASK_1 << LL_RCC_APB2_GPIOB_POS)
#define LL_RCC_APB2_GPIOC_MASK  (LL_MASK_1 << LL_RCC_APB2_GPIOC_POS)
#define LL_RCC_APB2_GPIOD_MASK  (LL_MASK_1 << LL_RCC_APB2_GPIOD_POS)
#define LL_RCC_APB2_GPIOE_MASK  (LL_MASK_1 << LL_RCC_APB2_GPIOE_POS)
#define LL_RCC_APB2_ADC1_MASK   (LL_MASK_1 << LL_RCC_APB2_ADC1_POS)
#define LL_RCC_APB2_ADC2_MASK   (LL_MASK_1 << LL_RCC_APB2_ADC2_POS)
#define LL_RCC_APB2_TIM1_MASK   (LL_MASK_1 << LL_RCC_APB2_TIM1_POS)
#define LL_RCC_APB2_SPI1_MASK   (LL_MASK_1 << LL_RCC_APB2_SPI1_POS)
#define LL_RCC_APB2_USART1_MASK (LL_MASK_1 << LL_RCC_APB2_USART1_POS)

/* ---------- 参数 ---------- */

/* 系统时钟源 */
typedef enum
{
    LL_RCC_SYSCLK_SOURCE_HSI = 0x00UL, // HSI 作为系统时钟
    LL_RCC_SYSCLK_SOURCE_HSE = 0x01UL, // HSE 作为系统时钟
    LL_RCC_SYSCLK_SOURCE_PLL = 0x02UL, // PLL 作为系统时钟
} ll_rcc_sysclk_source;

/* 系统时钟状态 */
typedef enum
{
    LL_RCC_SYSCLK_STATUS_HSI     = 0x00UL, // HSI 作为系统时钟
    LL_RCC_SYSCLK_STATUS_HSE     = 0x01UL, // HSE 作为系统时钟
    LL_RCC_SYSCLK_STATUS_PLL     = 0x02UL, // PLL 作为系统时钟
    LL_RCC_SYSCLK_STATUS_INVALID = 0x03UL, // 保留值
} ll_rcc_sysclk_status;

#define LL_RCC_SYSCLK_STATUS_NOALL LL_RCC_SYSCLK_STATUS_INVALID

/* AHB 分频系数（HPRE 字段值） */
typedef enum
{
    LL_RCC_AHB_PRESCALER_DIV1   = 0x00UL, // HCLK = SYSCLK
    LL_RCC_AHB_PRESCALER_DIV2   = 0x08UL, // HCLK = SYSCLK / 2
    LL_RCC_AHB_PRESCALER_DIV4   = 0x09UL, // HCLK = SYSCLK / 4
    LL_RCC_AHB_PRESCALER_DIV8   = 0x0AUL, // HCLK = SYSCLK / 8
    LL_RCC_AHB_PRESCALER_DIV16  = 0x0BUL, // HCLK = SYSCLK / 16
    LL_RCC_AHB_PRESCALER_DIV64  = 0x0CUL, // HCLK = SYSCLK / 64
    LL_RCC_AHB_PRESCALER_DIV128 = 0x0DUL, // HCLK = SYSCLK / 128
    LL_RCC_AHB_PRESCALER_DIV256 = 0x0EUL, // HCLK = SYSCLK / 256
    LL_RCC_AHB_PRESCALER_DIV512 = 0x0FUL, // HCLK = SYSCLK / 512
} ll_rcc_ahb_prescaler;

/* APB 分频系数（PPRE 字段值） */
typedef enum
{
    LL_RCC_APB_PRESCALER_DIV1  = 0x00UL, // PCLK = HCLK
    LL_RCC_APB_PRESCALER_DIV2  = 0x04UL, // PCLK = HCLK / 2
    LL_RCC_APB_PRESCALER_DIV4  = 0x05UL, // PCLK = HCLK / 4
    LL_RCC_APB_PRESCALER_DIV8  = 0x06UL, // PCLK = HCLK / 8
    LL_RCC_APB_PRESCALER_DIV16 = 0x07UL, // PCLK = HCLK / 16
} ll_rcc_apb_prescaler;

/* PLL 时钟源 */
typedef enum
{
    LL_RCC_PLL_SOURCE_HSI_DIV2 = 0x00UL, // (HSI / 2) 作为 PLL 时钟源
    LL_RCC_PLL_SOURCE_HSE      = 0x01UL, // HSE 作为 PLL 时钟源
} ll_rcc_pll_source;

/* PLL 倍频系数（PLLMUL 字段值） */
typedef enum
{
    LL_RCC_PLL_MUL_2  = 0x00UL, // 2 倍频
    LL_RCC_PLL_MUL_3  = 0x01UL, // 3 倍频
    LL_RCC_PLL_MUL_4  = 0x02UL, // 4 倍频
    LL_RCC_PLL_MUL_5  = 0x03UL, // 5 倍频
    LL_RCC_PLL_MUL_6  = 0x04UL, // 6 倍频
    LL_RCC_PLL_MUL_7  = 0x05UL, // 7 倍频
    LL_RCC_PLL_MUL_8  = 0x06UL, // 8 倍频
    LL_RCC_PLL_MUL_9  = 0x07UL, // 9 倍频
    LL_RCC_PLL_MUL_10 = 0x08UL, // 10 倍频
    LL_RCC_PLL_MUL_11 = 0x09UL, // 11 倍频
    LL_RCC_PLL_MUL_12 = 0x0AUL, // 12 倍频
    LL_RCC_PLL_MUL_13 = 0x0BUL, // 13 倍频
    LL_RCC_PLL_MUL_14 = 0x0CUL, // 14 倍频
    LL_RCC_PLL_MUL_15 = 0x0DUL, // 15 倍频
    LL_RCC_PLL_MUL_16 = 0x0EUL, // 16 倍频
} ll_rcc_pll_mul;

/* HSE 送入 PLL 前的分频系数 */
typedef enum
{
    LL_RCC_PLL_HSE_DIV_1 = 0x00UL, // HSE 不分频
    LL_RCC_PLL_HSE_DIV_2 = 0x01UL, // HSE 分频 2
} ll_rcc_pll_hse_div;

/* ========== 对外接口 ========== */

/* ---------- 时钟源控制 ---------- */

void    ll_rcc_hsi_enable(void);
void    ll_rcc_hsi_disable(void);
isREADY ll_rcc_hsi_is_ready(void);

void    ll_rcc_hse_enable(void);
void    ll_rcc_hse_disable(void);
isREADY ll_rcc_hse_is_ready(void);

void    ll_rcc_pll_enable(void);
void    ll_rcc_pll_disable(void);
isREADY ll_rcc_pll_is_ready(void);

void ll_rcc_hse_bypass_enable(void);
void ll_rcc_hse_bypass_disable(void);

/* ---------- 系统时钟与分频 ---------- */

void                 ll_rcc_sysclk_select(ll_rcc_sysclk_source sysclk_source);
void                 ll_rcc_ahb_prescaler_set(ll_rcc_ahb_prescaler ahb_prescaler);
void                 ll_rcc_apb1_prescaler_set(ll_rcc_apb_prescaler apb1_prescaler);
void                 ll_rcc_apb2_prescaler_set(ll_rcc_apb_prescaler apb2_prescaler);
ll_rcc_sysclk_source ll_rcc_sysclk_source_get(void);
ll_rcc_sysclk_status ll_rcc_sysclk_status_get(void);

/* ---------- PLL 配置 ---------- */

void              ll_rcc_pll_source_set(ll_rcc_pll_source source);
void              ll_rcc_pll_mul_set(ll_rcc_pll_mul value);
ll_rcc_pll_source ll_rcc_pll_source_get(void);
ll_rcc_pll_mul    ll_rcc_pll_mul_get(void);
void              ll_rcc_pll_hse_div_set(ll_rcc_pll_hse_div div);

/* ---------- 外设时钟门控 ---------- */

void     ll_rcc_ahb_enable(ll_rcc_ahbenr_bits mask);
void     ll_rcc_ahb_disable(ll_rcc_ahbenr_bits mask);
isENABLE ll_rcc_ahb_is_enabled(ll_rcc_ahbenr_bits mask);

void     ll_rcc_apb1_enable(ll_rcc_apb1enr_bits mask);
void     ll_rcc_apb1_disable(ll_rcc_apb1enr_bits mask);
isENABLE ll_rcc_apb1_is_enabled(ll_rcc_apb1enr_bits mask);

void     ll_rcc_apb2_enable(ll_rcc_apb2enr_bits mask);
void     ll_rcc_apb2_disable(ll_rcc_apb2enr_bits mask);
isENABLE ll_rcc_apb2_is_enabled(ll_rcc_apb2enr_bits mask);

#endif /* __DRI_LL_RCC_H__ */
