/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月16日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosUser.h
 * @author  Zuolong
 *
 * @brief   User-defined callback functions.
 */

#ifndef _REROSUSER_H_
#define _REROSUSER_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosBase.h"
#include "rerosNode.h"
#include "rerosRpcCall.h"

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosUserNodeConfigLoad(RerosNodeConfig *cfgp);
void rerosUserNodeConfigSave(const RerosNodeConfig *cfgp);

reros_err_t rerosUserShutdown(const RerosString *msgp);

void rerosUserRegisterStaticTypes(void);

reros_err_t rerosUserPublishTopics(void);
reros_err_t rerosUserUnpublishTopics(void);

reros_err_t rerosUserSubscribeTopics(void);
reros_err_t rerosUserUnsubscribeTopics(void);

reros_err_t rerosUserPublishServices(void);
reros_err_t rerosUserUnpublishServices(void);

reros_err_t rerosUserSubscribeParams(void);
reros_err_t rerosUserUnsubscribeParams(void);
reros_err_t rerosUserParamUpdate(const RerosString *keyp,
                               const RerosRpcParam *paramp);

#ifdef __cplusplus
}
#endif
#endif /* _REROSUSER_H_ */
