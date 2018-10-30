/*******************************************************************************
 *
 * 版权：中国电子科技集团公司第三十二研究所
 * 时间：2015年11月25日
 * 创建：zuolong
 * 修改：
 *
 */

/**
 * @file    rerosBase.h
 * @author  Zuolong
 *
 * @brief   Basic features of the middleware.
 */

#ifndef _REROSBASE_H_
#define _REROSBASE_H_

/*===========================================================================*/
/* HEADER FILES                                                              */
/*===========================================================================*/

#include <rerosconf.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*===========================================================================*/
/* TYPES & MACROS                                                            */
/*===========================================================================*/

/** @addtogroup base_macros */
/** @{ */

/** @brief @p false boolean value. */
#define REROS_FALSE  (0)

/** @brief @p true boolean value. */
#define REROS_TRUE   (!REROS_FALSE)

/** @brief <em>No operation</em> placeholder.*/
#define REROS_NOP    (void)(0)

/** @brief @p semphore success value. */
#define SEM_SUCCESS 0

/** @brief @p semphore failed value. */
#define SEM_FAIL -1

/**
 * @brief   Endianness of the architecture.
 * @details By default, it is set to <i>little-endian</i> through the constant
 *          @p 123. To enable <i>big-endian</i>ness, define it as @p 321.
 */
#if !defined(REROS_ENDIANNESS) || defined(__DOXYGEN__)
#define REROS_ENDIANNESS 123
#endif
#if REROS_ENDIANNESS != 123 && REROS_ENDIANNESS != 321
#error "REROS_ENDIANNESS must be either 123 or 321"
#endif

/**
 * @brief   Pre-processes @p expr as a ROM string.
 *
 * @param[in] expr
 *          Expression to be pre-processed as a ROM string.
 * @return
 *          ROM string representing @p expr.
 *
 * @par     Example
 *          @code{.c}
 *          REROS_STRINGIFY(a == b)
 *          @endcode
 *          results in
 *          @code{.c}
 *          "a == b"
 *          @endcode
 */
#define REROS_STRINGIFY(expr)    #expr

/**
 * @brief   Pre-processes the value of @p define as a ROM string.
 *
 * @param[in] define
 *          Pre-processor definition holding the value to be represented.
 * @return
 *          ROM string representing the value of the @p define definition.
 *
 * @par     Example
 *          @code{.c}
 *          #define VALUE 123+456
 *
            REROS_STRINGIFY2(VALUE)
 *          @endcode
 *          results in
 *          @code{.c}
 *          "123+456"
 *          @endcode
 */
#define REROS_STRINGIFY2(define) REROS_STRINGIFY(define)

/**
 * @brief   Makes the formatted parameters for an @p RerosString object.
 * @details Generates a list of values to be passed to a variable arguments
 *          function.
 * @note    To be used with the <tt>"%.*s"</tt> format string, which must be
 *          supported by a @p printf() compatible user function.
 *
 * @param[in] stringp
 *          Pointer to an @p RerosString object.
 * @return
 *          List of values for a variable arguments function.
 *
 * @par     Example
 * @anchor  base_ex_strarg
 *          @code{.c}
 *          RerosString str = rerosStringCloneZ("Hello World");
 *          printf("I'll print: %.*s!", REROS_STRARG(&str));
 *          rerosStringClean(&str);
 *          @endcode
 *          prints
 *          @verbatim I'll print: Hello World!@endverbatim
 */
#define REROS_STRARG(stringp) \
  ((unsigned)((stringp)->length)), ((stringp)->datap)

#if !defined(REROS_STACK_BLKSIZE) || defined(__DOXYGEN__)
/**
 * @brief   Size of a stack memory block.
 * @note    This macro should be overridden in <tt>rerosconf.h</tt>, so that it
 *          can satisfy memory alignment rules, if any.
 *
 * @param[in] stksize
 *          Nominal stack size, in bytes. The total allocated space may be
 *          greater because of alignment rules, or space reserved for the
 *          <i>thread control block</i>.
 * @return
 *          Size of a stack memory block.
 */
#  define REROS_STACK_BLKSIZE(stksize) \
  ((size_t)(stksize))
#endif

