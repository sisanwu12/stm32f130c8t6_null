/**
 * @file dri_ll_tim.h
 * @author sisanwu12 (sisanwu12@outlook.com)
 * @brief TIM 底层寄存器接口
 * @version 0.1
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef __DRI_LL_TIM_H__
#define __DRI_LL_TIM_H__

#include "data_type.h"

/* ========== 数据定义 ==========*/

/* ---------- TIM 地址定义层 ---------- */

/* 通用定时器 基地址 */
#define LL_TIM2_BASE_ADDR 0x40000000UL // 定时器2 基地址
#define LL_TIM3_BASE_ADDR 0x40000400UL // 定时器3 基地址
#define LL_TIM4_BASE_ADDR 0x40000800UL // 定时器4 基地址
/* 高级定时器 基地址*/
#define LL_TIM1_BASE_ADDR 0x40012C00UL // 定时器1 基地址

/* ---------- TIM 寄存器定义层 ---------- */
/* TIM 寄存器偏移地址 */
#define LL_TIM_CR1_OFFSET   0x00UL // 控制寄存器 1
#define LL_TIM_CR2_OFFSET   0x04UL // 控制寄存器 2
#define LL_TIM_SMCR_OFFSET  0x08UL // 从模式控制寄存器
#define LL_TIM_DIER_OFFSET  0x0CUL // DMA/终端使能寄存器
#define LL_TIM_SR_OFFSET    0x10UL // 状态寄存器
#define LL_TIM_EGR_OFFSET   0x14UL // 事件生成寄存器
#define LL_TIM_CCMR1_OFFSET 0x18UL // 捕获/比较模式寄存器 1
#define LL_TIM_CCMR2_OFFSET 0x1CUL // 捕获/比较模式寄存器 2
#define LL_TIM_CCER_OFFSET  0x20UL // 捕获/比较使能寄存器
#define LL_TIM_CNT_OFFSET   0x24UL // 计数器寄存器
#define LL_TIM_PSC_OFFSET   0x28UL // 预分频器寄存器
#define LL_TIM_ARR_OFFSET   0x2CUL // 自动重装载寄存器

#define LL_TIM_RCR_OFFSET 0x30UL // 重复计数寄存器（高级定时器独有）

#define LL_TIM_CCR1_OFFSET 0x34UL // 捕获/比较寄存器 1
#define LL_TIM_CCR2_OFFSET 0x38UL // 捕获/比较寄存器 2
#define LL_TIM_CCR3_OFFSET 0x3CUL // 捕获/比较寄存器 3
#define LL_TIM_CCR4_OFFSET 0x40UL // 捕获/比较寄存器 4

#define LL_TIM_BDTR_OFFSET 0x44UL // 死区时间寄存器（高级定时器独有）

#define LL_TIM_DCR_OFFSET  0x48UL // DMA 控制寄存器
#define LL_TIM_DMAR_OFFSET 0x4CUL // 连续模式的 DMA 地址寄存器

/* ---------- TIM 寄存器 字段/掩码 定义 ---------- */

/* TIM_CR1 位位置 */
#define LL_TIM_CR1_CEN_POS  0U // 计数器使能位置
#define LL_TIM_CR1_UDIS_POS 1U // 更新禁用位置
#define LL_TIM_CR1_URS_POS  2U // 更新请求源位置
#define LL_TIM_CR1_OPM_POS  3U // 单脉冲模式位置
#define LL_TIM_CR1_DIR_POS  4U // 计数方向位置
#define LL_TIM_CR1_CMS_POS  5U // 从模式选择位置
#define LL_TIM_CR1_ARPE_POS 7U // 自动重装载预装载使能位置
#define LL_TIM_CR1_CKD_POS  8U // 时钟分割位置

/* TIM_CR1 位掩码 */
#define LL_TIM_CR1_CEN_MASK  (LL_MASK_1 << LL_TIM_CR1_CEN_POS)
#define LL_TIM_CR1_UDIS_MASK (LL_MASK_1 << LL_TIM_CR1_UDIS_POS)
#define LL_TIM_CR1_URS_MASK  (LL_MASK_1 << LL_TIM_CR1_URS_POS)
#define LL_TIM_CR1_OPM_MASK  (LL_MASK_1 << LL_TIM_CR1_OPM_POS)
#define LL_TIM_CR1_DIR_MASK  (LL_MASK_1 << LL_TIM_CR1_DIR_POS)
#define LL_TIM_CR1_CMS_MASK  (LL_MASK_2 << LL_TIM_CR1_CMS_POS)
#define LL_TIM_CR1_ARPE_MASK (LL_MASK_1 << LL_TIM_CR1_ARPE_POS)
#define LL_TIM_CR1_CKD_MASK  (LL_MASK_2 << LL_TIM_CR1_CKD_POS)

