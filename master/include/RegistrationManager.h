/*************************************************
 * 
	Copyright (c) 2016, CETC32. All rights reserved.

	Author 	: 	Zuo Long <asdzuo@qq.com>
	Date	:	2016.4.20

**************************************************/

#ifndef __REGISTRATIONMANAGER_H__
#define __REGISTRATIONMANAGER_H__

#include <iostream>
#include <stdlib.h>
#include <map>
#include <set>
#include <Registrations.h>
#include <pthread.h> 
#include <Masterutility.h>
#include <MasterBase.h>
#include <MasterThreadPool.h>



namespace CMaster {

	class RegistrationManager
	{
		public:
			/**< @brief  Create a server object.*/
			RegistrationManager();
			/**< @brief  Destructor.*/
			virtual ~RegistrationManager();
			std::map<std::string,std::string>  topic_type;     //  For Topic type check < topic name:topic type >   
			std::map<std::string,RosNodeInfo>  node_list;
			Registrations PUB_Reg;
			Registrations SUB_Reg;
			Registrations SRV_Reg;
			
			std::string RegMagtopicname;
			MasterMutex	RegMag_mutex;			//used to manager registration			
			MasterThreadPool    	RegMagSubThdPool; 		/**< @brief XMLRPC Slave worker thread pool.*/
			
		/* Function */
			bool _register(Registrations &r, std::string topicname, std::string nodename, std::string nodeuri, bool isservice=false ,std::string  serviceuri = "");
			bool check_topic_type(std::string name, std::string type);
			void notify_topic_subscribers(std::string topicname);

	};

}

#endif /* __REGISTRATIONMANAGER_H__ */
