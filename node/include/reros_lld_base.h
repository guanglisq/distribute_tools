/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2016年1月11日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    reros_lld_base.h
 * @author  Zuolong
 *
 * @brief   Low-level basic features of the middleware.
 */

#ifndef _REROS_LLD_BASE_H_
#define _REROS_LLD_BASE_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void reros_lld_init(void);
void *reros_lld_alloc(RerosMemHeap *heapp, size_t size);
void reros_lld_free(void *chunkp);

#if REROS_USE_BUILTIN_MEMPOOL == REROS_FALSE
void reros_lld_mempool_objectinit(RerosMemPool *poolp, size_t blocksize,
                                 reros_alloc_f provider);
void *reros_lld_mempool_alloc(RerosMemPool *poolp);
void reros_lld_mempool_free(RerosMemPool *poolp, void *objp);
reros_cnt_t reros_lld_mempool_numfree(RerosMemPool *poolp);
void reros_lld_mempool_loadarray(RerosMemPool *poolp,
                                void *objp, reros_cnt_t n);
size_t reros_lld_mempool_blocksize(RerosMemPool *poolp);
#endif /* REROS_USE_BUILTIN_MEMPOOL == REROS_FALSE */

#ifdef __cplusplus
}
#endif
#endif /* _REROS_LLD_BASE_H_ */
