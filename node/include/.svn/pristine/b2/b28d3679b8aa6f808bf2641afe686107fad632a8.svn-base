/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月16日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosTcpRos.h
 * @author  Zuolong
 *
 * @brief   TCPROS features of the middleware.
 */

#ifndef _REROSTCPROS_H_
#define _REROSTCPROS_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"
#include "rerosConn.h"
#include "rerosThreading.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup tcpros_types */
/** @{ */

/**
 * @brief   TCPROS Client thread creation arguments.
 */
typedef struct reros_tcpcliargs_t {
  RerosString        topicName;      /**< @brief Topic name.*/
  reros_topicflags_t topicFlags;     /**< @brief Topic flags.*/
  RerosAddr          remoteAddr;     /**< @brief Remote connection address.*/
} reros_tcpcliargs_t;

/**
 * @brief   TCPROS connection status object.
 */
typedef struct RerosTcpRosStatus {
  reros_err_t        err;            /**< @brief Last error code.*/
  RerosConn          *csp;           /**< @brief Connection status pointer.*/
  RerosString        callerId;       /**< @brief Caller ID.*/
  RerosTopic         *topicp;        /**< @brief Referenced topic/service.*/
  reros_topicflags_t remoteFlags;    /**< @brief Remote topic/service flags.*/
  reros_bool_t       threadExit;     /**< @brief Thread exit request.*/
  RerosMutex         threadExitMtx;  /**< @brief Thread exit request mutex.*/
  RerosString        errstr;         /**< @brief Error string.*/
} RerosTcpRosStatus;

/**
 * @brief   TCPROS variable array descriptor.
 */
typedef struct RerosTcpRosArray {
  uint32_t          length;         /**< @brief Number of entries.*/
  void              *entriesp;      /**< @brief Pointer to the entries chunk.*/
} RerosTcpRosArray;

/**
 * @brief   TCPROS Service call handler.
 *
 * @param[in,out] tcpstp
 *          Pointer to a TCPROS statuc with a working connection.
 * @param[out] resobjp
 *          Pointer to the allocated object being received.
 * @return
 *          Error code.
 */
typedef reros_err_t (*reros_tcpsrvcall_t)(RerosTcpRosStatus *tcpstp,
                                        void *reqobjp,
                                        void *resobjp);

/** @} */

/** @addtogroup tcpros_macros */
/** @{ */

/*~~~ TCPROS CONNECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS connection */
/** @{ */

/**
 * @brief   Reads a raw value.
 * @details The raw value is received from a little-endian fashion.
 * @warning On big endian architectures, be careful not to specify a @p value
 *          of complex (@e struct or @e union) type, because the @b whole value
 *          will be received in reverse order, not its primitive fields
 *          individually as expected.
 *
 * @param[in,out] tcpstp
 *          Pointer to a TCPROS status with a working connection.
 * @param[in] value
 *          Value to be read. It must be addressable by a pointer.
 * @return
 *          Error code.
 */
#if REROS_ENDIANNESS == 321
#define rerosTcpRosRecvRaw(tcpstp, value) \
  rerosTcpRosRecvRev((tcpstp), &(value), sizeof(value))
#else
#define rerosTcpRosRecvRaw(tcpstp, value) \
  rerosTcpRosRecv((tcpstp), &(value), sizeof(value))
#endif

/**
 * @brief   Writes a raw value.
 * @details The raw value is sent in a little-endian fashion.
 * @warning On big endian architectures, be careful not to specify a @p value
 *          of complex (@e struct or @e union) type, because the @b whole value
 *          will be sent in reverse order, not its primitive fields
 *          individually as expected.
 *
 * @param[in,out] tcpstp
 *          Pointer to a TCPROS status with a working connection.
 * @param[in] value
 *          Value to be written. It must be addressable by a pointer.
 * @return
 *          Error code.
 */
#if REROS_ENDIANNESS == 321
#define rerosTcpRosSendRaw(tcpstp, value) \
  rerosTcpRosSendRev((tcpstp), &(value), sizeof(value))
#else
#define rerosTcpRosSendRaw(tcpstp, value) \
  rerosTcpRosSend((tcpstp), &(value), sizeof(value))
#endif

/** @} */

