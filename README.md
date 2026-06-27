#### Linux의 SocketCAN 인터페이스(can0)를 설정
```sh
sudo ip link set can0 up type can bitrate 500000
sudo ip link set can0 txqueuelen 1000
ip link show can0 
```
