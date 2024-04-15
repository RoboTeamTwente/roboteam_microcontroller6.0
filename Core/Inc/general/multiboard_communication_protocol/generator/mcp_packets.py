from mcp_boards import board
'''
data is as follows
[name, bits, None or [min, max], description]
use [min, max] only for floats
'''
packets = {
    "areYouAlive" : {
        "from" : board.TOP,
        "to" : [board.POWER, board.KICKER, board.DRIBBLER],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"]
        ]
    },
    "setDribblerSpeed" : {
        "from" : board.TOP,
        "to" : [board.DRIBBLER],
        "data" : [
                ["speed", 8, [0, 1], "desired speed of the dribbler"],
            ]
    },
    "kickerCharge" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [
            ["voltage", 10, None, "target voltage"]
        ],
    },
    "kickerStopCharge" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [

        ]
    },
    "kick" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [
            ["shootPower", 4, [0, 6.5], "desired speed of the ball"]
        ]
    },
    "chip" : {
        "from" : board.TOP,
        "to" : [board.KICKER],
        "data" : [
            ["shootPower", 4, [0, 6.5], "desired speed of the ball"]
        ]
    },
    "dribblerAlive" : {
        "from" : board.DRIBBLER,
        "to" : [board.TOP],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"],
            ["dribblerEncoderWorking", 1, None, "status of dribbler encoder"],
            ["ballsensorWorking", 1, None, "status of ballsensor"]
        ],
    },
    "seesBall" : {
        "from" : board.DRIBBLER,
        "to" : [board.TOP],
        "data" : [
            ["dribblerSeesBall", 1, None, "true if dribbler encoder detects ball"],
            ["ballsensorSeesBall", 1, None, "true if ball sensor detects ball"]
        ]
    },
    "kickerAlive" : {
        "from" : board.KICKER,
        "to" : [board.TOP],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"],
            ["sensorWorking", 1, None, "capacitor voltage sensor working"]
        ],
    },
    "kickerCapacitorVoltage" : {
        "from" : board.KICKER,
        "to" : [board.TOP],
        "data" : [
            ["voltage", 10, None, "capacitor voltage"]
        ]
    },
    "powerAlive" : {
        "from" : board.POWER,
        "to" : [board.TOP],
        "data" : [
            ["mcpVersion", 4, None, "version of mcp"],
            ["sensorWorking", 1, None, "voltage sensor working"]
        ]
    },
    "powerVoltage" : {
        "from" : board.POWER,
        "to" : [board.TOP, board.DRIBBLER],
        "data" : [
            ["voltagePowerBoard", 8, [20, 30], "power board voltage"]
        ]
    },
}
