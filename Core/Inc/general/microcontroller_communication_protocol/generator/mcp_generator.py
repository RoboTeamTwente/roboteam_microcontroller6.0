from mcp_packets import packets
import math

############################## UTILITY FUNCTIONS ##############################

# Capitalizes the first letter of a word
def upperFirst(word):
	return word[0].capitalize() + word[1:]
# RobotCommand => rc
def CamelCaseToAbbrev(word):
	return ''.join([letter for letter in word if letter.isupper()]).lower()
# REM_RobotCommand => REM_ROBOT_COMMAND
def CamelCaseToUpper(word):

	# Find all indices where a lowercase letter is followed by an uppercase letter
	indices = [ i for i in range(1, len(word)) if word[i-1].islower() and word[i].isupper() ]
	# Insert a _ at all of those indices
	for i in reversed(indices):	word = word[:i] + "_" +  word[i:]
	# Uppercase word
	word = word.upper()

	return word

def stripBrackets(string):
	while string[0] == "(" and string[-1] == ")":
		string = string[1:-1]
	return string

### Returns a string of 0bxxxxxxxx where x=1 if x in range [start, stop), else 0. If reverse=True, swap 0 and 1
# bitString(1, 2, reverse=False) = 0b01000000	
# bitString(5, 6, reverse=True ) = 0b11111011
def bitString(start, stop, reverse = False):
	set1 = list(range(start, stop))
	bitstring = "0b" + ''.join(["%d" % ((i in set1) ^ reverse) for i in range(8)])
	return bitstring

# Return either <<, >>, or nothing, depending on left vs right	
def shift(left, right):
	if left == right: return ""
	if left < right: return " >> %d" % (right-left)
	if right < left: return " << %d" % (left-right)

# Change number of bits to required integer size
def getType(n_bits, _range):
	_type = "bool"
	if  1 < n_bits: _type = "uint32_t"
	if 32 < n_bits: _type = "uint64_t"
	return _type

# Returns a and b in the formula y = ax+b
def getConversion(nBits, _range):
		vMin, vMax = _range
		vTotal = vMax - vMin
		return vTotal / (2**nBits - 1), vMin

# Intermediate type for a variable. Contains the name, number of bits, range, and description. Used for type hinting
Variable = tuple[str, int, list[float, float] | None, str]

