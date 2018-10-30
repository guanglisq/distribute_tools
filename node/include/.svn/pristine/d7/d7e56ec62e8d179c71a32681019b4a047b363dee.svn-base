/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月17日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosRpcStreamer.h
 * @author  Zuolong
 *
 * @brief   XMLRPC streamer functions.
 */

#ifndef _REROSRPCSTREAMER_H_
#define _REROSRPCSTREAMER_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"
#include "rerosConn.h"
#include "rerosRpcCall.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/**
 * @brief  Use the <tt>\<string\></tt> tag for string values.
 */
#if !defined(REROS_RPCSTREAMER_USE_STRING_TAG) || defined(__DOXYGEN__)
#define REROS_RPCSTREAMER_USE_STRING_TAG     REROS_FALSE
#endif

/** @addtogroup rpc_types */
/** @{ */

/**
 * @brief   XMLRPC streamer object.
 */
typedef struct RerosRpcStreamer {
  reros_err_t    err;        /**< @brief Last error message.*/
  RerosConn      *csp;       /**< @brief Connection status.*/
  char          *bufp;      /**< @brief Pointer to the refill buffer.*/
  size_t        buflen;     /**< @brief Refill buffer length.*/
  char          *curp;      /**< @brief Current parsing pointer.*/
  size_t        free;       /**< @brief Remaining free buffer characters.*/
  size_t        total;      /**< @brief Total streamed characters counter.*/
  size_t        mark;       /**< @brief Position mark, for user purposes.*/
  reros_bool_t   chunked;    /**< @brief Use HTTP chunked Transfer-Encoding.*/
} RerosRpcStreamer;

/** @} */

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosRpcStreamerObjectInit(RerosRpcStreamer *sp,
                               RerosConn *csp,
                               char *bufp, size_t buflen);
void rerosRpcStreamerClean(RerosRpcStreamer *sp, reros_bool_t freeBuffer);
reros_err_t rerosRpcStreamerFlush(RerosRpcStreamer *sp);
reros_err_t rerosRpcStreamerWrite(RerosRpcStreamer *sp,
                                const void *chunkp, size_t chunklen);
reros_err_t rerosRpcStreamerUint32(RerosRpcStreamer *sp, uint32_t value);
reros_err_t rerosRpcStreamerInt32(RerosRpcStreamer *sp, int32_t value);
reros_err_t rerosRpcStreamerIp(RerosRpcStreamer *sp, RerosIp ip);
reros_err_t rerosRpcStreamerHttpPost(RerosRpcStreamer *sp);
reros_err_t rerosRpcStreamerHttpStatus(RerosRpcStreamer *sp, uint32_t code);
reros_err_t rerosRpcStreamerHttpHeader(RerosRpcStreamer *sp,
                                     const char *keyp, size_t keylen,
                                     const char *valp, size_t vallen);
reros_err_t rerosRpcStreamerHttpEnd(RerosRpcStreamer *sp);
reros_err_t rerosRpcStreamerHttpContentLength(RerosRpcStreamer *sp);
reros_err_t rerosRpcStreamerXmlEndHack(RerosRpcStreamer *sp);

reros_err_t rerosRpcStreamerXmlAttrWVal(RerosRpcStreamer *sp,
                                      const char *namep, size_t namelen,
                                      const char *valp, size_t vallen,
                                      const char quotec);
reros_err_t rerosRpcStreamerXmlTagBegin(RerosRpcStreamer *sp,
                                      const char *tagp, size_t taglen);
reros_err_t rerosRpcStreamerXmlTagEnd(RerosRpcStreamer *sp);
reros_err_t rerosRpcStreamerXmlTagSlashEnd(RerosRpcStreamer *sp);
reros_err_t rerosRpcStreamerXmlTagOpen(RerosRpcStreamer *sp,
                                     const char *tagp, size_t taglen);
reros_err_t rerosRpcStreamerXmlTagClose(RerosRpcStreamer *sp,
                                      const char *tagp, size_t taglen);
reros_err_t rerosRpcStreamerXmlHeader(RerosRpcStreamer *sp);

reros_err_t rerosRpcStreamerParamValueInt(RerosRpcStreamer *sp,
                                        const RerosRpcParam *paramp);
reros_err_t rerosRpcStreamerParamValueBoolean(RerosRpcStreamer *sp,
                                            const RerosRpcParam *paramp);
reros_err_t rerosRpcStreamerParamValueString(RerosRpcStreamer *sp,
                                           const RerosRpcParam *paramp);
reros_err_t rerosRpcStreamerParamValueDouble(RerosRpcStreamer *sp,
                                           const RerosRpcParam *paramp);
reros_err_t rerosRpcStreamerParamValueBase64(RerosRpcStreamer *sp,
                                           const RerosRpcParam *paramp);
reros_err_t rerosRpcStreamerParamValueStruct(RerosRpcStreamer *sp,
                                           const RerosRpcParam *paramp);
reros_err_t rerosRpcStreamerParamValueArray(RerosRpcStreamer *sp,
                                          const RerosRpcParam *paramp);
reros_err_t rerosRpcStreamerParam(RerosRpcStreamer *sp,
                                const RerosRpcParam *paramp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSRPCSTREAMER_H_ */
