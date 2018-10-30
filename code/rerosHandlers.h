/*
Copyright (c) 2015-2016, CETC32. All rights reserved.

Zuo Long <asdzuo@qq.com>
Hubing   <hubinghank@163.com>
*/

/**
 * @file    rerosHandlers.h
 * @author  LiGuang
 *
 * @brief   TCPROS topic and service handlers.
 */

#ifndef _REROSHANDLERS_H_
#define _REROSHANDLERS_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosMsgTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/**
 * @brief  Subscriber Callback Function pointer of Topic: /message.
 *
 * @param[in] datap
 *           Pointer to a generic data structure.
 * @return 
 *           None.
 */
typedef void (*subcallback__message_f)(struct msg__demo_test__example_message *datap);

/**
 *@brief  Service Callback Function pointer of Service: /service.
 *
 *@param[in] requestp
 *         Pointer to requset data structure.
 *@param[out] resultp
 *         Pointer to result data structure.
 *@return 
 *         None.
 */
typedef void (*srvcallback__service_f)(struct in_srv__demo_test__example_srv *requestp,struct out_srv__demo_test__example_srv *resultp);


/*===========================================================================*/
/* PUBLISHED TOPIC PROTOTYPES                                                */
/*===========================================================================*/
/*~~~ PUBLISHED TOPIC: /message ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
reros_err_t pub_tpc__message(RerosTcpRosStatus *tcpstp);


/*===========================================================================*/
/* SUBSCRIBED TOPIC PROTOTYPES                                               */
/*===========================================================================*/
/*~~~ SUBSCRIBED TOPIC: /message ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
reros_err_t sub_tpc__message(RerosTcpRosStatus *tcpstp);


/*===========================================================================*/
/* PUBLISHED SERVICE PROTOTYPES                                              */
/*===========================================================================*/
/*~~~ PUBLISHED SERVICE: /service ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
reros_err_t pub_srv__service(RerosTcpRosStatus *tcpstp);


/*===========================================================================*/
/* CALLED SERVICE PROTOTYPES                                                 */
/*===========================================================================*/
/*~~~ CALLED SERVICE: /service ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
reros_err_t call_srv__service(
  RerosTcpRosStatus *tcpstp,
  struct in_srv__demo_test__example_srv *inmsgp,
  struct out_srv__demo_test__example_srv *outmsgp
);


/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/
void rerosHandlersPublishTopics(void);
void rerosHandlersUnpublishTopics(void);

void rerosHandlersSubscribeTopics(void);
void rerosHandlersUnsubscribeTopics(void);

void rerosHandlersPublishServices(void);
void rerosHandlersUnpublishServices(void);

/*===========================================================================*/
/* API                                                                       */
/*===========================================================================*/
/* Publish Topic API */
reros_err_t rerosPublish__message(struct msg__demo_test__example_message msg);

/* Register Subscribe Callback API */
reros_err_t rerosSubscribe__message_RegCallback(subcallback__message_f func_p) ;

/* Register Service Function API */
reros_err_t rerosService__service_RegFunction(srvcallback__service_f func_p);

/* Call Service Function API */
reros_err_t rerosCallSrv__service(
struct in_srv__demo_test__example_srv *requestp,
struct out_srv__demo_test__example_srv *resultp
);

/*global mem free*/
void reros_GlobalMemfree();
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _REROSHANDLERS_H_ */

