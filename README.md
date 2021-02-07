# pressure_logger
Pressure sensor data logger [STM32F103 Nucleo]



1) Debug

openocd -f ${HOME}/openocd-code/tcl/board/st_nucleo_f103rb.cfg

gdb-multiarch -tui --eval-command="target extended-remote localhost:3333" target.elf
[set architecture arm] if necessary
[flash-erase -> relaunch openocd] if necessary
[load target.elf] if necessary
[run] if necessary
