//
// Created by JiangYC on 2025/10/25.
//

#include "usart.h"
#include "RemoteController.h"
extern RC rc;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
  if (huart == &huart3) {
    int ticks = HAL_GetTick();
    if (rc.check_connection(ticks)) {
      rc.handle();
    }
  }
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rc.rx_buf, 18);
}