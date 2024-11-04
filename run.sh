#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <path_to_executable> [-dgr]"
    exit 1
fi

EXECUTABLE="$1"

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: File '$EXECUTABLE' does not exist."
    exit 1
fi
shift

CFLAGS=""
for arg in "$@"; do
    if [[ $arg == -* ]]; then
        for ((i=1; i<${#arg}; i++)); do
            case ${arg:i:1} in
                d)
                    CFLAGS+=" -DSTELLA_DEBUG "
                    ;;
                g)
                    CFLAGS+=" -DSTELLA_GC_STATS"
                    ;;
                r)
                    CFLAGS+=" -DSTELLA_RUNTIME_STATS"
                    ;;
                *)
                    echo "Unknown flag: ${arg:i:1}"
                    exit 1
                    ;;
            esac
        done
    else
        echo "Unknown argument: $arg"
        exit 1
    fi
done

export G1_SPACE_SIZE="1300"

mkdir -p ./out
gcc -std=c11 $CFLAGS $EXECUTABLE ./src/runtime.c ./src/gc.c -o ./out/run
chmod a+x ./out/run
echo "Running $EXECUTABLE with flags: $CFLAGS"
echo "" | ./out/run
