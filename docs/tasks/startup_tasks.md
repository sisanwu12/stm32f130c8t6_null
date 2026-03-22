# STM32F103C8T6 Startup Tasks

这份清单用于拆解 `startup_stm32f103c8t6.c` 需要完成的工作，并标出每一项应参考的 ST 官方文档位置。

## 文档集合

- `PM0056 Rev 7` - STM32F10xxx/20xxx/21xxx/L1xxxx Cortex-M3 programming manual
  - 仓库内文件：`docs/lib/pm0056-stm32f10xxx-cortexm3-编程手册.pdf`
- `RM0008 Rev 21` - STM32F101xx/102xx/103xx/105xx/107xx Reference manual
  - 仓库内文件：`docs/lib/rm0008-stm32f103xx参考手册.pdf`
- `DS5319 Rev 20` - STM32F103x8 / STM32F103xB Datasheet
  - 这是 `STM32F103C8T6` 对应的官方 datasheet，当前仓库里没有，建议补充一份

## Tasks

- [ ] 1. 确认芯片具体归属与边界条件
  - 目标：确认 `STM32F103C8T6` 属于 `STM32F103x8`、`medium-density`，并明确这会影响内存大小、可用外设、中断向量表版本。
  - 完成标准：已经明确不能直接照抄 `connectivity line`、`XL-density` 或 `high-density` 的 startup 模板。
  - 依据文档：
    - `DS5319 Rev 20` Table 1 `Device summary`，第 1 页
    - `DS5319 Rev 20` `2.1 Device overview`，第 10 页
    - `DS5319 Rev 20` `2.3 Overview`，第 14-20 页

- [ ] 2. 确认启动时向量表的装载规则
  - 目标：弄清楚复位后 CPU 先从哪里取初始栈顶、从哪里取 `Reset_Handler`，以及后续是否需要重定位向量表。
  - 完成标准：知道 startup 文件里为什么第一项必须是栈顶地址、第二项必须是复位入口。
  - 依据文档：
    - `PM0056 Rev 7` `2.3.4 Vector table`，第 35 页
    - `PM0056 Rev 7` `4.4.4 Vector table offset register (SCB_VTOR)`，第 133 页
    - `RM0008 Rev 21` `4 Boot configuration`，第 60 页
    - `DS5319 Rev 20` `2.3.8 Boot modes`，第 15 页

- [ ] 3. 先写 linker script 与 startup 之间的符号契约
  - 目标：先定义 startup 需要使用的链接符号，再写 `Reset_Handler`。
  - 完成标准：链接脚本中已经定义这些符号：`_estack`、`_sidata`、`_sdata`、`_edata`、`_sbss`、`_ebss`。
  - 依据文档：
    - `DS5319 Rev 20` `4 Memory mapping`，第 34 页
    - `RM0008 Rev 21` `3 Memory and bus architecture`，第 47 页
    - `RM0008 Rev 21` `3.2 Memory organization`，第 49 页
    - `RM0008 Rev 21` `3.3 Memory map`，第 50 页
    - `PM0056 Rev 7` `2.1.2 Stacks`，第 13 页

- [ ] 4. 在 linker script 中给出正确的 FLASH/RAM 布局
  - 目标：把 `FLASH`、`RAM` 的起始地址和长度写对，并保证向量表固定在 Flash 起始区域。
  - 完成标准：链接脚本里已经有 `MEMORY`、`ENTRY(Reset_Handler)`、`KEEP(*(.isr_vector))`，且 `_estack = ORIGIN(RAM) + LENGTH(RAM)`。
  - 依据文档：
    - `DS5319 Rev 20` `2.3.1 Arm Cortex-M3 core with embedded flash and SRAM`，第 14 页
    - `DS5319 Rev 20` `2.3.2 Embedded flash memory`，第 14 页
    - `DS5319 Rev 20` `2.3.4 Embedded SRAM`，第 14 页
    - `DS5319 Rev 20` `4 Memory mapping`，第 34 页
    - `RM0008 Rev 21` `3.3 Memory map`，第 50 页

- [ ] 5. 写出异常向量表的核心部分
  - 目标：按 Cortex-M3 规定顺序写出 `Initial SP`、`Reset`、`NMI`、`HardFault`、`MemManage`、`BusFault`、`UsageFault`、`SVCall`、`PendSV`、`SysTick`。
  - 完成标准：核心异常顺序与保留槽位位置完全正确，不靠“感觉”填写。
  - 依据文档：
    - `PM0056 Rev 7` `2.3.3 Exception handlers`，第 34 页
    - `PM0056 Rev 7` `2.3.4 Vector table`，第 35 页
    - `PM0056 Rev 7` `2.3.7 Exception entry and return`，第 37 页

