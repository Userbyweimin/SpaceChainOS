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
** 文   件   名: px_execinfo.h
**
** 创   建   人: Han.Hui (韩辉)
**
** 文件创建日期: 2013 年 12 月 10 日
**
** 描        述: execinfo 兼容库.
*********************************************************************************************************/

#ifndef __PX_EXECINFO_H
#define __PX_EXECINFO_H

#include "SylixOS.h"                                                    /*  操作系统头文件              */

/*********************************************************************************************************
  裁剪支持
*********************************************************************************************************/
#if LW_CFG_POSIX_EN > 0 && LW_CFG_MODULELOADER_EN > 0

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

LW_API int     backtrace(void **array, int size);
LW_API char  **backtrace_symbols(void *const *array, int size);
LW_API void    backtrace_symbols_fd(void *const *array, int size, int fd);

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  LW_CFG_POSIX_EN > 0         */
                                                                        /*  LW_CFG_MODULELOADER_EN > 0  */
#endif                                                                  /*  __PX_EXECINFO_H             */
/*********************************************************************************************************
  END
*********************************************************************************************************/
