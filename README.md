# pressure_logger
Pressure sensor data logger [STM32F103 Nucleo]



1) Debug

openocd -f ${HOME}/openocd-code/tcl/board/st_nucleo_f103rb.cfg

gdb-multiarch -tui --eval-command="target extended-remote localhost:3333" build/target.elf
[set architecture arm] if necessary
[flash-erase -> relaunch openocd] if necessary
load build/target.elf
run

----------

picocom -b 115200 /dev/ttyUSB0
[WARNING : apparently, 230400 in UART_MODE_TX_RX -> 115200 each ! big up to the scope who saved my life...]

