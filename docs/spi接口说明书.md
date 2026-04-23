# STM32F103C8T6 SPI 接口说明书

这份文档说明 `Libraries/driver/ll/dri_ll_spi.h` 与 `Libraries/driver/ll/dri_ll_spi.c` 的第一版对外接口、固定边界和使用方式。

## 模块边界

- SPI v1 负责：
  - `SPI1/SPI2` 主机模式初始化
  - 默认 `SCK/MISO/MOSI` 引脚配置
  - 阻塞轮询等待状态位
  - 单字节收发
  - 缓冲区收发
  - 超时返回
- SPI v1 不负责：
  - RCC 开时钟
  - `CS/NSS` 拉高拉低
  - 从设备寄存器协议
  - 多从设备仲裁
  - `AFIO remap`
  - 中断、DMA、CRC
  - 从机模式
  - `16-bit` 帧格式

## 调用前置条件

- `SPI1` 使用前，外部必须先打开 `SPI1 + GPIOA` 时钟。
- `SPI2` 使用前，外部必须先打开 `SPI2 + GPIOB` 时钟。
- `ll_spi_init()` 不会打开任何 RCC 时钟。
- 本版 SPI 固定为主机、全双工、`8-bit`、`SSM=1`、`SSI=1`、`CRCEN=0`、`DFF=0`、`BIDIMODE=0`、`RXONLY=0`。

## 默认引脚

| SPI 实例 | SCK  | MISO | MOSI |
| --- | --- | --- | --- |
| `LL_SPI_1` | `PA5` | `PA6` | `PA7` |
| `LL_SPI_2` | `PB13` | `PB14` | `PB15` |

固定 GPIO 配置：

- `SCK/MOSI`：`LL_GPIO_MODE_OUTPUT_50 + LL_GPIO_CNF_OUTPUT_AF_PP`
- `MISO`：`LL_GPIO_MODE_INPUT + LL_GPIO_CNF_INPUT_FLOAT`
- 不配置 `NSS/CS`

## 初始化参数

### `ll_spi_instance_t`

- `LL_SPI_1`
- `LL_SPI_2`

### `ll_spi_mode_t`

- `LL_SPI_MODE_0`：`CPOL=0`、`CPHA=0`
- `LL_SPI_MODE_1`：`CPOL=0`、`CPHA=1`
- `LL_SPI_MODE_2`：`CPOL=1`、`CPHA=0`
- `LL_SPI_MODE_3`：`CPOL=1`、`CPHA=1`

### `ll_spi_baud_prescaler_t`

- `LL_SPI_BAUD_PRESCALER_DIV2`
- `LL_SPI_BAUD_PRESCALER_DIV4`
- `LL_SPI_BAUD_PRESCALER_DIV8`
- `LL_SPI_BAUD_PRESCALER_DIV16`
- `LL_SPI_BAUD_PRESCALER_DIV32`
- `LL_SPI_BAUD_PRESCALER_DIV64`
- `LL_SPI_BAUD_PRESCALER_DIV128`
- `LL_SPI_BAUD_PRESCALER_DIV256`

### `ll_spi_first_bit_t`

- `LL_SPI_FIRST_BIT_MSB`
- `LL_SPI_FIRST_BIT_LSB`

### `ll_spi_status_t`

- `LL_SPI_OK`
- `LL_SPI_ERROR_INVALID_PARAM`
- `LL_SPI_ERROR_TIMEOUT`

## 接口列表

### `ll_spi_status_t ll_spi_init(const ll_spi_init_t* cfg);`

- 作用：初始化 SPI 外设，并配置默认 GPIO。
- 返回值：
  - `LL_SPI_OK`：初始化成功
  - `LL_SPI_ERROR_INVALID_PARAM`：`cfg == NULL` 或实例/枚举参数非法

### `ll_spi_status_t ll_spi_wait_flag_set(ll_spi_instance_t instance, u32 flag_mask, u32 timeout_count);`

- 作用：等待 `SR` 中指定状态位被置位。
- 返回值：
  - `LL_SPI_OK`：等待成功
  - `LL_SPI_ERROR_INVALID_PARAM`：实例非法或 `flag_mask == 0`
  - `LL_SPI_ERROR_TIMEOUT`：超时

### `ll_spi_status_t ll_spi_wait_flag_clear(ll_spi_instance_t instance, u32 flag_mask, u32 timeout_count);`

- 作用：等待 `SR` 中指定状态位清零。
- 返回值与 `ll_spi_wait_flag_set()` 一致。

### `ll_spi_status_t ll_spi_transfer_byte(ll_spi_instance_t instance, u8 tx_byte, u8* rx_byte, u32 timeout_count);`

