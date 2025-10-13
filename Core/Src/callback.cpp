//
// Created by JiangYC on 2025/10/12.
//

#include "tim.h"
#include "bmi088.h"
#include "imu.h"

extern uint8_t reg;
extern uint8_t  rx_gyro_data[6];
extern uint8_t  rx_accel_data[7];
extern uint8_t  tx_gyro_data;
extern uint8_t  tx_accel_data;

extern IMU imu;

// float cnt;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim == &htim6) {
  //   bmi088_accel_read_reg(0x12, rx_accel_data, 6);
  //   // bmi088_gyro_read_reg(0x02, rx_gyro_data, 6);
  //   //bmi088_accel_read_reg(0x00, rx_accel_data, 1);
  //   bmi088_gyro_read_reg(0x02, rx_gyro_data, 6);
  //   // if (rx_accel_data[1] == 0x1E) cnt++;
		// // cnt++;
    imu.accel_calculate();
    imu.gyro_calculate();
  }
}