- [ ] 6. 写出 STM32F103C8T6 对应的外部 IRQ 部分
  - 目标：把 `WWDG` 到最后一个有效外部中断按正确顺序写入向量表。
  - 完成标准：使用的是 `STM32F103C8T6` 对应的 `medium-density` IRQ 集，而不是别的 F10x 子系列。
  - 依据文档：
    - `RM0008 Rev 21` `10.1.2 Interrupt and exception vectors`，第 198-206 页
    - `RM0008 Rev 21` `10.1 Nested vectored interrupt controller (NVIC)`，第 197 页
    - `DS5319 Rev 20` `2.1 Device overview`，第 10 页
    - `DS5319 Rev 20` `2.3 Overview`，第 14-20 页
  - 备注：`RM0008` 覆盖多个 F10x 变体，写向量表时必须结合 datasheet 排除并不存在的外设中断。

- [ ] 7. 为所有异常和中断准备默认处理函数
  - 目标：先给所有 handler 建立声明，并统一弱定义到 `Default_Handler`。
  - 完成标准：未实现的中断不会链接失败，后续只需覆盖自己需要的 IRQ handler。
  - 依据文档：
    - `PM0056 Rev 7` `2.3.2 Exception types`，第 32 页
    - `PM0056 Rev 7` `2.3.3 Exception handlers`，第 34 页
    - `RM0008 Rev 21` `10.1.2 Interrupt and exception vectors`，第 198-206 页

- [ ] 8. 实现 `Reset_Handler` 的运行时初始化
  - 目标：完成 `.data` 拷贝、`.bss` 清零、必要的早期初始化，然后进入 `main()`。
  - 完成标准：startup 里没有依赖尚未初始化好的全局变量，也没有在运行时未准备好之前调用不必要的库函数。
  - 依据文档：
    - `PM0056 Rev 7` `2.1.2 Stacks`，第 13 页
    - `PM0056 Rev 7` `2.3.7 Exception entry and return`，第 37 页
    - `RM0008 Rev 21` `3.3.1 Embedded SRAM`，第 53 页
    - `RM0008 Rev 21` `3.3.3 Embedded Flash memory`，第 54 页

- [ ] 9. 决定是否在 startup 中调用 `SystemInit()`
  - 目标：决定时钟树、PLL、HSE 启动、向量表重定位这些工作是放在 `SystemInit()` 还是先保持复位默认值，稍后在 `main()` 中处理。
  - 完成标准：已经明确“startup 最小职责”和“板级时钟初始化职责”的边界。
  - 依据文档：
    - `DS5319 Rev 20` `2.3.7 Clocks and startup`，第 15 页
    - `DS5319 Rev 20` `5.3.6 External clock source characteristics`，第 50 页
    - `RM0008 Rev 21` `7 Low-, medium-, high- and XL-density reset and clock control (RCC)`，第 90 页
    - `RM0008 Rev 21` `7.3.1 Clock control register (RCC_CR)`，第 99 页
    - `RM0008 Rev 21` `7.3.2 Clock configuration register (RCC_CFGR)`，第 101 页
    - `RM0008 Rev 21` `7.3.7 APB2 peripheral clock enable register (RCC_APB2ENR)`，第 112 页

- [ ] 10. 决定是否需要库初始化或 C++ 构造器支持
  - 目标：如果工程未来会使用 `static` 构造、`newlib` 初始化或 C++，则在 startup 中补充相应初始化；纯 C 裸机最小工程可以先不加。
  - 完成标准：已经明确这部分属于工具链职责，不是 STM32 芯片手册直接规定的内容。
  - 依据文档：
    - 这部分主要参考编译器/运行库文档，不属于 ST 芯片手册本体

- [ ] 11. 给默认异常路径留下可调试入口
  - 目标：至少保证 `Default_Handler` 和 `HardFault_Handler` 进入死循环，后续调试时可进一步扩展为读取 fault status 寄存器。
  - 完成标准：异常发生时程序不会静默跑飞，能够稳定停在可观察的位置。
  - 依据文档：
    - `PM0056 Rev 7` `2.4 Fault handling`，第 39 页
    - `PM0056 Rev 7` `2.4.3 Fault status registers and fault address registers`，第 41 页

- [ ] 12. 回头验证 startup 与链接结果
  - 目标：确认向量表确实放在镜像最前面，`Reset_Handler` 确实是入口，`.data/.bss` 相关符号位置正确。
  - 完成标准：查看 map/elf/objdump 后，启动链路与预期一致。
  - 依据文档：
    - `PM0056 Rev 7` `2.3.4 Vector table`，第 35 页
    - `PM0056 Rev 7` `4.4.4 Vector table offset register (SCB_VTOR)`，第 133 页
    - `RM0008 Rev 21` `3.3 Memory map`，第 50 页

## 建议执行顺序

1. 先完成 Task 1 到 Task 4，先把 linker script 和符号边界定死。
2. 再完成 Task 5 到 Task 8，写出最小可启动 startup。
3. 最后做 Task 9 到 Task 12，把时钟、调试、工具链初始化这些“可选但重要”的部分补齐。

## 一句话原则

startup 文件的最小职责只有四件事：`放向量表`、`建立栈`、`初始化 .data/.bss`、`跳到 main()`；其余内容都应该带着“是否真的属于启动阶段”的判断再加入。