/* TIM_CR2 位位置 */
#define LL_TIM_CR2_CCPC_POS  0U  // 捕获/比较预装载使能位置
#define LL_TIM_CR2_CCUS_POS  2U  // 捕获/比较更新选择位置
#define LL_TIM_CR2_CCDS_POS  3U  // 捕获/比较 DMA 选择位置
#define LL_TIM_CR2_MMS_POS   4U  // 主模式选择位置
#define LL_TIM_CR2_TI1S_POS  7U  // TI1 输入选择位置
#define LL_TIM_CR2_OIS1_POS  8U  // 输出比较1反向位置
#define LL_TIM_CR2_OIS1N_POS 9U  // 输出比较1N反向位置
#define LL_TIM_CR2_OIS2_POS  10U // 输出比较2反向位置
#define LL_TIM_CR2_OIS2N_POS 11U // 输出比较2N反向位置
#define LL_TIM_CR2_OIS3_POS  12U // 输出比较3反向位置
#define LL_TIM_CR2_OIS3N_POS 13U // 输出比较3N反向位置
#define LL_TIM_CR2_OIS4_POS  14U // 输出比较4反向位置

/* TIM_CR2 位掩码 */
#define LL_TIM_CR2_CCPC_MASK  (LL_MASK_1 << LL_TIM_CR2_CCPC_POS)
#define LL_TIM_CR2_CCUS_MASK  (LL_MASK_1 << LL_TIM_CR2_CCUS_POS)
#define LL_TIM_CR2_CCDS_MASK  (LL_MASK_1 << LL_TIM_CR2_CCDS_POS)
#define LL_TIM_CR2_MMS_MASK   (LL_MASK_3 << LL_TIM_CR2_MMS_POS)
#define LL_TIM_CR2_TI1S_MASK  (LL_MASK_1 << LL_TIM_CR2_TI1S_POS)
#define LL_TIM_CR2_OIS1_MASK  (LL_MASK_1 << LL_TIM_CR2_OIS1_POS)
#define LL_TIM_CR2_OIS1N_MASK (LL_MASK_1 << LL_TIM_CR2_OIS1N_POS)
#define LL_TIM_CR2_OIS2_MASK  (LL_MASK_1 << LL_TIM_CR2_OIS2_POS)
#define LL_TIM_CR2_OIS2N_MASK (LL_MASK_1 << LL_TIM_CR2_OIS2N_POS)
#define LL_TIM_CR2_OIS3_MASK  (LL_MASK_1 << LL_TIM_CR2_OIS3_POS)
#define LL_TIM_CR2_OIS3N_MASK (LL_MASK_1 << LL_TIM_CR2_OIS3N_POS)
#define LL_TIM_CR2_OIS4_MASK  (LL_MASK_1 << LL_TIM_CR2_OIS4_POS)

/* TIM_SMCR 位位置 */
#define LL_TIM_SMCR_SMS_POS  0U  // 从模式选择位置
#define LL_TIM_SMCR_TS_POS   4U  // 触发选择位置
#define LL_TIM_SMCR_MSM_POS  7U  // 主模式选择位置
#define LL_TIM_SMCR_ETF_POS  8U  // 外部触发滤波位置
#define LL_TIM_SMCR_ETPS_POS 12U // 外部触发预分频位置
#define LL_TIM_SMCR_ECE_POS  14U // 外部时钟使能位置
#define LL_TIM_SMCR_ETP_POS  15U // 外部触发极性位置

/* TIM_SMCR 位掩码 */
#define LL_TIM_SMCR_SMS_MASK  (LL_MASK_3 << LL_TIM_SMCR_SMS_POS)
#define LL_TIM_SMCR_TS_MASK   (LL_MASK_3 << LL_TIM_SMCR_TS_POS)
#define LL_TIM_SMCR_MSM_MASK  (LL_MASK_1 << LL_TIM_SMCR_MSM_POS)
#define LL_TIM_SMCR_ETF_MASK  (LL_MASK_4 << LL_TIM_SMCR_ETF_POS)
#define LL_TIM_SMCR_ETPS_MASK (LL_MASK_2 << LL_TIM_SMCR_ETPS_POS)
#define LL_TIM_SMCR_ECE_MASK  (LL_MASK_1 << LL_TIM_SMCR_ECE_POS)
#define LL_TIM_SMCR_ETP_MASK  (LL_MASK_1 << LL_TIM_SMCR_ETP_POS)

