################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM-ESP/Src/espuartproto.c 

OBJS += \
./Drivers/STM-ESP/Src/espuartproto.o 

C_DEPS += \
./Drivers/STM-ESP/Src/espuartproto.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM-ESP/Src/%.o Drivers/STM-ESP/Src/%.su Drivers/STM-ESP/Src/%.cyclo: ../Drivers/STM-ESP/Src/%.c Drivers/STM-ESP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ututo/STM32CubeIDE/workspace_2.0.0/INA219_DC_Sensor/Drivers/ICM20948/Include" -I"/home/ututo/STM32CubeIDE/workspace_2.0.0/INA219_DC_Sensor/Drivers/INA219/Include" -I"/home/ututo/STM32CubeIDE/workspace_2.0.0/INA219_DC_Sensor/Drivers/STM-ESP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM-2d-ESP-2f-Src

clean-Drivers-2f-STM-2d-ESP-2f-Src:
	-$(RM) ./Drivers/STM-ESP/Src/espuartproto.cyclo ./Drivers/STM-ESP/Src/espuartproto.d ./Drivers/STM-ESP/Src/espuartproto.o ./Drivers/STM-ESP/Src/espuartproto.su

.PHONY: clean-Drivers-2f-STM-2d-ESP-2f-Src

