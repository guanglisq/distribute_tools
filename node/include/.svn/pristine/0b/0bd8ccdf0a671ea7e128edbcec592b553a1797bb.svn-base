/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月16日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosNode.h
 * @author  Zuolong
 *
 * @brief   Node features of the middleware.
 */

#ifndef _REROSNODE_H_
#define _REROSNODE_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"
#include "rerosThreading.h"
#include "rerosTcpRos.h"
#include "rerosRpcSlave.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup node_macros */
/** @{ */

/** @brief Enables a periodic check of the Master node reachability.*/
#if !defined(REROS_NODE_POLL_MASTER) || defined(__DOXYGEN__)
#define REROS_NODE_POLL_MASTER       REROS_FALSE
#endif

/** @brief Exit condition polling period, in milliseconds.*/
#if !defined(REROS_NODE_POLL_PERIOD) || defined(__DOXYGEN__)
#define REROS_NODE_POLL_PERIOD       2000
#endif

/** @} */

/** @addtogroup node_types */
/** @{ */

/**
 * @brief   Node states.
 */
typedef enum reros_nodestate_t {
  REROS_NODE_UNINIT = 0,                 /**< @brief Node is uninitialized.*/
  REROS_NODE_IDLE,                       /**< @brief Node is stopped.*/
  REROS_NODE_STARTUP,                    /**< @brief Startup sequence.*/
  REROS_NODE_RUNNING,                    /**< @brief Node is running.*/
  REROS_NODE_SHUTDOWN                    /**< @brief Shutdown sequence.*/
} reros_nodestate_t;

/**
 * @brief   Node configuration descriptor.
 */
typedef struct RerosNodeConfig {
  /* Local node settings.*/
  RerosString        nodeName;           /**< @brief Node name.*/
  RerosAddr          xmlrpcAddr;         /**< @brief XMLRPC Listener address.*/
  RerosString        xmlrpcUri;          /**< @brief XMLRPC Listener URI.*/
  RerosAddr          tcprosAddr;         /**< @brief TCPROS Listener address.*/
  RerosString        tcprosUri;          /**< @brief TCPROS Listener URI.*/

  /* Master (remote) settings.*/
  RerosAddr          masterAddr;         /**< @brief ROS Master XMLRPC server address.*/
  RerosString        masterUri;          /**< @brief ROS Master XMLRPC server URI.*/
} RerosNodeConfig;

/**
 * @brief   Node status record.
 */
typedef struct RerosNodeStatus {
  /* Status variables.*/
  reros_nodestate_t  state;              /**< @brief Current node state.*/
  int32_t           xmlrpcPid;          /**< @brief PID of the XMLRPC Listener process.*/
  RerosList          subTopicList;       /**< @brief List of subscribed topics.*/
  RerosList          pubTopicList;       /**< @brief List of published topics.*/
  RerosList          pubServiceList;     /**< @brief List of published services.*/
  RerosList          subParamList;       /**< @brief List of parameter subscriptions.*/
  RerosList          subTcpList;         /**< @brief Subscribed TCPROS connections.*/
  RerosList          pubTcpList;         /**< @brief Published TCPROS connections.*/

  RerosMutex         stateLock;          /**< @brief State and exit lock.*/
  RerosMutex         xmlrpcPidLock;      /**< @brief PID lock.*/
  RerosMutex         subTopicListLock;   /**< @brief Topic subscriptions lock.*/
  RerosMutex         pubTopicListLock;   /**< @brief Topic publications lock.*/
  RerosMutex         pubServiceListLock; /**< @brief Publisher connections lock.*/
  RerosMutex         subParamListLock;   /**< @brief Parameter subscriptions lock.*/
  RerosMutex         subTcpListLock;     /**< @brief Subscribed connections lock.*/
  RerosMutex         pubTcpListLock;     /**< @brief Published connections lock.*/

  /* Threads stuff.*/
  RerosMemPool       tcpcliMemPool;      /**< @brief TCPROS Client worker stack pool.*/
  RerosMemPool       tcpsvrMemPool;      /**< @brief TCPROS Server worker stack pool.*/
  RerosMemPool       slaveMemPool;       /**< @brief XMLRPC Slave worker stack pool.*/
  RerosThreadPool    tcpcliThdPool;      /**< @brief TCPROS Client worker thread pool.*/
  RerosThreadPool    tcpsvrThdPool;      /**< @brief TCPROS Server worker thread pool.*/
  RerosThreadPool    slaveThdPool;       /**< @brief XMLRPC Slave worker thread pool.*/
  RerosThreadId      xmlrpcListenerId;   /**< @brief XMLRPC Listener thread id.*/
  RerosThreadId      tcprosListenerId;   /**< @brief TCPROS Listener thread id.*/
  RerosThreadId      nodeThreadId;       /**< @brief Node thread id.*/
  reros_bool_t       exitFlag;           /**< @brief Thread exit flag.*/
  RerosString        exitMsg;            /**< @brief Exit message string.*/
} RerosNodeStatus;

