// AUTOGENERATED. Run generator/main.py to regenerate
#ifndef __MCP_BASETYPES_H
#define __MCP_BASETYPES_H

#include <stdint.h>
#include <stdbool.h>


#define MCP_LOCAL_VERSION 1
#define MCP_LARGEST_PACKET_IN_BYTES 3
#define MCP_MAX_ID_PLUS_ONE 16

#define MCP_TOP_BOARD                                                               0
#define MCP_DRIBBLER_BOARD                                                          4
#define MCP_KICKER_BOARD                                                            7
#define MCP_POWER_BOARD                                                             15

#define MCP_ERROR_BIT_MASK                                                          0x10000000
#define MCP_ERROR_BIT_SHIFT                                                         28
#define MCP_VERSION_BIT_MASK                                                        0x0F000000
#define MCP_VERSION_BIT_SHIFT                                                       24
#define MCP_FROM_ID_BIT_MASK                                                        0x000000F0
#define MCP_FROM_ID_BIT_SHIFT                                                       4
#define MCP_TO_ID_BIT_MASK                                                          0x0000000F
#define MCP_TO_ID_BIT_SHIFT                                                         0

#define MCP_PACKET_TYPE_MCP_ACK                                                     0
#define MCP_PACKET_ID_POWER_TO_KICKER_MCP_ACK                                       0x010000f7
#define MCP_PACKET_ID_POWER_TO_DRIBBLER_MCP_ACK                                     0x010000f4
#define MCP_PACKET_ID_POWER_TO_TOP_MCP_ACK                                          0x010000f0
#define MCP_PACKET_ID_KICKER_TO_POWER_MCP_ACK                                       0x0100007f
#define MCP_PACKET_ID_KICKER_TO_DRIBBLER_MCP_ACK                                    0x01000174
#define MCP_PACKET_ID_KICKER_TO_TOP_MCP_ACK                                         0x01000170
#define MCP_PACKET_ID_DRIBBLER_TO_POWER_MCP_ACK                                     0x0100014f
#define MCP_PACKET_ID_DRIBBLER_TO_KICKER_MCP_ACK                                    0x01000147
#define MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_ACK                                       0x01000240
#define MCP_PACKET_ID_TOP_TO_POWER_MCP_ACK                                          0x0100020f
#define MCP_PACKET_ID_TOP_TO_KICKER_MCP_ACK                                         0x01000207
#define MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_ACK                                       0x01000204
#define MCP_PACKET_SIZE_MCP_ACK                                                     1
#define MCP_PACKET_RANGE_MCP_ACK_ACK_NUMBER_MIN                                     0
#define MCP_PACKET_RANGE_MCP_ACK_ACK_NUMBER_MAX                                     255

#define MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE                                           1
#define MCP_PACKET_ID_TOP_TO_POWER_MCP_ARE_YOU_ALIVE                                0x0100030f
#define MCP_PACKET_ID_TOP_TO_KICKER_MCP_ARE_YOU_ALIVE                               0x01000307
#define MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_ARE_YOU_ALIVE                             0x01000304
#define MCP_PACKET_SIZE_MCP_ARE_YOU_ALIVE                                           1
#define MCP_PACKET_RANGE_MCP_ARE_YOU_ALIVE_ACK_NUMBER_MIN                           0
#define MCP_PACKET_RANGE_MCP_ARE_YOU_ALIVE_ACK_NUMBER_MAX                           255

#define MCP_PACKET_TYPE_MCP_SET_DRIBBLER_SPEED                                      2
#define MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_SET_DRIBBLER_SPEED                        0x01000404
#define MCP_PACKET_SIZE_MCP_SET_DRIBBLER_SPEED                                      2
#define MCP_PACKET_RANGE_MCP_SET_DRIBBLER_SPEED_ACK_NUMBER_MIN                      0
#define MCP_PACKET_RANGE_MCP_SET_DRIBBLER_SPEED_ACK_NUMBER_MAX                      255
#define MCP_PACKET_RANGE_MCP_SET_DRIBBLER_SPEED_SPEED_MIN                           0.0000000000000000F
#define MCP_PACKET_RANGE_MCP_SET_DRIBBLER_SPEED_SPEED_MAX                           1.0000000000000000F

