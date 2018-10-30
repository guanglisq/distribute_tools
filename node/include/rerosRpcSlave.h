/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月17日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosRpcSlave.h
 * @author  Zuolong
 *
 * @brief   XMLRPC Slave API functions.
 */

#ifndef _REROSSLAVE_H_
#define _REROSSLAVE_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"
#include "rerosRpcCall.h"
#include "rerosTcpRos.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup rpc_types */
/** @{ */

/**
 * @brief   XMLRPC Slave API methods.
 */
typedef enum reros_rpcslave_methodid_t {

  REROS_RPCSM_GET_BUS_INFO,      /**< @brief @p getBusInfo() command.*/
  REROS_RPCSM_GET_BUS_STATS,     /**< @brief @p getBusStatus() command.*/
  REROS_RPCSM_GET_MASTER_URI,    /**< @brief @p getMasterUri() command.*/
  REROS_RPCSM_GET_PID,           /**< @brief @p getPid() command.*/
  REROS_RPCSM_GET_PUBLICATIONS,  /**< @brief @p getPublications() command.*/
  REROS_RPCSM_GET_SUBSCRIPTIONS, /**< @brief @p getSubscriptions() command.*/
  REROS_RPCSM_PARAM_UPDATE,      /**< @brief @p paramUpdate() command.*/
  REROS_RPCSM_PUBLISHER_UPDATE,  /**< @brief @p publisherUpdate() command.*/
  REROS_RPCSM_REQUEST_TOPIC,     /**< @brief @p requestTopic() command.*/
  REROS_RPCSM_SHUTDOWN,          /**< @brief @p shutdown() command.*/

  REROS_RPCSM__LENGTH
} reros_rpcslave_methodid_t;

/** @} */

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

reros_err_t rerosRpcSlaveConnectToPublishers(const RerosString *topicp,
                                           const RerosList *addrlstp);
reros_err_t rerosRpcSlaveListenerThread(void *data);
reros_err_t rerosRpcSlaveServerThread(RerosConn *csp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSSLAVE_H_ */
