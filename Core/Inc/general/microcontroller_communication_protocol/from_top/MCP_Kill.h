// AUTOGENERATED. Run generator/main.py to regenerate
/*
[  0   ]
11111111 ack_number
*/

#ifndef __MCP_KILL_H
#define __MCP_KILL_H

#include <stdbool.h>
#include <stdint.h>
#include "MCP_BaseTypes.h"

typedef struct _MCP_KillPayload {
    uint8_t payload[MCP_PACKET_SIZE_MCP_KILL];
} MCP_KillPayload;

typedef struct _MCP_Kill {
    uint32_t   ack_number          ; // integer [0, 255]             acknowledgements
} MCP_Kill;

// ================================ GETTERS ================================
static inline uint32_t MCP_Kill_get_ack_number(MCP_KillPayload *mcpkp){
   return ((mcpkp->payload[0]));
}

// ================================ SETTERS ================================
static inline void MCP_Kill_set_ack_number(MCP_KillPayload *mcpkp, uint32_t ack_number){
    mcpkp->payload[0] = ack_number;
}

// ================================ ENCODE ================================
static inline void encodeMCP_Kill(MCP_KillPayload *mcpkp, MCP_Kill *mcpk){
    MCP_Kill_set_ack_number          (mcpkp, mcpk->ack_number);
}

// ================================ DECODE ================================
static inline void decodeMCP_Kill(MCP_Kill *mcpk, MCP_KillPayload *mcpkp){
    mcpk->ack_number     = MCP_Kill_get_ack_number(mcpkp);
}

#endif /*__MCP_KILL_H*/
