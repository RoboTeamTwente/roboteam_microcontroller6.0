import os
import math
from mcp_packets import packets
from datetime import datetime
from mcp_boards import board


# REM_RobotCommand => REM_ROBOT_COMMAND
def CamelCaseToUpper(word):
	# Find all indices where a lowercase letter is followed by an uppercase letter
	indices = [ i for i in range(1, len(word)) if word[i-1].islower() and word[i].isupper() ]
	# Insert a _ at all of those indices
	for i in reversed(indices):	word = word[:i] + "_" +  word[i:]
	# Uppercase word
	word = word.upper()

	return word

# packet should be a definition from packet.py, e.g. 
# [
#	['header',    8, None, 'Header byte indicating the type of packet'], 
#	['toRobotId', 4, None, 'Id of the receiving robot'],
# ]
def packet_to_size_in_bytes(packet):
	total_bits = sum([variable[1] for variable in packet['data']])
	total_bytes = math.ceil(total_bits / 8)
	return total_bytes

def indent():
    return "    "

def doubleIndent():
    return indent() + indent()

def tripleIndent():
    return indent() + doubleIndent()

type_to_id, type_to_size = {}, {}
l_just_ = 75

class BaseTypeGenerator:

    def generate(self, packets, version):

        timestamp = datetime.now()
        timestamp_string = timestamp.strftime("%B %d %Y, %H:%M:%S")
        
        
        file_string = ""

        file_string += "// AUTOGENERATED. Run generator/main.py to regenerate\n"
        # file_string += f"{c} Generated on %s\n\n" % timestamp.strftime("%B %d %Y, %H:%M:%S")

        # file_string += f"{c} Warning : Check the unicode table before assigning a byte, to make sure that the byte isn't used for anything special : https://unicode-table.com/\n"
        # file_string += f"{c} For example, don't use the following bytes\n"
        # file_string += f"{c} 0b00000000 : The null-terminator, used to signal the end of strings / arrays / etc.\n"
        # file_string += f"{c} 0b00001010 : The byte for newline, used for line termination.\n"
        # file_string += f"\n"

        file_string += self.to_begin(packets) + "\n"

        largest_packet_in_bytes = max([packet_to_size_in_bytes(packets[packet_name]) for iPacket, packet_name in enumerate(packets.keys())])

        if (largest_packet_in_bytes > 8):
            print('A payload is larger than 8 bytes, this is not allowed')
            exit()

        file_string += self.to_constant("MCP_LOCAL_VERSION", version) + "\n"
        file_string += self.to_constant("MCP_LARGEST_PACKET_IN_BYTES", largest_packet_in_bytes) + "\n\n"

        file_string += self.define_boards() + "\n"

        file_string += self.defines_per_packet(packets, version) + "\n"

        file_string += self.type_to_size(type_to_size) + "\n"

        file_string += self.type_to_id_mapping(type_to_id) + "\n"

        file_string += self.to_end() + "\n"

        return file_string

    def to_begin(self, packets):
        begin_string = ""
        begin_string += "#ifndef __MCP_BASETYPES_H\n"
        begin_string += "#define __MCP_BASETYPES_H\n"
        begin_string += "\n"
        begin_string += "#include <stdint.h>\n"
        begin_string += "#include <stdbool.h>\n"
        begin_string += "\n"
        return begin_string

    def to_end(self):
        return "#endif /*__MCP_BASETYPES_H*/"

    def to_constant(self, variable_name, value):
        return f"#define {variable_name} {value}"

    def type_to_id_mapping(self, type_to_id):
        tti_string = "static uint32_t MCP_TYPE_TO_ID(uint16_t type, uint8_t receiving_board) {\n"
        first_round = True

        for b in type_to_id:
            if not first_round:
                tti_string += " else "
            else :
                tti_string += indent()
            tti_string += f"if (receiving_board == {b})" + " {\n"
            
            for id, name in type_to_id[b]:
                tti_string += doubleIndent()
                tti_string += f"if (type == {name})".ljust(l_just_)

                tti_string += f"return {id}".ljust(l_just_) + ";\n"

            tti_string += indent() + "}"
            first_round = False

        tti_string += "\n" + indent() + "return 0x10000000;\n"
        tti_string += "\n}\n"
        return tti_string
    
    def define_boards(self):
        db_string = ""

        for b in board:
            VARIABLE_NAME_BOARD = f"MCP_{CamelCaseToUpper(b.name)}_BOARD"
            db_string += self.to_constant(VARIABLE_NAME_BOARD.ljust(l_just_), b.value) + "\n"
            type_to_id[VARIABLE_NAME_BOARD] = []

        return db_string
    
    def type_to_size(self, type_to_size):
        tts_string = "static uint8_t MCP_TYPE_TO_SIZE(uint16_t type) {\n"

        for type in type_to_size:
            tts_string += indent() + f"if (type == {type})".ljust(l_just_)
            tts_string += f"return {type_to_size[type]};\n"

        tts_string += indent() + "return 1;\n"
        tts_string += "}\n" 

        return tts_string
    
    def defines_per_packet(self, packets, version):
        index = 0
        message_id_per_board = {}
        for b in board:
            message_id_per_board[b] = 0
        dpp_string = ""

        for packet_name in packets:
            total_bytes = packet_to_size_in_bytes(packets[packet_name])
            PACKET_NAME = CamelCaseToUpper(packet_name)

            VARIABLE_NAME_TYPE = f"MCP_PACKET_TYPE_{PACKET_NAME}"
            dpp_string += self.to_constant(VARIABLE_NAME_TYPE.ljust(l_just_), index) + "\n"
            index += 1

            '''
            message id
            [  00  ] [  01  ] [  02  ] [  03  ]
            111----- -------- -------- -------- RESERVED (DO NOT USE)
            ---1---- -------- -------- -------- ERROR INDICATOR
            ----1111 -------- -------- -------- MCP VERSION
            -------- 11111111 -------- -------- UNUSED
            -------- -------- 11111111 -------- MESSAGE ID
            -------- -------- -------- 1111---- FROM ID
            -------- -------- -------- ----1111 TO ID

            the message id needs to be unique to be able to tell messages apart
            '''
            for from_board in packets[packet_name]["from"]:
                for to_board in packets[packet_name]["to"]:
                    if from_board == to_board:
                        continue

                    message_id = 0b00000000000 # 11 bits, length of standard ID
                    message_id = message_id | (to_board.value)
                    message_id = message_id | (from_board.value << 4)
                    message_id = message_id | (message_id_per_board[to_board] << 8)
                    message_id = message_id | (version << 24)
                    message_id = str(hex(message_id))
                    message_id_per_board[to_board] += 1

                    if (message_id_per_board[to_board] > 0xFF):
                        print("TO MANY PACKETS FOR " + packets[packet_name]["to"])
                        exit()

                    message_id_str = '0x' + message_id[2:].zfill(8)
                    VARIABLE_NAME_ID = f"MCP_PACKET_ID_{from_board.name.upper()}_TO_{to_board.name.upper()}_{PACKET_NAME}"
                    dpp_string += self.to_constant(VARIABLE_NAME_ID.ljust(l_just_), message_id_str) + "\n"
                    VARIABLE_NAME_BOARD = f"MCP_{CamelCaseToUpper(to_board.name)}_BOARD"
                    type_to_id[VARIABLE_NAME_BOARD].append([VARIABLE_NAME_ID, VARIABLE_NAME_TYPE])

            # size
            VARIABLE_NAME_SIZE = f"MCP_PACKET_SIZE_{PACKET_NAME}"
            type_to_size[VARIABLE_NAME_TYPE] = VARIABLE_NAME_SIZE
            dpp_string += self.to_constant(VARIABLE_NAME_SIZE.ljust(l_just_), max(packet_to_size_in_bytes(packets[packet_name]), 1)) + "\n"
            				
            # min max
            for variable, n_bits, _range, description, in packets[packet_name]["data"]:
                VARIABLE_NAME = CamelCaseToUpper(variable)
                range_min, range_max = 0, 2**n_bits-1
                if _range is not None: range_min, range_max = _range
                # Return simply 'x' if integer range, or 'x.[abcde]F' if float range
				# So: float 8.4000 -> 8.4F | float 8.0000F -> 8.F | int 8 -> 8
                get_value_string = lambda x: f"{x}" if _range is None else f"{x:.16f}F".rstrip('0')

                dpp_string += self.to_constant(f"MCP_PACKET_RANGE_{PACKET_NAME}_{VARIABLE_NAME}_MIN".ljust(l_just_), get_value_string(range_min)) + "\n"
                dpp_string += self.to_constant(f"MCP_PACKET_RANGE_{PACKET_NAME}_{VARIABLE_NAME}_MAX".ljust(l_just_), get_value_string(range_max)) + "\n"

            dpp_string += "\n"
        return dpp_string