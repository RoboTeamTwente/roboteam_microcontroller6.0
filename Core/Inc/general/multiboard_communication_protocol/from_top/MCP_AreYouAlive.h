// AUTOGENERATED. Run generator/main.py to regenerate
/*
[  0   ]
1111---- mcpVersion
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
    uint32_t   mcpVersion          ; // integer [0, 15]              version of mcp
} MCP_AreYouAlive;

// ================================ GETTERS ================================
static inline uint32_t MCP_AreYouAlive_get_mcpVersion(MCP_AreYouAlivePayload *mcpayap){
   return ((mcpayap->payload[0] & 0b11110000) >> 4);
}

// ================================ SETTERS ================================
static inline void MCP_AreYouAlive_set_mcpVersion(MCP_AreYouAlivePayload *mcpayap, uint32_t mcpVersion){
    mcpayap->payload[0] = ((mcpVersion << 4) & 0b11110000) | (mcpayap->payload[0] & 0b00001111);
}

// ================================ ENCODE ================================
static inline void encodeMCP_AreYouAlive(MCP_AreYouAlivePayload *mcpayap, MCP_AreYouAlive *mcpaya){
    MCP_AreYouAlive_set_mcpVersion          (mcpayap, mcpaya->mcpVersion);
}

// ================================ DECODE ================================
static inline void decodeMCP_AreYouAlive(MCP_AreYouAlive *mcpaya, MCP_AreYouAlivePayload *mcpayap){
    mcpaya->mcpVersion   = MCP_AreYouAlive_get_mcpVersion(mcpayap);
}

#endif /*__MCP_ARE_YOU_ALIVE_H*/
