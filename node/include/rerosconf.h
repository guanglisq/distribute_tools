/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2016年2月22日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosconf.h
 * @author  Zuolong
 *
 * @brief   User definitions for middleware configuration.
 */

#ifndef _REROSCONF_H_
#define _REROSCONF_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

/** @brief Use the updated socket interface.*/
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE   600
#endif

/* @brief Using GNU extensions.*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE     1
#endif

#include <stdint.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>

/*===========================================================================*/
/* NODE CONFIGURATION                                                        */
/*===========================================================================*/

/** @addtogroup node_config */
/** @{ */

/** @name Configuration */
/** @{ */

/** @brief Default ROS node name, C string.*/
#define REROS_NODE_NAME                      "/ReworksNode1"

/** @brief Node thread priorty.*/
#define REROS_NODE_THREAD_PRIO               301

/** @brief Node thread stack size.*/
/* lrk modify 20160601 */
/* increase stack size */
#define REROS_NODE_THREAD_STKSIZE            (PTHREAD_STACK_MIN << 3 /*1*/)

/** @} */
/** @} */

/*===========================================================================*/
/* XMLRPC CONFIGURATION                                                      */
/*===========================================================================*/

/** @addtogroup rpc_config */
/** @{ */

/*~~~ MASTER CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name XMLRPC Master configuration */
/** @{ */

/** @brief Default Master server IP address, little-endian dword.*/
#define REROS_XMLRPC_MASTER_IP               rerosIpDword(192, 168, 1, 131)

/** @brief Default Master server IP address, C string.*/
#define REROS_XMLRPC_MASTER_IP_SZ            "192.168.1.131"

/** @brief Default Master server port.*/
#define REROS_XMLRPC_MASTER_PORT             11311

/** @} */

/*~~~ LISTENER CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name XMLRPC listener configuration */
/** @{ */

/** @brief Default XMLRPC listener IP address, little-endian dword.*/
#define REROS_XMLRPC_LISTENER_IP             rerosIpDword(192, 168, 1, 100)

/** @brief Default XMLRPC listener IP address, C string.*/
#define REROS_XMLRPC_LISTENER_IP_SZ          "192.168.1.100"

/** @brief Default XMLRPC listener port.*/
#define REROS_XMLRPC_LISTENER_PORT           777

/** @brief Maximum concurrent connections for XMLRPC Slave API.*/
#define REROS_XMLRPC_LISTENER_BACKLOG        8

/** @brief XMLRPC listener thread priority.*/
#define REROS_XMLRPC_LISTENER_PRIO           110

/** @brief XMLRPC listener thread stack size.*/
#define REROS_XMLRPC_LISTENER_STKSIZE        (PTHREAD_STACK_MIN << 1)

/** @} */

/*~~~ SLAVE CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name XMLRPC Slave configuration */
/** @{ */

/** @brief XMLRPC Slave server thread pool size.*/
#define REROS_XMLRPC_SLAVE_POOLSIZE          4

/** @brief XMLRPC Slave server thread priority.*/
#define REROS_XMLRPC_SLAVE_PRIO              125

/** @brief XMLRPC Slave server thread stack size.*/
#define REROS_XMLRPC_SLAVE_STKSIZE           (PTHREAD_STACK_MIN << 1)

/** @} */

/*~~~ MISC OPTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name XMLRPC timeouts configuration */
/** @{ */

/** @brief Default timeout for incoming XMLRPC transactions, in milliseconds.*/
#define REROS_XMLRPC_RECVTIMEOUT             5000

/** @brief Default timeout for outgoing XMLRPC transactions, in milliseconds.*/
#define REROS_XMLRPC_SENDTIMEOUT             5000

/** @} */
/** @} */

/*===========================================================================*/
/* TCPROS CONFIGURATION                                                      */
/*===========================================================================*/

/** @addtogroup tcpros_config */
/** @{ */

/*~~~ LISTENER CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS listener configuration */
/** @{ */

/** @brief Default TCPROS listener IP address, little-endian dword.*/
#define REROS_TCPROS_LISTENER_IP             REROS_XMLRPC_LISTENER_IP

/** @brief Default TCPROS listener IP address, C string.*/
#define REROS_TCPROS_LISTENER_IP_SZ          REROS_XMLRPC_LISTENER_IP_SZ

/** @brief Default TCPROS listener port.*/
#define REROS_TCPROS_LISTENER_PORT           999

/** @brief Maximum number of partially set up TCPROS connections.*/
#define REROS_TCPROS_LISTENER_BACKLOG        8

