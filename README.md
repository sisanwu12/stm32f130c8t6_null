# STM32F103C8T6 从零裸机工程

这是一个围绕 `STM32F103C8T6` 搭建的从零裸机工程，主线不是依赖 HAL / StdPeriph 这类现成库，而是自己把启动链路、链接脚本、`SystemInit()`、寄存器级 LL 封装和静态对象 RTOS 一步步搭起来。仓库当前更接近“持续收敛中的实验/学习型工程”，首页重点提供项目总览、进入方式和文档导航。

## 项目目标与设计原则

- 以 `STM32F103C8T6 / Cortex-M3` 为目标平台，梳理一条可读、可验证的裸机工程路径。
- 不把现成 BSP/HAL 当作主线抽象，优先直接面对启动流程、内存布局、时钟树与寄存器语义。
- 驱动层采用分层思路：
  - `dri_xxx` 面向更直接可用的功能接口
  - `dri_ll_xxx` 面向单外设、低层、稳定的寄存器语义封装
  - `dri_ll.h` 只保留通用寄存器访问原语
- RTOS 采用静态对象模型，不依赖 heap，强调 public API 与内部对象布局分离。
- 文档不是附属品，`docs/` 中的设计说明和任务拆解与代码实现并行推进。

## 当前已落地内容

按当前仓库可直接核实的状态，这个工程已经具备以下基础能力：

- 启动链路已经成形：
  - 自定义 startup 文件、异常/中断向量表、`Reset_Handler`
  - `STM32F103C8T6` 对应的链接脚本
  - `SystemInit()` 与 `72MHz` 时钟切换路径
- 已有若干寄存器级 LL 基础设施，至少包括 `FLASH`、`RCC`、`GPIO` 等模块。
- RTOS 已提供稳定入口 [`RTOS/include/os.h`](RTOS/include/os.h)，并对外暴露 `kernel / task / sem / mutex / queue / timer / diag` 公共接口。
- [`user/main.c`](user/main.c) 中已经放入基于 `RTOS_REGRESSION_CASE` 的板上 smoke / regression 入口，用于当前阶段的最小回归验证。

## 当前状态与已知问题

- 仓库已经提供一套相对完整的开发工作流：`Nix + CMake + VS Code + OpenOCD`。
- 但当前主线代码仍在命名收敛中。按仓库自带脚本构建时，[`user/main.c`](user/main.c) 仍在使用旧的 `dri_ll_*` 命名，而现有头文件已经使用 `ll_*` 命名，因此当前构建不会直接通过。
- `docs/tasks/*.md` 更适合理解“应该怎么实现”和“下一步怎么推进”，不应直接理解为“这些特性都已经完成”。

## 仓库结构

- [`project/`](project/)：CMake 工程入口、交叉编译工具链配置。
- [`Libraries/`](Libraries/)：启动文件、系统初始化、链接脚本、驱动实现。
- [`RTOS/`](RTOS/)：内核、对象实现、端口层与 public headers。
- [`user/`](user/)：应用入口与当前阶段的板上回归/冒烟测试代码。
- [`docs/`](docs/)：设计说明、专题任务拆解、参考资料与示意图。
- [`CMSIS/`](CMSIS/)：Cortex-M3 Core 与 STM32F1 设备头文件。

## 快速开始

### 推荐路径：VS Code

仓库已经在 [`.vscode/`](.vscode/) 中准备了常用任务与调试配置，推荐直接使用：

- `CMake Build`
- `Flash`
- `Debug with OpenOCD`

这些任务会通过仓库内的包装脚本自动进入 `nix develop` 环境，再调用 `cmake`、`arm-none-eabi-gdb` 和 `openocd`。

### CLI 路径

如果你更习惯命令行，可以直接复用仓库里的包装脚本，而不是假定宿主机已经全局安装完整工具链：

```bash
nix develop
./.vscode/nix-cmake --fresh -S project -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=project/arm-gnu-none-eabi.cmake
./.vscode/nix-cmake --build build --target all
./.vscode/nix-openocd -f interface/cmsis-dap.cfg -f target/stm32f1x.cfg -c "program build/null_proj.elf verify reset exit"
```

说明：

- `nix develop` 会进入仓库定义的开发环境，提供 `cmake`、`ninja`、`gcc-arm-embedded`、`openocd` 等工具。
- `build` 目录用于 CMake/Ninja 构建输出。
- 当前仓库仍有命名收敛问题，因此构建流程本身已经接好，但主线代码并不保证一次通过。

## 文档阅读顺序

如果你是第一次阅读这个仓库，建议按下面的顺序进入：

1. [`docs/库设计.md`](docs/%E5%BA%93%E8%AE%BE%E8%AE%A1.md)
   先理解整个工程里驱动分层、职责边界和后续落地建议。
2. [`docs/tasks/startup_tasks.md`](docs/tasks/startup_tasks.md)
   看 startup 文件应该承担哪些最小职责。
3. [`docs/tasks/linkscript_tasks.md`](docs/tasks/linkscript_tasks.md)
   看链接脚本如何与 startup 配合，闭合最小启动路径。
4. [`docs/tasks/systeminit_clock_tasks.md`](docs/tasks/systeminit_clock_tasks.md)
   看 `SystemInit()`、`72MHz` 时钟树和初始化顺序。
5. [`docs/tasks/rcc_tasks.md`](docs/tasks/rcc_tasks.md)
   看 RCC 低层封装的实现范围与拆解方法。
6. [`docs/tasks/flash_tasks.md`](docs/tasks/flash_tasks.md)
   看 `FLASH_ACR` 与升频前等待周期配置的设计依据。
7. [`docs/tasks/spi_tasks.md`](docs/tasks/spi_tasks.md)
   看 SPI v1 的职责边界和接口收敛方式。
8. [`RTOS/README.md`](RTOS/README.md)
   最后再进入 RTOS 的 public API、调用约束和对象模型。

这里特别说明：

- [`docs/库设计.md`](docs/%E5%BA%93%E8%AE%BE%E8%AE%A1.md) 是分层设计说明。
- [`docs/tasks/`](docs/tasks/) 下的文档是专题任务拆解与实现思路，不等同于“已完成清单”。
- [`RTOS/README.md`](RTOS/README.md) 是当前阶段 RTOS 稳定 public API 的主说明文档。

## RTOS 概览

- 应用层通常只需要 `#include "os.h"`。
- 当前对外 public API 已覆盖：
  - `os_kernel`
  - `os_task`
  - `os_sem`
  - `os_mutex`
  - `os_queue`
  - `os_timer`
  - `os_diag`
- 当前 RTOS 采用静态对象模型：
  - 任务对象由调用方提供
  - 任务栈由调用方提供
  - 队列缓冲区由调用方提供
  - 不依赖动态分配
- 线程态 / ISR 调用约束、兼容 API、对象布局边界，以 [`RTOS/README.md`](RTOS/README.md) 为准。

## 参考资料说明

- [`docs/lib/`](docs/lib/)：收录 ST 官方手册、datasheet、参考资料 PDF。
- [`docs/示意图/`](docs/%E7%A4%BA%E6%84%8F%E5%9B%BE/)：放置辅助理解的图示文件。

如果你想快速知道“这是什么项目、现在做到哪里、该先看什么”，根目录这份 README 就是入口；如果你想继续下钻实现细节，请直接进入 `docs/` 和 [`RTOS/README.md`](RTOS/README.md)。