/*~~~ TCPROS ARRAY ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS array */
/** @{ */

/**
 * @brief   Generate a variable-length array structure.
 * @details Generates a structure compatible with @p RerosTcpRosArray, where the
 *          entries pointer is correctly typed.
 *
 * @param[in] type
 *          Type of an array entry object. To be valid, a valid pointer
 *          type must be obtained by appending a @p * to @p type.
 */
#define REROS_VARARR(type) \
  struct { uint32_t length; type *entriesp; }

/**
 * @brief   Indexes an array item at the provided index.
 *
 * @param[in,out] array
 *          Pointer to an initialized @p RerosTcpRosArray object.
 * @param[in] type
 *          Type of an array entry object. To be valid, a valid pointer
 *          type must be obtained by appending a @p * to @p type.
 * @param[in] index
 *          Index of the involved array entry.
 * @return
 *          The object value at position @p index.
 */
#define rerosTcpRosArrayAt(array, type, index) \
  ((type *)(array))[(index)]

/** @} */

/*~~~ TCPROS HANDLERS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS handlers */
/** @{ */

/**
 * @brief   Name of the message length variable in TCPROS handlers.
 */
#if !defined(REROS_HND_LENGTH) || defined(__DOXYGEN__)
#define REROS_HND_LENVAR         msglen
#endif

/**
 * @brief   Name of the TCPROS status pointer in handlers.
 */
#if !defined(REROS_HND_TCPSTP) || defined(__DOXYGEN__)
#define REROS_HND_TCPSTP         tcpstp
#endif

/**
 * @brief   Name of the label called when exiting from a handler.
 */
#if !defined(REROS_HND_FINALLY) || defined(__DOXYGEN__)
#define REROS_HND_FINALLY        _finally
#endif

/*~~~ TCPROS MESSAGES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS messages */
/** @{ */

/**
 * @brief   Message descriptor initialization.
 * @details Tries to allocate the descriptor on the heap. In unsuccessful,
 *          goes to @p REROS_HND_FINALLY with an @p REROS_ERR_NOMEM error.
 *
 * @param[in] msgvarp
 *          Pointer to the message.
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_MSG_INIT_H(msgvarp, ctypename) \
  { msgvarp = rerosNew(NULL, struct ctypename); \
    if (msgvarp == NULL) { \
      (REROS_HND_TCPSTP)->err = REROS_ERR_NOMEM; goto REROS_HND_FINALLY; } \
    init_##ctypename(msgvarp); }

/**
 * @brief   Message descriptor initialization.
 * @details Initializes a message descriptor located on the stack.
 *
 * @param[in] msgvarp
 *          Pointer to the message.
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_MSG_INIT_S(msgvarp, ctypename) \
  { init_##ctypename(msgvarp); }

/**
 * @brief   Uninitializes a message descriptor located in the heap.
 * @details The allocated descriptor is deleted from the heap.
 *
 * @param[in] msgvarp
 *          Pointer to the message.
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_MSG_UNINIT_H(msgvarp, ctypename) \
  { clean_##ctypename(msgvarp); \
    rerosFree(msgvarp); }

/**
 * @brief   Uninitializes a message descriptor located on the stack.
 *
 * @param[in] msgvarp
 *          Pointer to the message.
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_MSG_UNINIT_S(msgvarp, ctypename) \
  { clean_##ctypename(msgvarp); }

/**
 * @brief   Sends the length of the message (message header).
 * @details This macro handles timeouts and errors. If unsuccessful, it goes to
 *          @p REROS_HND_FINALLY.
 *
 * @param[in] msgvarp
 *          Pointer to an initialized message.
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_MSG_SEND_LENGTH(msgvarp, ctypename) \
  { size_t start = (REROS_HND_TCPSTP)->csp->sentlen; \
    REROS_HND_LENVAR = (uint32_t)length_##ctypename(msgvarp); \
    while (rerosTcpRosSendRaw(REROS_HND_TCPSTP, REROS_HND_LENVAR) != REROS_OK) { \
      if ((REROS_HND_TCPSTP)->err != REROS_ERR_TIMEOUT || \
          (REROS_HND_TCPSTP)->csp->sentlen != start || \
          rerosTcpRosStatusCheckExit(REROS_HND_TCPSTP)) { \
        goto REROS_HND_FINALLY; } } }

/**
 * @brief   Receives the length of the message (message header).
 * @details This macro handles timeouts and errors. If unsuccessful, it goes to
 *          @p REROS_HND_FINALLY.
 */
