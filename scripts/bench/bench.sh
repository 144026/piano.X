#!/usr/bin/env bash

# verbose
#set -x
# errexit, errtrace
set -eE

# check argument
if [ $# != 1 ]; then
	echo "usage: $0 <c_source_file>"
	echo "example: $0 src/lcd.c"
	exit 1
fi

if [ ! -f "$1" ]; then
	echo "$0: can't find file \`$1'."
	exit 2
fi

# setup environments
mplab_path_file="$(dirname "$0")"/.mplab_makepath
if [ ! -f "$mplab_path_file" ]; then
	echo "$0: can't find \`$mplab_path_file' to load MPLAB location!"
	exit 3
fi
mplab_path="$(cat "$mplab_path_file")"

export PATH="$mplab_path":"$PATH"
export MAKE=make

# setup ERR and INT handlers
clear_bak() { [ -f "$1.bak" ] && mv "$1.bak" "$1"; }
trap 'clear_bak "$1"' ERR
trap 'clear_bak "$1"' SIGINT

# create bench report directory
report_dir="build/bench"
if [ -f "$report_dir" ]; then
	echo "$0: can't create \`$report_dir', file exists."
	exit 4
fi
mkdir -p "$report_dir"
report_file="$report_dir/$(basename "$1")-report.txt"


# start bench
echo -e "\e[36mbenching \`$1' ...\e[0m"

# bench: normal
# git stash
make clean > /dev/null
echo "build: normal" | tee "$report_file"
make build | grep -E --color=auto 'Program space|Data space' | tee -a "$report_file"

# bench: no function duplication
make clean > /dev/null
echo "build: force no function duplication" | tee -a "$report_file"
cp "$1" "$1.bak"
sed -i -E '/^(\S+\s+)+\S+\s*\(.*\)\s*\{\s*$/i #pragma interrupt_level 1' "$1"
make build | grep -E --color=auto 'Program space|Data space' | tee -a "$report_file"

# finish bench
clear_bak "$1"
echo -e "\e[32mbench result for \`$1' in $report_dir.\e[0m\n"
