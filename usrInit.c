#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <rerosNode.h>
#include <rerosHandlers.h>
#include <rerosMsgTypes.h>
#include <MasterServer.h>
#include <rerosParaConfig.h>

/* Node Thread */
static void * reros_node_thread(void *arg)
{
	printf("=> REROSnode Test Begin <=\n");
	/* Initialize ReROS & Creat Node. */
	rerosInit();
	rerosNodeCreateThread();
	/* Wait until the node has shut down. */
	rerosThreadJoin(rerosNode.status.nodeThreadId);
	printf("\nNode has shut down successfully,User Thread return \n");
	return NULL;
}

/* Master Thread */
static void * reros_master_thread(void *arg)
{
	MasterServer(11311);
  printf("\nMaster Server shut down,User Thread return \n");
	return NULL;
}

/* �������?�� */
void subcallback(struct msg__demo_test__example_message *receive)
{
	printf("Received[%d][%d][%d]\n",receive->A,receive->B,receive->C);
}

void regsub()
{
	rerosSubscribe__message_RegCallback(subcallback);
}

void pub()
{
	struct msg__demo_test__example_message msg;  /* ����������� */
	msg.A = 10;    /* ������ */
	msg.B = 20;    /* ������ */
	msg.C = 30;    /* ������ */
  rerosPublish__message (msg);    /* ��ݷ��� */	
}
int main(void)
{
	pthread_t ptd_m,ptd_n;
	int ret; 
	ret = pthread_create(&ptd_m, NULL, reros_master_thread, NULL);
	if(ret!= 0)
	{
		printf("Create Master_thread failed!\r\n");
	}
	
	ret = pthread_create(&ptd_n, NULL, reros_node_thread, NULL);
	if(ret!= 0)
	{
		printf("Create Node_thread failed!\r\n");
	}
	sleep(1);
	regsub();
	while(1)
	{
		sleep(1);
		pub();			
	}	
	return 0;
}

/* Shell Test Code 2016.11 <<< */