#define REROS_MSG_RECV_LENGTH() \
  { size_t start = (REROS_HND_TCPSTP)->csp->recvlen; \
    while (rerosTcpRosRecvRaw(REROS_HND_TCPSTP, REROS_HND_LENVAR) != REROS_OK) { \
      if ((REROS_HND_TCPSTP)->err != REROS_ERR_TIMEOUT || \
          start != (REROS_HND_TCPSTP)->csp->recvlen || \
          rerosTcpRosStatusCheckExit(REROS_HND_TCPSTP)) { \
        goto REROS_HND_FINALLY; } } }

/**
 * @brief   Sends the body of the message.
 * @details This macro handles timeouts and errors. If unsuccessful, it goes to
 *          @p REROS_HND_FINALLY.
 *
 * @param[in] msgvarp
 *          Pointer to an initialized message.
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_MSG_SEND_BODY(msgvarp, ctypename) \
  { send_##ctypename(REROS_HND_TCPSTP, msgvarp); \
    if ((REROS_HND_TCPSTP)->err != REROS_OK) { \
      goto REROS_HND_FINALLY; } }

/**
 * @brief   Receives the body of the message.
 * @details This macro handles timeouts and errors. If unsuccessful, it goes to
 *          @p REROS_HND_FINALLY.
 *
 * @param[in] msgvarp
 *          Pointer to an initialized message.
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_MSG_RECV_BODY(msgvarp, ctypename) \
  { recv_##ctypename(REROS_HND_TCPSTP, msgvarp); \
    if ((REROS_HND_TCPSTP)->err != REROS_OK) { goto REROS_HND_FINALLY; } \
    rerosError((size_t)REROS_HND_LENVAR != length_##ctypename(msgvarp), \
              { (REROS_HND_TCPSTP)->err = REROS_ERR_BADPARAM; \
                goto REROS_HND_FINALLY; }, \
              ("Wrong message length %u, expected %u\n", \
                (unsigned)REROS_HND_LENVAR, \
                (unsigned)length_##ctypename(msgvarp))); }

/** @} */

/*~~~ TCPROS TOPICS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS topics */
/** @{ */

/**
 * @brief   Declaration of a topic message in the heap.
 * @note    To be used inside <code>REROS_TPC_INIT_H()</code>.
 */
#if !defined(REROS_TPC_MSGDECL_H) || defined(__DOXYGEN__)
#define REROS_TPC_MSGDECL_H      *msgp = NULL
#endif

/**
 * @brief   Declaration of a topic message on the stack.
 * @note    To be used inside <code>REROS_TPC_INIT_S()</code>.
 */
#if !defined(REROS_TPC_MSGDECL_S) || defined(__DOXYGEN__)
#define REROS_TPC_MSGDECL_S      msg
#endif

/**
 * @brief   Pointer to a topic message in the heap.
 */
#if !defined(REROS_TPC_MSGPTR_H) || defined(__DOXYGEN__)
#define REROS_TPC_MSGPTR_H       msgp
#endif

/**
 * @brief   Pointer to a topic message on the stack.
 */
#if !defined(REROS_TPC_MSGPTR_S) || defined(__DOXYGEN__)
#define REROS_TPC_MSGPTR_S       (&msg)
#endif

/**
 * @brief   Topic handler prologue.
 * @details This macro defines the following:
 *          -# declaration of the @p REROS_TPC_MSGDECL_H message pointer and the
 *             @p REROS_HND_LENGTH variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 *          -# allocation and initialization of the message descriptor, with
 *             error checks.
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 *
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*).
 */
#define REROS_TPC_INIT_H(ctypename) \
  struct ctypename REROS_TPC_MSGDECL_H; \
  uint32_t REROS_HND_LENVAR; \
  rerosAssert((REROS_HND_TCPSTP) != NULL); \
  rerosAssert((REROS_HND_TCPSTP)->topicp != NULL); \
  rerosAssert(!(REROS_HND_TCPSTP)->topicp->flags.service); \
  rerosAssert(rerosConnIsValid((REROS_HND_TCPSTP)->csp)); \
  REROS_MSG_INIT_H(REROS_TPC_MSGPTR_H, ctypename)

