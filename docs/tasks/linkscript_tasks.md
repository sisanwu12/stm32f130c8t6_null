# STM32F103C8T6 Linker Script Tasks

这份清单用于拆解 `stm32f103c8t6.ld` 需要完成的工作，并标出每一项应参考的 ST 官方文档与 GNU ld 资料。

## 当前项目状态

- `startup_stm32f103c8t6.c` 已经完成了最小启动路径：放置向量表、进入 `Reset_Handler`、复制 `.data`、清零 `.bss`、跳转到 `main()`。
- 当前 startup 已经对链接脚本提出了明确的符号契约，至少需要这些符号：
  - `_estack`
  - `_sidata`
  - `_sdata`
  - `_edata`
  - `_sbss`
  - `_ebss`
- 当前 startup 还声明了 `_etext`，但现阶段没有实际使用。它可以保留为兼容符号，但不是最小启动必需项。
- 当前 `startup_stm32f103c8t6.c` 将中断向量表放在 `.isr_vector` 段，所以链接脚本必须显式把 `.isr_vector` 固定到 Flash 起始区域。
- 当前仓库中的 `stm32f103c8t6.ld` 还是空文件，因此链接脚本的第一版目标不是“做复杂功能”，而是先把最小启动链路闭合。

## 链接脚本到底负责什么

链接脚本本身不执行任何启动动作。它负责的是三件事：

1. 描述内存布局：Flash 从哪里开始、RAM 从哪里开始、各自有多大。
2. 决定各个输出段放在哪里：`.isr_vector`、`.text`、`.rodata`、`.data`、`.bss`。
3. 导出启动代码要用到的边界符号：例如 `.data` 的加载地址和运行地址、`.bss` 的起止地址、栈顶地址。

运行时的“复制 `.data`”和“清零 `.bss`”不是链接脚本做的，而是 `Reset_Handler` 根据链接脚本给出的符号去做的。

## 一个最小可用链接脚本需要实现的功能

- 用 `ENTRY(Reset_Handler)` 标出 ELF 入口，便于调试器和 ELF 工具理解程序入口。
- 用 `MEMORY` 明确官方容量：
  - `FLASH` 起始地址 `0x08000000`，长度 `64K`
  - `RAM` 起始地址 `0x20000000`，长度 `20K`
- 导出 `_estack = ORIGIN(RAM) + LENGTH(RAM)`，供向量表第一项作为初始 MSP 使用。
- 把 `.isr_vector` 放到 Flash 最开始，并用 `KEEP(*(.isr_vector))` 防止 `--gc-sections` 时被错误回收。
- 把 `.text`、`.rodata` 这类只读执行内容放进 Flash。
- 把 `.data` 的运行地址放进 RAM，但把其初始值镜像保存在 Flash 中，并导出 `_sidata`、`_sdata`、`_edata`。
- 把 `.bss` 放进 RAM，标记为 `NOLOAD`，并导出 `_sbss`、`_ebss`。
- 视后续是否接入 `newlib` / C++，决定是否加入 `.preinit_array`、`.init_array`、`.fini_array`、`.ARM.exidx`、`.ARM.extab`。
- 视后续是否需要 `malloc` / 固定堆栈预留，决定是否额外导出 `_end`、`end`、`__heap_start`、`__heap_end`，或增加大小断言。

## 推荐的最小骨架

下面这个骨架已经能满足当前 `startup_stm32f103c8t6.c` 的最小需求：

```ld
ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.glue_7) *(.glue_7t)
    . = ALIGN(4);
    _etext = .;
  } > FLASH

  .ARM.exidx :
  {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx* .ARM.extab*)
    __exidx_end = .;
    . = ALIGN(4);
  } > FLASH

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data .data.*)
    . = ALIGN(4);
    _edata = .;
  } > RAM AT > FLASH

  _sidata = LOADADDR(.data);

  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  . = ALIGN(8);
  _end = .;
  end = .;
}
```

## 这个骨架为什么这样写