/* TIM_DIER 位位置 */
#define LL_TIM_DIER_UIE_POS   0U  // 更新中断使能位置
#define LL_TIM_DIER_CC1IE_POS 1U  // 捕获/比较1中断使能位置
#define LL_TIM_DIER_CC2IE_POS 2U  // 捕获/比较2中断使能位置
#define LL_TIM_DIER_CC3IE_POS 3U  // 捕获/比较3中断使能位置
#define LL_TIM_DIER_CC4IE_POS 4U  // 捕获/比较4中断使能位置
#define LL_TIM_DIER_COMIE_POS 5U  // COM中断使能位置
#define LL_TIM_DIER_TIE_POS   6U  // 触发中断使能位置
#define LL_TIM_DIER_BIE_POS   7U  // 背景中断使能位置
#define LL_TIM_DIER_UDE_POS   8U  // 更新DMA请求使能位置
#define LL_TIM_DIER_CC1DE_POS 9U  // 捕获/比较1 DMA请求使能位置
#define LL_TIM_DIER_CC2DE_POS 10U // 捕获/比较2 DMA请求使能位置
#define LL_TIM_DIER_CC3DE_POS 11U // 捕获/比较3 DMA请求使能位置
#define LL_TIM_DIER_CC4DE_POS 12U // 捕获/比较4 DMA请求使能位置
#define LL_TIM_DIER_COMDE_POS 13U // COM DMA请求使能位置
#define LL_TIM_DIER_TDE_POS   14U // 触发 DMA请求使能位置

/* TIM_DIER 位掩码 */
#define LL_TIM_DIER_UIE_MASK   (LL_MASK_1 << LL_TIM_DIER_UIE_POS)
#define LL_TIM_DIER_CC1IE_MASK (LL_MASK_1 << LL_TIM_DIER_CC1IE_POS)
#define LL_TIM_DIER_CC2IE_MASK (LL_MASK_1 << LL_TIM_DIER_CC2IE_POS)
#define LL_TIM_DIER_CC3IE_MASK (LL_MASK_1 << LL_TIM_DIER_CC3IE_POS)
#define LL_TIM_DIER_CC4IE_MASK (LL_MASK_1 << LL_TIM_DIER_CC4IE_POS)
#define LL_TIM_DIER_COMIE_MASK (LL_MASK_1 << LL_TIM_DIER_COMIE_POS)
#define LL_TIM_DIER_TIE_MASK   (LL_MASK_1 << LL_TIM_DIER_TIE_POS)
#define LL_TIM_DIER_BIE_MASK   (LL_MASK_1 << LL_TIM_DIER_BIE_POS)
#define LL_TIM_DIER_UDE_MASK   (LL_MASK_1 << LL_TIM_DIER_UDE_POS)
#define LL_TIM_DIER_CC1DE_MASK (LL_MASK_1 << LL_TIM_DIER_CC1DE_POS)
#define LL_TIM_DIER_CC2DE_MASK (LL_MASK_1 << LL_TIM_DIER_CC2DE_POS)
#define LL_TIM_DIER_CC3DE_MASK (LL_MASK_1 << LL_TIM_DIER_CC3DE_POS)
#define LL_TIM_DIER_CC4DE_MASK (LL_MASK_1 << LL_TIM_DIER_CC4DE_POS)
#define LL_TIM_DIER_COMDE_MASK (LL_MASK_1 << LL_TIM_DIER_COMDE_POS)
#define LL_TIM_DIER_TDE_MASK   (LL_MASK_1 << LL_TIM_DIER_TDE_POS)

/* TIM_SR 位位置 */
#define LL_TIM_SR_UIF_POS   0U  // 更新标志位置
#define LL_TIM_SR_CC1IF_POS 1U  // 捕获/比较1标志位置
#define LL_TIM_SR_CC2IF_POS 2U  // 捕获/比较2标志位置
#define LL_TIM_SR_CC3IF_POS 3U  // 捕获/比较3标志位置
#define LL_TIM_SR_CC4IF_POS 4U  // 捕获/比较4标志位置
#define LL_TIM_SR_COMIF_POS 5U  // COM标志位置
#define LL_TIM_SR_TIF_POS   6U  // 触发标志位置
#define LL_TIM_SR_BIF_POS   7U  // 背景标志位置
#define LL_TIM_SR_CC1OF_POS 9U  // 捕获/比较1溢出位置
#define LL_TIM_SR_CC2OF_POS 10U // 捕获/比较2溢出位置
#define LL_TIM_SR_CC3OF_POS 11U // 捕获/比较3溢出位置
#define LL_TIM_SR_CC4OF_POS 12U // 捕获/比较4溢出位置