- 作用：执行一次 1-byte 全双工传输。
- 固定流程：
  - 等 `TXE`
  - 写 `DR`
  - 等 `RXNE`
  - 读 `DR`
  - 等 `BSY` 清零
- 返回值：
  - `LL_SPI_OK`
  - `LL_SPI_ERROR_INVALID_PARAM`：实例非法或 `rx_byte == NULL`
  - `LL_SPI_ERROR_TIMEOUT`

### `ll_spi_status_t ll_spi_write_byte(ll_spi_instance_t instance, u8 tx_byte, u32 timeout_count);`

- 作用：发送 1 字节。
- 固定行为：内部复用 `ll_spi_transfer_byte()`，并丢弃回读值。
- 返回值同上。

### `ll_spi_status_t ll_spi_read_byte(ll_spi_instance_t instance, u8* rx_byte, u32 timeout_count);`

- 作用：读取 1 字节。
- 固定行为：内部发送 dummy `0xFF` 产生时钟。
- 返回值同上。

### `ll_spi_status_t ll_spi_transfer_buffer(ll_spi_instance_t instance, const u8* tx_buf, u8* rx_buf, u32 len, u32* completed_len, u32 timeout_count);`

- 作用：执行多字节全双工传输。
- 参数约束：
  - `len > 0` 时，`tx_buf` 和 `rx_buf` 都必须非空
  - `completed_len` 可为 `NULL`
- 返回值：
  - `LL_SPI_OK`
  - `LL_SPI_ERROR_INVALID_PARAM`
  - `LL_SPI_ERROR_TIMEOUT`

### `ll_spi_status_t ll_spi_write_buffer(ll_spi_instance_t instance, const u8* tx_buf, u32 len, u32* completed_len, u32 timeout_count);`

- 作用：连续发送多字节。
- 固定行为：逐字节复用 `ll_spi_write_byte()`。

### `ll_spi_status_t ll_spi_read_buffer(ll_spi_instance_t instance, u8* rx_buf, u32 len, u32* completed_len, u32 timeout_count);`

- 作用：连续读取多字节。
- 固定行为：逐字节复用 `ll_spi_read_byte()`，每字节发送 dummy `0xFF`。

## 超时与 `completed_len` 规则

- 所有等待逻辑都使用递减计数的轮询超时。
- `timeout_count == 0` 立即返回 `LL_SPI_ERROR_TIMEOUT`。
- `completed_len` 允许为 `NULL`。
- `completed_len` 非空时，接口入口先清零。
- 缓冲区接口每成功完成 1 字节，`completed_len` 增加 1。
- 中途超时时，保留已经完成的字节数。
- `len == 0` 时，缓冲区接口直接返回 `LL_SPI_OK`，并保持 `completed_len == 0`。

## 最小使用示例

### `SPI1`

```c
#include "dri_ll_rcc.h"
#include "dri_ll_spi.h"

void spi1_example(void)
{
    ll_spi_init_t spi_cfg = {
        .instance        = LL_SPI_1,
        .mode            = LL_SPI_MODE_0,
        .baud_prescaler  = LL_SPI_BAUD_PRESCALER_DIV8,
        .first_bit       = LL_SPI_FIRST_BIT_MSB,
    };

    ll_rcc_apb2_enable(LL_RCC_APB2_GPIOA_MASK | LL_RCC_APB2_SPI1_MASK);

    ll_spi_init(&spi_cfg);

    /* 这里手动拉低 CS */
    ll_spi_write_byte(LL_SPI_1, 0x9FU, 100000U);
    /* 这里继续收发数据 */
    /* 这里手动拉高 CS */
}
```

### `SPI2`

```c
#include "dri_ll_rcc.h"
#include "dri_ll_spi.h"

void spi2_example(void)
{
    u8 rx_data[2];

    ll_spi_init_t spi_cfg = {
        .instance        = LL_SPI_2,
        .mode            = LL_SPI_MODE_3,
        .baud_prescaler  = LL_SPI_BAUD_PRESCALER_DIV16,
        .first_bit       = LL_SPI_FIRST_BIT_MSB,
    };

    ll_rcc_apb2_enable(LL_RCC_APB2_GPIOB_MASK);
    ll_rcc_apb1_enable(LL_RCC_APB1_SPI2_MASK);

    ll_spi_init(&spi_cfg);

    /* 这里手动拉低 CS */
    ll_spi_read_buffer(LL_SPI_2, rx_data, 2U, NULL, 100000U);
    /* 这里手动拉高 CS */
}
```