- `ENTRY(Reset_Handler)` 只是在 ELF 元数据里声明入口，真正上电复位时，Cortex-M3 仍然是从向量表读取初始栈顶和 `Reset_Handler`。
- `.isr_vector` 必须在 Flash 起始区域，因为在 `BOOT0=0` 的常规启动模式下，主 Flash 会别名到 `0x00000000`，CPU 复位后会先从 `0x00000000` 取初始 MSP，再从 `0x00000004` 取复位入口。
- `.data > RAM AT > FLASH` 的意思是：
  - 运行时地址在 RAM
  - 初始值镜像存放在 Flash
  - `Reset_Handler` 启动时把 `LOADADDR(.data)` 指向的内容拷贝到 `_sdata ... _edata`
- `.bss (NOLOAD)` 表示该段只需要在 RAM 中保留空间，不需要在 Flash 镜像中占用初始化内容。
- `*(COMMON)` 是对旧式公共未初始化符号的兼容处理，虽然现代 GCC 默认为 `-fno-common`，保留它依然是稳妥做法。
- `.ARM.exidx` / `.ARM.extab` 对当前纯 C 最小模板不是硬要求，但加入后对后续异常回溯、某些工具链默认段兼容性更友好。
- 现阶段不一定要显式创建 `.stack` 段。对于最小裸机模板，只要 `_estack` 正确指向 RAM 顶部，MSP 就能正常工作。是否额外“切出一段固定栈空间”，取决于你后续是否需要堆、RTOS、或严格的 RAM 断言。

## 文档集合

- `DS5319 Rev 20` - STM32F103x8 / STM32F103xB Datasheet
  - 仓库内文件：`docs/lib/ds5319-stm32f103c8-datasheet.pdf`
- `RM0008 Rev 21` - STM32F101xx/102xx/103xx/105xx/107xx Reference manual
  - 仓库内文件：`docs/lib/rm0008-stm32f103xx参考手册.pdf`
- `PM0056 Rev 7` - STM32F10xxx Cortex-M3 programming manual
  - 仓库内文件：`docs/lib/pm0056-stm32f10xxx-cortexm3-编程手册.pdf`
- GNU ld / `arm-none-eabi-ld` 链接脚本语法资料
  - 重点关注：`ENTRY`、`MEMORY`、`SECTIONS`、`AT`、`LOADADDR()`、`ALIGN()`、`KEEP()`、`PROVIDE()`
  - 本地工具链可用 `arm-none-eabi-ld --verbose` 观察默认脚本和常见输出段命名
  - 注意：默认脚本里的地址布局不是 MCU 专用布局，只能拿来参考段名和语法，不能直接照搬到 STM32F103C8T6

## Tasks

- [ ] 1. 确认芯片型号、容量和密度级别
  - 目标：确认 `STM32F103C8T6` 属于 `STM32F103x8`、`medium-density`，模板第一版必须按官方 `64 KB Flash + 20 KB SRAM` 编写，而不是按常见“C8 实际带 128 KB”的板卡经验写。
  - 完成标准：`MEMORY` 中 `FLASH` 长度采用官方 64K，`RAM` 长度采用 20K；如果后续确实要兼容带 128K 的克隆板，另起一个脚本或单独做配置开关。
  - 依据文档：
    - `DS5319 Rev 20` Table 1 `Device summary`，第 1 页
    - `DS5319 Rev 20` `2.3.2 Embedded flash memory`，第 14 页
    - `DS5319 Rev 20` `2.3.4 Embedded SRAM`，第 14 页

- [ ] 2. 确认复位取址和 Boot alias 规则
  - 目标：弄清楚为什么向量表虽然最终烧录在 `0x08000000`，但 CPU 复位时仍然会从 `0x00000000` 和 `0x00000004` 取栈顶和入口。
  - 完成标准：明确“主 Flash 在启动时会别名到 boot memory space”，因此第一版应用把向量表放在 Flash 起始处即可，不需要在 startup 里额外重定位。
  - 依据文档：
    - `RM0008 Rev 21` `3.4 Boot configuration`，第 60 页
    - `RM0008 Rev 21` Table 9 `Boot modes`，第 60 页
    - `PM0056 Rev 7` `2.3.4 Vector table`，第 35 页