/* TIM_SR 位掩码 */
#define LL_TIM_SR_UIF_MASK   (LL_MASK_1 << LL_TIM_SR_UIF_POS)
#define LL_TIM_SR_CC1IF_MASK (LL_MASK_1 << LL_TIM_SR_CC1IF_POS)
#define LL_TIM_SR_CC2IF_MASK (LL_MASK_1 << LL_TIM_SR_CC2IF_POS)
#define LL_TIM_SR_CC3IF_MASK (LL_MASK_1 << LL_TIM_SR_CC3IF_POS)
#define LL_TIM_SR_CC4IF_MASK (LL_MASK_1 << LL_TIM_SR_CC4IF_POS)
#define LL_TIM_SR_COMIF_MASK (LL_MASK_1 << LL_TIM_SR_COMIF_POS)
#define LL_TIM_SR_TIF_MASK   (LL_MASK_1 << LL_TIM_SR_TIF_POS)
#define LL_TIM_SR_BIF_MASK   (LL_MASK_1 << LL_TIM_SR_BIF_POS)
#define LL_TIM_SR_CC1OF_MASK (LL_MASK_1 << LL_TIM_SR_CC1OF_POS)
#define LL_TIM_SR_CC2OF_MASK (LL_MASK_1 << LL_TIM_SR_CC2OF_POS)
#define LL_TIM_SR_CC3OF_MASK (LL_MASK_1 << LL_TIM_SR_CC3OF_POS)
#define LL_TIM_SR_CC4OF_MASK (LL_MASK_1 << LL_TIM_SR_CC4OF_POS)

/* TIM_EGR 位位置 */
#define LL_TIM_EGR_UG_POS   0U // 更新生成位置
#define LL_TIM_EGR_CC1G_POS 1U // 捕获/比较1生成位置
#define LL_TIM_EGR_CC2G_POS 2U // 捕获/比较2生成位置
#define LL_TIM_EGR_CC3G_POS 3U // 捕获/比较3生成位置
#define LL_TIM_EGR_CC4G_POS 4U // 捕获/比较4生成位置
#define LL_TIM_EGR_COMG_POS 5U // COM生成位置
#define LL_TIM_EGR_TG_POS   6U // 触发生成位置
#define LL_TIM_EGR_BG_POS   7U // 背景生成位置

/* TIM_EGR 位掩码 */
#define LL_TIM_EGR_UG_MASK   (LL_MASK_1 << LL_TIM_EGR_UG_POS)
#define LL_TIM_EGR_CC1G_MASK (LL_MASK_1 << LL_TIM_EGR_CC1G_POS)
#define LL_TIM_EGR_CC2G_MASK (LL_MASK_1 << LL_TIM_EGR_CC2G_POS)
#define LL_TIM_EGR_CC3G_MASK (LL_MASK_1 << LL_TIM_EGR_CC3G_POS)
#define LL_TIM_EGR_CC4G_MASK (LL_MASK_1 << LL_TIM_EGR_CC4G_POS)
#define LL_TIM_EGR_COMG_MASK (LL_MASK_1 << LL_TIM_EGR_COMG_POS)
#define LL_TIM_EGR_TG_MASK   (LL_MASK_1 << LL_TIM_EGR_TG_POS)
#define LL_TIM_EGR_BG_MASK   (LL_MASK_1 << LL_TIM_EGR_BG_POS)

/* TIM_CCMR1 位位置 */
#define LL_TIM_CCMR1_CC1S_POS  0U  // 捕获/比较1源选择位置
#define LL_TIM_CCMR1_OC1FE_POS 2U  // 捕获/比较1快速使能位置
#define LL_TIM_CCMR1_OC1PE_POS 3U  // 捕获/比较1预装载使能位置
#define LL_TIM_CCMR1_OC1M_POS  4U  // 捕获/比较1模式位置
#define LL_TIM_CCMR1_OC1CE_POS 7U  // 捕获/比较1清除使能位置
#define LL_TIM_CCMR1_CC2S_POS  8U  // 捕获/比较2源选择位置
#define LL_TIM_CCMR1_OC2FE_POS 10U // 捕获/比较2快速使能位置
#define LL_TIM_CCMR1_OC2PE_POS 11U // 捕获/比较2预装载使能位置
#define LL_TIM_CCMR1_OC2M_POS  12U // 捕获/比较2模式位置
#define LL_TIM_CCMR1_OC2CE_POS 15U // 捕获/比较2清除使能位置

#define LL_TIM_CCMR1_IC1PSC_POS 2U  // 捕获/比较1输入预分频位置
#define LL_TIM_CCMR1_IC1F_POS   4U  // 捕获/比较1输入滤波位置
#define LL_TIM_CCMR1_IC2PSC_POS 10U // 捕获/比较2输入预分频位置
#define LL_TIM_CCMR1_IC2F_POS   12U // 捕获/比较2输入滤波位置

