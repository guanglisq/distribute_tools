/*
Copyright (c) 2015-2016, CETC32. All rights reserved.

Zuo Long <asdzuo@qq.com>
Hubing   <hubinghank@163.com>
*/

/**
 * @file    rerosHandlers.c
 * @author  LiGuang
 *
 * @brief   TCPROS topic and service handlers.
 */

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include "rerosHandlers.h"

#include <rerosNode.h>
#include <rerosTcpRos.h>
#include <rerosUser.h>

/*===========================================================================*/
/* LOCAL VARIABLES                                                           */
/*===========================================================================*/

/** @brief topic <tt>/message</tt> publish semphore */
static RerosSemphore *tpc__message_semp = NULL;

/** @brief topic type <tt>demo_test/example_message</tt> publish variable */
static struct msg__demo_test__example_message data__message;

static subcallback__message_f cb__message_fp = NULL;

static srvcallback__service_f srv__service_fp = NULL;

/*===========================================================================*/
/* PUBLISHED TOPIC FUNCTIONS                                                 */
/*===========================================================================*/

/** @addtogroup tcpros_pubtopic_funcs */
/** @{ */

/*~~~ PUBLISHED TOPIC: /message ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name Topic <tt>/message</tt> publisher */
/** @{ */

/**
 * @brief   TCPROS <tt>/message</tt> published topic handler.
 *
 * @param[in,out] tcpstp
 *          Pointer to a working @p RerosTcpRosStatus object.
 * @return
 *          Error code.
 */
reros_err_t pub_tpc__message(RerosTcpRosStatus *tcpstp) {

  /* Message allocation and initialization.*/
  REROS_TPC_INIT_H(msg__demo_test__example_message);

  /* Published messages loop.*/
  while (!rerosTcpRosStatusCheckExit(tcpstp)) {

  if(NULL != tpc__message_semp){
    rerosSemphoreWait(tpc__message_semp);
    copy_msg__demo_test__example_message(&data__message,msgp);

    /* Send the message.*/
    REROS_MSG_SEND_LENGTH(msgp, msg__demo_test__example_message);
    REROS_MSG_SEND_BODY(msgp, msg__demo_test__example_message);

    /* Dispose the contents of the message.*/
    clean_msg__demo_test__example_message(msgp);

  }
  else {
    rerosThreadSleepMsec(50);
    }
  }
  tcpstp->err = REROS_OK;

_finally:
  /* Message deinitialization and deallocation.*/
  REROS_TPC_UNINIT_H(msg__demo_test__example_message);
  return tcpstp->err;
}

/** @} */

/** @} */

/*===========================================================================*/
/* SUBSCRIBED TOPIC FUNCTIONS                                                */
/*===========================================================================*/

/** @addtogroup tcpros_subtopic_funcs */
/** @{ */

/*~~~ SUBSCRIBED TOPIC: /message ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name Topic <tt>/message</tt> subscriber */
/** @{ */

/**
 * @brief   TCPROS <tt>/message</tt> subscribed topic handler.
 *
 * @param[in,out] tcpstp
 *          Pointer to a working @p RerosTcpRosStatus object.
 * @return
 *          Error code.
 */
reros_err_t sub_tpc__message(RerosTcpRosStatus *tcpstp) {

  /* Message allocation and initialization.*/
  REROS_TPC_INIT_H(msg__demo_test__example_message);

  /* Subscribed messages loop.*/
  while (!rerosTcpRosStatusCheckExit(tcpstp)) {
    /* Receive the next message.*/
    REROS_MSG_RECV_LENGTH();
    REROS_MSG_RECV_BODY(msgp, msg__demo_test__example_message);

    /* Process the received message.*/
    if(NULL != cb__message_fp){
      cb__message_fp(msgp);
    }

    /* Dispose the contents of the message.*/
    clean_msg__demo_test__example_message(msgp);
  }
  tcpstp->err = REROS_OK;

_finally:
  /* Message deinitialization and deallocation.*/
  REROS_TPC_UNINIT_H(msg__demo_test__example_message);
  return tcpstp->err;
}

