//
// Created by JiangYC on 2025/10/25.
//

#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// void rc_init();

class RC {
private:
  uint8_t rx_data[18] = {0};
  int last_ticks = 0;
  static constexpr int ticks_timeout = 1000;
  bool connection_status = true;

  static constexpr int CH_low = 364;
  static constexpr int CH_mid = 1024;
  static constexpr int CH_high = 1684;

  enum SwitchState {
    UP = 1,
    DOWN = 2,
    MID = 3
  };

  float CH0 = 0;     // 364 - 1024 - 1684
  float CH1 = 0;     // 364 - 1024 - 1684
  float CH2 = 0;     // 364 - 1024 - 1684
  float CH3 = 0;     // 364 - 1024 - 1684
  SwitchState S1 = MID;         // 1 - 3
  SwitchState S2 = MID;         // 1 - 3
  int axis_X = 0;          // -32768 - 0 - 32767
  int axis_Y = 0;          // -32768 - 0 - 32767
  int axis_Z = 0;          // -32768 - 0 - 32767
  int left = 0;       // 0 - 1
  int right = 0;      // 0 - 1
  int key_W = 0;      // 0 - 1
  int key_S = 0;      // 0 - 1
  int key_A = 0;      // 0 - 1
  int key_D = 0;      // 0 - 1
  int key_Q = 0;      // 0 - 1
  int key_E = 0;      // 0 - 1
  int key_SHIFT = 0;  // 0 - 1
  int key_CTRL = 0;   // 0 - 1

  static float linear_mapping(int raw, int raw_low, int raw_high, float res_low, float res_high) {
    return float(raw - raw_low) / float(raw_high - raw_low) * (res_high - res_low) + res_low;
  }
public:
  uint8_t rx_buf[32] = {0};

  RC(){}
  void handle();
  bool check_connection(int ticks);
};

#ifdef __cplusplus
}
#endif

#endif //REMOTECONTROLLER_H