class Generator:

    payload_abbrev = None

    def generate(self, packet_name:str, variables:list[Variable]) -> str:
        """ Entrypoint for generating a packet. This function calls all other functions in the correct order, and returns
        the generated file as a string

        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet. Each variable is a 
            tuple of (name, n_bits, range (optional), description)

        Returns:
            str: The generated file as a string
        """
    
        
        file_string = ""
        file_string += "// AUTOGENERATED. Run generator/main.py to regenerate\n"

        file_string += self.to_packet_description(packet_name, variables)
        file_string += "\n"
        
        file_string += self.to_begin(packet_name)
        file_string += "\n"
        
        file_string += self.to_payload_instance(packet_name, variables)
        file_string += "\n\n"
        
        file_string += self.to_instance(packet_name, variables)
        file_string += "\n\n"

        file_string += "// ================================ GETTERS ================================\n"
        file_string += self.generate_getters(packet_name, variables)

        file_string += "// ================================ SETTERS ================================\n"
        file_string += self.generate_setters(packet_name, variables)

        file_string += "// ================================ ENCODE ================================\n"
        file_string += self.to_encode(packet_name, variables)
        file_string += "\n\n"

        file_string += "// ================================ DECODE ================================\n"
        file_string += self.to_decode(packet_name, variables)
        file_string += "\n\n"

        file_string += self.to_end(packet_name)

        return file_string

    def generate_getters(self, packet_name:str, variables:list[Variable]) -> str:
        """ Generates all getters for a packet. A getter is a function that takes a payload instance, and returns a variable. These
        are all the get_rho, get_theta, get_* etc functions
        
        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet

        Returns:
            str: The generated getters
        """
        current_bit = 0
        getters_string = ""
        for variable in variables:
            getters_string += self.to_function_call_get(packet_name, variable)
            getters_string += self.to_getter(packet_name, variable, current_bit)
            getters_string += "}\n\n"
            _, n_bits, _, _ = variable
            current_bit += n_bits
        return getters_string

    def generate_setters(self, packet_name:str, variables:list[Variable]):
        """ Generates all setters for a packet. A setter is a function that takes a payload instance, and a variable, and sets the
        variable in the payload instance. These are all the set_rho, set_theta, set_* etc functions

        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet

        Returns:
            str: The generated setters
        """
        current_bit = 0
        setters_string = ""
        for variable in variables:
            setters_string += self.to_function_call_set(packet_name, variable)
            setters_string += self.to_setter(packet_name, variable, current_bit)
            setters_string += "}\n\n"
            _, n_bits, _, _ = variable
            current_bit += n_bits
        return setters_string

    def to_packet_description(self, packet_name, variables:list[Variable]):
        """ Generates a description of the packet, such as the packet name, the date, and a description of all variables

        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet

        Returns:
            str: The description of the packet
        """
        # Calculate number of bytes needed to store all variables. ceil(total number of bits / 8)
        n_bytes = math.ceil(sum([n_bits for (_, n_bits, _, _) in variables]) / 8)
        # Create [---0--] [---1--] [---2--] .......
        string_description = "/*\n"
        string_description += ' '.join([ f"[{i : ^6}]" for i in range(n_bytes) ])
        # Keep track of location in the packet
        current_bit = 0
        for variable, n_bits, _, desc in variables:
            string_description += "\n"	
            active_bits = list(range(current_bit, current_bit + n_bits)) # Indices of active bits
            for i in range(n_bytes * 8): # For all bits
                if i != 0 and i % 8 == 0: string_description += " " # Add whitespace
                string_description += "1" if i in active_bits else "-" # Add '1' if bit active, '-' if inactive
            string_description += f" {variable}"
            current_bit += n_bits
        string_description += "\n*/\n"
        return string_description

    def to_getter(self, packet_name:str, variable:Variable, current_bit:int) -> str:
        """ Generates the body for the getter function, that gets a variable from a payload instance, decodes it, and returns it

        Example for C REM_RobotCommand_get_rho: 
            uint32_t _rho = ((remrcp->payload[8]) << 8) | ((remrcp->payload[9]));
            return (_rho * 0.0001220721751736F);

        Args:
            packet_name (str): The name of the packet 
            variable (Variable): The variable to create the getter for
            current_bit (int): The current bit index within the encoded packet where the start of the variable is located

        Returns:
            str: The code for the body of the getter function
        """

        variable_name, n_bits, _range, desc = variable			# Unpack Variable
        at_byte, at_bit = current_bit // 8, current_bit % 8		# Calculate byte and bit index of current variable within the encoded packet
        _type = getType(n_bits, _range) 						# Figure out the type of the variable
        float_conversion = _range is not None					# Check if the variable needs to be converted from integer to float

        payload_variable = self.get_payload_variable(packet_name)

        if _type == "bool":
            return f"    return ({payload_variable}[{at_byte}] & {bitString(at_bit, at_bit+1)}) > 0;\n"

        if _type in ["uint32_t", "uint64_t"]:
            n_bits_remaining = n_bits
            bitwise_operations = []
            
            while 0 < n_bits_remaining:
                # Find the byte index in the packet, and the bit index within that byte
                at_byte, at_bit = current_bit // 8, current_bit % 8
                # Calculate the number of bits to process from the current byte. Always 8 or less
                # Either the remaining bits in the variable, or the remaining bits in the byte, whichever one is smaller
                bits_from_byte = min(n_bits_remaining, 8 - at_bit)
                # Figure out which bits we need from the byte
                start_bit, stop_bit = at_bit, at_bit + bits_from_byte
                # Generate bitshift mask, except if the entire byte is used, e.g. " & 0b00111000"
                bitshift_mask = "" if bits_from_byte == 8 else f" & {bitString(start_bit, stop_bit)}"
                # Figure out how much we need to shift this baby in total
                shift_to_right = (8 - stop_bit)
                shift_to_left = n_bits_remaining - bits_from_byte
                # for C, figure out if type casting is needed
                type_cast = self.to_typecast(shift_to_left)		

                bitwise_operation = f"({type_cast}({payload_variable}[{at_byte}]{bitshift_mask}){shift(shift_to_left, shift_to_right)})"
                bitwise_operations.append(bitwise_operation)

                n_bits_remaining -= bits_from_byte
                current_bit += bits_from_byte

            # Concatenate all bit operations
            bitwise_operations_string = ' | '.join(bitwise_operations)

            # No range given, so no conversion to float needed
            if not float_conversion:
                return f"   return {bitwise_operations_string};\n"
            # Range given. Do integer => float conversion
            else: 
                a, b = getConversion(n_bits, _range) # y = ax + b
                variable_type = "" if self.convert_type(_type) is None else f"{self.convert_type(_type)} "
                conversion_string  = f"    {variable_type}_{variable_name} = {bitwise_operations_string};\n"
                conversion_string += f"    return (_{variable_name} * {a:.16f}F)"
                if b != 0: conversion_string += f" + {b:.16f}F"
                conversion_string += ";\n"
                return conversion_string

    def to_setter(self, packet_name:str, variable:Variable, current_bit:int) -> str:
        """ Generates the body for the sets function, that encodes a value, and places it in a payload instance

        Example for C REM_RobotCommand_set_rho: 
            uint32_t _rho = (uint32_t)(rho / 0.0001220721751736F);
            remrcp->payload[8] = (_rho >> 8);
            remrcp->payload[9] = _rho;

        Args:
            packet_name (str): The name of the packet 
            variable (Variable): The variable to create the getter for
            current_bit (int): The current bit index within the encoded packet where the start of the variable is located

        Returns:
            str: The code for the body of the setter function
        """
        variable_name, n_bits, _range, desc = variable			# Unpack Variable
        at_byte, at_bit = current_bit // 8, current_bit % 8		# Calculate byte and bit index of current variable within the encoded packet
        _type = getType(n_bits, _range) 						# Figure out the type of the variable
        float_conversion = _range is not None					# Check if the variable needs to be converted from integer to float

        payload_variable = self.get_payload_variable(packet_name)

        # Create the conversion from float to integer, if needed
        conversion_string = ""
        if float_conversion:
            # Formula : y = ax + b => x = (y - b) / a
            a, b = getConversion(n_bits, _range)
            variable_type = "" if self.convert_type(_type) is None else f"{self.convert_type(_type)} "
            subtract_string = f"{variable_name}" if b == 0 else f"({variable_name} {-b:+.16f}F)"
            division_string = f" / {int(a)}" if int(a) == float(a) else f" / {a:.16f}F"
            calculation_string = self.cast_to_type(f"{subtract_string}{division_string}", _type)
            conversion_string += f"    {variable_type}_{variable_name} = {calculation_string};\n"
            variable_name = f"_{variable_name}"

        # Create all bitwise operations
        n_bits_remaining = n_bits
        bitwise_operations = []
        
        while 0 < n_bits_remaining:
            # Find the byte index in the packet, and the bit index within that byte
            at_byte, at_bit = current_bit // 8, current_bit % 8
            # Calculate the number of bits to process from the current byte. Always 8 or less
            # Either the remaining bits in the variable, or the remaining bits in the byte, whichever one is smaller
            bits_from_byte = min(n_bits_remaining, 8 - at_bit)
            # Figure out which bits we need from the byte
            start_bit, stop_bit = at_bit, at_bit + bits_from_byte

            # Generate bitshift mask, except if the entire byte is used, e.g. " & 0b00111000"
            bitshift_mask = "" if bits_from_byte == 8 else f" & {bitString(start_bit, stop_bit)}"
            # Generate inverse bitmask
            bitmask_inverted = f" & {bitString(start_bit, stop_bit, True)}"

            # Figure out how much we need to shift this baby in total
            shift_to_left = 8 - stop_bit
            shift_to_right = max(0, n_bits_remaining - bits_from_byte)

            # Create the mask that prevents unrelated bits from being set
            string_inverse = ""
            if bits_from_byte < 8:
                string_inverse = f" | ({payload_variable}[{at_byte}]{bitmask_inverted})"

            # Add shifting of variable if needed
            string_shift = variable_name
            if shift_to_left != 0 or shift_to_right != 0:
                string_shift = f"({variable_name}{shift(shift_to_left, shift_to_right)})"
                
            # Add masking to variable if needed
            string_bitmask = string_shift
            if bits_from_byte != 8:
                string_bitmask = f"({string_shift}{bitshift_mask})"

            operation_string = f"    {payload_variable}[{at_byte}] = {string_bitmask}{string_inverse};"
            bitwise_operations.append(operation_string)

            n_bits_remaining -= bits_from_byte
            current_bit += bits_from_byte

        operations_string = conversion_string
        operations_string += '\n'.join(bitwise_operations) + "\n"
        return operations_string

    def convert_type(self, variable_type):
        """ Converts a type bool, float, uint32_t, uint64_t to a type in the language of the generator. For example,
        in C, uint32_t is converted to uint32_t, but in Python, uint32_t is converted to int

        Args:
            variable_type (str): The type to convert, such as bool, float, uint32_t, uint64_t

        Returns:
            str: The converted type, such as uint32_t, int, etc
        """
        return variable_type

    def cast_to_type(self, string, variable_type):
        """_summary_

        Args:
            string (str): The variable to convert, such as 0.6124 or any other expression such as (a + b)
            variable_type (str): Any type such as float, bool, uint32_t, uint64_t

        Returns:
            str: The conversation, such as (uint32_t)(0.6124), or (int)(0.6124)
        """		 
        return f"({variable_type})({string})"

    def get_payload_name(self, packet_name):
        """ Generates the name of the payload variable, such as 'payload' or an abbreviation such as rcp

        Args:
            packet_name (str): The name of the packet such as REM_RobotCommand

        Returns:
            str: The name of the payload variable
        """
        return f"{CamelCaseToAbbrev(packet_name)}p"
    def get_payload_variable(self, packet_name):
        """ Generates the code to get the payload from the payload variable. For python, this is simply 'payload', but
        for C, this is e.g. 'rcp->payload'

        Args:
            packet_name (str): The name of the packet such as REM_RobotCommand

        Returns:
            str: The code to get the payload from the payload variable
        """
        return f"{self.get_payload_name(packet_name)}->payload"

    def to_begin(self, packet_name):
        """ Generates anything needed at the beginning of a file, such as '#include <stdint.h>'

        Args:
            packet_name (str): The name of the packet

        Returns:
            str: The string to be added at the beginning of the file
        """
        begin_string = ""
        begin_string += f"#ifndef {self.to_header_guard(packet_name)}\n"
        begin_string += f"#define {self.to_header_guard(packet_name)}\n"
        begin_string += "\n"
        begin_string += f"#include <stdbool.h>\n"
        begin_string += f"#include <stdint.h>\n"
        begin_string += f"#include \"MCP_BaseTypes.h\"\n"
        return begin_string

    def to_end(self, packet_name):
        """ Generates anything needed at the end of a file, such as '#endif // __REM_ROBOTCOMMAND_H__'

        Args:
            packet_name (str): The name of the packet

        Returns:
            str: The string to be added at the end of the file
        """
        return f"#endif /*{self.to_header_guard(packet_name)}*/\n"

    # typedef struct _RobotCommandPayload {
    #     uint8_t payload[MCP_PACKET_SIZE_ROBOT_COMMAND];
    # } RobotCommandPayload;
    def to_payload_instance(self, packet_name, variables):
        """ Generates the code for the payload instance. For C, this is a struct with a uint8_t array

        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet

        Returns:
            str: The code for the payload instance
        """
        string_struct  = f"typedef struct _{packet_name}Payload {{\n"
        string_struct += f"    uint8_t payload[MCP_PACKET_SIZE_{CamelCaseToUpper(packet_name)}];\n"
        string_struct += f"}} {packet_name}Payload;"
        return string_struct

    # typedef struct _RobotCommand {
    #    uint8_t    header;                  // Header byte indicating the type of packet
    #    uint8_t    id;                      // Id of the robot
    #    uint8_t    messageId;               // Id of the message
    #    ....
    def to_instance(self, packet_name, variables):
        """ Generates the code for the packet instance. For C, this is a struct with all variables

        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet

        Returns:
            str: The code for the packet instance
        """
        string_struct = f"typedef struct _{packet_name} {{\n"
        
        for variable, n_bits, _range, desc in variables:
            # Get type (bool, uint32_t, uint64_t, float)
            if _range is not None: _type = "float"
            else: _type = getType(n_bits, _range)

            if _type == "float": range_string = f"float   [{_range[0]:.3f}, {_range[1]:.3f}]".ljust(28)
            else:                range_string = f"integer [0, {2**n_bits-1}]".ljust(28)

            string_struct += f"    {_type.ljust(10)}"		# Add type
            string_struct += f" {variable.ljust(20)};"		# Add variable name
            string_struct += f" // {range_string} {desc}\n" # Add description
        
        string_struct += f"}} {packet_name};"
        return string_struct

    def to_function_call_get(self, packet_name, variable):
        """ Generates the code for the function call to get a variable from a payload instance.

        Returns:
            str: The code for the function call
        """
        variable_name, n_bits, _range, desc = variable
        _type = "float" if _range is not None else getType(n_bits, _range) 
        return f"static inline {_type} {packet_name}_get_{variable_name}({packet_name}Payload *{self.get_payload_name(packet_name)}){{\n"
    def to_typecast(self, shift_to_left):
        """ Generates the code to peform type casting

        Args:
            shift_to_left: amount of bits the byte needs to be shifted to the left

        Returns
            str: The type cast that needs to happen
        """
        if shift_to_left >= 32:
            return "(uint64_t) "
        elif shift_to_left >= 24:
            return "(uint32_t) "
        return ""
    def to_function_call_set(self, packet_name, variable):
        variable_name, n_bits, _range, desc = variable
        _type = "float" if _range is not None else getType(n_bits, _range) 
        return f"static inline void {packet_name}_set_{variable_name}({packet_name}Payload *{CamelCaseToAbbrev(packet_name)}p, {_type} {variable_name}){{\n"


    def to_decode(self, packet_name, variables):
        """ Generates the code for the decode function. This function takes a payload instance, and decodes it into a
        packet instance

        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet

        Returns:
            str: The code for the decode function
        """
        packet_abbrev = CamelCaseToAbbrev(packet_name)
        function_string = f"static inline void decode{packet_name}({packet_name} *{packet_abbrev}, {packet_name}Payload *{packet_abbrev}p){{\n"
        for variable_name, n_bits, _, _ in variables:
            function_string += f"    {packet_abbrev}->{variable_name}".ljust(25) + f"= {packet_name}_get_{variable_name}({packet_abbrev}p);\n"
        function_string += "}"		
        return function_string

    def to_encode(self, packet_name, variables):
        """ Generates the code for the encode function. This function takes a packet instance, and encodes it into a
        payload instance

        Args:
            packet_name (str): The name of the packet
            variables (list[Variable]): The variables in the packet
        
        Returns:
            str: The code for the encode function
        """
        packet_abbrev = CamelCaseToAbbrev(packet_name)
        function_string = f"static inline void encode{packet_name}({packet_name}Payload *{packet_abbrev}p, {packet_name} *{packet_abbrev}){{\n"
        for variable_name, n_bits, _, _ in variables:
            function_string += f"    {packet_name}_set_{variable_name:<20}({packet_abbrev}p, {packet_abbrev}->{variable_name});\n"
        function_string += "}"
        return function_string

    # RobotCommand => __ROBOT_COMMAND_H
    def to_header_guard(self, packet_name):
        return f"__{CamelCaseToUpper(packet_name)}_H"

class Include_Generator:
    def generate(self, packets, board, sending):
        c = "TO" if sending else "FROM"

        file_string = ""
        file_string += "// AUTOGENERATED. Run generator/main.py to regenerate\n"

        file_string += f"#ifndef __MCP_{c}_{board.name.upper()}_H\n"
        file_string += f"#define __MCP_{c}_{board.name.upper()}_H\n"
        file_string += "\n"

        for packet in packets:
            if (not sending and packets[packet]["from"] == board) or (sending and board in packets[packet]["to"]):
                file_string += f"#include \"{packet}.h\"\n"

        file_string += f"#endif /* __MCP_{c}_{board.name.upper()}_H */\n"

        return file_string
         