/** @brief TCPROS listener thread priority.*/
#define REROS_TCPROS_LISTENER_PRIO           115

/** @brief TCPROS listener thread stack size.*/
#define REROS_TCPROS_LISTENER_STKSIZE        (PTHREAD_STACK_MIN << 1)

/** @} */

/*~~~ CLIENT CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS Client configuration */
/** @{ */

/** @brief TCPROS Client thread pool size.*/
#define REROS_TCPROS_CLIENT_POOLSIZE         8

/** @brief TCPROS Client thread priority.*/
#define REROS_TCPROS_CLIENT_PRIO             252

/** @brief TCPROS Client thread stack size.*/
#define REROS_TCPROS_CLIENT_STKSIZE          (PTHREAD_STACK_MIN << 1)

/** @} */

/*~~~ SERVER CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS Server configuration */
/** @{ */

/** @brief TCPROS Server thread pool size.*/
#define REROS_TCPROS_SERVER_POOLSIZE         8

/** @brief TCPROS Server thread priority.*/
#define REROS_TCPROS_SERVER_PRIO             253

/** @brief TCPROS server thread stack size.*/
#define REROS_TCPROS_SERVER_STKSIZE          (PTHREAD_STACK_MIN << 1)

/** @} */

/*~~~ MISC OPTIONS `~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS misc options */
/** @{ */

/** @brief Reads the message definition, instead of skipping it.*/
#define REROS_TCPROS_USE_MSGDEF              0

/** @} */

/** @name TCPROS timeouts configuration */
/** @{ */

/** @brief Default timeout for incoming TCPROS transactions, in milliseconds.*/
#define REROS_TCPROS_RECVTIMEOUT             1000

/** @brief Default timeout for outgoing TCPROS transactions, in milliseconds.*/
#define REROS_TCPROS_SENDTIMEOUT             1000

/** @} */
/** @} */

/*===========================================================================*/
/* INTERNAL MODULES CONFIGURATION                                            */
/*===========================================================================*/

/** @addtogroup rpc_config */
/** @{ */

/*~~~ XMLRPC PARSER OPTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name XMLRPC parser configuration */
/** @{ */

/** @brief Default length of the reading buffer.*/
#define REROS_RPCPARSER_RDBUFLEN             256

/** @brief Reads the status message, instead of skipping it.*/
#define REROS_RPCPARSER_USE_STATMSG          0

/** @} */

/*~~~ XMLRPC STREAMER OPTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name XMLRPC streamer configuration */
/** @{ */

/** @brief Fixed Content-Length, when the message spans more packets.*/
#define REROS_RPCSTREAMER_FIXLEN             4000

/** @} */
/** @} */

/*~~~ MISC OPTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`*/

/** @addtogroup conn_config */
/** @{ */

/** @name Connectivity configuration */
/** @{ */

/** @brief Size of a MTU.*/
#define REROS_MTU_SIZE                       1500

/** @} */
/** @} */

/*===========================================================================*/
/* FEATURE FLAGS                                                             */
/*===========================================================================*/

/** @addtogroup base_config */
/** @{ */

/*~~~ GLOBAL SWITCHES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name Global switches */
/** @{ */

/** @brief Uses the built-in memory pool.*/
#define REROS_USE_BUILTIN_MEMPOOL            1

/** @brief Enables assertion evaluations.*/
#define REROS_USE_ASSERT                     1

/** @brief Enables error messages.*/
#define REROS_USE_ERROR_MSG                  1

/** @} */

/*~~~ PER-FILE ASSERTION SWITCHES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name Assertion switches */
/** @{ */

/** @brief Enables assertions for <tt>rerosBase.c</tt>.*/
#define REROS_BASE_C_USE_ASSERT              1

/** @brief Enables assertions for <tt>rerosConn.c</tt>.*/
#define REROS_CONN_C_USE_ASSERT              1

/** @brief Enables assertions for <tt>rerosNode.c</tt>.*/
#define REROS_NODE_C_USE_ASSERT              1

/** @brief Enables assertions for <tt>rerosRpcCall.c</tt>.*/
#define REROS_RPCCALL_C_USE_ASSERT           1

/** @brief Enables assertions for <tt>rerosRpcParser.c</tt>.*/
#define REROS_RPCPARSER_C_USE_ASSERT         1

/** @brief Enables assertions for <tt>rerosRpcSlave.c</tt>.*/
#define REROS_RPCSLAVE_C_USE_ASSERT          1

/** @brief Enables assertions for <tt>rerosRpcStreamer.c</tt>.*/
#define REROS_RPCSTREAMER_C_USE_ASSERT       1

