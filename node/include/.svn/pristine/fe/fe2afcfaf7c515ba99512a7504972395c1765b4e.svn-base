/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月16日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosThreading.h
 * @author  Zuolong
 *
 * @brief   Threading features of the middleware.
 */

#ifndef _REROSTHREADING_H_
#define _REROSTHREADING_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup threading_types */
/** @{ */

/**
 * @brief   Thread pool object.
 */
typedef struct RerosThreadPool {
  RerosMemPool   *stackPoolp;    /**< @brief Memory pool for thread stacks.*/
  reros_cnt_t    size;           /**< @brief Thread pool size.*/
  reros_proc_f   routine;        /**< @brief User routine for children.*/
  const char    *namep;         /**< @brief Default thread name.*/
  reros_prio_t   priority;       /**< @brief Default thread priority.*/
  RerosThreadId  *threadsp;      /**< @brief Thread identifier array.*/
  void          *argp;          /**< @brief Next thread argument pointer.*/
  reros_cnt_t    readyCnt;       /**< @brief Ready threads counter.*/
  RerosMutex     readyMtx;       /**< @brief Ready threads mutex.*/
  RerosCondVar   readyCond;      /**< @brief Ready threads condvar.*/
  reros_cnt_t    busyCnt;        /**< @brief Busy threads counter.*/
  RerosMutex     busyMtx;        /**< @brief Busy threads mutex.*/
  RerosCondVar   busyCond;       /**< @brief Busy threads condvar.*/
  reros_bool_t   exitFlag;       /**< @brief Exit request flag, broadcast.*/
} RerosThreadPool;

/** @} */

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosSemObjectInit(RerosSem *semp, reros_cnt_t n);
void rerosSemClean(RerosSem *semp);
void rerosSemWait(RerosSem *semp);
void rerosSemSignal(RerosSem *semp);

void rerosMutexObjectInit(RerosMutex *mtxp);
void rerosMutexClean(RerosMutex *mtxp);
void rerosMutexLock(RerosMutex *mtxp);
void rerosMutexUnlock(RerosMutex *mtxp);

void rerosCondVarObjectInit(RerosCondVar *cvp);
void rerosCondVarClean(RerosCondVar *cvp);
void rerosCondVarWait(RerosCondVar *cvp, RerosMutex *mtxp);
void rerosCondVarSignal(RerosCondVar *cvp);
void rerosCondVarBroadcast(RerosCondVar *cvp);

reros_err_t rerosThreadPoolObjectInit(RerosThreadPool *poolp,
                                    RerosMemPool *stackpoolp,
                                    reros_proc_f routine,
                                    const char *namep,
                                    reros_prio_t priority);
void rerosThreadPoolClean(RerosThreadPool *poolp);
reros_err_t rerosThreadPoolCreateAll(RerosThreadPool *poolp);
reros_err_t rerosThreadPoolJoinAll(RerosThreadPool *poolp);
reros_err_t rerosThreadPoolStartWorker(RerosThreadPool *poolp, void *argp);
reros_err_t rerosThreadPoolWorkerThread(RerosThreadPool *poolp);

RerosThreadId rerosThreadSelf(void);
const char *rerosThreadGetName(RerosThreadId id);
reros_err_t rerosThreadCreateStatic(RerosThreadId *idp, const char *namep,
                                  reros_prio_t priority,
                                  reros_proc_f routine, void *argp,
                                  void *stackp, size_t stacksize);
reros_err_t rerosThreadCreateFromMemPool(RerosThreadId *threadp, const char *namep,
                                       reros_prio_t priority,
                                       reros_proc_f routine, void *argp,
                                       RerosMemPool *mempoolp);
reros_err_t rerosThreadCreateFromHeap(RerosThreadId *idp, const char *namep,
                                    reros_prio_t priority,
                                    reros_proc_f routine, void *argp,
                                    size_t stacksize);
reros_err_t rerosThreadJoin(RerosThreadId id);
void rerosThreadSleepSec(uint32_t sec);
void rerosThreadSleepMsec(uint32_t msec);
void rerosThreadSleepUsec(uint32_t usec);

uint32_t rerosGetTimestampMsec(void);

RerosSemphore * rerosSemphoreOpen(char * semname);
int rerosSemphoreWait(RerosSemphore * semp);
int rerosSemphorePost(RerosSemphore * semp);
int rerosSemphoreFlush(RerosSemphore * semp);
int rerosSemphoreDestroy(RerosSemphore ** semp);
int rerosSemphoreUnlink(char *semname);

#ifdef __cplusplus
}
#endif
#endif /* _REROSTHREADING_H_ */
