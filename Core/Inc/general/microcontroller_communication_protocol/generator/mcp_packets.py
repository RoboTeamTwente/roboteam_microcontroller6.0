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
    "MCP_Reboot" : {
        "from" : [board.TOP],
        "to" : [board.POWER, board.KICKER, board.DRIBBLER],
        "data" : [
        ]
    },
    "MCP_AreYouAlive" : {
        "from" : [board.TOP],
        "to" : [board.POWER, board.KICKER, board.DRIBBLER],
        "data" : [
        ]
    },
    "MCP_DribblerCommand" : {
        "from" : [board.TOP],
        "to" : [board.DRIBBLER],
        "data" : [
            ["dribblerOn",          1,  None, "Dribbler on/off"],
            ["dribblerOption1",     1,  None, "Dribbler option 1"],
            ["dribblerOption2",     1,  None, "Dribbler option 2"],
            ["dribblerOption3",     1,  None, "Dribbler option 3"],
            ["dribblerOption4",     1,  None, "Dribbler option 4"],
            ["dribblerOption5",     1,  None, "Dribbler option 5"],
            ["dribblerOption6",     1,  None, "Dribbler option 6"],
            ["dribblerOption7",     1,  None, "Dribbler option 7"],
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
            ["shootPower", 8, [0, 6.5], "desired speed of the ball"],
        ]
    },
    "MCP_Chip" : {
        "from" : [board.TOP],
        "to" : [board.KICKER],
        "data" : [
            ["shootPower", 8, [0, 6.5], "desired speed of the ball"],
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
            ["dribblerSpeedBefore", 16, [0, 5000.0], "dribbler speed before it got the ball"],
            ["dribblerSeesBall", 1, None, "true if dribbler encoder detects ball"],
            ["ballsensorSeesBall", 1, None, "true if ball sensor detects ball"],
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
    "MCP_KickerStatus" : {
        "from" : [board.KICKER],
        "to" : [board.TOP],
        "data" : [
            ["kickerOn", 1, None, "If kicker is on & charging"],
            ["kickerFault", 1, None, "If kicker return fault"],
            ["kickerReady", 1, None, "Indicatei if kicker is ready to shoot"]
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
            ["voltagePowerBoard", 16, [15, 30], "power board voltage"]
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
            ["measuredSpeed", 16, [0, 5000.0], "Measured dribbler speed"],
            ["filteredSpeed", 16, [0, 5000.0], "Filtered dribbler speed"],
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