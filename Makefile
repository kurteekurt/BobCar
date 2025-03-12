# Project settings
PROJECT_NAME := bobcar
BUILD_DIR := bin
INC_DIR := inc

# Toolchain settings
CC := arm-linux-gnueabihf-gcc
CXX := arm-linux-gnueabihf-g++

# Module directories
MODULES := drivers waveshare sensors core

MAIN_FILE := src/main.c  # Adjust the file name if necessary

CFILES := $(foreach module, $(MODULES), $(wildcard src/$(module)/*.c)) $(MAIN_FILE)
CPPFILES := $(foreach module, $(MODULES), $(wildcard src/$(module)/*.cpp))

# Include directories
HF_INC_DIR := -I/usr/include/ # Temporary for dev
OPENCV_INC_DIR := -I/usr/include/opencv4
INCLUDES := -I$(INC_DIR) $(addprefix -I$(INC_DIR)/, $(MODULES)) $(OPENCV_INC_DIR)

# Library directories
HF_LIB_DIR := -L/usr/lib/arm-linux-gnueabihf

# Compiler and linker flags (also temporary for dev)
CFLAGS := $(INCLUDES) $(HF_INC_DIR) -Wall -Wextra
CXXFLAGS := $(INCLUDES) -Wall -Wextra

# Libraries
OPENCV_LIBS := -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
WIRINGPI_LIBS := -lwiringPi
LDFLAGS := $(HF_LIB_DIR) $(OPENCV_LIBS) $(WIRINGPI_LIBS) -lstdc++ 

# Include additional makefiles
include rules.mk
include ws.mk