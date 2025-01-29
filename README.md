# How to use it ?
- Clone the repository:
```shell
git clone https://github.com/danieljs-dev/minitalk.git
```
```shell
cd minitalk
```
```bash
make
```
```shell
./server
```
- Open other terminal and run:
```bash
chmod +x get_server_pid.sh
```
```shell
source ./get_server_pid.sh  && ./client $SERVER_PID "Hello world"
```
- If you want to run with valgrind, run the following command
```shell
valgrind --leak-check=full --show-leak-kinds=all ./server

# and in other terminal run
source ./get_server_pid.sh && valgrind --leak-check=full --show-leak-kinds=all ./client $SERVER_PID "Hello world"
```
