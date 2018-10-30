/*
Copyright (c) 2015-2016, CETC32. All rights reserved.

Zuo Long <asdzuo@qq.com>
Hubing   <hubinghank@163.com>
*/

/**
 * @file    rerosMsgTypes.h
 * @author  LiGuang
 *
 * @brief   TCPROS message and service descriptors.
 */

#ifndef _REROSMSGTYPES_H_
#define _REROSMSGTYPES_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include <rerosTcpRos.h>

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/
/*  MESSAGE TYPES                                                            */
/*===========================================================================*/

/** @addtogroup tcpros_msg_types */
/** @{ */

/*~~~ MESSAGE: demo_test/example_message ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief   TCPROS <tt>demo_test/example_message</tt> message descriptor.
 * @details MD5 sum: <tt>66a88178a10328d6ece4bb53d1bb5181</tt>.
 */
struct msg__demo_test__example_message {
  int32_t   A;
  int32_t   B;
  int32_t   C;
};

/** @} */

/*===========================================================================*/
/* SERVICE TYPES                                                             */
/*===========================================================================*/

/** @addtogroup tcpros_srv_types */
/** @{ */

/*~~~ SERVICE: demo_test/example_srv ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief   TCPROS <tt>demo_test/example_srv</tt> service request descriptor.
 */
struct in_srv__demo_test__example_srv {
  int32_t   A;
  int32_t   B;
  int32_t   C;
};

/**
 * @brief   TCPROS <tt>demo_test/example_srv</tt> service response descriptor.
 */
struct out_srv__demo_test__example_srv {
  int32_t   SUM;
};

/** @} */

/*===========================================================================*/
/* MESSAGE CONSTANTS                                                         */
/*===========================================================================*/

/** @addtogroup tcpros_msg_consts */
/** @{ */

/* There are no message costants.*/

/** @} */

/*===========================================================================*/
/* SERVICE CONSTANTS                                                         */
/*===========================================================================*/

/** @addtogroup tcpros_srv_consts */
/** @{ */

/* There are no service costants.*/

/** @} */

/*===========================================================================*/
/* MESSAGE PROTOTYPES                                                        */
/*===========================================================================*/

/*~~~ MESSAGE: demo_test/example_message ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t length_msg__demo_test__example_message(
  struct msg__demo_test__example_message *objp
);
void init_msg__demo_test__example_message(
  struct msg__demo_test__example_message *objp
);
reros_err_t copy_msg__demo_test__example_message(
  struct msg__demo_test__example_message *src_objp,
  struct msg__demo_test__example_message *des_objp
);
void clean_msg__demo_test__example_message(
  struct msg__demo_test__example_message *objp
);
reros_err_t recv_msg__demo_test__example_message(
  RerosTcpRosStatus *tcpstp,
  struct msg__demo_test__example_message *objp
);
reros_err_t send_msg__demo_test__example_message(
  RerosTcpRosStatus *tcpstp,
  struct msg__demo_test__example_message *objp
);

/*===========================================================================*/
/* SERVICE PROTOTYPES                                                        */
/*===========================================================================*/

/*~~~ SERVICE: demo_test/example_srv ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t length_in_srv__demo_test__example_srv(
  struct in_srv__demo_test__example_srv *objp
);
size_t length_out_srv__demo_test__example_srv(
  struct out_srv__demo_test__example_srv *objp
);
void init_in_srv__demo_test__example_srv(
  struct in_srv__demo_test__example_srv *objp
);
void init_out_srv__demo_test__example_srv(
  struct out_srv__demo_test__example_srv *objp
);
void clean_in_srv__demo_test__example_srv(
  struct in_srv__demo_test__example_srv *objp
);
void clean_out_srv__demo_test__example_srv(
  struct out_srv__demo_test__example_srv *objp
);
reros_err_t recv_in_srv__demo_test__example_srv(
  RerosTcpRosStatus *tcpstp,
  struct in_srv__demo_test__example_srv *objp
);
reros_err_t send_out_srv__demo_test__example_srv(
  RerosTcpRosStatus *tcpstp,
  struct out_srv__demo_test__example_srv *objp
);
reros_err_t send_in_srv__demo_test__example_srv(
  RerosTcpRosStatus *tcpstp,
  struct in_srv__demo_test__example_srv *objp
);
reros_err_t recv_out_srv__demo_test__example_srv(
  RerosTcpRosStatus *tcpstp,
  struct out_srv__demo_test__example_srv *objp
);

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

void rerosMsgTypesRegStaticTypes(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _REROSMSGTYPES_H_ */