/**
 * @brief   Node object.
 */
typedef struct RerosNode {
  const RerosNodeConfig  config;         /**< @brief Node configuration (loaded at boot time).*/
  RerosNodeStatus        status;         /**< @brief Node status.*/
} RerosNode;

/** @} */

/*===========================================================================*/
/* GLOBAL VARIABLES                                                          */
/*===========================================================================*/

extern RerosNode rerosNode;

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosNodeObjectInit(RerosNode *np);
reros_err_t rerosNodeCreateThread(void);
reros_err_t rerosNodeThread(void *argp);

void rerosNodeConfigLoadDefaults(RerosNodeConfig *cfgp);

reros_err_t rerosNodePublishTopic(const RerosString *namep,
                                const RerosString *typep,
                                reros_proc_f procf,
                                reros_topicflags_t flags);
reros_err_t rerosNodePublishTopicSZ(const char *namep,
                                  const char *typep,
                                  reros_proc_f procf,
                                  reros_topicflags_t flags);
reros_err_t rerosNodePublishTopicByDesc(RerosTopic *topicp);
reros_err_t rerosNodeUnpublishTopic(const RerosString *namep);
reros_err_t rerosNodeUnpublishTopicSZ(const char *namep);

reros_err_t rerosNodeSubscribeTopic(const RerosString *namep,
                                  const RerosString *typep,
                                  reros_proc_f procf,
                                  reros_topicflags_t flags);
reros_err_t rerosNodeSubscribeTopicSZ(const char *namep,
                                    const char *typep,
                                    reros_proc_f procf,
                                    reros_topicflags_t flags);
reros_err_t rerosNodeSubscribeTopicByDesc(RerosTopic *topicp);
reros_err_t rerosNodeUnsubscribeTopic(const RerosString *namep);
reros_err_t rerosNodeUnsubscribeTopicSZ(const char *namep);

reros_err_t rerosNodeCallService(const RerosString *namep,
                               const RerosString *typep,
                               reros_tcpsrvcall_t callf,
                               reros_topicflags_t flags,
                               void *reqobjp,
                               void *resobjp);
reros_err_t rerosNodeCallServiceSZ(const char *namep,
                                 const char *typep,
                                 reros_tcpsrvcall_t callf,
                                 reros_topicflags_t flags,
                                 void *reqobjp,
                                 void *resobjp);
reros_err_t rerosNodeCallServiceByDesc(const RerosTopic *servicep,
                                     void *reqobjp,
                                     void *resobjp);

reros_err_t rerosNodePublishService(const RerosString *namep,
                                  const RerosString *typep,
                                  reros_proc_f procf,
                                  reros_topicflags_t flags);
reros_err_t rerosNodePublishServiceSZ(const char *namep,
                                    const char *typep,
                                    reros_proc_f procf,
                                    reros_topicflags_t flags);
reros_err_t rerosNodePublishServiceByDesc(const RerosTopic *servicep);
reros_err_t rerosNodeUnpublishService(const RerosString *namep);
reros_err_t rerosNodeUnpublishServiceSZ(const char *namep);

reros_err_t rerosNodeSubscribeParam(const RerosString *namep);
reros_err_t rerosNodeSubscribeParamSZ(const char *namep);
reros_err_t rerosNodeUnsubscribeParam(const RerosString *namep);
reros_err_t rerosNodeUnsubscribeParamSZ(const char *namep);

reros_err_t rerosNodeFindNewTopicPublishers(const RerosString *topicnamep,
                                          const RerosRpcParam *publishersp,
                                          RerosList *newpubsp);
reros_err_t rerosNodeResolveTopicPublisher(const RerosAddr *apiaddrp,
                                         const RerosString *namep,
                                         RerosAddr *tcprosaddrp);
reros_err_t rerosNodeResolveServicePublisher(const RerosString *namep,
                                           RerosAddr *pubaddrp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSNODE_H_ */