/** @brief Enables assertions for <tt>rerosTcpRos.c</tt>.*/
#define REROS_TCPROS_C_USE_ASSERT            1

/** @brief Enables assertions for <tt>rerosThreading.c</tt>.*/
#define REROS_THREADING_C_USE_ASSERT         1

/** @} */

/*~~~ PER-FILE ERROR MESSAGE SWITCHES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name Error message switches */
/** @{ */

/** @brief Enables error messages for <tt>rerosBase.c</tt>.*/
#define REROS_BASE_C_USE_ERROR_MSG           1

/** @brief Enables error messages for <tt>rerosConn.c</tt>.*/
#define REROS_CONN_C_USE_ERROR_MSG           1

/** @brief Enables error messages for <tt>rerosNode.c</tt>.*/
#define REROS_NODE_C_USE_ERROR_MSG           1

/** @brief Enables error messages for <tt>rerosRpcCall.c</tt>.*/
#define REROS_RPCCALL_C_USE_ERROR_MSG        1

/** @brief Enables error messages for <tt>rerosRpcParser.c</tt>.*/
#define REROS_RPCPARSER_C_USE_ERROR_MSG      1

/** @brief Enables error messages for <tt>rerosRpcSlave.c</tt>.*/
#define REROS_RPCSLAVE_C_USE_ERROR_MSG       1

/** @brief Enables error messages for <tt>rerosRpcStreamer.c</tt>.*/
#define REROS_RPCSTREAMER_C_USE_ERROR_MSG    1

/** @brief Enables error messages for <tt>rerosTcpRos.c</tt>.*/
#define REROS_TCPROS_C_USE_ERROR_MSG         1

/** @brief Enables error messages for <tt>rerosThreading.c</tt>.*/
#define REROS_THREADING_C_USE_ERROR_MSG      1

/** @} */
/** @} */

/*===========================================================================*/
/* USER MACROS                                                               */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
/* Define your own assertion and error procedures below.*/

#define rerosAssert(expr) \
  assert(expr)

/* msgargs as ("format", ...) */
#define rerosError(when, action, msgargs) \
  { if (when) { \
      printf("Error at %s:%d\n" \
             "  function: %s\n" \
             "  reason:   %s\n" \
             "  message:  ", \
             __FILE__, __LINE__, __PRETTY_FUNCTION__, #when); \
      printf msgargs ; \
      { action; } } }

#endif /* !defined(__DOXYGEN__) */

/*===========================================================================*/
/*  PLATFORM-DEPENDENT TYPES                                                 */
/*===========================================================================*/

/** @addtogroup base_types */
/** @{ */

/** @brief Error type, compatible with thread return type.*/
typedef int             reros_err_t;

/** @brief Heap type.*/
typedef void            RerosMemHeap;

/** @brief Memory pool type, platform-dependent.*/
struct RerosMemPool;

/** @} */

/** @addtogroup threading_types */
/** @{ */

/** @brief Thread ID type, platform-dependent.*/
typedef pthread_t       RerosThreadId;
/** @brief Invalid thread ID.*/
#define REROS_NULL_THREADID  (~0ul)

/** @brief Thread priority type, platform-dependent.*/
typedef int             reros_prio_t;

/** @brief Semaphore type, platform-dependent.*/
typedef struct {
  unsigned          counter;    /**< @brief Semaphore counter.*/
  pthread_mutex_t   mutex;      /**< @brief Semapgore mutex.*/
  pthread_cond_t    cond;       /**< @brief Semaphore condvar.*/
} RerosSem;

/** @brief Mutex type, platform-dependent.*/
typedef pthread_mutex_t RerosMutex;

/** @brief Condvar type, platform-dependent.*/
typedef pthread_cond_t  RerosCondVar;

/** @} */

/** @addtogroup base_macros */
/** @{ */

/** @brief Platform-dependent variables for @p RerosConn.*/
#define RerosConn__LLD \
  int       socket;         /**< @brief Socket descriptor identifier.*/ \
  uint32_t  recvtimeout;    /**< @brief Receive timeout in milliseconds, or @p 0.*/ \
  uint32_t  sendtimeout;    /**< @brief Send timeout in milliseconds, or @p 0.*/ \
  void      *recvbufp;      /**< @brief Pointer to the receiver buffer.*/ \
  size_t    recvbuflen;     /**< @brief Receiver buffer length*/

/** @} */

/** @addtogroup semphore_types */
/** @{ */

/** @brief semphore type, platform-dependent.*/
typedef sem_t       RerosSemphore;

/** @} */


#endif /* _REROSCONF_H_ */
