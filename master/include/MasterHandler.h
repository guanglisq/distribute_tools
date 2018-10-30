/*************************************************
 * 
	Copyright (c) 2016, CETC32. All rights reserved.

	Author 	: 	Zuo Long <asdzuo@qq.com>
	Date	:	2016.4.20

**************************************************/

#ifndef __MASTERHANDLER_H__
#define __MASTERHANDLER_H__


#include <iostream>
#include <stdlib.h>
#include <map>
#include <set>
#include <RegistrationManager.h>
#include <XmlRpc.h>

using namespace XmlRpc;

namespace CMaster {
	
	class GetPid : public XmlRpcServerMethod
	{
		public:
			GetPid(XmlRpcServer* s) : XmlRpcServerMethod("getPid", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};    

	class RegisterPublisher : public XmlRpcServerMethod
	{
		public:
			RegisterPublisher(XmlRpcServer* s) : XmlRpcServerMethod("registerPublisher", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	}; 

	class UnregisterPublisher : public XmlRpcServerMethod
	{
		public:
			UnregisterPublisher(XmlRpcServer* s) : XmlRpcServerMethod("unregisterPublisher", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	}; 

	class RegisterSubscriber : public XmlRpcServerMethod
	{
		public:
			RegisterSubscriber(XmlRpcServer* s) : XmlRpcServerMethod("registerSubscriber", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	}; 

	class UnregisterSubscriber : public XmlRpcServerMethod
	{
		public:
			UnregisterSubscriber(XmlRpcServer* s) : XmlRpcServerMethod("unregisterSubscriber", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	}; 
		
	class RegisterService : public XmlRpcServerMethod
	{
		public:
			RegisterService(XmlRpcServer* s) : XmlRpcServerMethod("registerService", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};  

	class UnregisterService : public XmlRpcServerMethod
	{
		public:
			UnregisterService(XmlRpcServer* s) : XmlRpcServerMethod("unregisterService", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};  

	class LookupService : public XmlRpcServerMethod
	{
		public:
			LookupService(XmlRpcServer* s) : XmlRpcServerMethod("lookupService", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};  	
	class GetParam : public XmlRpcServerMethod
	{
		public:
			GetParam(XmlRpcServer* s) : XmlRpcServerMethod("getParam", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};
	class LookupNode : public XmlRpcServerMethod
	{
		public:
			LookupNode(XmlRpcServer* s) : XmlRpcServerMethod("lookupNode", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};
	class GetPublishedTopics : public XmlRpcServerMethod
	{
		public:
			GetPublishedTopics(XmlRpcServer* s) : XmlRpcServerMethod("getPublishedTopics", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};	
	class GetTopicTypes : public XmlRpcServerMethod
	{
		public:
			GetTopicTypes(XmlRpcServer* s) : XmlRpcServerMethod("getTopicTypes", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};
	class GetSystemState : public XmlRpcServerMethod
	{
		public:
			GetSystemState(XmlRpcServer* s) : XmlRpcServerMethod("getSystemState", s) {}
			void execute(XmlRpcValue& params, XmlRpcValue& result);
	};

}
using namespace CMaster;
extern RegistrationManager *RegManager;
#endif /* __MASTERHANDLER_H__ */
