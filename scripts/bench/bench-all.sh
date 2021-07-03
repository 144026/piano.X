#!/usr/bin/env bash

# verbose
#set -x
# errexit, errtrace
set -eE

if [ $# != 1 ]; then
	echo "usage: $0 <c_source_dir>"
	echo "example: $0 src/"
	exit 1
fi

if [ ! -d "$1" ]; then
	echo "$0: can't find directory \`$1'."
	exit 2
fi

find "$1" -regex '.*\.c' | while read -r f; do
	"$(dirname "$0")"/bench.sh "$f"
done
