/*************************************************
 * 
	Copyright (c) 2016, CETC32. All rights reserved.

	Author 	: 	Zuo Long <asdzuo@qq.com>
	Date	:	2016.4.20

**************************************************/

#ifndef __REGISTRATIONS_H__
#define __REGISTRATIONS_H__

#include <iostream>
#include <stdlib.h>
#include <map>
#include <set>
#include <NodeInfo.h>

namespace CMaster {

	class Registrations
	{
		public:
	
			RegistrationsType Reg_type ;
			std::map<std::string,std::map<std::string,std::string> > Reg_list; /* Topic Name: {[Node name, Node uri] ...}  */

			Registrations (RegistrationsType t):Reg_type(t){}

			bool is_empty(std::string key);
			std::map<std::string,std::map<std::string,std::string> >::iterator get_uri(std::string key);  /* Get URI From Topic/Service Name */
			void regist(std::string topicname,std::string  nodename,std::string  nodeuri,bool isservice,std::string  serviceuri);

	};
}

#endif /* __REGISTRATIONS_H__ */