/* TIM_CCMR1 位掩码 */
#define LL_TIM_CCMR1_CC1S_MASK  (LL_MASK_2 << LL_TIM_CCMR1_CC1S_POS)
#define LL_TIM_CCMR1_OC1FE_MASK (LL_MASK_1 << LL_TIM_CCMR1_OC1FE_POS)
#define LL_TIM_CCMR1_OC1PE_MASK (LL_MASK_1 << LL_TIM_CCMR1_OC1PE_POS)
#define LL_TIM_CCMR1_OC1M_MASK  (LL_MASK_3 << LL_TIM_CCMR1_OC1M_POS)
#define LL_TIM_CCMR1_OC1CE_MASK (LL_MASK_1 << LL_TIM_CCMR1_OC1CE_POS)
#define LL_TIM_CCMR1_CC2S_MASK  (LL_MASK_2 << LL_TIM_CCMR1_CC2S_POS)
#define LL_TIM_CCMR1_OC2FE_MASK (LL_MASK_1 << LL_TIM_CCMR1_OC2FE_POS)
#define LL_TIM_CCMR1_OC2PE_MASK (LL_MASK_1 << LL_TIM_CCMR1_OC2PE_POS)
#define LL_TIM_CCMR1_OC2M_MASK  (LL_MASK_3 << LL_TIM_CCMR1_OC2M_POS)
#define LL_TIM_CCMR1_OC2CE_MASK (LL_MASK_1 << LL_TIM_CCMR1_OC2CE_POS)

#define LL_TIM_CCMR1_IC1PSC_MASK (LL_MASK_2 << LL_TIM_CCMR1_IC1PSC_POS)
#define LL_TIM_CCMR1_IC1F_MASK   (LL_MASK_4 << LL_TIM_CCMR1_IC1F_POS)
#define LL_TIM_CCMR1_IC2PSC_MASK (LL_MASK_2 << LL_TIM_CCMR1_IC2PSC_POS)
#define LL_TIM_CCMR1_IC2F_MASK   (LL_MASK_4 << LL_TIM_CCMR1_IC2F_POS)

/* TIM_CCMR2 位位置 */
#define LL_TIM_CCMR2_CC3S_POS  0U  // 捕获/比较3源选择位置
#define LL_TIM_CCMR2_OC3FE_POS 2U  // 捕获/比较3快速使能位置
#define LL_TIM_CCMR2_OC3PE_POS 3U  // 捕获/比较3预装载使能位置
#define LL_TIM_CCMR2_OC3M_POS  4U  // 捕获/比较3模式位置
#define LL_TIM_CCMR2_OC3CE_POS 7U  // 捕获/比较3清除使能位置
#define LL_TIM_CCMR2_CC4S_POS  8U  // 捕获/比较4源选择位置
#define LL_TIM_CCMR2_OC4FE_POS 10U // 捕获/比较4快速使能位置
#define LL_TIM_CCMR2_OC4PE_POS 11U // 捕获/比较4预装载使能位置
#define LL_TIM_CCMR2_OC4M_POS  12U // 捕获/比较4模式位置
#define LL_TIM_CCMR2_OC4CE_POS 15U // 捕获/比较4清除使能位置

#define LL_TIM_CCMR2_IC3PSC_POS 2U  // 捕获/比较3输入预分频位置
#define LL_TIM_CCMR2_IC3F_POS   4U  // 捕获/比较3输入滤波位置
#define LL_TIM_CCMR2_IC4PSC_POS 10U // 捕获/比较4输入预分频位置
#define LL_TIM_CCMR2_IC4F_POS   12U // 捕获/比较4输入滤波位置

/* TIM_CCMR2 位掩码 */
#define LL_TIM_CCMR2_CC3S_MASK  (LL_MASK_2 << LL_TIM_CCMR2_CC3S_POS)
#define LL_TIM_CCMR2_OC3FE_MASK (LL_MASK_1 << LL_TIM_CCMR2_OC3FE_POS)
#define LL_TIM_CCMR2_OC3PE_MASK (LL_MASK_1 << LL_TIM_CCMR2_OC3PE_POS)
#define LL_TIM_CCMR2_OC3M_MASK  (LL_MASK_3 << LL_TIM_CCMR2_OC3M_POS)
#define LL_TIM_CCMR2_OC3CE_MASK (LL_MASK_1 << LL_TIM_CCMR2_OC3CE_POS)
#define LL_TIM_CCMR2_CC4S_MASK  (LL_MASK_2 << LL_TIM_CCMR2_CC4S_POS)
#define LL_TIM_CCMR2_OC4FE_MASK (LL_MASK_1 << LL_TIM_CCMR2_OC4FE_POS)
#define LL_TIM_CCMR2_OC4PE_MASK (LL_MASK_1 << LL_TIM_CCMR2_OC4PE_POS)
#define LL_TIM_CCMR2_OC4M_MASK  (LL_MASK_3 << LL_TIM_CCMR2_OC4M_POS)
#define LL_TIM_CCMR2_OC4CE_MASK (LL_MASK_1 << LL_TIM_CCMR2_OC4CE_POS)

