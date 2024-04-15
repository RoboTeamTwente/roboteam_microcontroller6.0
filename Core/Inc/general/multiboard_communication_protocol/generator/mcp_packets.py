from mcp_boards import board
'''
data is as follows
[name, bits, None or [min, max], description]
use [min, max] only for floats
'''
packets = {
    "MCP_AreYouAlive" : {
        "from" : board.TOP,
        "to" : [board.POWER, board.KICKER, board.DRIBBLER],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"]
        ]
    },
    "MCP_SetDribblerSpeed" : {
        "from" : board.TOP,
        "to" : [board.DRIBBLER],
        "data" : [
                ["speed", 8, [0, 1], "desired speed of the dribbler"],
            ]
    },
    "MCP_KickerCharge" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [
            ["voltage", 10, None, "target voltage"]
        ],
    },
    "MCP_KickerStopCharge" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [

        ]
    },
    "MCP_Kick" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [
            ["shootPower", 4, [0, 6.5], "desired speed of the ball"]
        ]
    },
    "MCP_Chip" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [
            ["shootPower", 4, [0, 6.5], "desired speed of the ball"]
        ]
    },
    "MCP_DribblerAlive" : {
        "from" : board.DRIBBLER,
        "to" : [board.TOP],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"],
            ["dribblerEncoderWorking", 1, None, "status of dribbler encoder"],
            ["ballsensorWorking", 1, None, "status of ballsensor"]
        ],
    },
    "MCP_SeesBall" : {
        "from" : board.DRIBBLER,
        "to" : [board.TOP],
        "data" : [
            ["dribblerSeesBall", 1, None, "true if dribbler encoder detects ball"],
            ["ballsensorSeesBall", 1, None, "true if ball sensor detects ball"]
        ]
    },
    "MCP_KickerAlive" : {
        "from" : board.KICKER,
        "to" : [board.TOP],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"],
            ["sensorWorking", 1, None, "capacitor voltage sensor working"]
        ],
    },
    "MCP_KickerCapacitorVoltage" : {
        "from" : board.KICKER,
        "to" : [board.TOP],
        "data" : [
            ["voltage", 10, None, "capacitor voltage"]
        ]
    },
    "MCP_PowerAlive" : {
        "from" : board.POWER,
        "to" : [board.TOP],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"],
            ["sensorWorking", 1, None, "voltage sensor working"]
        ]
    },
    "MCP_PowerVoltage" : {
        "from" : board.POWER,
        "to" : [board.TOP, board.DRIBBLER],
        "data" : [
            ["voltagePowerBoard", 8, [20, 30], "power board voltage"]
        ]
    },
}
