/*************************************************
 * 
	Copyright (c) 2016, CETC32. All rights reserved.

	Author 	: 	Li Guang
	Date	:	2016.5.9

**************************************************/
#ifndef __MASTERTHREADPOOL_H__
#define __MASTERTHREADPOOL_H__
#include <iostream>
#include <stdlib.h>
#include <Masterutility.h>
#include <MasterBase.h>
#include <MasterMemPool.h>

#define 	Reg_Mag_Sub_PRIO 	351

namespace CMaster {
	
	class MasterThreadPool
	{
		public:
			/**< @brief  Create a server object.*/
			MasterThreadPool();
			/**< @brief  Destructor.*/
			virtual ~MasterThreadPool();
			/**< @brief Memory pool for thread stacks.*/
			MasterMemPool   stackPoolp;
			/**< @brief Thread pool size.*/
			master_cnt_t    size;
			/**< @brief User routine for children.*/
			master_proc_f   routine;
			/**< @brief Default thread name.*/
			const char    *namep;
			/**< @brief Default thread priority.*/
			master_prio_t   priority;
			/**< @brief Thread identifier array.*/
			MasterThreadId  *threadsp;
			/**< @brief Next thread argument pointer.*/
			void          *argp;
			/**< @brief Ready threads counter.*/
			master_cnt_t    readyCnt;
			/**< @brief Ready threads mutex.*/
			MasterMutex     readyMtx;
			/**< @brief Ready threads condvar.*/
			MasterCondVar   readyCond;
			/**< @brief Busy threads counter.*/
			master_cnt_t    busyCnt;
			/**< @brief Busy threads mutex.*/
			MasterMutex     busyMtx;
			/**< @brief Busy threads condvar.*/
			MasterCondVar   busyCond;
			/**< @brief Exit request flag, broadcast.*/
			master_bool_t   exitFlag;    
			std::string 	argp_str;
			
			int masterThreadPoolCreateAll();
			void MasterThreadPoolAllocThreadId(MasterMemPool *stackpoolp);
			int masterThreadPoolJoinAll(MasterThreadPool *poolp);
			int masterThreadPoolStartWorker(MasterThreadPool *poolp, std::string &argp);
			int masterThreadPoolWorkerThread(void *poolp);			
			int RegMagSubThread(std::string &data);
			int master_lld_thread_createstatic(MasterThreadId *idp, const char *namep,
                    master_prio_t priority,
                    master_proc_f routine, void *argp,
                    void *stackp, size_t stacksize);
			int masterThreadCreateFromMemPool(MasterThreadId *idp, const char *namep,
                    master_prio_t priority,
                    master_proc_f routine, void *argp,
                    MasterMemPool *mempoolp);	
			int master_lld_thread_createfrommempool(MasterThreadId *idp, const char *namep,
			                                             master_prio_t priority,
			                                             master_proc_f routine, void *argp, 
			                                             MasterMemPool *mempoolp);
	};
}

#endif
