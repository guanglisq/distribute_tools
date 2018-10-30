/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月16日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosConn.h
 * @author  Zuolong
 *
 * @brief   Connectivity features of the middleware.
 */

#ifndef _REROSCONN_H_
#define _REROSCONN_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup conn_macros */
/** @{ */

/** @name Address values */
/** @{ */

/**
 * @brief   Makes an IP address packed @em dword.
 *
 * @param[in] f1
 *          IP address field 1 (byte 3).
 * @param[in] f2
 *          IP address field 2 (byte 2).
 * @param[in] f3
 *          IP address field 3 (byte 1).
 * @param[in] f4
 *          IP address field 4 (byte 0).
 * @return
 *          The packed little-endian @em dword IP address.
 *
 * @par     Example
 *          See @ref conn_ex_ipfmt "REROS_IPFMT example".
 */
#define rerosIpDword(f1, f2, f3, f4) \
  ((((uint32_t)(f1) & 0xFFu) << 24u) | \
   (((uint32_t)(f2) & 0xFFu) << 16u) | \
   (((uint32_t)(f3) & 0xFFu) <<  8u) | \
   (((uint32_t)(f4) & 0xFFu) <<  0u))

/**
 * @brief   Binds to any IP addresses.
 * @note    Packed little-endian @em dword.
 */
#define REROS_ANY_IP     rerosIpDword(0, 0, 0, 0)

/**
 * @brief   Binds to any ports.
 */
#define REROS_ANY_PORT   ((uint16_t)0)

/** @} */

/** @name Variable arguments macros */
/** @{ */

/**
 * @brief   @p printf() compatible format string for an IP address.
 *
 * @par     Example
 * @anchor  conn_ex_ipfmt
 *          @code{.c}
 *          RerosIp ip;
 *          ip.dword = rerosIpAddr(192, 168, 1, 1);
 *          printf("The IP address is: "REROS_IPFMT, REROS_IPARG(&ip));
 *          @endcode
 *          prints
 *          @verbatim The IP address is: 192.168.1.1@endverbatim
 */
#define REROS_IPFMT      "%u.%u.%u.%u"

/**
 * @brief   @p printf() compatible format string for a connection address.
 *
 * @par     Example
 * @anchor  conn_ex_addrfmt
 *          @code{.c}
 *          RerosAddr addr;
 *          addr.ip.dword = rerosIpAddr(192, 168, 1, 1);
 *          addr.port = 12345;
 *          printf("The TCP/IP address is: "REROS_ADDRFMT, REROS_ADDRARG(&addr));
 *          @endcode
 *          prints
 *          @verbatim The TCP/IP address is: 192.168.1.1:12345@endverbatim
 */
#define REROS_ADDRFMT    REROS_IPFMT":%u"

/**
 * @brief   Makes the formatted parameters for an IP address.
 * @details Generates a list of values to be passed to a variable arguments
 *          function.
 * @note    To be used with the @p REROS_IPFMT format string.
 *
 * @param[in] ipp
 *          Pointer to an @p RerosIp descriptor.
 * @return
 *          List of values for a variable arguments function.
 *
 * @par     Example
 *          See @ref conn_ex_ipfmt "REROS_IPFMT example".
 */
#define REROS_IPARG(ipp) \
  (unsigned)((ipp)->fields.field1), \
  (unsigned)((ipp)->fields.field2), \
  (unsigned)((ipp)->fields.field3), \
  (unsigned)((ipp)->fields.field4)

/**
 * @brief   Makes the formatted parameters for a connection address.
 * @details Generates a list of values to be passed to a variable arguments
 *          function.
 * @note    To be used with the @p REROS_ADDRFMT format string.
 *
 * @param[in] addrp
 *          Pointer to an @p RerosAddr descriptor.
 * @return
 *          List of values for a variable arguments function.
 *
 * @par     Example
 *          See @ref conn_ex_addrfmt "REROS_IPFMT example".
 */
#define REROS_ADDRARG(addrp) \
  REROS_IPARG(&(addrp)->ip), (unsigned)((addrp)->port)

/** @} */
/** @} */

/** @addtogroup conn_types */
/** @{ */

/**
 * @brief   Connection transport protocol identifier.
 */
