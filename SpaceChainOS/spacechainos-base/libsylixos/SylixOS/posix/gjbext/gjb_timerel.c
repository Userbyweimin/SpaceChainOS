/*********************************************************************************************************
**
**                                    中国软件开源组织
**
**                                   嵌入式实时操作系统
**
**                                       SylixOS(TM)
**
**                               Copyright  All Rights Reserved
**
**--------------文件信息--------------------------------------------------------------------------------
**
** 文   件   名: gjb_timerrel.c
**
** 创   建   人: Han.Hui (韩辉)
**
** 文件创建日期: 2016 年 04 月 13 日
**
** 描        述: GJB7714 扩展接口定时器时间相关部分.
*********************************************************************************************************/
#define  __SYLIXOS_KERNEL
#include "SylixOS.h"
/*********************************************************************************************************
  裁剪支持
*********************************************************************************************************/
#if (LW_CFG_POSIX_EN > 0) && (LW_CFG_GJB7714_EN > 0)
#include "../include/px_gjbext.h"
/*********************************************************************************************************
** 函数名称: tick_get
** 功能描述: 获得系统 tick.
** 输　入  : NONE
** 输　出  : 系统 tick 计数.
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
uint64_t  tick_get (void)
{
    return  ((uint64_t)API_TimeGet64());
}
/*********************************************************************************************************
** 函数名称: tick_set
** 功能描述: 设置系统 tick.
** 输　入  : ticks     系统时间
** 输　出  : NONE
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
void  tick_set (uint64_t  ticks)
{
    errno = ENOTSUP;
}
/*********************************************************************************************************
** 函数名称: sys_clk_rate_get
** 功能描述: 获得系统 tick 频率.
** 输　入  : NONE
** 输　出  : 系统 tick 计数频率.
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
uint32_t  sys_clk_rate_get (void)
{
    return  ((uint32_t)LW_TICK_HZ);
}
/*********************************************************************************************************
** 函数名称: sys_clk_rate_set
** 功能描述: 设置系统 tick 频率.
** 输　入  : ticks_per_second      系统 tick 计数频率
** 输　出  : NONE
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  sys_clk_rate_set (int  ticks_per_second)
{
    errno = ENOTSUP;
    return  (PX_ERROR);
}
/*********************************************************************************************************
** 函数名称: wdg_create
** 功能描述: 创建一个定时器.
** 输　入  : wdg_id        定时器句柄
** 输　出  : ERROR or OK
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  wdg_create (wdg_t *wdg_id)
{
    if (!wdg_id) {
        errno = EINVAL;
        return  (PX_ERROR);
    }
    
    *wdg_id = API_TimerCreate("GJB wd", LW_OPTION_HTIMER, LW_NULL);
    if (*wdg_id) {
        return  (ERROR_NONE);
    
    } else {
        return  (PX_ERROR);
    }
}
/*********************************************************************************************************
** 函数名称: wdg_start
** 功能描述: 启动定时器.
** 输　入  : wdg_id        定时器句柄
**           ticks         定时器时间
**           func          回调函数
**           arg           参数
** 输　出  : ERROR or OK
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  wdg_start (wdg_t wdg_id, int ticks, void (*func)(void *arg), void *arg)
{
    ULONG  ulError;
    
    if (ticks <= 0) {
        errno = EINVAL;
        return  (PX_ERROR);
    }

    ulError = API_TimerStart(wdg_id, (ULONG)ticks, LW_OPTION_MANUAL_RESTART,
                            (PTIMER_CALLBACK_ROUTINE)func, (PVOID)arg);
    if (ulError) {
        return  (PX_ERROR);
    
    } else {
        return  (ERROR_NONE);
    }
}
/*********************************************************************************************************
** 函数名称: wdg_cancel
** 功能描述: 停止定时器.
** 输　入  : wdg_id        定时器句柄
** 输　出  : ERROR or OK
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  wdg_cancel (wdg_t wdg_id)
{
    if (API_TimerCancel(wdg_id)) {
        return  (PX_ERROR);
    
    } else {
        return  (ERROR_NONE);
    }
}
/*********************************************************************************************************
** 函数名称: wdg_delete
** 功能描述: 删除定时器.
** 输　入  : wdg_id        定时器句柄
** 输　出  : ERROR or OK
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  wdg_delete (wdg_t wdg_id)
{
    if (API_TimerDelete(&wdg_id)) {
        errno = EINVAL;
        return  (PX_ERROR);
    
    } else {
        return  (ERROR_NONE);
    }
}
/*********************************************************************************************************
** 函数名称: wdg_getinfo
** 功能描述: 获得定时器信息.
** 输　入  : wdg_id        定时器句柄
**           info          定时器信息
** 输　出  : ERROR or OK
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  wdg_getinfo (wdg_t wdg_id, wdg_info_t *info)
{
    if (!info) {
        errno = EINVAL;
        return  (PX_ERROR);
    }
    
    if (API_TimerStatus(wdg_id, (BOOL *)&info->run, LW_NULL, &info->cnt, LW_NULL)) {
        errno = EINVAL;
        return  (PX_ERROR);
    
    } else {
        return  (ERROR_NONE);
    }
}
/*********************************************************************************************************
** 函数名称: wdg_show
** 功能描述: 显示定时器信息.
** 输　入  : wdg_id        定时器句柄
** 输　出  : ERROR or OK
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  wdg_show (wdg_t wdg_id)
{
    if (wdg_id == LW_OBJECT_HANDLE_INVALID) {
        errno = EINVAL;
        return  (PX_ERROR);
    }

    API_TimerShow(wdg_id);
    
    return  (ERROR_NONE);
}
/*********************************************************************************************************
** 函数名称: timer_getinfo
** 功能描述: 获得一个定时器信息
** 输　入  : timer        定时器句柄
**           pvFile       文件结构
** 输　出  : ERROR_NONE  or  PX_ERROR
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
#if LW_CFG_PTIMER_EN > 0

LW_API 
int  timer_getinfo (timer_t  timer, timer_info_t  *timer_info)
{    
    if (!timer || (timer_info == LW_NULL)) {
        _ErrorHandle(EINVAL);
        return  (PX_ERROR);
    }
    
    if (API_TimerStatusEx(timer, &timer_info->run, LW_NULL,
                          &timer_info->cnt, 
                          &timer_info->interval, 
                          &timer_info->clockid)) {
        _ErrorHandle(EINVAL);
        return  (PX_ERROR);
    }
    
    return  (ERROR_NONE);
}

#endif                                                                  /*  LW_CFG_PTIMER_EN > 0        */
#endif                                                                  /*  LW_CFG_POSIX_EN > 0         */
                                                                        /*  LW_CFG_GJB7714_EN > 0       */
/*********************************************************************************************************
  END
*********************************************************************************************************/