#define MCP_PACKET_TYPE_MCP_KICKER_CHARGE                                           3
#define MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICKER_CHARGE                               0x01000407
#define MCP_PACKET_SIZE_MCP_KICKER_CHARGE                                           3
#define MCP_PACKET_RANGE_MCP_KICKER_CHARGE_ACK_NUMBER_MIN                           0
#define MCP_PACKET_RANGE_MCP_KICKER_CHARGE_ACK_NUMBER_MAX                           255
#define MCP_PACKET_RANGE_MCP_KICKER_CHARGE_VOLTAGE_MIN                              0
#define MCP_PACKET_RANGE_MCP_KICKER_CHARGE_VOLTAGE_MAX                              1023

#define MCP_PACKET_TYPE_MCP_KICKER_STOP_CHARGE                                      4
#define MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICKER_STOP_CHARGE                          0x01000507
#define MCP_PACKET_SIZE_MCP_KICKER_STOP_CHARGE                                      1
#define MCP_PACKET_RANGE_MCP_KICKER_STOP_CHARGE_ACK_NUMBER_MIN                      0
#define MCP_PACKET_RANGE_MCP_KICKER_STOP_CHARGE_ACK_NUMBER_MAX                      255

#define MCP_PACKET_TYPE_MCP_KICK                                                    5
#define MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICK                                        0x01000607
#define MCP_PACKET_SIZE_MCP_KICK                                                    2
#define MCP_PACKET_RANGE_MCP_KICK_ACK_NUMBER_MIN                                    0
#define MCP_PACKET_RANGE_MCP_KICK_ACK_NUMBER_MAX                                    255
#define MCP_PACKET_RANGE_MCP_KICK_SHOOT_POWER_MIN                                   0.0000000000000000F
#define MCP_PACKET_RANGE_MCP_KICK_SHOOT_POWER_MAX                                   6.5000000000000000F

#define MCP_PACKET_TYPE_MCP_CHIP                                                    6
#define MCP_PACKET_ID_TOP_TO_KICKER_MCP_CHIP                                        0x01000707
#define MCP_PACKET_SIZE_MCP_CHIP                                                    2
#define MCP_PACKET_RANGE_MCP_CHIP_ACK_NUMBER_MIN                                    0
#define MCP_PACKET_RANGE_MCP_CHIP_ACK_NUMBER_MAX                                    255
#define MCP_PACKET_RANGE_MCP_CHIP_SHOOT_POWER_MIN                                   0.0000000000000000F
#define MCP_PACKET_RANGE_MCP_CHIP_SHOOT_POWER_MAX                                   6.5000000000000000F

#define MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE                                          7
#define MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_DRIBBLER_ALIVE                            0x01000340
#define MCP_PACKET_SIZE_MCP_DRIBBLER_ALIVE                                          2
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ALIVE_ACK_NUMBER_MIN                          0
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ALIVE_ACK_NUMBER_MAX                          255
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ALIVE_DRIBBLER_ENCODER_WORKING_MIN            0
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ALIVE_DRIBBLER_ENCODER_WORKING_MAX            1
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ALIVE_BALLSENSOR_WORKING_MIN                  0
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ALIVE_BALLSENSOR_WORKING_MAX                  1

