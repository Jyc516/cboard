//
// Created by JiangYC on 2025/10/25.
//

#include "init.h"
#include "RemoteController.h"
#include "usart.h"

extern RC rc;

void rc_init() {
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rc.rx_buf, 18);
}