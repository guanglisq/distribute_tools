/*
Copyright (c) 2015-2016, CETC32. All rights reserved.

Zuo Long <asdzuo@qq.com>
Hubing   <hubinghank@163.com>
*/

/**
 * @file    rerosParaConfig.h
 * @author  LiGuang
 *
 * @brief   parameter descriptors.
 */

#ifndef _REROSPARACONFIG_H_
#define _REROSPARACONFIG_H_

#include <rerosHandlers.h>
#include <rerosUser.h>

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @brief ROS node name, C string.*/
#define NODE_NAME  "/Node0"

/** @brief Master server IP address, little-endian dword.*/
#define XMLRPC_MASTER_IP   rerosIpDword(192 ,168 ,1 ,107)

/** @brief Master server IP address, C string.*/
#define XMLRPC_MASTER_IP_SZ  "192.168.1.107"

/** @brief Master server port.*/
#define XMLRPC_MASTER_PORT  11311

/** @brief XMLRPC listener IP address, little-endian dword.*/
#define XMLRPC_LISTENER_IP   rerosIpDword(192 ,168 ,1 ,107)

/** @brief XMLRPC listener IP address, C string.*/
#define XMLRPC_LISTENER_IP_SZ          "192.168.1.107"

/** @brief XMLRPC listener port.*/
#define XMLRPC_LISTENER_PORT  110

/** @brief TCPROS listener IP address, little-endian dword.*/
#define TCPROS_LISTENER_IP             XMLRPC_LISTENER_IP

/** @brief TCPROS listener IP address, C string.*/
#define TCPROS_LISTENER_IP_SZ          XMLRPC_LISTENER_IP_SZ

/** @brief TCPROS listener port.*/
#define TCPROS_LISTENER_PORT  120

/*===========================================================================*/
/* LOCAL FUNCTIONS                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* GLOBAL FUNCTIONS                                                          */
/*===========================================================================*/

/**
 * @brief   Loads node configuration.
 * @details Any previously allocated data is freed, then the configuration is
 *          loaded from a static non-volatile memory chunk.
 * @see     reros_lld_nodeconfig_load()
 *
 * @pre     The related @p RerosNode is initialized.
 * 
 * @param[in,out] cfgp
 *          Pointer to the target configuration descriptor.
 */
void rerosUserNodeConfigLoad(RerosNodeConfig *cfgp) {

  rerosAssert(cfgp != NULL);

  /* Clean any allocated variables.*/
  rerosStringClean(&cfgp->nodeName);
  rerosStringClean(&cfgp->xmlrpcUri);
  rerosStringClean(&cfgp->tcprosUri);
  rerosStringClean(&cfgp->masterUri);

  rerosAssert(XMLRPC_LISTENER_PORT != TCPROS_LISTENER_PORT);
  cfgp->nodeName = rerosStringCloneZ(NODE_NAME);
  cfgp->xmlrpcAddr.ip.dword = XMLRPC_LISTENER_IP;
  cfgp->xmlrpcAddr.port = XMLRPC_LISTENER_PORT;
  cfgp->xmlrpcUri = rerosStringCloneZ(
    "http://"XMLRPC_LISTENER_IP_SZ
    ":"REROS_STRINGIFY2(XMLRPC_LISTENER_PORT));
  cfgp->tcprosAddr.ip.dword = TCPROS_LISTENER_IP;
  cfgp->tcprosAddr.port = TCPROS_LISTENER_PORT;
  cfgp->tcprosUri = rerosStringCloneZ(
    "rosrpc://"TCPROS_LISTENER_IP_SZ
    ":"REROS_STRINGIFY2(TCPROS_LISTENER_PORT));
  cfgp->masterAddr.ip.dword = XMLRPC_MASTER_IP;
  cfgp->masterAddr.port = XMLRPC_MASTER_PORT;
  cfgp->masterUri = rerosStringCloneZ(
    "http://"XMLRPC_MASTER_IP_SZ
    ":"REROS_STRINGIFY2(XMLRPC_MASTER_PORT));
}

/**
 * @brief   Saves the node configuration.
 * @details The node configuration is saved to a static non-volatile memory
 *          chunk.
 * @see     reros_lld_nodeconfig_save()
 *
 * @pre     The related @p RerosNode is initialized.
 *
 * @param[in] cfgp
 *          Pointer to the configuration descriptor to be saved.
 */
void rerosUserNodeConfigSave(const RerosNodeConfig *cfgp) {

  rerosAssert(cfgp != NULL);

  /* TODO: Save configuration values.*/
  (void)cfgp;
}