/**
 * @brief   Topic handler prologue.
 * @details This macro defines the following:
 *          -# declaration of the @p REROS_TPC_MSGDECL_S message descriptor and
 *            the @p REROS_HND_LENGTH variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 *          -# initialization of the message descriptor.
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 *
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*).
 */
#define REROS_TPC_INIT_S(ctypename) \
  struct ctypename REROS_TPC_MSGDECL_S; \
  uint32_t REROS_HND_LENVAR; \
  rerosAssert((REROS_HND_TCPSTP) != NULL); \
  rerosAssert((REROS_HND_TCPSTP)->topicp != NULL); \
  rerosAssert(!(REROS_HND_TCPSTP)->topicp->flags.service); \
  rerosAssert(rerosConnIsValid((REROS_HND_TCPSTP)->csp)); \
  REROS_MSG_INIT_S(REROS_TPC_MSGPTR_S, ctypename)

/**
 * @brief   Topic handler epilogue.
 * @details This macro cleans the message descriptor and deallocates it from
 *          the heap.
 * @note    This macro should be placed after the @p REROS_HND_FINALLY label.
 *
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_TPC_UNINIT_H(ctypename) \
  REROS_MSG_UNINIT_H(REROS_TPC_MSGPTR_H, ctypename);

/**
 * @brief   Topic handler epilogue.
 * @details This macro cleans the message descriptor.
 * @note    This macro should be placed after the @p REROS_HND_FINALLY label.
 *
 * @param[in] ctypename
 *          Mangled version of the type name (@p msg_*, @p in_srv_*,
 *          @p out_srv_*).
 */
#define REROS_TPC_UNINIT_S(ctypename) \
  REROS_MSG_UNINIT_S(REROS_TPC_MSGPTR_S, ctypename);

/** @} */

/*~~~ TCPROS SERVICES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name TCPROS services */
/** @{ */

/**
 * @brief   Declaration of a service request message in the heap.
 * @note    To be used inside @p REROS_SRV_INIT_H().
 */
#if !defined(REROS_SRV_INDECL_H) || defined(__DOXYGEN__)
#define REROS_SRV_INDECL_H       *inmsgp = NULL
#endif

/**
 * @brief   Declaration of a service response message in the heap.
 * @note    To be used inside @p REROS_SRV_INIT_H().
 */
#if !defined(REROS_SRV_OUTDECL_H) || defined(__DOXYGEN__)
#define REROS_SRV_OUTDECL_H      *outmsgp = NULL
#endif

/**
 * @brief   Declaration of a service request message on the stack.
 * @note    To be used inside @p REROS_SRV_INIT_S().
 */
#if !defined(REROS_SRV_INDECL_S) || defined(__DOXYGEN__)
#define REROS_SRV_INDECL_S       inmsg
#endif

/**
 * @brief   Declaration of a service response message on the stack.
 * @note    To be used inside @p REROS_SRV_INIT_S().
 */
#if !defined(REROS_SRV_OUTDECL_S) || defined(__DOXYGEN__)
#define REROS_SRV_OUTDECL_S      outmsg
#endif

/**
 * @brief   Pointer to a service request message in the heap.
 */
#if !defined(REROS_SRV_INPTR_H) || defined(__DOXYGEN__)
#define REROS_SRV_INPTR_H        inmsgp
#endif

/**
 * @brief   Pointer to a service response message in the heap.
 */
#if !defined(REROS_SRV_OUTPTR_H) || defined(__DOXYGEN__)
#define REROS_SRV_OUTPTR_H       outmsgp
#endif

/**
 * @brief   Pointer to a service request message on the stack.
 */
#if !defined(REROS_SRV_INPTR_S) || defined(__DOXYGEN__)
#define REROS_SRV_INPTR_S        (&inmsg)
#endif

/**
 * @brief   Pointer to a service response message on the stack.
 */
