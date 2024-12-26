#!/bin/bash
set -e

run_cmd() {
	test -c "$1" || (echo "$1" not found.; return 1)
	printf "%s\r" "$2" | tee "$1" &
	timeout 20s head -n "$3" "$1"
}

TTY="$1"
FILE="$2"

test "$#" -eq 2 || (echo "$0 {TTY} {FILE}"; exit 1)

stty -F "$TTY" 115200 crtscts -hup -raw
run_cmd "$TTY" "ATM2" "3" > /dev/null
run_cmd "$TTY" "ATD" "4" | tail -n1 | grep -av "CONNECT" && (echo Dial failed.; exit 1)
echo "Connected!"
sleep 10
echo "Sending file..."
cat "$FILE" > "$TTY"
echo "Sent file! Exiting..."
