/**
 * @file dri_ll_spi.c
 * @author sisanwu12
 * @brief STM32F103 SPI 底层寄存器接口实现。
 * @version 0.1
 * @date 2026-04-23
 *
 */

#include "dri_ll_spi.h"
#include "dri_ll.h"
#include "dri_ll_gpio.h"

/* ========== 内部函数声明 ========== */

static bool            ll_spi_is_valid_instance(ll_spi_instance_t instance);
static bool            ll_spi_is_valid_mode(ll_spi_mode_t mode);
static bool            ll_spi_is_valid_baud_prescaler(ll_spi_baud_prescaler_t baud_prescaler);
static bool            ll_spi_is_valid_first_bit(ll_spi_first_bit_t first_bit);
static uptr            ll_spi_get_base(ll_spi_instance_t instance);
static ll_spi_status_t ll_spi_configure_default_gpio(ll_spi_instance_t instance);
static void            ll_spi_write_dr8(uptr base_addr, u8 value);
static u8              ll_spi_read_dr8(uptr base_addr);

/* ========== 对外接口实现 ========== */

/**
 * @brief 初始化 SPI 外设
 *
 * @param cfg 初始化配置结构体指针
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_init(const ll_spi_init_t* cfg)
{
    u32 cr1_value = 0U;
    uptr base_addr;

    if (cfg == NULL)
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    if (!ll_spi_is_valid_instance(cfg->instance) || !ll_spi_is_valid_mode(cfg->mode) ||
        !ll_spi_is_valid_baud_prescaler(cfg->baud_prescaler) ||
        !ll_spi_is_valid_first_bit(cfg->first_bit))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    base_addr = ll_spi_get_base(cfg->instance);

    ll_clear_bits(base_addr, LL_SPI_CR1_OFFSET, LL_SPI_CR1_SPE_MASK);
    ll_clear_bits(base_addr, LL_SPI_I2SCFGR_OFFSET, LL_SPI_I2SCFGR_I2SMOD_MASK);

    if (ll_spi_configure_default_gpio(cfg->instance) != LL_SPI_OK)
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    cr1_value |= LL_SPI_CR1_MSTR_MASK;
    cr1_value |= LL_SPI_CR1_SSM_MASK;
    cr1_value |= LL_SPI_CR1_SSI_MASK;
    cr1_value |= ((u32)cfg->baud_prescaler << LL_SPI_CR1_BR_POS) & LL_SPI_CR1_BR_MASK;

    if (cfg->first_bit == LL_SPI_FIRST_BIT_LSB)
    {
        cr1_value |= LL_SPI_CR1_LSBFIRST_MASK;
    }

    switch (cfg->mode)
    {
    case LL_SPI_MODE_0:
        break;
    case LL_SPI_MODE_1:
        cr1_value |= LL_SPI_CR1_CPHA_MASK;
        break;
    case LL_SPI_MODE_2:
        cr1_value |= LL_SPI_CR1_CPOL_MASK;
        break;
    case LL_SPI_MODE_3:
        cr1_value |= LL_SPI_CR1_CPOL_MASK;
        cr1_value |= LL_SPI_CR1_CPHA_MASK;
        break;
    default:
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    ll_write_reg(base_addr, LL_SPI_CR2_OFFSET, 0U);
    ll_write_reg(base_addr, LL_SPI_CR1_OFFSET, cr1_value);
    ll_set_bits(base_addr, LL_SPI_CR1_OFFSET, LL_SPI_CR1_SPE_MASK);

    return LL_SPI_OK;
}

/**
 * @brief 等待状态位被置位
 *
 * @param instance SPI 实例
 * @param flag_mask 状态位掩码
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_wait_flag_set(ll_spi_instance_t instance, u32 flag_mask, u32 timeout_count)
{
    uptr base_addr;

    if (!ll_spi_is_valid_instance(instance) || (flag_mask == 0U))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    if (timeout_count == 0U)
    {
        return LL_SPI_ERROR_TIMEOUT;
    }

    base_addr = ll_spi_get_base(instance);

    while (timeout_count > 0U)
    {
        if ((ll_read_reg(base_addr, LL_SPI_SR_OFFSET) & flag_mask) == flag_mask)
        {
            return LL_SPI_OK;
        }
        timeout_count--;
    }

    return LL_SPI_ERROR_TIMEOUT;
}

/**
 * @brief 等待状态位被清零
 *
 * @param instance SPI 实例
 * @param flag_mask 状态位掩码
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_wait_flag_clear(ll_spi_instance_t instance, u32 flag_mask, u32 timeout_count)
{
    uptr base_addr;

    if (!ll_spi_is_valid_instance(instance) || (flag_mask == 0U))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    if (timeout_count == 0U)
    {
        return LL_SPI_ERROR_TIMEOUT;
    }

    base_addr = ll_spi_get_base(instance);

    while (timeout_count > 0U)
    {
        if ((ll_read_reg(base_addr, LL_SPI_SR_OFFSET) & flag_mask) == 0U)
        {
            return LL_SPI_OK;
        }
        timeout_count--;
    }

    return LL_SPI_ERROR_TIMEOUT;
}

/**
 * @brief 单字节全双工传输
 *
 * @param instance SPI 实例
 * @param tx_byte 发送字节
 * @param rx_byte 接收字节缓冲区
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_transfer_byte(ll_spi_instance_t instance, u8 tx_byte, u8* rx_byte,
                                     u32 timeout_count)
{
    uptr            base_addr;
    ll_spi_status_t ret;

    if (!ll_spi_is_valid_instance(instance) || (rx_byte == NULL))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    ret = ll_spi_wait_flag_set(instance, LL_SPI_SR_TXE_MASK, timeout_count);
    if (ret != LL_SPI_OK)
    {
        return ret;
    }

    base_addr = ll_spi_get_base(instance);
    ll_spi_write_dr8(base_addr, tx_byte);

    ret = ll_spi_wait_flag_set(instance, LL_SPI_SR_RXNE_MASK, timeout_count);
    if (ret != LL_SPI_OK)
    {
        return ret;
    }

    *rx_byte = ll_spi_read_dr8(base_addr);

    ret = ll_spi_wait_flag_clear(instance, LL_SPI_SR_BSY_MASK, timeout_count);
    if (ret != LL_SPI_OK)
    {
        return ret;
    }

    return LL_SPI_OK;
}

/**
 * @brief 单字节发送
 *
 * @param instance SPI 实例
 * @param tx_byte 待发送字节
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_write_byte(ll_spi_instance_t instance, u8 tx_byte, u32 timeout_count)
{
    u8 dummy_rx = 0U;

    return ll_spi_transfer_byte(instance, tx_byte, &dummy_rx, timeout_count);
}

/**
 * @brief 单字节读取
 *
 * @param instance SPI 实例
 * @param rx_byte 接收字节缓冲区
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_read_byte(ll_spi_instance_t instance, u8* rx_byte, u32 timeout_count)
{
    if (rx_byte == NULL)
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    return ll_spi_transfer_byte(instance, 0xFFU, rx_byte, timeout_count);
}

/**
 * @brief 缓冲区全双工传输
 *
 * @param instance SPI 实例
 * @param tx_buf 发送缓冲区
 * @param rx_buf 接收缓冲区
 * @param len 传输长度
 * @param completed_len 已完成长度
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_transfer_buffer(ll_spi_instance_t instance, const u8* tx_buf, u8* rx_buf,
                                       u32 len, u32* completed_len, u32 timeout_count)
{
    u32 index;

    if (completed_len != NULL)
    {
        *completed_len = 0U;
    }

    if (!ll_spi_is_valid_instance(instance))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    if (len == 0U)
    {
        return LL_SPI_OK;
    }

    if ((tx_buf == NULL) || (rx_buf == NULL))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    for (index = 0U; index < len; index++)
    {
        ll_spi_status_t ret = ll_spi_transfer_byte(instance, tx_buf[index], &rx_buf[index],
                                                   timeout_count);
        if (ret != LL_SPI_OK)
        {
            return ret;
        }

        if (completed_len != NULL)
        {
            (*completed_len)++;
        }
    }

    return LL_SPI_OK;
}

/**
 * @brief 缓冲区发送
 *
 * @param instance SPI 实例
 * @param tx_buf 发送缓冲区
 * @param len 发送长度
 * @param completed_len 已完成长度
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_write_buffer(ll_spi_instance_t instance, const u8* tx_buf, u32 len,
                                    u32* completed_len, u32 timeout_count)
{
    u32 index;

    if (completed_len != NULL)
    {
        *completed_len = 0U;
    }

    if (!ll_spi_is_valid_instance(instance))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    if (len == 0U)
    {
        return LL_SPI_OK;
    }

    if (tx_buf == NULL)
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    for (index = 0U; index < len; index++)
    {
        ll_spi_status_t ret = ll_spi_write_byte(instance, tx_buf[index], timeout_count);
        if (ret != LL_SPI_OK)
        {
            return ret;
        }

        if (completed_len != NULL)
        {
            (*completed_len)++;
        }
    }

    return LL_SPI_OK;
}

/**
 * @brief 缓冲区读取
 *
 * @param instance SPI 实例
 * @param rx_buf 接收缓冲区
 * @param len 读取长度
 * @param completed_len 已完成长度
 * @param timeout_count 超时计数
 * @return ll_spi_status_t 状态码
 */
