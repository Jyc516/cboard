//
// Created by JiangYC on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"

osMessageQueueId_t test_queue_handle;
constexpr osMessageQueueAttr_t test_queue_attributes ={
  .name = "test_queue",
};



uint32_t send = 0;
uint32_t recv = 0;

osThreadId_t test_task_handle;
constexpr osThreadAttr_t test_task_attributes ={
  .name = "test_task",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

[[noreturn]]void test_task(void *) {
  while (true) {
    const auto tick = osKernelGetTickCount();
    ++send;
    osMessageQueuePut(test_queue_handle, &send, 0, 0);
    osDelayUntil(tick + 100);
  }
}



osThreadId_t test1_task_handle;
constexpr osThreadAttr_t test1_task_attributes ={
  .name = "test_task",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

[[noreturn]]void test1_task(void *) {
  while (true) {
    osMessageQueueGet(test_queue_handle, &recv, nullptr, osWaitForever);
  }
}



void user_tasks_init() {
  test_task_handle = osThreadNew(test_task, nullptr, &test_task_attributes);
  test1_task_handle = osThreadNew(test1_task, nullptr, &test1_task_attributes);

  test_queue_handle = osMessageQueueNew(16, sizeof(uint32_t), &test_queue_attributes);
}