/** @} */

/** @} */

/*===========================================================================*/
/* PUBLISHED SERVICE FUNCTIONS                                               */
/*===========================================================================*/

/** @addtogroup tcpros_pubservice_funcs */
/** @{ */

/*~~~ PUBLISHED SERVICE: /service ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name Service <tt>/service</tt> publisher */
/** @{ */

/**
 * @brief   TCPROS <tt>/service</tt> published service handler.
 *
 * @param[in,out] tcpstp
 *          Pointer to a working @p RerosTcpRosStatus object.
 * @return
 *          Error code.
 */
reros_err_t pub_srv__service(RerosTcpRosStatus *tcpstp) {

  /* Service messages allocation and initialization.*/
  REROS_SRV_INIT_HIHO(in_srv__demo_test__example_srv,
                     out_srv__demo_test__example_srv);

  /* Service message loop (if the service is persistent).*/
  do {
    /* Receive the request message.*/
    REROS_MSG_RECV_LENGTH();
    REROS_MSG_RECV_BODY(inmsgp, in_srv__demo_test__example_srv);

    tcpstp->err = REROS_OK;
    rerosStringClean(&tcpstp->errstr);

    /*Process the received message.*/
    if(NULL != srv__service_fp){

      srv__service_fp(inmsgp,outmsgp);
      okByte = 1;
    }
    else{
      okByte = 0;
    }

    /* Dispose the contents of the request message.*/
    clean_in_srv__demo_test__example_srv(inmsgp);

    /* Send the response message.*/
    REROS_SRV_SEND_OKBYTE_ERRSTR();
    REROS_MSG_SEND_LENGTH(outmsgp, out_srv__demo_test__example_srv);
    REROS_MSG_SEND_BODY(outmsgp, out_srv__demo_test__example_srv);

    /* Dispose the contents of the response message.*/
    clean_out_srv__demo_test__example_srv(outmsgp);
  } while (tcpstp->topicp->flags.persistent &&
           !rerosTcpRosStatusCheckExit(tcpstp));
  tcpstp->err = REROS_OK;

_finally:
  /* Service messages deinitialization and deallocation.*/
  REROS_SRV_UNINIT_HIHO(in_srv__demo_test__example_srv,
                       out_srv__demo_test__example_srv);
  return tcpstp->err;
}

/** @} */

/** @} */

/*===========================================================================*/
/* CALLED SERVICE FUNCTIONS                                                  */
/*===========================================================================*/

/** @addtogroup tcpros_callservice_funcs */
/** @{ */

/*~~~ CALLED SERVICE: /service ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @name Service <tt>/service</tt> caller */
/** @{ */

/**
 * @brief   TCPROS <tt>/service</tt> called service handler.
 *
 * @param[in,out] tcpstp
 *          Pointer to a working @p RerosTcpRosStatus object.
 * @param[in] inmsgp
 *          Pointer to the initialized request message.
 * @param[out] outmsgp
 *          Pointer to the allocated response message. It will be initialized
 *          by this function. The service result will be written there only
 *          if the call is successful.
 * @return
 *          Error code.
 */
reros_err_t call_srv__service(
  RerosTcpRosStatus *tcpstp,
  struct in_srv__demo_test__example_srv *inmsgp,
  struct out_srv__demo_test__example_srv *outmsgp
) {

  /* Service messages allocation and initialization.*/
  REROS_SRVCALL_INIT(in_srv__demo_test__example_srv,
                    out_srv__demo_test__example_srv);

  /* Send the request message.*/
  REROS_MSG_SEND_LENGTH(inmsgp, in_srv__demo_test__example_srv);
  REROS_MSG_SEND_BODY(inmsgp, in_srv__demo_test__example_srv);

  /* Receive the response message.*/
  REROS_SRV_RECV_OKBYTE();
  REROS_MSG_RECV_LENGTH();
  REROS_MSG_RECV_BODY(outmsgp, out_srv__demo_test__example_srv);

  tcpstp->err = REROS_OK;
_finally:
  return tcpstp->err;
}

/** @} */

/** @} */