#define LL_TIM_CCMR2_IC3PSC_MASK (LL_MASK_2 << LL_TIM_CCMR2_IC3PSC_POS)
#define LL_TIM_CCMR2_IC3F_MASK   (LL_MASK_4 << LL_TIM_CCMR2_IC3F_POS)
#define LL_TIM_CCMR2_IC4PSC_MASK (LL_MASK_2 << LL_TIM_CCMR2_IC4PSC_POS)
#define LL_TIM_CCMR2_IC4F_MASK   (LL_MASK_4 << LL_TIM_CCMR2_IC4F_POS)

/* TIM_CCER 位位置 */
#define LL_TIM_CCER_CC1E_POS  0U  // 捕获/比较1输出使能位置
#define LL_TIM_CCER_CC1P_POS  1U  // 捕获/比较1输出极性位置
#define LL_TIM_CCER_CC1NP_POS 3U  // 捕获/比较1非反相输出极性位置
#define LL_TIM_CCER_CC2E_POS  4U  // 捕获/比较2输出使能位置
#define LL_TIM_CCER_CC2P_POS  5U  // 捕获/比较2输出极性位置
#define LL_TIM_CCER_CC2NP_POS 7U  // 捕获/比较2非反相输出极性位置
#define LL_TIM_CCER_CC3E_POS  8U  // 捕获/比较3输出使能位置
#define LL_TIM_CCER_CC3P_POS  9U  // 捕获/比较3输出极性位置
#define LL_TIM_CCER_CC3NP_POS 11U // 捕获/比较3非反相输出极性位置
#define LL_TIM_CCER_CC4E_POS  12U // 捕获/比较4输出使能位置
#define LL_TIM_CCER_CC4P_POS  13U // 捕获/比较4输出极性位置

/* TIM_CCER 位掩码 */
#define LL_TIM_CCER_CC1E_MASK  (LL_MASK_1 << LL_TIM_CCER_CC1E_POS)
#define LL_TIM_CCER_CC1P_MASK  (LL_MASK_1 << LL_TIM_CCER_CC1P_POS)
#define LL_TIM_CCER_CC1NP_MASK (LL_MASK_1 << LL_TIM_CCER_CC1NP_POS)
#define LL_TIM_CCER_CC2E_MASK  (LL_MASK_1 << LL_TIM_CCER_CC2E_POS)
#define LL_TIM_CCER_CC2P_MASK  (LL_MASK_1 << LL_TIM_CCER_CC2P_POS)
#define LL_TIM_CCER_CC2NP_MASK (LL_MASK_1 << LL_TIM_CCER_CC2NP_POS)
#define LL_TIM_CCER_CC3E_MASK  (LL_MASK_1 << LL_TIM_CCER_CC3E_POS)
#define LL_TIM_CCER_CC3P_MASK  (LL_MASK_1 << LL_TIM_CCER_CC3P_POS)
#define LL_TIM_CCER_CC3NP_MASK (LL_MASK_1 << LL_TIM_CCER_CC3NP_POS)
#define LL_TIM_CCER_CC4E_MASK  (LL_MASK_1 << LL_TIM_CCER_CC4E_POS)
#define LL_TIM_CCER_CC4P_MASK  (LL_MASK_1 << LL_TIM_CCER_CC4P_POS)

/* TIM_CNT 位位置 */
#define LL_TIM_CNT_CNT_POS 0U // 计数器值位置

/* TIM_CNT 位掩码 */
#define LL_TIM_CNT_CNT_MASK (LL_MASK_16 << LL_TIM_CNT_CNT_POS)

/* TIM_PSC 位位置 */
#define LL_TIM_PSC_PSC_POS 0U // 预分频值位置

/* TIM_PSC 位掩码 */
#define LL_TIM_PSC_PSC_MASK (LL_MASK_16 << LL_TIM_PSC_PSC_POS)

/* TIM_ARR 位位置 */
#define LL_TIM_ARR_ARR_POS 0U // 自动重载值位置

/* TIM_ARR 位掩码 */
#define LL_TIM_ARR_ARR_MASK (LL_MASK_16 << LL_TIM_ARR_ARR_POS)

/* TIM_RCR 位位置 */
#define LL_TIM_RCR_RCR_POS 0U // 重复计数器值位置

/* TIM_RCR 位掩码 */
#define LL_TIM_RCR_RCR_MASK (LL_MASK_8 << LL_TIM_RCR_RCR_POS)

/* TIM_CCR1 位位置 */
#define LL_TIM_CCR1_CCR1_POS 0U // 捕获/比较1值位置