#if !defined(REROS_STACK) || defined(__DOXYGEN__)
/**
 * @brief   Defines a static stack memory chunk.
 * @note    The stack is meant to be allocated statically, as a global
 *          variable.
 * @note    This macro should be overridden in <tt>rerosconf.h</tt>, so that it
 *          can satisfy memory alignment rules, if any.
 *
 * @param[in] varname
 *          Name of the array variable to be defined.
 * @param[in] stksize
 *          Nominal stack size, in bytes. The total allocated space may be
 *          greater because of alignment rules, or space reserved for the
 *          <i>thread control block</i>.
 */
#  define REROS_STACK(varname, stksize) \
  uint8_t varname[REROS_STACK_BLKSIZE(stksize)]
#endif /* !defined(REROS_STACK) || defined(__DOXYGEN__) */

#if !defined(REROS_STACKPOOL_BLKSIZE) || defined(__DOXYGEN__)
/**
 * @brief   Size of a stack pool memory block.
 * @details Automatically adds the space for the reserved @p RerosMemPool
 *          pointer at the very beginning of the stack memory chunk.
 * @note    This macro should be overridden in <tt>rerosconf.h</tt>, so that it
 *          can satisfy memory alignment rules, if any.
 *
 * @param[in] stksize
 *          Nominal stack size, in bytes. The total allocated space may be
 *          greater because of alignment rules, or space reserved for the
 *          <i>thread control block</i>.
 * @return
 *          Size of a stack pool memory block.
 */
#  define REROS_STACKPOOL_BLKSIZE(stksize) \
  (sizeof(void*) + (size_t)(stksize))
#endif /* !defined(REROS_STACKPOOL_BLKSIZE) || defined(__DOXYGEN__) */

#if !defined(REROS_STACKPOOL) || defined(__DOXYGEN__)
/**
 * @brief   Defines a stack pool memory chunk.
 * @details The defined memory pool automatically adds the space for the
 *          reserved @p RerosMemPool pointer at the very beginning of each
 *          stack memory chunk.
 * @note    The stacks are meant to be allocated statically, as a global
 *          variable.
 * @note    This macro should be overridden in <tt>rerosconf.h</tt>, so that it
 *          can satisfy memory alignment rules, if any.
 *
 * @param[in] varname
 *          Name of the array variable to be defined.
 * @param[in] stksize
 *          Nominal stack size, in bytes. The total allocated space may be
 *          greater because of alignment rules, or space reserved for the
 *          <i>thread control block</i>.
 * @param[in] numstacks
 *          Number of stacks in the pool.
 */
#  define REROS_STACKPOOL(varname, stksize, numstacks) \
  uint8_t varname[(numstacks)][REROS_STACKPOOL_BLKSIZE(stksize)]
#endif /* !defined(REROS_STACKPOOL) || defined(__DOXYGEN__) */

#if REROS_USE_ASSERT == REROS_FALSE || !defined(rerosAssert) || defined(__DOXYGEN__)
#  if defined(rerosAssert)
#    undef rerosAssert
#  endif
/**
 * @brief   Evaluates an assertion.
 * @details If the constraint expression does not hold, the system is halted.
 * @warning An assertion is a @b very strong assumption. If an assertion does
 *          not hold, the @b whole system is halted. This is why it is commonly
 *          used only for very strict constraints, which must always hold.
 * @note    By default it does nothing. The user must provide an @p rerosAssert()
 *          macro inside the <tt>rerosconf.h</tt> configuration file to achieve
 *          the required behavior with platform-dependent code.
 * @note    Assertions can be disabled inside the <tt>rerosconf.h</tt>
 *          configuration file. A global switch is @p REROS_USE_ASSERT.
 *
 * @param[in] expr
 *          Assertion constraint expression, which must hold.
 *
 * @par     Example
 *          @code{.c}
 *          #include <assert.h>
 *
 *          #define rerosAssert(expr) \
 *            assert(expr)
 *
 *          void load_value(int *resultp) {
 *
 *              rerosAssert(resultp != NULL);
 *
 *              *resultp = 123;
 *          }
 *          @endcode
 */
#  define rerosAssert(expr)  REROS_NOP
#endif /* !REROS_USE_ASSERT || !defined(rerosAssert) || defined(__DOXYGEN__) */

