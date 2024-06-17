// AUTOGENERATED. Run generator/main.py to regenerate
/*
[  0   ] [  1   ] [  2   ] [  3   ]
11111111 -------- -------- -------- ack_number
-------- 11111111 11111111 -------- voltagePowerBoard
-------- -------- -------- 1------- sensorWorking
*/

#ifndef __MCP_POWER_ALIVE_H
#define __MCP_POWER_ALIVE_H

#include <stdbool.h>
#include <stdint.h>
#include "MCP_BaseTypes.h"

typedef struct _MCP_PowerAlivePayload {
    uint8_t payload[MCP_PACKET_SIZE_MCP_POWER_ALIVE];
} MCP_PowerAlivePayload;

typedef struct _MCP_PowerAlive {
    uint32_t   ack_number          ; // integer [0, 255]             acknowledgements
    float      voltagePowerBoard   ; // float   [15.000, 30.000]     power board voltage
    bool       sensorWorking       ; // integer [0, 1]               voltage sensor working
} MCP_PowerAlive;

// ================================ GETTERS ================================
static inline uint32_t MCP_PowerAlive_get_ack_number(MCP_PowerAlivePayload *mcppap){
   return ((mcppap->payload[0]));
}

static inline float MCP_PowerAlive_get_voltagePowerBoard(MCP_PowerAlivePayload *mcppap){
    uint32_t _voltagePowerBoard = ((mcppap->payload[1]) << 8) | ((mcppap->payload[2]));
    return (_voltagePowerBoard * 0.0002288853284504F) + 15.0000000000000000F;
}

static inline bool MCP_PowerAlive_get_sensorWorking(MCP_PowerAlivePayload *mcppap){
    return (mcppap->payload[3] & 0b10000000) > 0;
}

// ================================ SETTERS ================================
static inline void MCP_PowerAlive_set_ack_number(MCP_PowerAlivePayload *mcppap, uint32_t ack_number){
    mcppap->payload[0] = ack_number;
}

static inline void MCP_PowerAlive_set_voltagePowerBoard(MCP_PowerAlivePayload *mcppap, float voltagePowerBoard){
    uint32_t _voltagePowerBoard = (uint32_t)((voltagePowerBoard -15.0000000000000000F) / 0.0002288853284504F);
    mcppap->payload[1] = (_voltagePowerBoard >> 8);
    mcppap->payload[2] = _voltagePowerBoard;
}

static inline void MCP_PowerAlive_set_sensorWorking(MCP_PowerAlivePayload *mcppap, bool sensorWorking){
    mcppap->payload[3] = ((sensorWorking << 7) & 0b10000000) | (mcppap->payload[3] & 0b01111111);
}

// ================================ ENCODE ================================
static inline void encodeMCP_PowerAlive(MCP_PowerAlivePayload *mcppap, MCP_PowerAlive *mcppa){
    MCP_PowerAlive_set_ack_number          (mcppap, mcppa->ack_number);
    MCP_PowerAlive_set_voltagePowerBoard   (mcppap, mcppa->voltagePowerBoard);
    MCP_PowerAlive_set_sensorWorking       (mcppap, mcppa->sensorWorking);
}

// ================================ DECODE ================================
static inline void decodeMCP_PowerAlive(MCP_PowerAlive *mcppa, MCP_PowerAlivePayload *mcppap){
    mcppa->ack_number    = MCP_PowerAlive_get_ack_number(mcppap);
    mcppa->voltagePowerBoard= MCP_PowerAlive_get_voltagePowerBoard(mcppap);
    mcppa->sensorWorking = MCP_PowerAlive_get_sensorWorking(mcppap);
}

#endif /*__MCP_POWER_ALIVE_H*/