/* TIM_CCR1 位掩码 */
#define LL_TIM_CCR1_CCR1_MASK (LL_MASK_16 << LL_TIM_CCR1_CCR1_POS)

/* TIM_CCR2 位位置 */
#define LL_TIM_CCR2_CCR2_POS 0U // 捕获/比较2值位置

/* TIM_CCR2 位掩码 */
#define LL_TIM_CCR2_CCR2_MASK (LL_MASK_16 << LL_TIM_CCR2_CCR2_POS)

/* TIM_CCR3 位位置 */
#define LL_TIM_CCR3_CCR3_POS 0U // 捕获/比较3值位置

/* TIM_CCR3 位掩码 */
#define LL_TIM_CCR3_CCR3_MASK (LL_MASK_16 << LL_TIM_CCR3_CCR3_POS)

/* TIM_CCR4 位位置 */
#define LL_TIM_CCR4_CCR4_POS 0U // 捕获/比较4值位置

/* TIM_CCR4 位掩码 */
#define LL_TIM_CCR4_CCR4_MASK (LL_MASK_16 << LL_TIM_CCR4_CCR4_POS)

/* TIM_BDTR 位位置 */
#define LL_TIM_BDTR_DTG_POS  0U  // 死区时间生成位置
#define LL_TIM_BDTR_LOCK_POS 8U  // 锁定位置
#define LL_TIM_BDTR_OSSI_POS 10U // 离散死区时间位置
#define LL_TIM_BDTR_OSSR_POS 11U // 离散死区时间位置
#define LL_TIM_BDTR_BKE_POS  12U // 背景使能位置
#define LL_TIM_BDTR_BKP_POS  13U // 背景极性位置
#define LL_TIM_BDTR_AOE_POS  14U // 自动输出使能位置
#define LL_TIM_BDTR_MOE_POS  15U // 主输出使能位置

/* TIM_BDTR 位掩码 */
#define LL_TIM_BDTR_DTG_MASK  (LL_MASK_8 << LL_TIM_BDTR_DTG_POS)
#define LL_TIM_BDTR_LOCK_MASK (LL_MASK_2 << LL_TIM_BDTR_LOCK_POS)
#define LL_TIM_BDTR_OSSI_MASK (LL_MASK_1 << LL_TIM_BDTR_OSSI_POS)
#define LL_TIM_BDTR_OSSR_MASK (LL_MASK_1 << LL_TIM_BDTR_OSSR_POS)
#define LL_TIM_BDTR_BKE_MASK  (LL_MASK_1 << LL_TIM_BDTR_BKE_POS)
#define LL_TIM_BDTR_BKP_MASK  (LL_MASK_1 << LL_TIM_BDTR_BKP_POS)
#define LL_TIM_BDTR_AOE_MASK  (LL_MASK_1 << LL_TIM_BDTR_AOE_POS)
#define LL_TIM_BDTR_MOE_MASK  (LL_MASK_1 << LL_TIM_BDTR_MOE_POS)

/* TIM_DCR 位位置 */
#define LL_TIM_DCR_DBA_POS 0U // 数据缓冲区地址位置
#define LL_TIM_DCR_DBL_POS 8U // 数据缓冲区长度位置

/* TIM_DCR 位掩码 */
#define LL_TIM_DCR_DBA_MASK (LL_MASK_5 << LL_TIM_DCR_DBA_POS)
#define LL_TIM_DCR_DBL_MASK (LL_MASK_5 << LL_TIM_DCR_DBL_POS)

/* TIM_DMAR 位位置 */
#define LL_TIM_DMAR_DMAB_POS 0U // 数据缓冲区地址位置

/* TIM_DMAR 位掩码 */
#define LL_TIM_DMAR_DMAB_MASK (LL_MASK_16 << LL_TIM_DMAR_DMAB_POS)

/* ---------- 参数定义 ---------- */

/* TIM 实例 */
typedef enum
{
    LL_TIM_1 = 1U,
    LL_TIM_2 = 2U,
    LL_TIM_3 = 3U,
    LL_TIM_4 = 4U,
} ll_tim_instance_t;

/* TIM 通道 */
typedef enum
{
    LL_TIM_CH1 = 0U,
    LL_TIM_CH2 = 1U,
    LL_TIM_CH3 = 2U,
    LL_TIM_CH4 = 3U,
} ll_tim_channel_t;

/* TIM 状态 */
typedef enum
{
    LL_TIM_OK                  = 0U,
    LL_TIM_ERROR_INVALID_PARAM = 1U, // 无效参数
    LL_TIM_ERROR_UNSUPPORTED   = 2U, // 不支持的功能
} ll_tim_status_t;

