/**
 * @file dri_ll_tim.c
 * @author sisanwu12 (sisanwu12@outlook.com)
 * @brief
 * @version 0.1
 * @date 2026-04-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "dri_ll_tim.h"
#include "dri_ll.h"

/* ---------- 内部函数 ---------- */

/**
 * @brief 获取 TIM 寄存器基地址
 *
 * @param timx TIM 实例
 * @return uptr 寄存器基地址
 */
static inline uptr ll_tim_get_tim_addr(ll_tim_instance_t timx)
{
    switch (timx)
    {
    case LL_TIM_1:
        return LL_TIM1_BASE_ADDR;
    case LL_TIM_2:
        return LL_TIM2_BASE_ADDR;
    case LL_TIM_3:
        return LL_TIM3_BASE_ADDR;
    case LL_TIM_4:
        return LL_TIM4_BASE_ADDR;
    default:
        return 0; // 无效实例
    }
}

/* ========== 函数定义 ========== */

/**
 * @brief 初始化 TIM 基础配置
 *
 * @param cfg 配置结构体指针
 * @return ll_tim_status_t 状态码
 *
 */
ll_tim_status_t ll_tim_base_init(const ll_tim_base_init_t* cfg)
{
    if (cfg == NULL)
    {
        return LL_TIM_ERROR_INVALID_PARAM;
    }

    /* 配置预分频器 */
    ll_tim_set_prescaler(cfg->instance, cfg->prescaler);
    /* 配置自动重装载值 */
    ll_tim_set_auto_reload(cfg->instance, cfg->auto_reload);

    /* 配置计数模式和时钟分频 */
    u32 cr1_value = 0;
    cr1_value |= ((u32)(cfg->counter_mode) << LL_TIM_CR1_CMS_POS);
    cr1_value |= ((u32)(cfg->clock_div) << LL_TIM_CR1_CKD_POS);
    /* 配置自动重装载预装载使能 */
    if (cfg->arr_preload_enable)
    {
        cr1_value |= LL_TIM_CR1_ARPE_MASK;
    }
    /* 写入 CR1 寄存器 */
    ll_write_reg(ll_tim_get_tim_addr(cfg->instance), LL_TIM_CR1_OFFSET, cr1_value);

    /* 配置重复计数，仅 TIM1 有效 */
    if (cfg->instance == LL_TIM_1)
    {
        ll_write_reg(LL_TIM1_BASE_ADDR, LL_TIM_RCR_OFFSET, cfg->repetition);
    }

    return LL_TIM_OK;
}

/**
 * @brief 使能 TIM 计数器
 *
 * @param instance TIM 实例
 */
void ll_tim_counter_enable(ll_tim_instance_t instance)
{
    /* 使能计数器 */
    u32 cr1_value = ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CR1_OFFSET);
    cr1_value |= LL_TIM_CR1_CEN_MASK;
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CR1_OFFSET, cr1_value);
}

/**
 * @brief 禁用 TIM 计数器
 *
 * @param instance TIM 实例
 */
void ll_tim_counter_disable(ll_tim_instance_t instance)
{
    /* 禁用计数器 */
    u32 cr1_value = ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CR1_OFFSET);
    cr1_value &= ~LL_TIM_CR1_CEN_MASK;
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CR1_OFFSET, cr1_value);
}

/**
 * @brief 设置 TIM 预分频器
 *
 * @param instance TIM 实例
 * @param value 预分频器值
 */
void ll_tim_set_prescaler(ll_tim_instance_t instance, u16 value)
{
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_PSC_OFFSET, value);
}

/**
 * @brief 设置 TIM 自动重装载值
 *
 * @param instance TIM 实例
 * @param value 自动重装载值
 */
void ll_tim_set_auto_reload(ll_tim_instance_t instance, u16 value)
{
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_ARR_OFFSET, value);
}

/**
 * @brief 设置 TIM 计数器值
 *
 * @param instance TIM 实例
 * @param value 计数器值
 */
void ll_tim_set_counter(ll_tim_instance_t instance, u16 value)
{
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CNT_OFFSET, value);
}

/**
 * @brief 获取 TIM 计数器值
 *
 * @param instance TIM 实例
 * @return u16 计数器值
 */