#if !defined(REROS_SRV_OUTPTR_S) || defined(__DOXYGEN__)
#define REROS_SRV_OUTPTR_S       (&outmsg)
#endif

/**
 * @brief   Name of the <em>OK byte</em> variable in TCPROS service handlers.
 */
#if !defined(REROS_SRV_OKVAR) || defined(__DOXYGEN__)
#define REROS_SRV_OKVAR          okByte
#endif

/**
 * @brief   Service handler prologue.
 * @details This macro defines the following:
 *          -# declaration of the @p REROS_SRV_*DECL_* messages and the
 *             @p REROS_HND_LENVAR variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] indecl
 *          Declaration of the request message variable:
 *          - <code>*inmsgp = NULL</code> when in the heap,
 *          - <code>inmsg</code> when on the stack.
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 * @param[in] outdecl
 *          Declaration of the response message variable:
 *          - <code>*outmsgp = NULL</code> when in the heap,
 *          - <code>outmsg</code> when on the stack.
 */
#define REROS_SRV_INIT(inctypename, indecl, \
                          outctypename, outdecl) \
  struct inctypename indecl; \
  struct outctypename outdecl; \
  uint32_t REROS_HND_LENVAR; \
  uint8_t REROS_SRV_OKVAR; \
  rerosAssert((REROS_HND_TCPSTP) != NULL); \
  rerosAssert((REROS_HND_TCPSTP)->topicp != NULL); \
  rerosAssert((REROS_HND_TCPSTP)->topicp->flags.service); \
  rerosAssert(rerosConnIsValid((REROS_HND_TCPSTP)->csp));

/**
 * @brief   Service request/response initialization.
 * @details Request and response on the stack.
 *          This macro defines the following:
 *          -# declaration of the @p REROS_SRV_INDECL_S and
 *             @p REROS_SRV_OUTDECL_S messages, and the @p REROS_HND_LENVAR
 *             variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 *          -# allocation and initialization of the message descriptors, with
 *             error checks.
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_INIT_SISO(inctypename, outctypename) \
  REROS_SRV_INIT(inctypename, REROS_SRV_INDECL_S, \
                outctypename, REROS_SRV_OUTDECL_S) \
  REROS_MSG_INIT_S(REROS_SRV_INPTR_S, inctypename) \
  REROS_MSG_INIT_S(REROS_SRV_OUTPTR_S, outctypename)

/**
 * @brief   Service request/response initialization.
 * @details Request on the stack, response in the heap.
 *          This macro defines the following:
 *          -# declaration of the @p REROS_SRV_INDECL_S and
 *             @p REROS_SRV_OUTDECL_H messages, and the @p REROS_HND_LENVAR
 *             variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 *          -# allocation and initialization of the message descriptors, with
 *             error checks.
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 * @see     REROS_SRV_INIT()
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_INIT_SIHO(inctypename, outctypename) \
  REROS_SRV_INIT(inctypename, REROS_SRV_INDECL_S, \
                outctypename, REROS_SRV_OUTDECL_H) \
  REROS_MSG_INIT_S(REROS_SRV_INPTR_S, inctypename) \
  REROS_MSG_INIT_H(REROS_SRV_OUTPTR_H, outctypename)

/**
 * @brief   Service request/response initialization.
 * @details Request in the heap, response on the stack.
 *          This macro defines the following:
 *          -# declaration of the @p REROS_SRV_INDECL_H and
 *             @p REROS_SRV_OUTDECL_S messages, and the @p REROS_HND_LENVAR
 *             variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 *          -# allocation and initialization of the message descriptors, with
 *             error checks.
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 * @see     REROS_SRV_INIT()
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_INIT_HISO(inctypename, outctypename) \
  REROS_SRV_INIT(inctypename, REROS_SRV_INDECL_H, \
                outctypename, REROS_SRV_OUTDECL_S) \
  REROS_MSG_INIT_H(REROS_SRV_INPTR_H, inctypename) \
  REROS_MSG_INIT_S(REROS_SRV_OUTPTR_S, outctypename)

/**
 * @brief   Service request/response initialization.
 * @details Request and response in the heap.
 *          This macro defines the following:
 *          -# declaration of the @p REROS_SRV_INDECL_H and
 *             @p REROS_SRV_OUTDECL_H messages, and the @p REROS_HND_LENVAR
 *             variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 *          -# allocation and initialization of the message descriptors, with
 *             error checks.
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 * @see     REROS_SRV_INIT()
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_INIT_HIHO(inctypename, outctypename) \
  REROS_SRV_INIT(inctypename, REROS_SRV_INDECL_H, \
                outctypename, REROS_SRV_OUTDECL_H) \
  REROS_MSG_INIT_H(REROS_SRV_INPTR_H, inctypename) \
  REROS_MSG_INIT_H(REROS_SRV_OUTPTR_H, outctypename)

/**
 * @brief   Service request/response uninitialization.
 * @details Request and response on the stack.
 * @note    This macro should be placed after the @p REROS_HND_FINALLY label.
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_UNINIT_SISO(inctypename, outctypename) \
  REROS_MSG_UNINIT_S(REROS_SRV_INPTR_S, inctypename) \
  REROS_MSG_UNINIT_S(REROS_SRV_OUTPTR_S, outctypename)

/**
 * @brief   Service request/response uninitialization.
 * @details Request on the stack, response in the heap.
 * @note    This macro should be placed after the @p REROS_HND_FINALLY label.
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_UNINIT_SIHO(inctypename, outctypename) \
  REROS_MSG_UNINIT_S(REROS_SRV_INPTR_S, inctypename) \
  REROS_MSG_UNINIT_H(REROS_SRV_OUTPTR_H, outctypename)

/**
 * @brief   Service request/response uninitialization.
 * @details Request in the heap, response on the stack.
 * @note    This macro should be placed after the @p REROS_HND_FINALLY label.
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_UNINIT_HISO(inctypename, outctypename) \
  REROS_MSG_UNINIT_H(REROS_SRV_INPTR_H, inctypename) \
  REROS_MSG_UNINIT_S(REROS_SRV_OUTPTR_S, outctypename)

/**
 * @brief   Service request/response uninitialization.
 * @details Request and response in the heap.
 * @note    This macro should be placed after the @p REROS_HND_FINALLY label.
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRV_UNINIT_HIHO(inctypename, outctypename) \
  REROS_MSG_UNINIT_H(REROS_SRV_INPTR_H, inctypename) \
  REROS_MSG_UNINIT_H(REROS_SRV_OUTPTR_H, outctypename)

/**
 * @brief   Sends the <em>OK byte</em>, and error string if necessary.
 * @details If the <em>OK byte</em> is @p 0, it sends the string from
 *          @p REROS_HND_TCPSTP->errstr error, and it goes to
 *          @p REROS_HND_FINALLY.
 */