- [ ] 3. 先定义 startup 与 linker script 的符号契约
  - 目标：优先围绕现有 `startup_stm32f103c8t6.c` 写脚本，而不是先抄一份“大而全”的通用脚本。
  - 完成标准：第一版脚本至少导出 `_estack`、`_sidata`、`_sdata`、`_edata`、`_sbss`、`_ebss`；并明确 `_etext` 目前只是兼容符号。
  - 依据文档：
    - 当前仓库内的 `startup_stm32f103c8t6.c`
    - `PM0056 Rev 7` `2.1.2 Stacks`，第 13 页
    - `DS5319 Rev 20` `4 Memory mapping`，第 34 页

- [ ] 4. 写出 `ENTRY` 和 `MEMORY`
  - 目标：先把入口符号和物理内存边界定死。
  - 完成标准：脚本中已经具备 `ENTRY(Reset_Handler)` 与 `MEMORY { FLASH ... RAM ... }`；并理解 `ENTRY` 主要影响 ELF 工具，而不改变硬件复位机制。
  - 依据文档：
    - `DS5319 Rev 20` `4 Memory mapping`，第 34 页
    - `RM0008 Rev 21` `3.2 Memory organization`，第 49 页
    - GNU ld 语法：`ENTRY`、`MEMORY`

- [ ] 5. 固定 `.isr_vector` 的位置并防止被垃圾回收
  - 目标：让 `.isr_vector` 成为镜像的第一个有效输出段。
  - 完成标准：脚本中使用 `KEEP(*(.isr_vector))` 并将该段映射到 `> FLASH`；如果后续开启 `-ffunction-sections -fdata-sections -Wl,--gc-sections`，向量表仍不会被链接器丢弃。
  - 依据文档：
    - `PM0056 Rev 7` `2.3.4 Vector table`，第 35 页
    - `RM0008 Rev 21` `3.4 Boot configuration`，第 60 页
    - GNU ld 语法：`KEEP`

- [ ] 6. 放置 `.text`、`.rodata` 和工具链常见只读段
  - 目标：把代码和常量全部放到 Flash，并兼容 `*.text.*`、`*.rodata.*` 这类细分段。
  - 完成标准：脚本中 `.text` 段收拢 `*(.text .text.*)`、`*(.rodata .rodata.*)`；必要时兼容 `.glue_7`、`.glue_7t`、`.ARM.exidx`、`.ARM.extab`。
  - 依据文档：
    - `DS5319 Rev 20` `2.3.2 Embedded flash memory`，第 14 页
    - GNU ld 语法：`SECTIONS`
    - 本地观察：`arm-none-eabi-ld --verbose`

- [ ] 7. 处理 `.data` 的加载地址和运行地址分离
  - 目标：清楚地区分 LMA 和 VMA，让 `.data` 在 RAM 运行、在 Flash 存初值。
  - 完成标准：脚本中使用 `.data > RAM AT > FLASH`，并通过 `LOADADDR(.data)` 导出 `_sidata`；`Reset_Handler` 能据此正确完成拷贝。
  - 依据文档：
    - `DS5319 Rev 20` `4 Memory mapping`，第 34 页
    - `RM0008 Rev 21` `3.3 Memory map`，第 50 页
    - GNU ld 语法：`AT`、`LOADADDR()`

- [ ] 8. 处理 `.bss` 和未初始化数据
  - 目标：让所有未初始化的静态存储期对象只占用 RAM，不占用 Flash 镜像空间。
  - 完成标准：脚本中使用 `.bss (NOLOAD)`，并导出 `_sbss`、`_ebss`；同时包含 `*(COMMON)` 兼容旧式未初始化公共符号。
  - 依据文档：
    - `DS5319 Rev 20` `2.3.4 Embedded SRAM`，第 14 页
    - `RM0008 Rev 21` `3.3.1 Embedded SRAM`，第 53 页
    - GNU ld 语法：`NOLOAD`