typedef enum reros_connproto_t {
  REROS_PROTO_TCP = 0,   /**< @brief TCP/IP.*/
  REROS_PROTO_UDP,       /**< @brief UDP/IP.*/

  REROS_PROTO__LENGTH    /**< @brief Enumeration length.*/
} reros_connproto_t;

/**
 * @brief   Little-endian IP addres record.
 */
typedef union RerosIp {
  uint32_t  dword;      /**< @brief Packed dword.*/
  struct {
    uint8_t field4;     /**< @brief Address field 4.*/
    uint8_t field3;     /**< @brief Address field 3.*/
    uint8_t field2;     /**< @brief Address field 2.*/
    uint8_t field1;     /**< @brief Address field 1.*/
  }         fields;     /**< @brief Individual fields.*/
  uint8_t   bytes[4];   /**< @brief Individual bytes.*/
} RerosIp;

/**
 * @brief   Full address record (IP + port).
 */
typedef struct RerosAddr {
  RerosIp    ip;         /**< @brief Network address (IP).*/
  uint16_t  port;       /**< @brief Transport layer port.*/
} RerosAddr;

/**
 * @brief   Connection information record.
 * @pre     @p RerosConn_LLD defines additional platform-dependent fields.
 */
typedef struct RerosConn {
  RerosAddr          locaddr;    /**< @brief Local address.*/
  RerosAddr          remaddr;    /**< @brief Remote address.*/
  RerosAddr          rpcaddr;    /**< @brief XMLRPC address.*/ /* Add by Zuolong For Base Problem */
  reros_connproto_t  protocol;   /**< @brief Connection protocol.*/
  size_t            recvlen;    /**< @brief Number of received bytes up to now.*/
  size_t            sentlen;    /**< @brief Number of sent bytes up up now.*/

  /* Implementation dependent.*/
  RerosConn__LLD
} RerosConn;

/** @} */

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

reros_err_t rerosHostnameToIp(const RerosString *hostnamep, RerosIp *ipp);
reros_err_t rerosUriToAddr(const RerosString *uri, RerosAddr *addrp);

void rerosConnObjectInit(RerosConn *cp);

reros_bool_t rerosConnIsValid(RerosConn *cp);
reros_err_t rerosConnCreate(RerosConn *cp, reros_connproto_t protocol);
reros_err_t rerosConnBind(RerosConn *cp, const RerosAddr *locaddrp);
reros_err_t rerosConnAccept(RerosConn *cp, RerosConn *spawnedp);
reros_err_t rerosConnListen(RerosConn *cp, reros_cnt_t backlog);
reros_err_t rerosConnConnect(RerosConn *cp, const RerosAddr *remaddrp);
reros_err_t rerosConnRecv(RerosConn *cp,
                        void **bufpp, size_t *buflenp);
reros_err_t rerosConnRecvFrom(RerosConn *cp,
                            void **bufpp, size_t *buflenp,
                            const RerosAddr *remaddrp);
reros_err_t rerosConnSend(RerosConn *cp,
                        const void *bufp, size_t buflen);
reros_err_t rerosConnSendConst(RerosConn *cp,
                             const void *bufp, size_t buflen);
reros_err_t rerosConnSendTo(RerosConn *cp,
                          const void *bufp, size_t buflen,
                          const RerosAddr *remaddrp);
reros_err_t rerosConnSendToConst(RerosConn *cp,
                               const void *bufp, size_t buflen,
                               const RerosAddr *remaddrp);
reros_err_t rerosConnShutdown(RerosConn *cp,
                            reros_bool_t read, reros_bool_t write);
reros_err_t rerosConnClose(RerosConn *cp);

reros_err_t rerosConnGetTcpNoDelay(RerosConn *cp, reros_bool_t *enablep);
reros_err_t rerosConnSetTcpNoDelay(RerosConn *cp, reros_bool_t enable);
reros_err_t rerosConnGetRecvTimeout(RerosConn *cp, uint32_t *msp);
reros_err_t rerosConnSetRecvTimeout(RerosConn *cp, uint32_t ms);
reros_err_t rerosConnGetSendTimeout(RerosConn *cp, uint32_t *msp);
reros_err_t rerosConnSetSendTimeout(RerosConn *cp, uint32_t ms);

const char *rerosConnLastErrorText(const RerosConn *cp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSCONN_H_ */