#if REROS_USE_ERROR_MSG == REROS_FALSE || !defined(rerosError) || defined(__DOXYGEN__)
#  if defined(rerosError)
#    undef rerosError
#  endif
/**
 * @brief   Checks if an error occurred, and generates a message.
 * @details If the error condition holds, a formatted error message is
 *          generated, and a statement (even a code block) is executed.
 * @note    By default it simply ignores the formatted message. The user must
 *          provide an @p rerosError() macro inside the <tt>rerosconf.h</tt>
 *          configuration file to achieve the required behavior with
 *          platform-dependent code.
 * @note    Error messages can be disabled inside the <tt>rerosconf.h</tt>
 *          configuration file. A global switch is @p REROS_USE_ERROR_MSG.
 *
 * @param[in] when
 *          Error condition, which should not hold for a correct code.
 * @param[in] action
 *          A statement, or code block, which is executed if the error
 *          condition holds.
 * @param[in] msgargs
 *          Error message arguments. Must be enclosed between round parentheses
 *          in a @p printf() compatible format.
 *
 * @par     Example
 *          @code{.c}
 *          #include <rerosUser.h>
 *
 *          #define rerosError(when, action, msgargs) \
 *            { if (when) { \
 *                rerosUserErrPrintf("Error at %s:%d\n" \
 *                                  "  function: %s\n" \
 *                                  "  reason:   %s\n" \
 *                                  "  message:  ", \
 *                                  __FILE__, __LINE__, \
 *                                  __PRETTY_FUNCTION__, \
 *                                  #when); \
 *                rerosUserErrPrintf msgargs ; \
 *                { action; } } }
 *
 *          RerosString globalPassword = { 0, NULL };
 *
 *          reros_bool_t set_password(const RerosString *passwp) {
 *
 *              rerosAssert(rerosStringIsValid(passwp));
 *
 *              rerosError(passwp->length < 8, return REROS_FALSE,
 *                        ("Password [%.*s] too short: length %zu < 8",
 *                         REROS_STRARG(passwp), passwp->length));
 *
 *              rerosStringClean(&globalPassword);
 *              globalPassword = rerosStringClone(passwp);
 *              return REROS_TRUE;
 *          }
 *          @endcode
 *          when called with <tt>"F0o_B4r"</tt> as password, prints
 @verbatim
 Error at security.c:123
   function: set_password
   reason:   passwp->length < 8
   message:  Password [F0o_B4r] too short: length 7 < 8
 @endverbatim
 */
#  define rerosError(when, action, msgargs) { if (when) { action; } }
#endif /* !REROS_USE_ERROR_MSG || !defined(rerosError) || defined(__DOXYGEN__) */

/**
 * @brief   Allocates a typed object.
 * @details Allocates a memory chunk on the heap with the size of the provided
 *          type.
 * @see     rerosAlloc()
 *
 * @param[in,out] heapp
 *          Pointer to an initialized @p RerosHeap object, default if @p NULL.
 * @param[in] type
 *          Type of the object to be allocated. To be valid, a valid pointer
 *          type must be obtained by appending a @p * to @p type.
 * @return
 *          The address of the allocated memory chunk, casted to a pointer to
 *          the provided type.
 * @retval NULL
 *          There is not enough contiguous free memory to allocate a memory
 *          block of the requested size.
 *
 * @par     Example
 *          @code{.c}
 *          int *valuep;
 *          valuep = rerosNew(NULL, int);
 *          if (valuep != NULL) {
 *            *valuep = 123;
 *            printf("%d", *valuep);
 *            rerosFree(valuep);
 *          }
 *          @endcode
 */
#define rerosNew(heapp, type) \
  ((type *)rerosAlloc(heapp, sizeof(type)))

/**
 * @brief   Allocates an array.
 * @details Allocates a memory chunk which can hold an array of contiguous
 *          objects of the provided type.
 *
 * @param[in,out] heapp
 *          Pointer to an initialized @p RerosHeap object, default if @p NULL.
 * @param[in] n
 *          Number of objects to be allocated.
 * @param[in] type
 *          Type of the object to be allocated. To be valid, a valid pointer
 *          type must be obtained by appending a @p * to @p type.
 * @return
 *          The address of the allocated memory chunk, casted to a pointer to
 *          the provided type.
 * @retval NULL
 *          There is not enough contiguous free memory to allocate a memory
 *          block of the requested size.
 */