ll_spi_status_t ll_spi_read_buffer(ll_spi_instance_t instance, u8* rx_buf, u32 len,
                                   u32* completed_len, u32 timeout_count)
{
    u32 index;

    if (completed_len != NULL)
    {
        *completed_len = 0U;
    }

    if (!ll_spi_is_valid_instance(instance))
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    if (len == 0U)
    {
        return LL_SPI_OK;
    }

    if (rx_buf == NULL)
    {
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    for (index = 0U; index < len; index++)
    {
        ll_spi_status_t ret = ll_spi_read_byte(instance, &rx_buf[index], timeout_count);
        if (ret != LL_SPI_OK)
        {
            return ret;
        }

        if (completed_len != NULL)
        {
            (*completed_len)++;
        }
    }

    return LL_SPI_OK;
}

/* ========== 内部函数实现 ========== */

static bool ll_spi_is_valid_instance(ll_spi_instance_t instance)
{
    return (instance == LL_SPI_1) || (instance == LL_SPI_2);
}

static bool ll_spi_is_valid_mode(ll_spi_mode_t mode)
{
    return (mode == LL_SPI_MODE_0) || (mode == LL_SPI_MODE_1) || (mode == LL_SPI_MODE_2) ||
           (mode == LL_SPI_MODE_3);
}

static bool ll_spi_is_valid_baud_prescaler(ll_spi_baud_prescaler_t baud_prescaler)
{
    switch (baud_prescaler)
    {
    case LL_SPI_BAUD_PRESCALER_DIV2:
    case LL_SPI_BAUD_PRESCALER_DIV4:
    case LL_SPI_BAUD_PRESCALER_DIV8:
    case LL_SPI_BAUD_PRESCALER_DIV16:
    case LL_SPI_BAUD_PRESCALER_DIV32:
    case LL_SPI_BAUD_PRESCALER_DIV64:
    case LL_SPI_BAUD_PRESCALER_DIV128:
    case LL_SPI_BAUD_PRESCALER_DIV256:
        return true;
    default:
        return false;
    }
}

static bool ll_spi_is_valid_first_bit(ll_spi_first_bit_t first_bit)
{
    return (first_bit == LL_SPI_FIRST_BIT_MSB) || (first_bit == LL_SPI_FIRST_BIT_LSB);
}

static uptr ll_spi_get_base(ll_spi_instance_t instance)
{
    switch (instance)
    {
    case LL_SPI_1:
        return LL_SPI1_BASE_ADDR;
    case LL_SPI_2:
        return LL_SPI2_BASE_ADDR;
    default:
        return 0UL;
    }
}

static ll_spi_status_t ll_spi_configure_default_gpio(ll_spi_instance_t instance)
{
    ll_gpio_init_t gpio_cfg;

    gpio_cfg.mode  = LL_GPIO_MODE_OUTPUT_50;
    gpio_cfg.cnf   = LL_GPIO_CNF_OUTPUT_AF_PP;
    gpio_cfg.level = LL_GPIO_LEVEL_LOW;

    switch (instance)
    {
    case LL_SPI_1:
        gpio_cfg.port = LL_GPIO_PORT_A;

        gpio_cfg.pin = LL_GPIO_PIN_5;
        if (ll_gpio_init(&gpio_cfg) != GPIO_INIT_SUCCESS)
        {
            return LL_SPI_ERROR_INVALID_PARAM;
        }

        gpio_cfg.mode = LL_GPIO_MODE_INPUT;
        gpio_cfg.cnf  = LL_GPIO_CNF_INPUT_FLOAT;
        gpio_cfg.pin  = LL_GPIO_PIN_6;
        if (ll_gpio_init(&gpio_cfg) != GPIO_INIT_SUCCESS)
        {
            return LL_SPI_ERROR_INVALID_PARAM;
        }

        gpio_cfg.mode = LL_GPIO_MODE_OUTPUT_50;
        gpio_cfg.cnf  = LL_GPIO_CNF_OUTPUT_AF_PP;
        gpio_cfg.pin  = LL_GPIO_PIN_7;
        if (ll_gpio_init(&gpio_cfg) != GPIO_INIT_SUCCESS)
        {
            return LL_SPI_ERROR_INVALID_PARAM;
        }
        break;

    case LL_SPI_2:
        gpio_cfg.port = LL_GPIO_PORT_B;

        gpio_cfg.pin = LL_GPIO_PIN_13;
        if (ll_gpio_init(&gpio_cfg) != GPIO_INIT_SUCCESS)
        {
            return LL_SPI_ERROR_INVALID_PARAM;
        }

        gpio_cfg.mode = LL_GPIO_MODE_INPUT;
        gpio_cfg.cnf  = LL_GPIO_CNF_INPUT_FLOAT;
        gpio_cfg.pin  = LL_GPIO_PIN_14;
        if (ll_gpio_init(&gpio_cfg) != GPIO_INIT_SUCCESS)
        {
            return LL_SPI_ERROR_INVALID_PARAM;
        }

        gpio_cfg.mode = LL_GPIO_MODE_OUTPUT_50;
        gpio_cfg.cnf  = LL_GPIO_CNF_OUTPUT_AF_PP;
        gpio_cfg.pin  = LL_GPIO_PIN_15;
        if (ll_gpio_init(&gpio_cfg) != GPIO_INIT_SUCCESS)
        {
            return LL_SPI_ERROR_INVALID_PARAM;
        }
        break;

    default:
        return LL_SPI_ERROR_INVALID_PARAM;
    }

    return LL_SPI_OK;
}

static void ll_spi_write_dr8(uptr base_addr, u8 value)
{
    volatile u8* dr_addr = (volatile u8*)(base_addr + LL_SPI_DR_OFFSET);
    *dr_addr             = value;
}

static u8 ll_spi_read_dr8(uptr base_addr)
{
    volatile u8* dr_addr = (volatile u8*)(base_addr + LL_SPI_DR_OFFSET);
    return *dr_addr;
}
