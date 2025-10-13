//
// Created by JiangYC on 2025/10/12.
//

#ifndef IMU_H
#define IMU_H

#include <stdint.h>

class IMU {
private:
  uint8_t accel_raw_range;
  uint8_t rx_accel_data[7];
  int accel_data[6];
  uint8_t tx_accel_data[6];

  uint8_t gyro_raw_range;
  uint8_t rx_gyro_data[6];
  int gyro_data[6];
  uint8_t tx_gyro_data[6];

  template<class T1, class T2>
    static T2 linear_mapping(T1 org, T1 org_max, T2 res_max) {
    return T2(org) / org_max * res_max;
  }

public:
  IMU();
  ~IMU();

  void accel_calculate();
  void gyro_calculate();
};



#endif //IMU_H
