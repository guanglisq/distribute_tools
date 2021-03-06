/*************************************************
 * 
	Copyright (c) 2016, CETC32. All rights reserved.

	Author 	: 	Li Guang
	Date	:	2016.5.9

**************************************************/
#ifndef __MASTERMEMPOOL_H__
#define __MASTERMEMPOOL_H__


#include <Masterutility.h>
#include <MasterBase.h>
#include <limits.h>
namespace CMaster {

	class MasterMemPool
	{
		public:
			/**< @brief  Create a server object.*/
			MasterMemPool();
			/**< @brief  Destructor.*/
			virtual ~MasterMemPool();
			/**< @brief Pointer to the first free block.*/
			void          *_headp;
			/**< @brief Block size.*/
			size_t        _blockSize;
			/**< @brief Allocation provider.*/
			master_alloc_f  _allocator;
			/**< @brief Number of free blocks.*/
			master_cnt_t    _free;
			/**< @brief Memory pool lock.*/
			MasterMutex     lock;
			
			MASTER_STACKPOOL(RegMagSubMemPoolChunk, (PTHREAD_STACK_MIN << 1), 4);
			
			/**< @brief Alloc Memory from MasterMemPool.*/
			void *masterMemPoolAlloc(MasterMemPool *poolp);
			/**< @brief Load MemPool from Array.*/
			void masterMemPoolLoadArray(MasterMemPool *poolp, void *arrayp, master_cnt_t n);
			/**< @brief Find Free Number From MemPool.*/
			master_cnt_t masterMemPoolNumFree(MasterMemPool *poolp);
			void masterMemPoolFree(MasterMemPool *poolp, void *objp);	

	};

}

#endif