#define MCP_PACKET_TYPE_MCP_SEES_BALL                                               8
#define MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_SEES_BALL                                 0x01000440
#define MCP_PACKET_SIZE_MCP_SEES_BALL                                               2
#define MCP_PACKET_RANGE_MCP_SEES_BALL_ACK_NUMBER_MIN                               0
#define MCP_PACKET_RANGE_MCP_SEES_BALL_ACK_NUMBER_MAX                               255
#define MCP_PACKET_RANGE_MCP_SEES_BALL_DRIBBLER_SEES_BALL_MIN                       0
#define MCP_PACKET_RANGE_MCP_SEES_BALL_DRIBBLER_SEES_BALL_MAX                       1
#define MCP_PACKET_RANGE_MCP_SEES_BALL_BALLSENSOR_SEES_BALL_MIN                     0
#define MCP_PACKET_RANGE_MCP_SEES_BALL_BALLSENSOR_SEES_BALL_MAX                     1

#define MCP_PACKET_TYPE_MCP_KICKER_ALIVE                                            9
#define MCP_PACKET_ID_KICKER_TO_TOP_MCP_KICKER_ALIVE                                0x01000570
#define MCP_PACKET_SIZE_MCP_KICKER_ALIVE                                            2
#define MCP_PACKET_RANGE_MCP_KICKER_ALIVE_ACK_NUMBER_MIN                            0
#define MCP_PACKET_RANGE_MCP_KICKER_ALIVE_ACK_NUMBER_MAX                            255
#define MCP_PACKET_RANGE_MCP_KICKER_ALIVE_SENSOR_WORKING_MIN                        0
#define MCP_PACKET_RANGE_MCP_KICKER_ALIVE_SENSOR_WORKING_MAX                        1

#define MCP_PACKET_TYPE_MCP_KICKER_CAPACITOR_VOLTAGE                                10
#define MCP_PACKET_ID_KICKER_TO_TOP_MCP_KICKER_CAPACITOR_VOLTAGE                    0x01000670
#define MCP_PACKET_SIZE_MCP_KICKER_CAPACITOR_VOLTAGE                                3
#define MCP_PACKET_RANGE_MCP_KICKER_CAPACITOR_VOLTAGE_ACK_NUMBER_MIN                0
#define MCP_PACKET_RANGE_MCP_KICKER_CAPACITOR_VOLTAGE_ACK_NUMBER_MAX                255
#define MCP_PACKET_RANGE_MCP_KICKER_CAPACITOR_VOLTAGE_VOLTAGE_MIN                   0
#define MCP_PACKET_RANGE_MCP_KICKER_CAPACITOR_VOLTAGE_VOLTAGE_MAX                   1023

#define MCP_PACKET_TYPE_MCP_POWER_ALIVE                                             11
#define MCP_PACKET_ID_POWER_TO_TOP_MCP_POWER_ALIVE                                  0x010007f0
#define MCP_PACKET_SIZE_MCP_POWER_ALIVE                                             2
#define MCP_PACKET_RANGE_MCP_POWER_ALIVE_ACK_NUMBER_MIN                             0
#define MCP_PACKET_RANGE_MCP_POWER_ALIVE_ACK_NUMBER_MAX                             255
#define MCP_PACKET_RANGE_MCP_POWER_ALIVE_SENSOR_WORKING_MIN                         0
#define MCP_PACKET_RANGE_MCP_POWER_ALIVE_SENSOR_WORKING_MAX                         1

#define MCP_PACKET_TYPE_MCP_POWER_VOLTAGE                                           12
#define MCP_PACKET_ID_POWER_TO_TOP_MCP_POWER_VOLTAGE                                0x010008f0
#define MCP_PACKET_ID_POWER_TO_DRIBBLER_MCP_POWER_VOLTAGE                           0x010005f4
#define MCP_PACKET_SIZE_MCP_POWER_VOLTAGE                                           2
#define MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_ACK_NUMBER_MIN                           0
#define MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_ACK_NUMBER_MAX                           255
#define MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_VOLTAGE_POWER_BOARD_MIN                  20.0000000000000000F
#define MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_VOLTAGE_POWER_BOARD_MAX                  30.0000000000000000F