- [ ] 9. 正确给出栈顶，并决定是否显式保留 heap/stack 空间
  - 目标：先保证 MSP 初值正确，再决定是否要在脚本里人为切出固定 heap/stack 区域。
  - 完成标准：第一版最小脚本至少有 `_estack = ORIGIN(RAM) + LENGTH(RAM)`；如果后续引入 `malloc`、RTOS 或更严格的 RAM 使用控制，再追加 `_Min_Heap_Size`、`_Min_Stack_Size`、`ASSERT`。
  - 依据文档：
    - `PM0056 Rev 7` `2.1.2 Stacks`，第 13 页
    - `PM0056 Rev 7` `2.3.4 Vector table`，第 35 页
    - GNU ld 语法：`ASSERT`

- [ ] 10. 决定是否加入 C/C++ 运行库相关段
  - 目标：明确哪些内容属于“当前纯 C 最小模板必须项”，哪些是“未来接入运行库后再加”。
  - 完成标准：当前纯 C 版本可以先不放 `.preinit_array`、`.init_array`、`.fini_array`；如果未来在 `Reset_Handler` 中调用 `__libc_init_array()` 或引入 C++，再把这些段和边界符号补齐。
  - 依据文档：
    - 这部分主要依据 GNU 工具链与运行库文档，不属于 ST 芯片手册直接规定的内容
    - 本地观察：`arm-none-eabi-ld --verbose`

- [ ] 11. 决定是否预留 Flash 子区域
  - 目标：判断当前工程是否只是“整片 Flash 都给应用”，还是需要预留 bootloader、参数区、CRC 签名区。
  - 完成标准：如果当前只是最小裸应用，`FLASH` 可直接从 `0x08000000` 起整片使用；如果未来预留应用起始地址，新的向量表基址仍需满足 VTOR 对齐要求，不能随便选一个非对齐偏移。
  - 依据文档：
    - `RM0008 Rev 21` Table 5 `Flash module organization (medium-density devices)`，第 54 页
    - `PM0056 Rev 7` `4.4.4 Vector table offset register (SCB_VTOR)`，第 133 页

- [ ] 12. 为脚本加上基本的健壮性和验证手段
  - 目标：不仅让它“能链接”，还要让它在溢出或布局错误时尽早报错。
  - 完成标准：后续版本中至少考虑加入 RAM/Flash 越界断言，并通过 `map/elf/objdump/readelf/nm` 验证输出布局与符号位置。
  - 依据文档：
    - GNU ld 语法：`ASSERT`
    - `PM0056 Rev 7` `2.3.4 Vector table`，第 35 页
    - `RM0008 Rev 21` `3.4 Boot configuration`，第 60 页

## 推荐验证项

当前仓库还没有完整构建系统；等 `elf` 能生成后，至少做下面几项检查：

```sh
arm-none-eabi-readelf -S build/firmware.elf
arm-none-eabi-objdump -h -t build/firmware.elf
arm-none-eabi-nm -n build/firmware.elf | rg '_estack|_sidata|_sdata|_edata|_sbss|_ebss|Reset_Handler'
arm-none-eabi-objdump -s -j .isr_vector build/firmware.elf
```

验证时要重点看：

- `.isr_vector` 是否是 Flash 里的第一个输出段。
- 向量表第一项是否等于 RAM 顶部地址。
- `.data` 的 VMA 是否在 RAM，LMA 是否在 Flash。
- `.bss` 是否只占 RAM，不占 Flash 镜像空间。
- `Reset_Handler` 是否能在符号表中找到，并且作为入口存在。

## 建议执行顺序

1. 先完成 Task 1 到 Task 4，把芯片边界、启动别名规则、入口和内存区域定死。
2. 再完成 Task 5 到 Task 8，把最小可启动脚本写出来，让现有 startup 有符号可用。
3. 然后完成 Task 9 到 Task 12，按工程演进决定是否加入 heap/stack 预留、运行库段、Flash 子区域和断言。

## 一句话原则

对这个项目当前阶段来说，链接脚本的最小职责不是“把所有 GNU ld 特性都堆上去”，而是准确完成三件事：`放对段`、`导出对符号`、`把 startup 需要的地址边界说明白`。
