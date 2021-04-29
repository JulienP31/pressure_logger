#ifndef __MAIN_H
#define __MAIN_H



#include <FreeRTOS.h>
#include <task.h>
#include "pl_host_manager.h"
#include "pl_proc_manager.h"


// -------------------- Constants --------------------
#define PL_HOST_TASK_PRIORITY 1 //< Low priority for user cmd interface from host
#define PL_PROC_TASK_PRIORITY 2 //< High priority for data acquisition process

#define PL_HP_QUEUE_LEN       2
#define PL_HP_QUEUE_ITEM_SIZE ( sizeof(pl_msg_host_proc_t) )



#endif /* __MAIN_H */