u16 ll_tim_get_counter(ll_tim_instance_t instance)
{
    return ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CNT_OFFSET);
}

/* 生成事件 */
void ll_tim_generate_event(ll_tim_instance_t instance, u32 event_mask)
{
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_EGR_OFFSET, event_mask);
}

/* 中断控制 */
void ll_tim_irq_enable(ll_tim_instance_t instance, u32 irq_mask)
{
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_DIER_OFFSET, irq_mask);
}

/* 中断禁用 */
void ll_tim_irq_disable(ll_tim_instance_t instance, u32 irq_mask)
{
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_DIER_OFFSET, ~irq_mask);
}

/* 标志位控制 */
isSET ll_tim_is_flag_set(ll_tim_instance_t instance, u32 flag_mask)
{
    u32 sr_value = ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_SR_OFFSET);
    return (sr_value & flag_mask) ? true : false;
}

/* 清除标志位 */
void ll_tim_clear_flag(ll_tim_instance_t instance, u32 flag_mask)
{
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_SR_OFFSET, ~flag_mask);
}

/* 输出比较控制 */
ll_tim_status_t ll_tim_oc_init(const ll_tim_oc_init_t* cfg)
{
    if (cfg == NULL)
    {
        return LL_TIM_ERROR_INVALID_PARAM;
    }

    /* 配置输出比较模式和预装载使能 */
    u32 ccmr_value = 0;
    switch (cfg->channel)
    {
    case LL_TIM_CH1:
        ccmr_value |= ((u32)(cfg->oc_mode) << LL_TIM_CCMR1_OC1M_POS);
        if (cfg->preload_enable)
        {
            ccmr_value |= LL_TIM_CCMR1_OC1PE_MASK;
        }
        break;
    case LL_TIM_CH2:
        ccmr_value |= ((u32)(cfg->oc_mode) << LL_TIM_CCMR1_OC2M_POS);
        if (cfg->preload_enable)
        {
            ccmr_value |= LL_TIM_CCMR1_OC2PE_MASK;
        }
        break;
    case LL_TIM_CH3:
        ccmr_value |= ((u32)(cfg->oc_mode) << LL_TIM_CCMR2_OC3M_POS);
        if (cfg->preload_enable)
        {
            ccmr_value |= LL_TIM_CCMR2_OC3PE_MASK;
        }
        break;
    case LL_TIM_CH4:
        ccmr_value |= ((u32)(cfg->oc_mode) << LL_TIM_CCMR2_OC4M_POS);
        if (cfg->preload_enable)
        {
            ccmr_value |= LL_TIM_CCMR2_OC4PE_MASK;
        }
        break;
    default:
        return LL_TIM_ERROR_INVALID_PARAM; // 无效通道
    }
    /* 写入 CCMR 寄存器 */
    if (cfg->channel == LL_TIM_CH1 || cfg->channel == LL_TIM_CH2)
    {
        ll_write_reg(ll_tim_get_tim_addr(cfg->instance), LL_TIM_CCMR1_OFFSET, ccmr_value);
    }
    else
    {
        ll_write_reg(ll_tim_get_tim_addr(cfg->instance), LL_TIM_CCMR2_OFFSET, ccmr_value);
    }

    /* 配置输出极性 */
    u32 ccER_value = ll_read_reg(ll_tim_get_tim_addr(cfg->instance), LL_TIM_CCER_OFFSET);
    switch (cfg->channel)
    {
    case LL_TIM_CH1:
        if (cfg->polarity_low)
        {
            ccER_value |= LL_TIM_CCER_CC1P_MASK;
        }
        else
        {
            ccER_value &= ~LL_TIM_CCER_CC1P_MASK;
        }
        break;
    case LL_TIM_CH2:
        if (cfg->polarity_low)
        {
            ccER_value |= LL_TIM_CCER_CC2P_MASK;
        }
        else
        {
            ccER_value &= ~LL_TIM_CCER_CC2P_MASK;
        }
        break;
    case LL_TIM_CH3:
        if (cfg->polarity_low)
        {
            ccER_value |= LL_TIM_CCER_CC3P_MASK;
        }
        else
        {
            ccER_value &= ~LL_TIM_CCER_CC3P_MASK;
        }
        break;
    case LL_TIM_CH4:
        if (cfg->polarity_low)
        {
            ccER_value |= LL_TIM_CCER_CC4P_MASK;
        }
        else
        {
            ccER_value &= ~LL_TIM_CCER_CC4P_MASK;
        }
        break;
    default:
        return LL_TIM_ERROR_INVALID_PARAM; // 无效通道
    }

    /* 写入 CCER 寄存器 */
    ll_write_reg(ll_tim_get_tim_addr(cfg->instance), LL_TIM_CCER_OFFSET, ccER_value);

    return LL_TIM_OK;
}

