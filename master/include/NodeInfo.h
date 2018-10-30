/*************************************************
 * 
	Copyright (c) 2016, CETC32. All rights reserved.

	Author 	: 	Zuo Long <asdzuo@qq.com>
	Date	:	2016.4.20

**************************************************/

#ifndef __NODEINFO_H__
#define __NODEINFO_H__

#include <iostream>
#include <stdlib.h>
#include <map>
#include <set>

namespace CMaster {

	enum RegistrationsType
	{
		TYPE_PUB,
		TYPE_SUB,
		TYPE_SRV
	};

	class RosNodeInfo
	{
	public:
	
		std::string name;
		std::string uri;
		std::set<std::string> topic_publications;	/* published topic list */
		std::set<std::string> topic_subscriptions;	/* subscribed topic list */
		std::set<std::string> service;				/* service list */

		RosNodeInfo(){}
		RosNodeInfo(std::string call_id,std::string call_api) :name(call_id),uri(call_api) {}

		void add_to_list(enum RegistrationsType t,std::string name);
		
	};
}
#endif /* __NODEINFO_H__ */
