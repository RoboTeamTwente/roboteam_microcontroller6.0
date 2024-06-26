// AUTOGENERATED. Run generator/main.py to regenerate
/*
[  0   ]
11111111 ack_number
*/

#ifndef __MCP_ARE_YOU_ALIVE_H
#define __MCP_ARE_YOU_ALIVE_H

#include <stdbool.h>
#include <stdint.h>
#include "MCP_BaseTypes.h"

typedef struct _MCP_AreYouAlivePayload {
    uint8_t payload[MCP_PACKET_SIZE_MCP_ARE_YOU_ALIVE];
} MCP_AreYouAlivePayload;

typedef struct _MCP_AreYouAlive {
    uint32_t   ack_number          ; // integer [0, 255]             acknowledgements
} MCP_AreYouAlive;

// ================================ GETTERS ================================
static inline uint32_t MCP_AreYouAlive_get_ack_number(MCP_AreYouAlivePayload *mcpayap){
   return ((mcpayap->payload[0]));
}

// ================================ SETTERS ================================
static inline void MCP_AreYouAlive_set_ack_number(MCP_AreYouAlivePayload *mcpayap, uint32_t ack_number){
    mcpayap->payload[0] = ack_number;
}

// ================================ ENCODE ================================
static inline void encodeMCP_AreYouAlive(MCP_AreYouAlivePayload *mcpayap, MCP_AreYouAlive *mcpaya){
    MCP_AreYouAlive_set_ack_number          (mcpayap, mcpaya->ack_number);
}

// ================================ DECODE ================================
static inline void decodeMCP_AreYouAlive(MCP_AreYouAlive *mcpaya, MCP_AreYouAlivePayload *mcpayap){
    mcpaya->ack_number   = MCP_AreYouAlive_get_ack_number(mcpayap);
}

#endif /*__MCP_ARE_YOU_ALIVE_H*/
