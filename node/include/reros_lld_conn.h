/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2016年1月11日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    reros_lld_conn.c
 * @author  Zuolong
 *
 * @brief   Low-level connectivity features of the middleware.
 */

#ifndef _REROS_LLD_CONN_H_
#define _REROS_LLD_CONN_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosConn.h"

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

reros_err_t reros_lld_hostnametoip(const RerosString *hostnamep,
                                 RerosIp *ipp);
void reros_lld_conn_objectinit(RerosConn *cp);
reros_bool_t reros_lld_conn_isvalid(RerosConn *cp);
reros_err_t reros_lld_conn_create(RerosConn *cp, reros_connproto_t protocol);
reros_err_t reros_lld_conn_bind(RerosConn *cp, const RerosAddr *locaddrp);
reros_err_t reros_lld_conn_accept(RerosConn *cp, RerosConn *spawnedp);
reros_err_t reros_lld_conn_listen(RerosConn *cp, reros_cnt_t backlog);
reros_err_t reros_lld_conn_connect(RerosConn *cp, const RerosAddr *remaddrp);
reros_err_t  reros_lld_conn_recv(RerosConn *cp,
                               void **bufpp, size_t *buflenp);
reros_err_t  reros_lld_conn_recvfrom(RerosConn *cp,
                                   void **bufpp, size_t *buflenp,
                                   const RerosAddr *remaddrp);
reros_err_t  reros_lld_conn_send(RerosConn *cp,
                               const void *bufp, size_t buflen);
reros_err_t  reros_lld_conn_sendconst(RerosConn *cp,
                                    const void *bufp, size_t buflen);
reros_err_t  reros_lld_conn_sendto(RerosConn *cp,
                                 const void *bufp, size_t buflen,
                                 const RerosAddr *remaddrp);
reros_err_t  reros_lld_conn_sendtoconst(RerosConn *cp,
                                      const void *bufp, size_t buflen,
                                      const RerosAddr *remaddrp);
reros_err_t reros_lld_conn_shutdown(RerosConn *cp,
                                  reros_bool_t read, reros_bool_t write);
reros_err_t reros_lld_conn_close(RerosConn *cp);

reros_err_t reros_lld_conn_gettcpnodelay(RerosConn *cp, reros_bool_t *enablep);
reros_err_t reros_lld_conn_settcpnodelay(RerosConn *cp, reros_bool_t enable);
reros_err_t reros_lld_conn_getrecvtimeout(RerosConn *cp, uint32_t *msp);
reros_err_t reros_lld_conn_setrecvtimeout(RerosConn *cp, uint32_t ms);
reros_err_t reros_lld_conn_getsendtimeout(RerosConn *cp, uint32_t *msp);
reros_err_t reros_lld_conn_setsendtimeout(RerosConn *cp, uint32_t ms);

const char *reros_lld_conn_lasterrortext(const RerosConn *cp);

#ifdef __cplusplus
}
#endif
#endif /* _REROS_LLD_CONN_H_ */