#define REROS_SRV_SEND_OKBYTE_ERRSTR() \
  { rerosTcpRosSendRaw(REROS_HND_TCPSTP, REROS_SRV_OKVAR); \
    if (REROS_SRV_OKVAR == 0) { \
      rerosTcpRosSendString(REROS_HND_TCPSTP, &(REROS_HND_TCPSTP)->errstr); \
      rerosStringObjectInit(&(REROS_HND_TCPSTP)->errstr); \
      goto REROS_HND_FINALLY; } }

/**
 * @brief   Sends the <em>OK byte</em>, and error string if necessary.
 * @details If the <em>OK byte</em> is @p 0, it sends the string from
 *          @p REROS_HND_TCPSTP->errstr error, and it goes to
 *          @p REROS_HND_FINALLY.
 */
#define REROS_SRV_RECV_OKBYTE() \
  { rerosTcpRosRecvRaw(REROS_HND_TCPSTP, REROS_SRV_OKVAR); \
    rerosError(REROS_SRV_OKVAR == 0, REROS_HND_TCPSTP->err = REROS_ERR_NOTIMPL;goto REROS_HND_FINALLY, \
              ("Service OK byte reveals an error (0)\n")); }

/**
 * @brief   Service call handler prologue.
 * @details This macro defines the following:
 *          -# declaration of the @p REROS_SRV_INDECL_* message and the
 *             @p REROS_HND_LENVAR variable, used by other macros;
 *          -# assertions about the @p REROS_HND_TCPSTP object
 *          -# initialization of the @p REROS_SRV_OUTPTR_H result object.
 * @note    This macro should be placed at the beginning of the handler
 *          function, just after variable declarations (if any).
 *
 * @param[in] inctypename
 *          Mangled version of the request type name (@p in_srv_*).
 * @param[in] outctypename
 *          Mangled version of the response type name (@p out_srv_*).
 */
