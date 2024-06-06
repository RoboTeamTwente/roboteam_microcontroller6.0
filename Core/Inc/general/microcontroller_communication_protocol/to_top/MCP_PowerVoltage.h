// AUTOGENERATED. Run generator/main.py to regenerate
/*
[  0   ] [  1   ] [  2   ]
11111111 -------- -------- ack_number
-------- 11111111 11111111 voltagePowerBoard
*/

#ifndef __MCP_POWER_VOLTAGE_H
#define __MCP_POWER_VOLTAGE_H

#include <stdbool.h>
#include <stdint.h>
#include "MCP_BaseTypes.h"

typedef struct _MCP_PowerVoltagePayload {
    uint8_t payload[MCP_PACKET_SIZE_MCP_POWER_VOLTAGE];
} MCP_PowerVoltagePayload;

typedef struct _MCP_PowerVoltage {
    uint32_t   ack_number          ; // integer [0, 255]             acknowledgements
    float      voltagePowerBoard   ; // float   [15.000, 30.000]     power board voltage
} MCP_PowerVoltage;

// ================================ GETTERS ================================
static inline uint32_t MCP_PowerVoltage_get_ack_number(MCP_PowerVoltagePayload *mcppvp){
   return ((mcppvp->payload[0]));
}

static inline float MCP_PowerVoltage_get_voltagePowerBoard(MCP_PowerVoltagePayload *mcppvp){
    uint32_t _voltagePowerBoard = ((mcppvp->payload[1]) << 8) | ((mcppvp->payload[2]));
    return (_voltagePowerBoard * 0.0002288853284504F) + 15.0000000000000000F;
}

// ================================ SETTERS ================================
static inline void MCP_PowerVoltage_set_ack_number(MCP_PowerVoltagePayload *mcppvp, uint32_t ack_number){
    mcppvp->payload[0] = ack_number;
}

static inline void MCP_PowerVoltage_set_voltagePowerBoard(MCP_PowerVoltagePayload *mcppvp, float voltagePowerBoard){
    uint32_t _voltagePowerBoard = (uint32_t)((voltagePowerBoard -15.0000000000000000F) / 0.0002288853284504F);
    mcppvp->payload[1] = (_voltagePowerBoard >> 8);
    mcppvp->payload[2] = _voltagePowerBoard;
}

// ================================ ENCODE ================================
static inline void encodeMCP_PowerVoltage(MCP_PowerVoltagePayload *mcppvp, MCP_PowerVoltage *mcppv){
    MCP_PowerVoltage_set_ack_number          (mcppvp, mcppv->ack_number);
    MCP_PowerVoltage_set_voltagePowerBoard   (mcppvp, mcppv->voltagePowerBoard);
}

// ================================ DECODE ================================
static inline void decodeMCP_PowerVoltage(MCP_PowerVoltage *mcppv, MCP_PowerVoltagePayload *mcppvp){
    mcppv->ack_number    = MCP_PowerVoltage_get_ack_number(mcppvp);
    mcppv->voltagePowerBoard= MCP_PowerVoltage_get_voltagePowerBoard(mcppvp);
}

#endif /*__MCP_POWER_VOLTAGE_H*/
