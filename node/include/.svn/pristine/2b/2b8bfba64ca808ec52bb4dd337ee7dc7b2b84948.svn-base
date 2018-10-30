/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月17日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosRpcParser.h
 * @author  Zuolong
 *
 * @brief   XMLRPC parser methods.
 */

#ifndef _REROSRPCPARSER_H_
#define _REROSRPCPARSER_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"
#include "rerosConn.h"
#include "rerosRpcCall.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup rpc_types */
/** @{ */

/**
 * @brief   XMLRPC parser object.
 */
typedef struct RerosRpcParser {
  reros_err_t    err;            /**< @brief Last error message.*/
  RerosConn      *csp;           /**< @brief Connection status.*/
  char          *rdbufp;        /**< @brief Reading buffer pointer.*/
  size_t        rdbuflen;       /**< @brief Reading buffer length.*/
  char          *curp;          /**< @brief Current parsing pointer.*/
  size_t        pending;        /**< @brief Remaining buffer characters to be parsed.*/
  size_t        total;          /**< @brief Parsed characters counter.*/
  size_t        mark;           /**< @brief Position mark, for user purposes.*/
  char          *bufp;          /**< @brief Pointer to the refill buffer.*/
  size_t        buflen;         /**< @brief Refill buffer length.*/
  size_t        contentLength;  /**< @brief Content-Length of XMLRPC message.*/
} RerosRpcParser;

/** @} */

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosRpcParserObjectInit(RerosRpcParser *pp,
                             RerosConn *csp,
                             char *rdbufp, size_t rdbuflen);
void rerosRpcParserClean(RerosRpcParser *pp, reros_bool_t freeBuffer);
reros_err_t rerosRpcParserRefill(RerosRpcParser *pp);
reros_err_t rerosRpcParserRead(RerosRpcParser *pp,
                             void *chunkp, size_t chunklen);
reros_err_t rerosRpcParserExpect(RerosRpcParser *pp,
                               const char *tokp, size_t toklen);
reros_err_t rerosRpcParserExpectQuiet(RerosRpcParser *pp,
                                    const char *tokp, size_t toklen);
reros_err_t rerosRpcParserExpectNoCase(RerosRpcParser *pp,
                                     const char *tokp, size_t toklen);
reros_err_t rerosRpcParserExpectNoCaseQuiet(RerosRpcParser *pp,
                                         const char *tokp, size_t toklen);
reros_err_t rerosRpcParserLookAhead(RerosRpcParser *pp, char c);
reros_err_t rerosRpcParserLookAheadQuiet(RerosRpcParser *pp, char c);
reros_err_t rerosRpcParserSkipUntil(RerosRpcParser *pp, char c);
reros_err_t rerosRpcParserSkip(RerosRpcParser *pp, size_t length);
reros_err_t rerosRpcParserSkipAfter(RerosRpcParser *pp,
                                  const char *tokp, size_t toklen);
reros_err_t rerosRpcParserSkipWs(RerosRpcParser *pp);
reros_err_t rerosRpcParserExpectWs(RerosRpcParser *pp);
reros_err_t rerosRpcParserUint32(RerosRpcParser *pp, uint32_t *valuep);
reros_err_t rerosRpcParserInt32(RerosRpcParser *pp, int32_t *valuep);
reros_err_t rerosRpcParserDouble(RerosRpcParser *pp, double *valuep);
reros_err_t rerosRpcParserFixStringChars(RerosString *strp);

reros_err_t rerosRpcParserHttpRequest(RerosRpcParser *pp);
reros_err_t rerosRpcParserHttpResponse(RerosRpcParser *pp, uint32_t *codep);

reros_err_t rerosRpcParserXmlAttrWVal(RerosRpcParser *pp,
                                    const char *namep, size_t namelen,
                                    const char *valp, size_t vallen);
reros_err_t rerosRpcParserXmlTagBeginNoName(RerosRpcParser *pp);
reros_err_t rerosRpcParserXmlTagBegin(RerosRpcParser *pp,
                                    const char *tagp, size_t taglen);
reros_err_t rerosRpcParserXmlTagEnd(RerosRpcParser *pp);
reros_err_t rerosRpcParserXmlTagSlashEnd(RerosRpcParser *pp);
reros_err_t rerosRpcParserXmlTagOpen(RerosRpcParser *pp,
                                   const char *tagp, size_t taglen);
reros_err_t rerosRpcParserXmlTagClose(RerosRpcParser *pp,
                                    const char *tagp, size_t taglen);
reros_err_t rerosRpcParserXmlHeader(RerosRpcParser *pp);

reros_err_t rerosRpcParserParamValueInt(RerosRpcParser *pp,
                                      RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamValueBoolean(RerosRpcParser *pp,
                                          RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamValueString(RerosRpcParser *pp,
                                         RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamValueDouble(RerosRpcParser *pp,
                                         RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamValueBase64(RerosRpcParser *pp,
                                         RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamValueStruct(RerosRpcParser *pp,
                                         RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamValueArray(RerosRpcParser *pp,
                                        RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamByTag(RerosRpcParser *pp,
                                   RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamByTagQuiet(RerosRpcParser *pp,
                                       RerosRpcParam *paramp);
reros_err_t rerosRpcParserParamByClass(RerosRpcParser *pp,
                                     RerosRpcParam *paramp);
reros_err_t rerosRpcParserParam(RerosRpcParser *pp,
                              RerosRpcParam *paramp,
                              reros_rpcparamclass_t paramclass);

reros_err_t rerosRpcParserMethodResponse(RerosRpcParser *pp,
                                       RerosRpcResponse *resp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSRPCPARSER_H_ */
