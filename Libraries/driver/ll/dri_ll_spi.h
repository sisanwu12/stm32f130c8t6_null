/**
 * @file dri_ll_spi.h
 * @author Beam
 * @brief STM32F103 SPI 底层寄存器接口。
 * @note
 * - SPI v1 只负责 `SPI1/SPI2` 主机模式、默认 `SCK/MISO/MOSI` 引脚、阻塞轮询收发。
 * - SPI v1 不负责 RCC 开时钟、不负责 `CS/NSS` 管理、不负责 remap、中断、DMA、CRC、从机模式。
 * - 调用 `ll_spi_init()` 前，外部必须先打开对应 SPI 和 GPIO 时钟。
 * @version 0.1
 * @date 2026-04-23
 *
 */

#ifndef __DRI_LL_SPI_H__
#define __DRI_LL_SPI_H__

#include "data_type.h"

/* ========== 数据定义 ==========*/

/* ---------- SPI 地址定义层 ---------- */

/* SPI 基地址 */
#define LL_SPI1_BASE_ADDR 0x40013000UL // SPI1 基地址
#define LL_SPI2_BASE_ADDR 0x40003800UL // SPI2 基地址

/* SPI 寄存器偏移地址 */
#define LL_SPI_CR1_OFFSET     0x00UL // 控制寄存器 1
#define LL_SPI_CR2_OFFSET     0x04UL // 控制寄存器 2
#define LL_SPI_SR_OFFSET      0x08UL // 状态寄存器
#define LL_SPI_DR_OFFSET      0x0CUL // 数据寄存器
#define LL_SPI_CRCPR_OFFSET   0x10UL // CRC 多项式寄存器
#define LL_SPI_RXCRCR_OFFSET  0x14UL // RX CRC 寄存器
#define LL_SPI_TXCRCR_OFFSET  0x18UL // TX CRC 寄存器
#define LL_SPI_I2SCFGR_OFFSET 0x1CUL // I2S 配置寄存器
#define LL_SPI_I2SPR_OFFSET   0x20UL // I2S 预分频寄存器

/* ---------- SPI 寄存器位/字段定义 ---------- */

/* SPI_CR1 位位置 */
#define LL_SPI_CR1_CPHA_POS     0U  // 时钟相位
#define LL_SPI_CR1_CPOL_POS     1U  // 时钟极性
#define LL_SPI_CR1_MSTR_POS     2U  // 主机选择
#define LL_SPI_CR1_BR_POS       3U  // 波特率分频
#define LL_SPI_CR1_SPE_POS      6U  // SPI 使能
#define LL_SPI_CR1_LSBFIRST_POS 7U  // 帧格式
#define LL_SPI_CR1_SSI_POS      8U  // 内部从设备选择
#define LL_SPI_CR1_SSM_POS      9U  // 软件从设备管理
#define LL_SPI_CR1_RXONLY_POS   10U // 仅接收模式
#define LL_SPI_CR1_DFF_POS      11U // 数据帧格式
#define LL_SPI_CR1_CRCEN_POS    13U // 硬件 CRC 使能
#define LL_SPI_CR1_BIDIOE_POS   14U // 双向输出使能
#define LL_SPI_CR1_BIDIMODE_POS 15U // 双向模式使能

/* SPI_CR1 位掩码 */
#define LL_SPI_CR1_CPHA_MASK     (LL_MASK_1 << LL_SPI_CR1_CPHA_POS)
#define LL_SPI_CR1_CPOL_MASK     (LL_MASK_1 << LL_SPI_CR1_CPOL_POS)
#define LL_SPI_CR1_MSTR_MASK     (LL_MASK_1 << LL_SPI_CR1_MSTR_POS)
#define LL_SPI_CR1_BR_MASK       (LL_MASK_3 << LL_SPI_CR1_BR_POS)
#define LL_SPI_CR1_SPE_MASK      (LL_MASK_1 << LL_SPI_CR1_SPE_POS)
#define LL_SPI_CR1_LSBFIRST_MASK (LL_MASK_1 << LL_SPI_CR1_LSBFIRST_POS)
#define LL_SPI_CR1_SSI_MASK      (LL_MASK_1 << LL_SPI_CR1_SSI_POS)
#define LL_SPI_CR1_SSM_MASK      (LL_MASK_1 << LL_SPI_CR1_SSM_POS)
#define LL_SPI_CR1_RXONLY_MASK   (LL_MASK_1 << LL_SPI_CR1_RXONLY_POS)
#define LL_SPI_CR1_DFF_MASK      (LL_MASK_1 << LL_SPI_CR1_DFF_POS)
#define LL_SPI_CR1_CRCEN_MASK    (LL_MASK_1 << LL_SPI_CR1_CRCEN_POS)
#define LL_SPI_CR1_BIDIOE_MASK   (LL_MASK_1 << LL_SPI_CR1_BIDIOE_POS)
#define LL_SPI_CR1_BIDIMODE_MASK (LL_MASK_1 << LL_SPI_CR1_BIDIMODE_POS)

