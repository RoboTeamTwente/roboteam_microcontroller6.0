from mcp_boards import board
'''
data is as follows
[name, bits, None or [min, max], description]
use [min, max] only for floats
'''
packets = {
    "MCP_Ack" : {
        "from" : [board.POWER, board.KICKER, board.DRIBBLER, board.TOP],
        "to" : [board.POWER, board.KICKER, board.DRIBBLER, board.TOP],
        "data" : []
    },
    "MCP_AreYouAlive" : {
        "from" : [board.TOP],
        "to" : [board.POWER, board.KICKER, board.DRIBBLER],
        "data" : [
        ]
    },
    "MCP_SetDribblerSpeed" : {
        "from" : [board.TOP],
        "to" : [board.DRIBBLER],
        "data" : [
                ["speed", 8, [0, 1], "desired speed of the dribbler"],
            ]
    },
    "MCP_KickerCharge" : {
        "from" : [board.TOP],
        "to" : [board.KICKER],
        "data" : [
            ["voltage", 10, None, "target voltage"]
        ],
    },
    "MCP_KickerStopCharge" : {
        "from" : [board.TOP],
        "to" : [board.KICKER],
        "data" : [

        ]
    },
    "MCP_Kick" : {
        "from" : [board.TOP],
        "to" : [board.KICKER],
        "data" : [
            ["shootPower", 4, [0, 6.5], "desired speed of the ball"],
            ["doForce", 1, None, "always kick"],
            ["onSeesBall", 1, None, "kick once robot sees ball"],
        ]
    },
    "MCP_Chip" : {
        "from" : [board.TOP],
        "to" : [board.KICKER],
        "data" : [
            ["shootPower", 4, [0, 6.5], "desired speed of the ball"],
            ["doForce", 1, None, "always chip"],
            ["onSeesBall", 1, None, "chip once robot sees ball"]
        ]
    },
    "MCP_DribblerAlive" : {
        "from" : [board.DRIBBLER],
        "to" : [board.TOP, board.KICKER, board.POWER],
        "data" : [
            ["dribblerEncoderWorking", 1, None, "status of dribbler encoder"],
            ["ballsensorWorking", 1, None, "status of ballsensor"]
        ],
    },
    "MCP_SeesBall" : {
        "from" : [board.DRIBBLER],
        "to" : [board.TOP],
        "data" : [
            ["dribblerSeesBall", 1, None, "true if dribbler encoder detects ball"],
            ["ballsensorSeesBall", 1, None, "true if ball sensor detects ball"]
        ]
    },
    "MCP_KickerAlive" : {
        "from" : [board.KICKER],
        "to" : [board.TOP, board.DRIBBLER, board.POWER],
        "data" : [
            ["sensorWorking", 1, None, "capacitor voltage sensor working"]
        ],
    },
    "MCP_KickerCapacitorVoltage" : {
        "from" : [board.KICKER],
        "to" : [board.TOP],
        "data" : [
            ["voltage", 10, None, "capacitor voltage"]
        ]
    },
    "MCP_PowerAlive" : {
        "from" : [board.POWER],
        "to" : [board.TOP, board.DRIBBLER, board.KICKER],
        "data" : [
            ["sensorWorking", 1, None, "voltage sensor working"]
        ]
    },
    "MCP_PowerVoltage" : {
        "from" : [board.POWER],
        "to" : [board.TOP, board.DRIBBLER],
        "data" : [
            ["voltagePowerBoard", 8, [20, 30], "power board voltage"]
        ]
    },
    "MCP_Kill" : {
        "from" : [board.TOP],
        "to" : [board.POWER],
        "data" : [

        ]
    },
    "MCP_DribblerEncoder" : {
        "from" : [board.DRIBBLER],
        "to" : [board.TOP],
        "data" : [
            ["value", 16, [0, 5000.0], "Dribbler speed"],
        ]
    },
    "MCP_StopSending" : {
        "from" : [board.TOP],
        "to" : [board.DRIBBLER, board.KICKER, board.POWER],
        "data" : []
    }
}

generic_packet = [
    ["ack_number", 8, None, "acknowledgements"]
]

for packet_name in packets:
    packets[packet_name]["data"] = generic_packet + packets[packet_name]["data"]