//
// Created by JiangYC on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"

osMessageQueueId_t test_queue_handle;
constexpr osMessageQueueAttr_t test_queue_attributes = {
  .name = "test_queue",
};



osSemaphoreId_t test_semaphore_handle;
constexpr osSemaphoreAttr_t test_semaphore_attributes = {
  .name = "test_semaphore",
};



osEventFlagsId_t test_event_handle;
constexpr osEventFlagsAttr_t test_event_attributes = {
  .name = "test_event",
};



// uint32_t send = 0;
// auto flag_1 = 1u;
//
// osThreadId_t test_task_handle;
// constexpr osThreadAttr_t test_task_attributes = {
//   .name = "test_task",
//   .stack_size = 256 * 4,
//   .priority = osPriorityNormal,
// };
//
// [[noreturn]]void test_task(void *) {
//   while (true) {
//     const auto tick = osKernelGetTickCount();
//     if (++send % 5 == 0) {
//       osSemaphoreRelease(test_semaphore_handle);
//
//       osEventFlagsSet(test_event_handle, flag_1);
//     }
//     // osMessageQueuePut(test_queue_handle, &send, 0, 0);
//     osDelayUntil(tick + 100);
//   }
// }
//
//
//
// uint32_t recv = 0;
// auto flag_2 = 1u << 1;
//
// osThreadId_t test1_task_handle;
// constexpr osThreadAttr_t test1_task_attributes = {
//   .name = "test_task",
//   .stack_size = 256 * 4,
//   .priority = osPriorityNormal,
// };
//
// [[noreturn]]void test1_task(void *) {
//   while (true) {
//     // osMessageQueueGet(test_queue_handle, &recv, nullptr, osWaitForever);
//     osSemaphoreAcquire(test_semaphore_handle, osWaitForever);
//
//     osEventFlagsSet(test_event_handle, flag_2);
//     ++recv;
//   }
// }





constexpr auto flag_3 = 1u;
osThreadId_t test3_task_handle;
constexpr osThreadAttr_t test3_task_attributes = {
  .name = "test3_task",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

[[noreturn]] void test3_task(void *) {
  // osEventFlagsClear(test_event_handle, flag_3);

  while (true) {
    osDelay(1000);
    osEventFlagsSet(test_event_handle, flag_3);
  }
}



auto flag_4 = 1u << 1;
uint32_t cnt4 = 0;

osThreadId_t test4_task_handle;
constexpr osThreadAttr_t test4_task_attributes = {
  .name = "test4_task",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

[[noreturn]] void test4_task(void *) {
  osEventFlagsClear(test_event_handle, flag_4);

  while (true) {
    osDelay(1500);
    cnt4 += 1;
    osEventFlagsSet(test_event_handle, flag_4);
  }
}



uint32_t cnt = 0;

osThreadId_t test2_task_handle;
constexpr osThreadAttr_t test2_task_attributes = {
  .name = "test_task",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

[[noreturn]]void test2_task(void *) {
  while (true) {
    osEventFlagsWait(test_event_handle, flag_3 | flag_4, osFlagsWaitAll, osWaitForever);
    ++cnt;
    // osEventFlagsClear(test_event_handle, flag_3 | flag_4);
  }
}



void user_tasks_init() {
  // test_queue_handle = osMessageQueueNew(16, sizeof(uint32_t), &test_queue_attributes);
  // test_semaphore_handle = osSemaphoreNew(1, 0, &test_semaphore_attributes);

  // test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes);
  // test1_task_handle = osThreadNew(test1_task, nullptr, &test1_task_attributes);
  test2_task_handle = osThreadNew(test2_task, nullptr, &test2_task_attributes);
  test3_task_handle = osThreadNew(test3_task, nullptr, &test3_task_attributes);
  test4_task_handle = osThreadNew(test4_task, nullptr, &test4_task_attributes);

  test_event_handle = osEventFlagsNew(&test_event_attributes);
}