/* SPI_SR 位位置 */
#define LL_SPI_SR_RXNE_POS 0U // 接收缓冲区非空
#define LL_SPI_SR_TXE_POS  1U // 发送缓冲区为空
#define LL_SPI_SR_OVR_POS  6U // 溢出标志
#define LL_SPI_SR_BSY_POS  7U // 总线忙标志

/* SPI_SR 位掩码 */
#define LL_SPI_SR_RXNE_MASK (LL_MASK_1 << LL_SPI_SR_RXNE_POS)
#define LL_SPI_SR_TXE_MASK  (LL_MASK_1 << LL_SPI_SR_TXE_POS)
#define LL_SPI_SR_OVR_MASK  (LL_MASK_1 << LL_SPI_SR_OVR_POS)
#define LL_SPI_SR_BSY_MASK  (LL_MASK_1 << LL_SPI_SR_BSY_POS)

/* SPI_I2SCFGR 位位置 */
#define LL_SPI_I2SCFGR_I2SMOD_POS 11U // I2S 模式选择

/* SPI_I2SCFGR 位掩码 */
#define LL_SPI_I2SCFGR_I2SMOD_MASK (LL_MASK_1 << LL_SPI_I2SCFGR_I2SMOD_POS)

/* ---------- 参数 ---------- */

/* SPI 实例 */
typedef enum
{
    LL_SPI_1 = 0U,
    LL_SPI_2 = 1U,
} ll_spi_instance_t;

/* SPI 模式 */
typedef enum
{
    LL_SPI_MODE_0 = 0U,
    LL_SPI_MODE_1 = 1U,
    LL_SPI_MODE_2 = 2U,
    LL_SPI_MODE_3 = 3U,
} ll_spi_mode_t;

/* SPI 波特率分频 */
typedef enum
{
    LL_SPI_BAUD_PRESCALER_DIV2   = 0U,
    LL_SPI_BAUD_PRESCALER_DIV4   = 1U,
    LL_SPI_BAUD_PRESCALER_DIV8   = 2U,
    LL_SPI_BAUD_PRESCALER_DIV16  = 3U,
    LL_SPI_BAUD_PRESCALER_DIV32  = 4U,
    LL_SPI_BAUD_PRESCALER_DIV64  = 5U,
    LL_SPI_BAUD_PRESCALER_DIV128 = 6U,
    LL_SPI_BAUD_PRESCALER_DIV256 = 7U,
} ll_spi_baud_prescaler_t;

/* SPI 首位传输顺序 */
typedef enum
{
    LL_SPI_FIRST_BIT_MSB = 0U,
    LL_SPI_FIRST_BIT_LSB = 1U,
} ll_spi_first_bit_t;

/* SPI 状态码 */
typedef enum
{
    LL_SPI_OK                  = 0U,
    LL_SPI_ERROR_INVALID_PARAM = 1U,
    LL_SPI_ERROR_TIMEOUT       = 2U,
} ll_spi_status_t;

/* SPI 初始化结构体 */
typedef struct
{
    ll_spi_instance_t       instance;       // SPI 实例
    ll_spi_mode_t           mode;           // SPI 模式
    ll_spi_baud_prescaler_t baud_prescaler; // 波特率分频
    ll_spi_first_bit_t      first_bit;      // 首位传输顺序
} ll_spi_init_t;

/* ========== 对外接口 ========== */

/* SPI 初始化 */
ll_spi_status_t ll_spi_init(const ll_spi_init_t* cfg);

/* 状态位等待 */
ll_spi_status_t ll_spi_wait_flag_set(ll_spi_instance_t instance, u32 flag_mask, u32 timeout_count);
ll_spi_status_t ll_spi_wait_flag_clear(ll_spi_instance_t instance, u32 flag_mask,
                                       u32 timeout_count);

/* 单字节收发 */
ll_spi_status_t ll_spi_transfer_byte(ll_spi_instance_t instance, u8 tx_byte, u8* rx_byte,
                                     u32 timeout_count);
ll_spi_status_t ll_spi_write_byte(ll_spi_instance_t instance, u8 tx_byte, u32 timeout_count);
ll_spi_status_t ll_spi_read_byte(ll_spi_instance_t instance, u8* rx_byte, u32 timeout_count);

/* 缓冲区收发 */
ll_spi_status_t ll_spi_transfer_buffer(ll_spi_instance_t instance, const u8* tx_buf, u8* rx_buf,
                                       u32 len, u32* completed_len, u32 timeout_count);
ll_spi_status_t ll_spi_write_buffer(ll_spi_instance_t instance, const u8* tx_buf, u32 len,
                                    u32* completed_len, u32 timeout_count);
ll_spi_status_t ll_spi_read_buffer(ll_spi_instance_t instance, u8* rx_buf, u32 len,
                                   u32* completed_len, u32 timeout_count);

#endif /* __DRI_LL_SPI_H__ */
