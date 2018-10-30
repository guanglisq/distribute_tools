/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月17日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosRpcCall.h
 * @author  Zuolong
 *
 * @brief   XMLRPC call functions.
 */

#ifndef _REROSRPC_H_
#define _REROSRPC_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"
#include "rerosConn.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup rpc_types */
/** @{ */

/**
 * @brief   XMLRPC status code.
 */
enum reros_rpccode_t {
  REROS_RPCC_ERROR       = -1,   /**< @brief Caller error, action not executed.*/
  REROS_RPCC_FAILURE     =  0,   /**< @brief Method error, possible side effects.*/
  REROS_RPCC_SUCCESS     =  1    /**< @brief Method completed successfully.*/
};

/**
 * @brief   XMLRPC parameter pclass id.
 */
typedef enum reros_rpcparamclass_t {

  REROS_RPCP_INT,                /**< @brief Signed 32-bits value.*/
  REROS_RPCP_BOOLEAN,            /**< @brief Boolean value (either @p 1 or @p 0).*/
  REROS_RPCP_STRING,             /**< @brief String value.*/
  REROS_RPCP_DOUBLE,             /**< @brief Double-precision floating point value.*/
  REROS_RPCP_BASE64,             /**< @brief Base64 data.*/
  REROS_RPCP_STRUCT,             /**< @brief Associative map.*/
  REROS_RPCP_ARRAY,              /**< @brief Generic array.*/

  REROS_RPCP__LENGTH
} reros_rpcparamclass_t;

struct reros_rpcparamlist_t;
/**
 * @brief   XMLRPC parameter value.
 * @details
 */
typedef struct RerosRpcParam {
  reros_rpcparamclass_t      pclass;      /**< @brief Parameter pclass.*/
  union {
    RerosString              string;     /**< @brief XMLRPC string.*/
    int32_t                 int32;      /**< @brief XMLRPC int/i4.*/
    reros_bool_t             boolean;    /**< @brief XMLRPC boolean.*/
    double                  real;       /**< @brief XMLRPC double.*/
    RerosString              base64;     /**< @brief XMLRPC base64.*/
    void                    *mapp;      /**< @brief XMLRPC struct (map pointer).*/ /* TODO */
    struct RerosRpcParamList *listp;     /**< @brief XMLRPC array (list pointer).*/
  }                         value;      /**< @brief Parameter value.*/
} RerosRpcParam;

/**
 * @brief   Parameter list node, forward only.
 */
typedef struct RerosRpcParamNode {
  RerosRpcParam              param;      /**< @brief Parameter value.*/
  struct RerosRpcParamNode   *nextp;     /**< @brief Pointer to the next node.*/
} RerosRpcParamNode;

/**
 * @brief   Parameter list, double ended.
 */
typedef struct RerosRpcParamList {
  RerosRpcParamNode  *headp;         /**< @brief Pointer to the first parameter.*/
  RerosRpcParamNode  *tailp;         /**< @brief Pointer to the last parameter.*/
  reros_cnt_t        length;         /**< @brief Number of list elements.*/
} RerosRpcParamList;

/**
 * @brief   XMLRPC call response object.
 */
typedef struct RerosRpcResponse {
  uint32_t          httpcode;       /**< @brief HTTP status code.*/
  int32_t           code;           /**< @brief Response code (@see @p REROS_RPCC_*).*/
  RerosString        *statusMsgp;    /**< @brief Status message.*/
  RerosRpcParam      *valuep;        /**< @brief Response value.*/
} RerosRpcResponse;

/** @} */

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosRpcParamClean(RerosRpcParam *paramp, reros_bool_t deep);
void rerosRpcParamDelete(RerosRpcParam *paramp, reros_bool_t deep);
void rerosRpcParamObjectInit(RerosRpcParam *paramp,
                            reros_rpcparamclass_t pclass);

void rerosRpcParamNodeClean(RerosRpcParamNode *nodep, reros_bool_t deep);
void rerosRpcParamNodeDelete(RerosRpcParamNode *nodep, reros_bool_t deep);
void rerosRpcParamNodeObjectInit(RerosRpcParamNode *nodep,
                                reros_rpcparamclass_t pclass);

void rerosRpcParamListClean(RerosRpcParamList *listp, reros_bool_t deep);
void rerosRpcParamListDelete(RerosRpcParamList *listp, reros_bool_t deep);
void rerosRpcParamListObjectInit(RerosRpcParamList *listp);
void rerosRpcParamListAppendNode(RerosRpcParamList *listp,
                                RerosRpcParamNode *nodep);
RerosRpcParamNode *rerosRpcParamListUnlinkNode(RerosRpcParamList *listp,
                                             RerosRpcParamNode *nodep);

void rerosRpcResponseObjectInit(RerosRpcResponse *rp);
void rerosRpcResponseClean(RerosRpcResponse *rp);

reros_err_t rerosRpcCallRegisterService(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *service,
  const RerosString      *service_api,
  const RerosString      *caller_api,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallUnregisterService(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *service,
  const RerosString      *service_api,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallRegisterSubscriber(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *topic,
  const RerosString      *topic_type,
  const RerosString      *caller_api,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallUnregisterSubscriber(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *topic,
  const RerosString      *caller_api,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallRegisterPublisher(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *topic,
  const RerosString      *topic_type,
  const RerosString      *caller_api,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallUnregisterPublisher(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *topic,
  const RerosString      *caller_api,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallLookupNode(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *node,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetPublishedTopics(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *subgraph,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetTopicTypes(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetSystemState(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetUri(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallLookupService(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *service,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallDeleteParam(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *key,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallSetParam(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *key,
  const RerosRpcParam    *value,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetParam(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *key,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallSearchParam(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *key,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallSubscribeParam(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *caller_api,
  const RerosString      *key,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallUnsubscribeParam(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *caller_api,
  const RerosString      *key,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallHasParam(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *key,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetParamNames(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetBusStats(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetBusInfo(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetMasterUri(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallShutdown(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *msg,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetPid(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetSubscriptions(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallGetPublications(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallParamUpdate(
  const RerosAddr        *addrp,
  const RerosString      *caller_id,
  const RerosString      *parameter_key,
  const RerosRpcParam    *parameter_value,
  RerosRpcResponse       *resp);
reros_err_t rerosRpcCallPublisherUpdate(
  const RerosAddr            *addrp,
  const RerosString          *caller_id,
  const RerosString          *topic,
  const RerosRpcParamList    *publishers,
  RerosRpcResponse           *resp);
reros_err_t rerosRpcCallRequestTopic(
  const RerosAddr            *addrp,
  const RerosString          *caller_id,
  const RerosString          *topic,
  const RerosRpcParamList    *protocols,
  RerosRpcResponse           *resp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSRPC_H_ */
