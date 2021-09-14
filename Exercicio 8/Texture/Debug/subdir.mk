################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Texture.c \
../glad.c \
../mytools2.c \
../stb_image.c 

OBJS += \
./Texture.o \
./glad.o \
./mytools2.o \
./stb_image.o 

C_DEPS += \
./Texture.d \
./glad.d \
./mytools2.d \
./stb_image.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -ID:/API_Packages/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


