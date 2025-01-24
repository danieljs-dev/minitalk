#!/bin/bash

PROCESS_NAME="./server"

PID=$(ps aux | grep "$PROCESS_NAME" | grep -v grep | awk '{print $2}')

if [ -z "$PID" ]; then
    echo "Processo '$PROCESS_NAME' não encontrado."
    exit 1
else
    echo "export SERVER_PID=$PID" > /tmp/set_server_pid.sh
    source /tmp/set_server_pid.sh
    echo "PID do processo '$PROCESS_NAME' salvo na variável de ambiente SERVER_PID: $SERVER_PID"
fi
