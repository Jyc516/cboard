//
// Created by JiangYC on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"

osMessageQueueId_t test_queue_handle;
constexpr osMessageQueueAttr_t test_queue_attributes ={
  .name = "test_queue",
};



osSemaphoreId_t test_semaphore_handle;
constexpr osSemaphoreAttr_t test_semaphore_attributes ={
  .name = "test_semaphore",
};



uint32_t send = 0;

osThreadId_t test_task_handle;
constexpr osThreadAttr_t test_task_attributes ={
  .name = "test_task",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

[[noreturn]]void test_task(void *) {
  while (true) {
    const auto tick = osKernelGetTickCount();
    if (++send % 5 == 0) {
      osSemaphoreRelease(test_semaphore_handle);
    }
    // osMessageQueuePut(test_queue_handle, &send, 0, 0);
    osDelayUntil(tick + 100);
  }
}



uint32_t recv = 0;

osThreadId_t test1_task_handle;
constexpr osThreadAttr_t test1_task_attributes ={
  .name = "test_task",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

[[noreturn]]void test1_task(void *) {
  while (true) {
    // osMessageQueueGet(test_queue_handle, &recv, nullptr, osWaitForever);
    osSemaphoreAcquire(test_semaphore_handle, osWaitForever);
    ++recv;
  }
}



void user_tasks_init() {
  test_queue_handle = osMessageQueueNew(16, sizeof(uint32_t), &test_queue_attributes);
  test_semaphore_handle = osSemaphoreNew(1, 0, &test_semaphore_attributes);

  test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes);
  test1_task_handle = osThreadNew(test1_task, nullptr, &test1_task_attributes);
}