/*===========================================================================*/
/* GLOBAL FUNCTIONS                                                          */
/*===========================================================================*/

/** @addtogroup tcpros_funcs */
/** @{ */

/**
 * @brief   Registers all the published topics to the Master node.
 * @note    Should be called at node initialization.
 */
void rerosHandlersPublishTopics(void) {

  /* /message */
  tpc__message_semp = rerosSemphoreOpen("/message");
  rerosNodePublishTopicSZ(
    "/message",
    "demo_test/example_message",
    (reros_proc_f)pub_tpc__message,
    reros_nulltopicflags
  );
}

/**
 * @brief   Unregisters all the published topics to the Master node.
 * @note    Should be called at node shutdown.
 */
void rerosHandlersUnpublishTopics(void) {

    /* /message */
    rerosNodeUnpublishTopicSZ(
        "/message"
    );
    tpc__message_semp = NULL;
    rerosSemphoreUnlink("/message");

}

/**
 * @brief   Registers all the subscribed topics to the Master node.
 * @note    Should be called at node initialization.
 */
void rerosHandlersSubscribeTopics(void) {

  /* /message */
  rerosNodeSubscribeTopicSZ(
    "/message",
    "demo_test/example_message",
    (reros_proc_f)sub_tpc__message,
    reros_nulltopicflags
  );
}

/**
 * @brief   Unregisters all the subscribed topics to the Master node.
 * @note    Should be called at node shutdown.
 */
void rerosHandlersUnsubscribeTopics(void) {

  /* /message */
  rerosNodeUnsubscribeTopicSZ(
    "/message"
  );
}

/**
 * @brief   Registers all the published services to the Master node.
 * @note    Should be called at node initialization.
 */
void rerosHandlersPublishServices(void) {

  /* /service */
  rerosNodePublishServiceSZ(
    "/service",
    "demo_test/example_srv",
    (reros_proc_f)pub_srv__service,
    reros_nullserviceflags
  );
}

/**
 * @brief   Unregisters all the published services to the Master node.
 * @note    Should be called at node shutdown.
 */
void rerosHandlersUnpublishServices(void) {

  /* /service */
  rerosNodeUnpublishServiceSZ(
    "/service"
  );
}

/**
 * @brief Publish a Message of Topic <tt>/message</tt>.
*/
reros_err_t rerosPublish__message(struct msg__demo_test__example_message msg){
  reros_err_t ret;
  ret = copy_msg__demo_test__example_message(&msg,&data__message);
  if( (REROS_OK == ret) && (NULL != tpc__message_semp) ){
    rerosSemphoreFlush(tpc__message_semp);
  }
  return ret;
}


/**
 *@brief  Register a Subscribe Callback of Topic <tt>/message</tt>.
*/
reros_err_t rerosSubscribe__message_RegCallback(subcallback__message_f func_p) {
  if(NULL != func_p){
    cb__message_fp = func_p;
    return REROS_OK;
  }
  else{
    return REROS_ERR_BADPARAM;
  }
}

/**
 * @brief Register a Service Function of Service <tt>/service</tt>.
*/
reros_err_t rerosService__service_RegFunction(srvcallback__service_f func_p){
  if ( NULL != func_p ){
    srv__service_fp = func_p;
    return REROS_OK;
  }
  else{
    return REROS_ERR_BADPARAM;
  }
}

/**
 * @brief Call <tt>/service</tt> Service.
*/
reros_err_t rerosCallSrv__service(
struct in_srv__demo_test__example_srv *requestp,
struct out_srv__demo_test__example_srv *resultp
){
  if(( NULL != requestp ) && ( NULL != resultp )){
    return rerosNodeCallServiceSZ(
                  "/service",
                  "demo_test/example_srv",
                  (reros_tcpsrvcall_t)call_srv__service,
                  reros_nullserviceflags,
                  (void *)requestp,
                  (void *)resultp);
  }
  else{
    return REROS_ERR_BADPARAM;
  }
}

void reros_GlobalMemfree()
{
  clean_msg__demo_test__example_message(&data__message);
}


/** @} */

