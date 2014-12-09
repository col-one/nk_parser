################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/parse.cpp \
../src/parse_fn.cpp \
../src/toto.cpp \
../src/use.cpp 

OBJS += \
./src/parse.o \
./src/parse_fn.o \
./src/toto.o \
./src/use.o 

CPP_DEPS += \
./src/parse.d \
./src/parse_fn.d \
./src/toto.d \
./src/use.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