#define MCP_PACKET_TYPE_MCP_KILL                                                    13
#define MCP_PACKET_ID_TOP_TO_POWER_MCP_KILL                                         0x0100040f
#define MCP_PACKET_SIZE_MCP_KILL                                                    1
#define MCP_PACKET_RANGE_MCP_KILL_ACK_NUMBER_MIN                                    0
#define MCP_PACKET_RANGE_MCP_KILL_ACK_NUMBER_MAX                                    255

#define MCP_PACKET_TYPE_MCP_DRIBBLER_ENCODER                                        14
#define MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_DRIBBLER_ENCODER                          0x01000940
#define MCP_PACKET_SIZE_MCP_DRIBBLER_ENCODER                                        3
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ENCODER_ACK_NUMBER_MIN                        0
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ENCODER_ACK_NUMBER_MAX                        255
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ENCODER_VALUE_MIN                             0.0000000000000000F
#define MCP_PACKET_RANGE_MCP_DRIBBLER_ENCODER_VALUE_MAX                             5000.0000000000000000F


static uint8_t MCP_TYPE_TO_SIZE(uint16_t type) {
    if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_SIZE_MCP_ACK;
    if (type == MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE)                             return MCP_PACKET_SIZE_MCP_ARE_YOU_ALIVE;
    if (type == MCP_PACKET_TYPE_MCP_SET_DRIBBLER_SPEED)                        return MCP_PACKET_SIZE_MCP_SET_DRIBBLER_SPEED;
    if (type == MCP_PACKET_TYPE_MCP_KICKER_CHARGE)                             return MCP_PACKET_SIZE_MCP_KICKER_CHARGE;
    if (type == MCP_PACKET_TYPE_MCP_KICKER_STOP_CHARGE)                        return MCP_PACKET_SIZE_MCP_KICKER_STOP_CHARGE;
    if (type == MCP_PACKET_TYPE_MCP_KICK)                                      return MCP_PACKET_SIZE_MCP_KICK;
    if (type == MCP_PACKET_TYPE_MCP_CHIP)                                      return MCP_PACKET_SIZE_MCP_CHIP;
    if (type == MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE)                            return MCP_PACKET_SIZE_MCP_DRIBBLER_ALIVE;
    if (type == MCP_PACKET_TYPE_MCP_SEES_BALL)                                 return MCP_PACKET_SIZE_MCP_SEES_BALL;
    if (type == MCP_PACKET_TYPE_MCP_KICKER_ALIVE)                              return MCP_PACKET_SIZE_MCP_KICKER_ALIVE;
    if (type == MCP_PACKET_TYPE_MCP_KICKER_CAPACITOR_VOLTAGE)                  return MCP_PACKET_SIZE_MCP_KICKER_CAPACITOR_VOLTAGE;
    if (type == MCP_PACKET_TYPE_MCP_POWER_ALIVE)                               return MCP_PACKET_SIZE_MCP_POWER_ALIVE;
    if (type == MCP_PACKET_TYPE_MCP_POWER_VOLTAGE)                             return MCP_PACKET_SIZE_MCP_POWER_VOLTAGE;
    if (type == MCP_PACKET_TYPE_MCP_KILL)                                      return MCP_PACKET_SIZE_MCP_KILL;
    if (type == MCP_PACKET_TYPE_MCP_DRIBBLER_ENCODER)                          return MCP_PACKET_SIZE_MCP_DRIBBLER_ENCODER;
    return 1;
}