#define rerosArrayNew(heapp, n, type) \
  ((type *)rerosAlloc(heapp, (size_t)(n) * sizeof(type)))

/**
 * @brief   Allocates an array.
 * @details Allocates a memory chunk which can hold an array of contiguous
 *          chunks with the provided size.
 *
 * @param[in,out] heapp
 *          Pointer to an initialized @p RerosHeap object, default if @p NULL.
 * @param[in] n
 *          Number of objects to be allocated.
 * @param[in] size
 *          Size of each single chunk to be allocated.
 * @return
 *          The address of the allocated memory chunk.
 * @retval NULL
 *          There is not enough contiguous free memory to allocate a memory
 *          block of the requested size.
 */
#define rerosArrayAlloc(heapp, n, size) \
  rerosAlloc(heapp, (size_t)(n) * (size_t)(size))

/** @} */

/** @addtogroup base_types */
/** @{ */

/**
 * @brief   Boolean data type.
 */
typedef uint8_t reros_bool_t;

/**
 * @brief   Unsigned counter data type.
 */
typedef uint32_t reros_cnt_t;

/**
 * @brief   ROS time.
 */
typedef struct reros_time_t {
  uint32_t  sec;    /**< @brief Seconds component.*/
  uint32_t  nsec;   /**< @brief Nanoseconds component.*/
} reros_time_t;

/**
 * @brief   ROS duration.
 */
typedef struct reros_duration_t {
  int32_t   sec;    /**< @brief Seconds component.*/
  int32_t   nsec;   /**< @brief Nanoseconds component.*/
} reros_duration_t;

/**
 * @brief   Error codes enumerator.
 */
enum {
  REROS_OK               =    0, /**< @brief No errors.*/
  REROS_ERR              =    -1, /**< @brief No errors.*/
  REROS_ERR_TIMEOUT      = -100, /**< @brief Timeout lost.*/
  REROS_ERR_NOMEM        = -101, /**< @brief Not enough free memory.*/
  REROS_ERR_PARSE        = -102, /**< @brief Parsing error.*/
  REROS_ERR_EOF          = -103, /**< @brief End of file/stream reached.*/
  REROS_ERR_BADPARAM     = -104, /**< @brief Bad parameter.*/
  REROS_ERR_NOCONN       = -105, /**< @brief Inactive connection.*/
  REROS_ERR_BADCONN      = -106, /**< @brief Bad connection, check the low-level error code.*/
  REROS_ERR_NOTIMPL      = -107  /**< @brief Feature not implemented.*/
};

/** @name Function pointers */
/** @{ */

/**
 * @brief   One-parameter procedure function pointer.
 *
 * @param[in] data
 *          Pointer to a generic data structure, or embedded value.
 * @return
 *          Error code.
 */
typedef reros_err_t (*reros_proc_f)(void *data);

/**
 * @brief   Predicate function.
 * @details Used to evaluate a predicate on an object.
 *
 * @param[in] obj
 *          Predicate object to be evaluated.
 * @return
 *          Value of the predicate evaluation.
 */
typedef reros_bool_t (*reros_pred_f)(const void *obj);

/**
 * @brief   Comparison function.
 * @details Used to evaluate the comparison of two objects; e.g. equality,
 *          inclusion, ordered comparison, etc.
 *
 * @param[in] obj1p
 *          First operand object.
 * @param[in] obj2p
 *          Second operand object.
 * @return
 *          Comparison predicate evaluation.
 */
typedef reros_bool_t (*reros_cmp_f)(const void *obj1p, const void *obj2p);

/**
 * @brief   Allocation function.
 * @details Generic allocation function pointer, compatible with a @p malloc()
 *          signature.
 *
 * @param[in] size
 *          Size of the memory block to be allocated, in bytes.
 * @return
 *          The address of the allocated memory chunk.
 * @retval NULL
 *          There is not enough contiguous free memory to allocate a memory
 *          block of the requested size.
 */
typedef void *(*reros_alloc_f)(size_t size);

