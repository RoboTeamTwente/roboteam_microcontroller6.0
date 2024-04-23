import argparse
import os
from datetime import datetime
import math
import shutil

import mcp_generator
from mcp_boards import board
from mcp_packets import packets
import mcp_BaseTypeGenerator

def read_version():
	return int(open("latest_mcp_version.txt", "r").read())
def write_version(version):
	open("latest_mcp_version.txt", "w").write(str(version % 16))
	
parser = argparse.ArgumentParser()
parser.add_argument('--version', help='MCP version number', type=int)

args = parser.parse_args()

version = read_version() + 1
if args.version is not None:
	version = args.version

print(f"Generating MCP version {version}")

folders = []

#prep folders
for from_board in board:
	from_board_formatted = from_board.name.lower()
	folder_name = f"from_{from_board_formatted}"
	folders.append(folder_name)
	os.makedirs(f"generated_{folder_name}", exist_ok=True)

for to_board in board:
	to_board_formatted = to_board.name.lower()
	folder_name = f"to_{to_board_formatted}"
	folders.append(folder_name)
	os.makedirs(f"generated_{folder_name}", exist_ok=True)

#generate files
for packet_name in packets:
	variables = packets[packet_name]["data"]

	generator_ = mcp_generator.Generator()
	generated = generator_.generate(packet_name, variables)

	filename = f"{packet_name}.h"
	for from_board in packets[packet_name]["from"]:
		with open(os.path.join(f"generated_from_{from_board.name.lower()}", filename), "w+") as file:
			file.write(generated)

	for to_board in packets[packet_name]["to"]:
		with open(os.path.join(f"generated_to_{to_board.name.lower()}", filename), "w+") as file:
			file.write(generated)

	print(f"Generated file {filename}")

#generate general include files
generator_ = mcp_generator.Include_Generator()
for b in board:
	filename = f"MCP_from_{b.name.lower()}.h"
	folder_name = b.name.lower()
	with open(os.path.join(f"generated_from_{folder_name}", filename), "w") as file:
		file.write(generator_.generate(packets, b, False))
		print("Generated file", filename)
	filename = f"MCP_to_{b.name.lower()}.h"
	with open(os.path.join(f"generated_to_{folder_name}", filename), "w") as file:
		file.write(generator_.generate(packets, b, True))
		print("Generated file", filename)

#move files to correct location	
for folder in folders:
	shutil.rmtree(f"../{folder}")
	os.makedirs(f"../{folder}", exist_ok=True)
	for file in os.listdir(f"generated_{folder}"):
		shutil.move(f"generated_{folder}/{file}", f"../{folder}/{file}")

#generate MCP_BaseTypes.h
basetypegenerator = mcp_BaseTypeGenerator.BaseTypeGenerator()
filename = "MCP_BaseTypes.h"
if (os.path.exists(f"../{filename}")):
	os.remove(f"../{filename}")
with open(os.path.join("../", filename), "w") as file:
	file.write(basetypegenerator.generate(packets, version))
print(f"Generated file {filename}")


write_version(version)

print("\n")
print(f"All files generated with MCP version {version}")
print("If you want to generate using a specific version, run 'python main.py --version %d'")