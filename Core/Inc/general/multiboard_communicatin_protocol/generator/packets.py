from boards import board
'''
from : {
    to : {
        name : [
            [data 1]
            [data 2]
            etc.
        ]
    }
}

where data is as follows
[name, bits, None or [min, max], description]
use [min, max] only for floats
'''
packets = {
    board.TOP : {
        board.ANY : {
            "areYouAlive" : [
                ["mcpVersion", 4, None, "version of mcp"]
            ]
        },
        board.DRIBBLER : {
            "setDribbler" : [
                ["speed", 8, [0, 1], "desired speed of the dribbler"],
            ]
        },
        board.KICKER : {
            "charge" : [
                ["voltage", 10, None, "target voltage"]
            ],
            "stopCharge" : [

            ],
            "kick" : [
                ["shootPower", 4, [0, 6.5], "desired speed of the ball"]
            ], 
            "chip" : [
                ["shootPower", 4, [0, 6.5], "desired speed of the ball"]
            ]
        }
    },
    board.DRIBBLER : {
        board.TOP : {
            "dribblerBoardAlive" : [
                ["mcpVersion", 4, None, "version of mcp"],
                ["dribblerEncoderWorking", 1, None, "status of dribbler encoder"],
                ["ballsensorWorking", 1, None, "status of ballsensor"]
            ],
            "seesBall" : [
                ["dribblerSeesBall", 1, None, "true if dribbler encoder detects ball"],
                ["ballsensorSeesBall", 1, None, "true if ball sensor detects ball"]
            ]
        }
    },
    board.KICKER : {
        board.TOP : {
            "kickerBoardAlive" : [
                ["mcpVersion", 4, None, "version of mcp"],
                ["sensorWorking", 1, None, "capacitor voltage sensor working"]
            ],
            "capacitorVoltage" : [
                ["voltage", 10, None, "capacitor voltage"]
            ]
        }
    },
    board.POWER : {
        board.TOP : {
            "powerBoardAlive" : [
                ["mcpVersion", 4, None, "version of mcp"],
                ["sensorWorking", 1, None, "voltage sensor working"]
            ],
            "powerVoltage" : [
                ["voltagePowerBoard", 16, [0, 26], "power board voltage"]
            ]
        },
        board.DRIBBLER : {
            "powerVoltage" : [
                ["voltagePowerBoard", 16, [0, 26], "power board voltage"]
            ]
        }
    }
}