/* TIM 计数模式 */
typedef enum
{
    LL_TIM_COUNTER_UP       = 0U, // 向上计数
    LL_TIM_COUNTER_DOWN     = 1U, // 向下计数
    LL_TIM_COUNTER_CENTER_1 = 2U, // 中心对齐模式 1
    LL_TIM_COUNTER_CENTER_2 = 3U, // 中心对齐模式 2
    LL_TIM_COUNTER_CENTER_3 = 4U, // 中心对齐模式 3
} ll_tim_counter_mode_t;

/* TIM 时钟分频 */
typedef enum
{
    LL_TIM_CKD_DIV1 = 0U, // 不分频
    LL_TIM_CKD_DIV2 = 1U, // 时钟频率/ 2
    LL_TIM_CKD_DIV4 = 2U, // 时钟频率/ 4
} ll_tim_clock_div_t;

/* TIM 输出比较模式 */
typedef enum
{
    LL_TIM_OC_FROZEN     = 0U, // 冻结模式
    LL_TIM_OC_ACTIVE     = 1U, // 强制输出高电平
    LL_TIM_OC_INACTIVE   = 2U, // 强制输出低电平
    LL_TIM_OC_TOGGLE     = 3U, // 翻转模式
    LL_TIM_OC_FORCE_LOW  = 4U, // 强制输出低电平
    LL_TIM_OC_FORCE_HIGH = 5U, // 强制输出高电平
    LL_TIM_OC_PWM1       = 6U, // PWM 模式 1
    LL_TIM_OC_PWM2       = 7U, // PWM 模式 2
} ll_tim_oc_mode_t;

/* TIM 基础配置结构体 */
typedef struct
{
    ll_tim_instance_t     instance;           // 定时器实例
    u16                   prescaler;          // 预分频值
    u16                   auto_reload;        // 自动重装载值
    ll_tim_counter_mode_t counter_mode;       // 计数模式
    ll_tim_clock_div_t    clock_div;          // 时钟分频
    bool                  arr_preload_enable; // 自动重装载预装载使能
    u8                    repetition;         // 仅 TIM1 有效
} ll_tim_base_init_t;

/* TIM 输出比较配置结构体 */
typedef struct
{
    ll_tim_instance_t instance;       // 定时器实例
    ll_tim_channel_t  channel;        // 定时器通道
    ll_tim_oc_mode_t  oc_mode;        // 输出比较模式
    u16               compare;        // 比较值
    bool              preload_enable; // 预装载使能
    bool              polarity_low;   // 输出极性，true = 低电平有效，false = 高电平有效
} ll_tim_oc_init_t;

/* ========== 对外接口 ========== */

/* 基础初始化 */
ll_tim_status_t ll_tim_base_init(const ll_tim_base_init_t* cfg);
/* 计数器控制 */
void ll_tim_counter_enable(ll_tim_instance_t instance);
/* 计数器禁用 */
void ll_tim_counter_disable(ll_tim_instance_t instance);
/* 设置预分频器 */
void ll_tim_set_prescaler(ll_tim_instance_t instance, u16 value);
/* 设置自动重装载值 */
void ll_tim_set_auto_reload(ll_tim_instance_t instance, u16 value);
/* 设置计数器值 */
void ll_tim_set_counter(ll_tim_instance_t instance, u16 value);
/* 获取计数器值 */
u16 ll_tim_get_counter(ll_tim_instance_t instance);
/* 生成事件 */
void ll_tim_generate_event(ll_tim_instance_t instance, u32 event_mask);

/* 中断控制 */
void ll_tim_irq_enable(ll_tim_instance_t instance, u32 irq_mask);
/* 中断禁用 */
void ll_tim_irq_disable(ll_tim_instance_t instance, u32 irq_mask);
/* 标志位控制 */
isSET ll_tim_is_flag_set(ll_tim_instance_t instance, u32 flag_mask);
/* 清除标志位 */
void ll_tim_clear_flag(ll_tim_instance_t instance, u32 flag_mask);

/* 输出比较控制 */
ll_tim_status_t ll_tim_oc_init(const ll_tim_oc_init_t* cfg);
/* 设置比较值 */
void ll_tim_set_compare(ll_tim_instance_t instance, ll_tim_channel_t channel, u16 value);
/* 获取比较值 */
u16 ll_tim_get_compare(ll_tim_instance_t instance, ll_tim_channel_t channel);
/* 通道使能 */
void ll_tim_channel_enable(ll_tim_instance_t instance, ll_tim_channel_t channel);
/* 通道禁用 */
void ll_tim_channel_disable(ll_tim_instance_t instance, ll_tim_channel_t channel);

/* 主输出控制 */
void ll_tim_main_output_enable(ll_tim_instance_t instance); // TIM1 only
/* 主输出禁用 */
void ll_tim_main_output_disable(ll_tim_instance_t instance); // TIM1 only

#endif /* __DRI_LL.TIM_H__ */