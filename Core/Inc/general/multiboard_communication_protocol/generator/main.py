import argparse
import os
from datetime import datetime
import math
import shutil

from mcp_boards import board
from mcp_packets import packets

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
for packet in packets:
	continue

#move files to correct location	
for folder in folders:
	shutil.rmtree(f"../{folder}")
	os.makedirs(f"../{folder}", exist_ok=True)
	for file in os.listdir(f"generated_{folder}"):
		shutil.move(f"generated_{folder}/{file}", f"../{folder}/{file}")

write_version(version)

print("\n")
print(f"All files generated with MCP version {version}")
print("If you want to generate using a specific version, run 'python main.py --version %d'")