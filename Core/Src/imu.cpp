//
// Created by JiangYC on 2025/10/12.
//

#include "imu.h"
#include "bmi088.h"

void IMU::accel_calculate(){
  bmi088_accel_read_reg(0x41, &accel_raw_range, 1);

}

void IMU::gyro_calculate() {

}