/**
 * @brief   Shutdown callback function.
 * @details This callback function notifies the user that a @p shutdown()
 *          XMLRPC call was issued by the Master node, and has to be handled.
 *
 * @param[in] msgp
 *          Pointer to a string which explains the reason why it is asked to be
 *          shutdown.
 * @return
 *          Error code.
 */
reros_err_t rerosUserShutdown(const RerosString *msgp) {

  static RerosNodeStatus *const stp = &rerosNode.status;

  (void)msgp;
  (void)stp;

#if REROS_USE_ASSERT
  rerosAssert(msgp != NULL);
  rerosMutexLock(&stp->stateLock);
  rerosAssert(stp->state == REROS_NODE_SHUTDOWN);
  rerosMutexUnlock(&stp->stateLock);
#endif

  /* TODO: Handle the shutdown() call and message.*/

  /* Send a dummy getPid() request, to unlock XMLRPC listener and pool.*/
  {
    RerosRpcResponse res;
    rerosRpcResponseObjectInit(&res);
    rerosRpcCallGetPid(
      &rerosNode.config.xmlrpcAddr,
      &rerosNode.config.nodeName,
      &res
    );
    rerosRpcResponseClean(&res);
  }

  return REROS_OK;
}

/**
 * @brief   Registers static message types.
 * @details This callback function is called at boot time to initialize the
 *          set of message types recognized by the system.
 *
 * @pre     The global static message type set has not been initialized yet.
 */
void rerosUserRegisterStaticTypes(void) {

  rerosMsgTypesRegStaticTypes();
}

/**
 * @brief   Registers all the published topics to the Master node.
 * @note    Should be called at node initialization.
 *
 * @return  Error code.
 */
reros_err_t rerosUserPublishTopics(void) {
  rerosHandlersPublishTopics();
  return REROS_OK;
}

/**
 * @brief   Unregisters all the published topics to the Master node.
 * @note    Should be called at node shutdown.
 *
 * @return  Error code.
 */
reros_err_t rerosUserUnpublishTopics(void) {

  rerosHandlersUnpublishTopics();
  return REROS_OK;
}

/**
 * @brief   Registers all the subscribed topics to the Master node.
 * @note    Should be called at node initialization.
 *
 * @return  Error code.
 */
reros_err_t rerosUserSubscribeTopics(void) {
  rerosHandlersSubscribeTopics(); 
  return REROS_OK;
}

/**
 * @brief   Unregisters all the subscribed topics to the Master node.
 * @note    Should be called at node shutdown.
 *
 * @return  Error code.
 */
reros_err_t rerosUserUnsubscribeTopics(void) {

  rerosHandlersUnsubscribeTopics(); 
  return REROS_OK;
}

/**
 * @brief   Registers all the published services to the Master node.
 * @note    Should be called at node initialization.
 *
 * @return  Error code.
 */
reros_err_t rerosUserPublishServices(void) {

  rerosHandlersPublishServices();
  return REROS_OK;
}
/**
 * @brief   Unregisters all the published services to the Master node.
 * @note    Should be called at node shutdown.
 *
 * @return  Error code.
 */
reros_err_t rerosUserUnpublishServices(void) {

  rerosHandlersUnpublishServices();
  return REROS_OK;
}

/**
 * @brief   Registers all the subscribed parameters to the Master node.
 * @note    Should be called at node initialization.
 *
 * @return  Error code.
 */
reros_err_t rerosUserSubscribeParams(void) {

  /* TODO: Subscribe to parameters.*/
  return REROS_OK;
}

/**
 * @brief   Unregisters all the subscribed parameters to the Master node.
 * @note    Should be called at node shutdown.
 *
 * @return  Error code.
 */
reros_err_t rerosUserUnsubscribeParams(void) {

  /* TODO: Unsubscribe from parameters.*/
  return REROS_OK;
}

/**
 * @brief   Updates a subscribed ROS parameter locally.
 * @details This callback function notifies the user that the value of a
 *          subscribed ROS parameter has changed.
 *
 * @param[in] keyp
 *          Pointer to the parameter name string.
 * @param[in] paramp
 *          Pointer to the parameter value.
 * @return
 *          Error code.
 */
reros_err_t rerosUserParamUpdate(const RerosString *keyp,
                               const RerosRpcParam *paramp) {
  rerosAssert(rerosStringNotEmpty(keyp));
  rerosAssert(paramp != NULL);

  /* TODO: Handle the new parameter value.*/
  (void)keyp;
  (void)paramp;
  return REROS_OK;
}
#endif
/* _REROSPARACONFIG_H_ */

