//
// Created by JiangYC on 2025/11/1.
//

#include "user_tasks.h"
#include "cmsis_os2.h"

uint32_t count = 0;

osThreadId_t test_task_handle;
constexpr osThreadAttr_t testTask_attibutes = {
  .name = "userTask",
  .stack_size = 128 * 4,
  .priority = osPriorityNormal,
};

void test_task(void *) {
  while (true) {
    const auto tick = osKernelGetTickCount();
    ++count;
    osDelayUntil(tick + 1);
  }
}

void user_tasks_init() {
  test_task_handle = osThreadNew(test_task, nullptr, &testTask_attibutes);
}