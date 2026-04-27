################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ICM20948/Src/icm20948.c 

OBJS += \
./Drivers/ICM20948/Src/icm20948.o 

C_DEPS += \
./Drivers/ICM20948/Src/icm20948.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ICM20948/Src/%.o Drivers/ICM20948/Src/%.su Drivers/ICM20948/Src/%.cyclo: ../Drivers/ICM20948/Src/%.c Drivers/ICM20948/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ututo/STM32CubeIDE/workspace_2.0.0/INA219_DC_Sensor/Drivers/ICM20948/Include" -I"/home/ututo/STM32CubeIDE/workspace_2.0.0/INA219_DC_Sensor/Drivers/INA219/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ICM20948-2f-Src

clean-Drivers-2f-ICM20948-2f-Src:
	-$(RM) ./Drivers/ICM20948/Src/icm20948.cyclo ./Drivers/ICM20948/Src/icm20948.d ./Drivers/ICM20948/Src/icm20948.o ./Drivers/ICM20948/Src/icm20948.su

.PHONY: clean-Drivers-2f-ICM20948-2f-Src

