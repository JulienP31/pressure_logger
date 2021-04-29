#ifndef __PL_APP_INFOS_H
#define __PL_APP_INFOS_H



#include <FreeRTOS.h>
#include <queue.h>


// -------------------- Typedefs --------------------
typedef struct pl_msg_host_proc
{
	uint8_t uiCmd;
} pl_msg_host_proc_t;


typedef struct pl_app_infos
{
	QueueHandle_t hQueue_HostProc;
} pl_app_infos_t;



#endif /* __PL_APP_INFOS_H */
