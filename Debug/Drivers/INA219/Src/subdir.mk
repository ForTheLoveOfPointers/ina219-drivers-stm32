################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/INA219/Src/ina219.c 

OBJS += \
./Drivers/INA219/Src/ina219.o 

C_DEPS += \
./Drivers/INA219/Src/ina219.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/INA219/Src/%.o Drivers/INA219/Src/%.su Drivers/INA219/Src/%.cyclo: ../Drivers/INA219/Src/%.c Drivers/INA219/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ututo/STM32CubeIDE/workspace_2.0.0/INA219_DC_Sensor/Drivers/ICM20948/Include" -I"/home/ututo/STM32CubeIDE/workspace_2.0.0/INA219_DC_Sensor/Drivers/INA219/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-INA219-2f-Src

clean-Drivers-2f-INA219-2f-Src:
	-$(RM) ./Drivers/INA219/Src/ina219.cyclo ./Drivers/INA219/Src/ina219.d ./Drivers/INA219/Src/ina219.o ./Drivers/INA219/Src/ina219.su

.PHONY: clean-Drivers-2f-INA219-2f-Src