static uint32_t MCP_TYPE_TO_ID(uint16_t type, uint8_t receiving_board, uint8_t sending_board) {
    if (sending_board == MCP_TOP_BOARD){
        if (receiving_board == MCP_DRIBBLER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_ACK                               ;
            if (type == MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE)                             return MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_ARE_YOU_ALIVE                     ;
            if (type == MCP_PACKET_TYPE_MCP_SET_DRIBBLER_SPEED)                        return MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_SET_DRIBBLER_SPEED                ;
        } else if (receiving_board == MCP_KICKER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_TOP_TO_KICKER_MCP_ACK                                 ;
            if (type == MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE)                             return MCP_PACKET_ID_TOP_TO_KICKER_MCP_ARE_YOU_ALIVE                       ;
            if (type == MCP_PACKET_TYPE_MCP_KICKER_CHARGE)                             return MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICKER_CHARGE                       ;
            if (type == MCP_PACKET_TYPE_MCP_KICKER_STOP_CHARGE)                        return MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICKER_STOP_CHARGE                  ;
            if (type == MCP_PACKET_TYPE_MCP_KICK)                                      return MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICK                                ;
            if (type == MCP_PACKET_TYPE_MCP_CHIP)                                      return MCP_PACKET_ID_TOP_TO_KICKER_MCP_CHIP                                ;
        } else if (receiving_board == MCP_POWER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_TOP_TO_POWER_MCP_ACK                                  ;
            if (type == MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE)                             return MCP_PACKET_ID_TOP_TO_POWER_MCP_ARE_YOU_ALIVE                        ;
            if (type == MCP_PACKET_TYPE_MCP_KILL)                                      return MCP_PACKET_ID_TOP_TO_POWER_MCP_KILL                                 ;
        }
    } else if (sending_board == MCP_DRIBBLER_BOARD){
        if (receiving_board == MCP_TOP_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_ACK                               ;
            if (type == MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE)                            return MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_DRIBBLER_ALIVE                    ;
            if (type == MCP_PACKET_TYPE_MCP_SEES_BALL)                                 return MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_SEES_BALL                         ;
            if (type == MCP_PACKET_TYPE_MCP_DRIBBLER_ENCODER)                          return MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_DRIBBLER_ENCODER                  ;
        } else if (receiving_board == MCP_KICKER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_DRIBBLER_TO_KICKER_MCP_ACK                            ;
        } else if (receiving_board == MCP_POWER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_DRIBBLER_TO_POWER_MCP_ACK                             ;
        }
    } else if (sending_board == MCP_KICKER_BOARD){
        if (receiving_board == MCP_TOP_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_KICKER_TO_TOP_MCP_ACK                                 ;
            if (type == MCP_PACKET_TYPE_MCP_KICKER_ALIVE)                              return MCP_PACKET_ID_KICKER_TO_TOP_MCP_KICKER_ALIVE                        ;
            if (type == MCP_PACKET_TYPE_MCP_KICKER_CAPACITOR_VOLTAGE)                  return MCP_PACKET_ID_KICKER_TO_TOP_MCP_KICKER_CAPACITOR_VOLTAGE            ;
        } else if (receiving_board == MCP_DRIBBLER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_KICKER_TO_DRIBBLER_MCP_ACK                            ;
        } else if (receiving_board == MCP_POWER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_KICKER_TO_POWER_MCP_ACK                               ;
        }
    } else if (sending_board == MCP_POWER_BOARD){
        if (receiving_board == MCP_TOP_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_POWER_TO_TOP_MCP_ACK                                  ;
            if (type == MCP_PACKET_TYPE_MCP_POWER_ALIVE)                               return MCP_PACKET_ID_POWER_TO_TOP_MCP_POWER_ALIVE                          ;
            if (type == MCP_PACKET_TYPE_MCP_POWER_VOLTAGE)                             return MCP_PACKET_ID_POWER_TO_TOP_MCP_POWER_VOLTAGE                        ;
        } else if (receiving_board == MCP_DRIBBLER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_POWER_TO_DRIBBLER_MCP_ACK                             ;
            if (type == MCP_PACKET_TYPE_MCP_POWER_VOLTAGE)                             return MCP_PACKET_ID_POWER_TO_DRIBBLER_MCP_POWER_VOLTAGE                   ;
        } else if (receiving_board == MCP_KICKER_BOARD) {
            if (type == MCP_PACKET_TYPE_MCP_ACK)                                       return MCP_PACKET_ID_POWER_TO_KICKER_MCP_ACK                               ;
        }
    }
    return 0x10000000;

}

#endif /*__MCP_BASETYPES_H*/