/**
 * @brief   Deletion procedure.
 * @details Generic function pointer called to free the memory block allocated
 *          for an object.
 *
 * @post    @p objp points to an invalid address.
 *
 * @param[in] obj
 *          Pointer to the memory block to be deallocated.
 *          A @p NULL value will simply be ignored.
 */
typedef void (*reros_delete_f)(void *objp);

/** @} */

#if REROS_USE_BUILTIN_MEMPOOL || defined(__DOXYGEN__)
/**
 * @brief   Built-in memory pool object.
 */
typedef struct RerosMemPool {
  void          *headp;         /**< @brief Pointer to the first free block.*/
  size_t        blockSize;      /**< @brief Block size.*/
  reros_alloc_f  allocator;      /**< @brief Allocation provider.*/
  reros_cnt_t    free;           /**< @brief Number of free blocks.*/
  RerosMutex     lock;           /**< @brief Memory pool lock.*/
} RerosMemPool;
#endif

/**
 * @brief   String object.
 * @details A string is stored as an object containing the string length and
 *          the pointer to the character data.
 */
typedef struct RerosString {
  size_t    length;             /**< @brief String length.*/
  char      *datap;             /**< @brief String data.*/
} RerosString;

/** @name List */
/** @{ */

/**
 * @brief   List node, forward only.
 */
typedef struct RerosListNode {
  void                  *datap; /**< @brief Generic data pointer.*/
  struct RerosListNode   *nextp; /**< @brief Pointer to the next list entry node.*/
} RerosListNode;

/**
 * @brief   Linked list, forward only.
 */
typedef struct RerosList {
  RerosListNode  *headp;         /**< @brief Pointer to the list head node.*/
  reros_cnt_t    length;         /**< @brief Number of list entries.*/
} RerosList;

/** @} */

/** @name Messaging related */
/** @{ */

/**
 * @brief   Message type descriptor.
 */
typedef struct RerosMsgType {
  RerosString name;       /**< @brief Type name.*/
  RerosString desc;       /**< @brief Long description.*/
  RerosString md5str;     /**< @brief Textual MD5 sum.*/
} RerosMsgType;

/**
 * @brief   Topic and service flags.
 */
typedef struct reros_topicflags_t {
  unsigned service    : 1;      /**< @brief Service/!TcpStatus connection.*/
  unsigned probe      : 1;      /**< @brief Just probing, do not call the handler.*/
  unsigned persistent : 1;      /**< @brief Peristent service connection (by client).*/
  unsigned latching   : 1;      /**< @brief Latching mode (i.e. send the
                                            last value to new subscribers).*/
  unsigned noDelay    : 1;      /**< @brief Nagle algorithm disabled.*/
  unsigned deleted    : 1;      /**< @brief Deleted topic descriptor, free asap.*/
} reros_topicflags_t;

/**
 * @brief   Topic descriptor.
 */
typedef struct RerosTopic {
  RerosString        name;       /**< @brief Topic/Service name.*/
  const RerosMsgType *typep;     /**< @brief Topic/Service message type.*/
  reros_proc_f       procf;      /**< @brief Procedure handler.*/
  reros_topicflags_t flags;      /**< @brief Topic/Service flags.*/

  /* Allocation stuff.*/
  reros_cnt_t        refcnt;     /**< @brief Reference counter.*/
} RerosTopic;

/** @} */
/** @} */

/*===========================================================================*/
/* GLOBAL VARIABLES                                                          */
/*===========================================================================*/

extern RerosList rerosMsgTypeList;
extern RerosList rerosSrvTypeList;

extern const reros_topicflags_t reros_nulltopicflags;
extern const reros_topicflags_t reros_nullserviceflags;

/*===========================================================================*/
/* GLOBAL PROTOTYPES                                                         */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void rerosInit(void);
const char *rerosErrorText(reros_err_t err);

void *rerosAlloc(RerosMemHeap *heapp, size_t size);
void rerosFree(void *chunkp);

void rerosMemPoolObjectInit(RerosMemPool *poolp, size_t blocksize,
                           reros_alloc_f allocator);
