cmake_minimum_required(VERSION 3.0)

project(PressureLogger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# ---------- Build specifications ----------

set(SRC_DIR Src)
set(INC_DIR Inc)

set(SRCS
	${SRC_DIR}/main.cpp
	${SRC_DIR}/pl_process.cpp
	${SRC_DIR}/pl_error.cpp
	${SRC_DIR}/pl_uart.cpp
	${SRC_DIR}/pl_report.cpp
	${SRC_DIR}/pl_report_bin.cpp
	${SRC_DIR}/pl_report_txt.cpp
   )

add_executable(PressureLogger ${SRCS})

target_include_directories(PressureLogger PUBLIC ${INC_DIR})