/* 设置比较值 */
void ll_tim_set_compare(ll_tim_instance_t instance, ll_tim_channel_t channel, u16 value)
{
    switch (channel)
    {
    case LL_TIM_CH1:
        ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR1_OFFSET, value);
        break;
    case LL_TIM_CH2:
        ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR2_OFFSET, value);
        break;
    case LL_TIM_CH3:
        ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR3_OFFSET, value);
        break;
    case LL_TIM_CH4:
        ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR4_OFFSET, value);
        break;
    default:
        // 无效通道，忽略
        break;
    }
}

/* 获取比较值 */
u16 ll_tim_get_compare(ll_tim_instance_t instance, ll_tim_channel_t channel)
{
    switch (channel)
    {
    case LL_TIM_CH1:
        return ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR1_OFFSET);
    case LL_TIM_CH2:
        return ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR2_OFFSET);
    case LL_TIM_CH3:
        return ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR3_OFFSET);
    case LL_TIM_CH4:
        return ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCR4_OFFSET);
    default:
        return 0; // 无效通道，返回0
    }
}

/* 通道使能 */
void ll_tim_channel_enable(ll_tim_instance_t instance, ll_tim_channel_t channel)
{
    u32 ccER_value = ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCER_OFFSET);
    switch (channel)
    {
    case LL_TIM_CH1:
        ccER_value |= LL_TIM_CCER_CC1E_MASK;
        break;
    case LL_TIM_CH2:
        ccER_value |= LL_TIM_CCER_CC2E_MASK;
        break;
    case LL_TIM_CH3:
        ccER_value |= LL_TIM_CCER_CC3E_MASK;
        break;
    case LL_TIM_CH4:
        ccER_value |= LL_TIM_CCER_CC4E_MASK;
        break;
    default:
        return; // 无效通道，忽略
    }
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCER_OFFSET, ccER_value);
}

/* 通道禁用 */
void ll_tim_channel_disable(ll_tim_instance_t instance, ll_tim_channel_t channel)
{
    u32 ccER_value = ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCER_OFFSET);
    switch (channel)
    {
    case LL_TIM_CH1:
        ccER_value &= ~LL_TIM_CCER_CC1E_MASK;
        break;
    case LL_TIM_CH2:
        ccER_value &= ~LL_TIM_CCER_CC2E_MASK;
        break;
    case LL_TIM_CH3:
        ccER_value &= ~LL_TIM_CCER_CC3E_MASK;
        break;
    case LL_TIM_CH4:
        ccER_value &= ~LL_TIM_CCER_CC4E_MASK;
        break;
    default:
        return; // 无效通道，忽略
    }
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_CCER_OFFSET, ccER_value);
}

/* 主输出控制 */
void ll_tim_main_output_enable(ll_tim_instance_t instance) // TIM1 only
{
    if (instance != LL_TIM_1)
    {
        return;
    }

    u32 bdtr_value = ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_BDTR_OFFSET);
    bdtr_value |= LL_TIM_BDTR_MOE_MASK;
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_BDTR_OFFSET, bdtr_value);
}

/* 主输出禁用 */
void ll_tim_main_output_disable(ll_tim_instance_t instance) // TIM1 only
{
    if (instance != LL_TIM_1)
    {
        return;
    }

    u32 bdtr_value = ll_read_reg(ll_tim_get_tim_addr(instance), LL_TIM_BDTR_OFFSET);
    bdtr_value &= ~LL_TIM_BDTR_MOE_MASK;
    ll_write_reg(ll_tim_get_tim_addr(instance), LL_TIM_BDTR_OFFSET, bdtr_value);
}