void *rerosMemPoolAlloc(RerosMemPool *poolp);
void rerosMemPoolFree(RerosMemPool *poolp, void *objp);
reros_cnt_t rerosMemPoolNumFree(RerosMemPool *poolp);
void rerosMemPoolLoadArray(RerosMemPool *poolp, void *arrayp, reros_cnt_t n);
size_t rerosMemPoolBlockSize(RerosMemPool *poolp);

void rerosStringObjectInit(RerosString *strp);
RerosString rerosStringAssignN(const char *datap, size_t datalen);
RerosString rerosStringAssignZ(const char *szp);
RerosString rerosStringClone(const RerosString *strp);
RerosString rerosStringCloneN(const char *datap, size_t datalen);
RerosString rerosStringCloneZ(const char *szp);
void rerosStringClean(RerosString *strp);
void rerosStringDelete(RerosString *strp);
reros_bool_t rerosStringIsValid(const RerosString *strp);
reros_bool_t rerosStringNotEmpty(const RerosString *strp);
int rerosStringCmp(const RerosString *str1, const RerosString *str2);

void rerosMsgTypeObjectInit(RerosMsgType *typep);
void rerosMsgTypeClean(RerosMsgType *typep);
void rerosMsgTypeDelete(RerosMsgType *typep);

reros_bool_t rerosMsgTypeNodeHasName(const RerosListNode *nodep,
                                   const RerosString *namep);

void rerosRegisterStaticMsgType(const RerosString *namep,
                               const RerosString *descp,
                               const RerosString *md5sump);
void rerosRegisterStaticMsgTypeSZ(const char *namep,
                                 const char *descp,
                                 const char *md5sump);
const RerosMsgType *rerosFindStaticMsgType(const RerosString *namep);
const RerosMsgType *rerosFindStaticMsgTypeSZ(const char *namep);

void rerosRegisterStaticSrvType(const RerosString *namep,
                               const RerosString *descp,
                               const RerosString *md5sump);
void rerosRegisterStaticSrvTypeSZ(const char *namep,
                                 const char *descp,
                                 const char *md5sump);
const RerosMsgType *rerosFindStaticSrvType(const RerosString *namep);
const RerosMsgType *rerosFindStaticSrvTypeSZ(const char *namep);

void rerosTopicObjectInit(RerosTopic *tp);
void rerosTopicClean(RerosTopic *tp);
void rerosTopicDelete(RerosTopic *tp);
reros_cnt_t rerosTopicRefInc(RerosTopic *tp);
reros_cnt_t rerosTopicRefDec(RerosTopic *tp);

void rerosListNodeObjectInit(RerosListNode *np);
void rerosListNodeDelete(RerosListNode *np, reros_delete_f datadelf);

void rerosListObjectInit(RerosList *lstp);
void rerosListClean(RerosList *lstp, reros_delete_f datadelf);
void rerosListDelete(RerosList *lstp, reros_delete_f datadelf);
reros_cnt_t rerosListLength(const RerosList *lstp);
reros_bool_t rerosListIsValid(const RerosList *lstp);
reros_bool_t rerosListNotEmpty(const RerosList *lstp);
reros_bool_t rerosListContains(const RerosList *lstp, const RerosListNode *np);
int rerosListIndexOf(const RerosList *lstp, const RerosListNode *np);
RerosListNode *rerosListFind(const RerosList *lstp,
                           reros_cmp_f filter, const void *featurep);
void rerosListAdd(RerosList *lstp, RerosListNode *np);
RerosListNode *rerosListRemove(RerosList *lstp, const RerosListNode *np);

reros_bool_t rerosStringListNodeHasString(const RerosListNode *np,
                                        const RerosString *strp);
RerosListNode *rerosStringListFindByName(const RerosList *lstp,
                                       const RerosString *strp);

reros_bool_t rerosTopicListNodeHasTopic(const RerosListNode *np,
                                      const RerosTopic *topicp);
reros_bool_t rerosTopicListNodeHasName(const RerosListNode *np,
                                     const RerosString *namep);
RerosListNode *rerosTopicListFindByTopic(const RerosList *lstp,
                                       const RerosTopic *topicp);
RerosListNode *rerosTopicListFindByName(const RerosList *lstp,
                                      const RerosString *namep);

#ifdef __cplusplus
}
#endif
#endif /* _REROSBASE_H_ */
