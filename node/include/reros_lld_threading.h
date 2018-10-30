/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2016年1月11日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    reros_lld_threading.h
 * @author  Zuolong
 *
 * @brief   Low-level threading features of the middleware.
 */

#ifndef _REROS_LLD_THREADING_H_
#define _REROS_LLD_THREADING_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosThreading.h"

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void reros_lld_sem_objectinit(RerosSem *semp, reros_cnt_t n);
void reros_lld_sem_clean(RerosSem *semp);
void reros_lld_sem_wait(RerosSem *semp);
void reros_lld_sem_signal(RerosSem *semp);
reros_cnt_t reros_lld_sem_value(RerosSem *semp);

void reros_lld_mutex_objectinit(RerosMutex *mtxp);
void reros_lld_mutex_clean(RerosMutex *mtxp);
void reros_lld_mutex_lock(RerosMutex *mtxp);
void reros_lld_mutex_unlock(RerosMutex *mtxp);

void reros_lld_condvar_objectinit(RerosCondVar *cvp);
void reros_lld_condvar_clean(RerosCondVar *cvp);
void reros_lld_condvar_wait(RerosCondVar *cvp, RerosMutex *mtxp);
void reros_lld_condvar_signal(RerosCondVar *cvp);
void reros_lld_condvar_broadcast(RerosCondVar *cvp);

RerosThreadId reros_lld_thread_self(void);
const char *reros_lld_thread_getname(RerosThreadId id);
reros_err_t reros_lld_thread_createstatic(RerosThreadId *idp, const char *namep,
                                        reros_prio_t priority,
                                        reros_proc_f routine, void *argp,
                                        void *stackp, size_t stacksize);
reros_err_t reros_lld_thread_createfrommempool(RerosThreadId *idp, const char *namep,
                                             reros_prio_t priority,
                                             reros_proc_f routine, void *argp,
                                             RerosMemPool *mempoolp);
reros_err_t reros_lld_thread_createfromheap(RerosThreadId *idp, const char *namep,
                                          reros_prio_t priority,
                                          reros_proc_f routine, void *argp,
                                          size_t stacksize);
reros_err_t reros_lld_thread_join(RerosThreadId id);
void reros_lld_thread_sleepsec(uint32_t sec);
void reros_lld_thread_sleepmsec(uint32_t msec);
void reros_lld_thread_sleepusec(uint32_t usec);

uint32_t reros_lld_threading_gettimestampmsec(void);

RerosSemphore * reros_lld_semphore_open(char * semname);
int reros_lld_semphore_wait(RerosSemphore * semp);
int reros_lld_semphore_post(RerosSemphore * semp);
int reros_lld_semphore_flush(RerosSemphore * semp);
int reros_lld_semphore_destroy(RerosSemphore ** sempp);
int reros_lld_semphore_unlink(char *semname);


#ifdef __cplusplus
}
#endif
#endif /* _REROS_LLD_THREADING_H_ */
