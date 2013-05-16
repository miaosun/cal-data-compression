################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ArvoreBinaria.cpp \
../src/CodeHuffman.cpp \
../src/CodecLZW.cpp \
../src/main.cpp 

OBJS += \
./src/ArvoreBinaria.o \
./src/CodeHuffman.o \
./src/CodecLZW.o \
./src/main.o 

CPP_DEPS += \
./src/ArvoreBinaria.d \
./src/CodeHuffman.d \
./src/CodecLZW.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