#define REROS_SRVCALL_INIT(inctypename, outctypename) \
  uint32_t REROS_HND_LENVAR; \
  uint8_t REROS_SRV_OKVAR; \
  rerosAssert((REROS_HND_TCPSTP) != NULL); \
  rerosAssert((REROS_HND_TCPSTP)->topicp != NULL); \
  rerosAssert((REROS_HND_TCPSTP)->topicp->flags.service); \
  rerosAssert(!(REROS_HND_TCPSTP)->topicp->flags.persistent); \
  rerosAssert(rerosConnIsValid((REROS_HND_TCPSTP)->csp)); \
  init_##outctypename(REROS_SRV_OUTPTR_H);

/** @} */

/** @} */

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosTopicSubParamsDelete(reros_tcpcliargs_t *parp);

void rerosTcpRosStatusObjectInit(RerosTcpRosStatus *tcpstp, RerosConn *csp);
void rerosTcpRosStatusClean(RerosTcpRosStatus *tcpstp, reros_bool_t deep);
void rerosTcpRosStatusDelete(RerosTcpRosStatus *tcpstp, reros_bool_t deep);
void rerosTcpRosStatusIssueExit(RerosTcpRosStatus *tcpstp);
reros_bool_t rerosTcpRosStatusCheckExit(RerosTcpRosStatus *tcpstp);

void rerosTcpRosArrayObjectInit(RerosTcpRosArray *arrayp);
void rerosTcpRosArrayClean(RerosTcpRosArray *arrayp);
void rerosTcpRosArrayDelete(RerosTcpRosArray *arrayp, reros_bool_t deep);

reros_err_t rerosTcpRosSkip(RerosTcpRosStatus *tcpstp, size_t length);
reros_err_t rerosTcpRosExpect(RerosTcpRosStatus *tcpstp,
                            void *tokp, size_t toklen);
reros_err_t rerosTcpRosRecv(RerosTcpRosStatus *tcpstp,
                          void *bufp, size_t buflen);
reros_err_t rerosTcpRosRecvRev(RerosTcpRosStatus *tcpstp,
                             void *bufp, size_t buflen);
reros_err_t rerosTcpRosRecvString(RerosTcpRosStatus *tcpstp,
                                RerosString *strp);
reros_err_t rerosTcpRosSend(RerosTcpRosStatus *tcpstp,
                          const void *bufp, size_t buflen);
reros_err_t rerosTcpRosSendRev(RerosTcpRosStatus *tcpstp,
                             const void *bufp, size_t buflen);
reros_err_t rerosTcpRosSendString(RerosTcpRosStatus *tcpstp,
                                const RerosString *strp);
reros_err_t rerosTcpRosSendStringSZ(RerosTcpRosStatus *tcpstp,
                                  const char *strp);
reros_err_t rerosTcpRosSendError(RerosTcpRosStatus *tcpstp);
reros_err_t rerosTcpRosSendHeader(RerosTcpRosStatus *tcpstp,
                                reros_bool_t isrequest);
reros_err_t rerosTcpRosRecvHeader(RerosTcpRosStatus *tcpstp,
                                reros_bool_t isrequest,
                                reros_bool_t isservice);

reros_err_t rerosTcpRosCallService(const RerosAddr *pubaddrp,
                                 const RerosTopic *servicep,
                                 void *reqobjp,
                                 void *resobjp);
reros_err_t rerosTcpRosListenerThread(void *data);
reros_err_t rerosTcpRosServerThread(RerosConn *csp);
reros_err_t rerosTcpRosClientThread(reros_tcpcliargs_t *argsp);
void rerosTcpRosTopicSubscriberDone(RerosTcpRosStatus *tcpstp);
void rerosTcpRosTopicPublisherDone(RerosTcpRosStatus *tcpstp);
void rerosTcpRosServiceDone(RerosTcpRosStatus *tcpstp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSTCPROS_H_ */
