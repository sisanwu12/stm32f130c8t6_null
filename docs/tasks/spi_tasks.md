# STM32F103C8T6 SPI Tasks

这份清单记录 `Libraries/driver/ll/dri_ll_spi.h` 与 `Libraries/driver/ll/dri_ll_spi.c` 的第一版 SPI LL 实现结果、固定边界和验收标准。

## 当前实现范围

- 已实现文件：
  - `Libraries/driver/ll/dri_ll_spi.h`
  - `Libraries/driver/ll/dri_ll_spi.c`
- 对外符号统一采用 `ll_spi_*`
- SPI v1 固定支持：
  - `SPI1/SPI2`
  - 主机模式
  - 全双工
  - `8-bit`
  - 阻塞轮询
  - 默认 `SCK/MISO/MOSI`
  - 轮询超时返回
- SPI v1 明确不支持：
  - RCC 开时钟
  - `CS/NSS` 管理
  - `AFIO remap`
  - 中断、DMA、CRC
  - 从机模式
  - `16-bit` 帧格式

## 固定接口

### 对外类型

- [x] `ll_spi_instance_t`
- [x] `ll_spi_mode_t`
- [x] `ll_spi_baud_prescaler_t`
- [x] `ll_spi_first_bit_t`
- [x] `ll_spi_status_t`
- [x] `ll_spi_init_t`

### 对外函数

- [x] `ll_spi_init()`
- [x] `ll_spi_wait_flag_set()`
- [x] `ll_spi_wait_flag_clear()`
- [x] `ll_spi_transfer_byte()`
- [x] `ll_spi_write_byte()`
- [x] `ll_spi_read_byte()`
- [x] `ll_spi_transfer_buffer()`
- [x] `ll_spi_write_buffer()`
- [x] `ll_spi_read_buffer()`

## 固定行为

- [x] `read_*` 接口固定发送 dummy `0xFF`
- [x] `write_*` 接口通过全双工路径读回接收数据
- [x] `completed_len` 允许为 `NULL`
- [x] `completed_len` 非空时，入口先清零
- [x] 每成功完成 `1` 字节，`completed_len` 递增 `1`
- [x] 中途超时保留已经完成的进度
- [x] `timeout_count == 0` 立即返回 `LL_SPI_ERROR_TIMEOUT`
- [x] `ll_spi_init()` 不负责打开任何 RCC 时钟

## 默认引脚与前置条件

- [x] `LL_SPI_1`：`PA5=SCK`、`PA6=MISO`、`PA7=MOSI`
- [x] `LL_SPI_2`：`PB13=SCK`、`PB14=MISO`、`PB15=MOSI`
- [x] `SCK/MOSI` 固定为 `LL_GPIO_MODE_OUTPUT_50 + LL_GPIO_CNF_OUTPUT_AF_PP`
- [x] `MISO` 固定为 `LL_GPIO_MODE_INPUT + LL_GPIO_CNF_INPUT_FLOAT`
- [x] 不配置 `NSS/CS`
- [x] 外部必须先打开对应 SPI 和 GPIO 时钟

## 验收清单

- [x] 头文件补齐 `SPI1/SPI2` 基地址、寄存器偏移、`CR1/SR/I2SCFGR` v1 所需位定义
- [x] 源文件补齐实例校验、实例到基地址映射、默认 GPIO 配置和 `DR` 的 8-bit 专用访问
- [x] `ll_spi_init()` 固定流程为：校验参数、关闭 `SPE`、关闭 `I2S`、配置 GPIO、写 `CR1`、打开 `SPE`
- [x] `ll_spi_transfer_byte()` 固定流程为：等 `TXE`、写 `DR`、等 `RXNE`、读 `DR`、等 `BSY` 清零
- [x] 缓冲区接口逐字节复用单字节接口
- [x] 参数边界覆盖 `cfg == NULL`、非法实例、非法枚举、空缓冲区、`len == 0`、`timeout_count == 0`
- [x] 独立接口说明书已补齐：`docs/spi接口说明书.md`

## 文档与验证

- [x] 接口说明书：`docs/spi接口说明书.md`
- [x] task 文档已与最终代码命名一致，不再使用 `dri_ll_spi_*`
- [x] Nix 下全量构建验证
  - 说明：已按仓库约定走 `./.vscode/nix-cmake`
  - 结果：`null_proj.elf` 成功生成

## 一句话原则

SPI 模块第一版只负责“把 SPI 外设和默认 `SCK/MISO/MOSI` 稳定驱动起来”，不负责 `CS` 管理，不负责设备协议，也不提前为第二版扩展复杂配置。
