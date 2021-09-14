################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSpline_Animated.c \
../glad.c \
../mytools2.c 

OBJS += \
./BSpline_Animated.o \
./glad.o \
./mytools2.o 

C_DEPS += \
./BSpline_Animated.d \
./glad.d \
./mytools2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -ID:/API_Packages/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


