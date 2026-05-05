# INA219 & ICM20948 Sensor Drivers
This repository contains drivers for INA219 and ICM20948, alongside the code for the UART communication protocol used to connect STM32 to ESP32.

## STM32
The STM32 includes the drivers for the sensors + the protocol code.

## ESP32
The ESP32 code included in ESP32_Code in the root directory is in charge of receiving data packets from the STM32 (the sensor data) and transmitting it via wi-fi to a remote DB.

## Communication Protocol Specification
Protocol is made to communicate via UART between both an STM32 and an ESP32 MCUs.                                                   
The implementation is pretty simple. The STM32 should only send sensor data (e.g. voltage readings, gyroscope data),                
this sensor data will be send by the ESP32 via wi-fi to a remote DB.                                                                
               																													   
The FRAME FORMAT is the following:																						           
																																   
START BYTE | TYPE | LEN | PAYLOAD | CHECKSUM | END BYTE 	 ------ This is transmit                                                   
START BYTE | TYPE=ACK | LEN=0 | CHECKSUM | END BYTE   ------ This is ACK												               
																																   
Where:																															   
																																   
START BYTE = 0xAA																												   
END BYTE = 0x55																													   
																																   
and TYPE could have the following 3 values:																						   
																																   
TYPE = 0x01  -> Is gyroscope data from the ICM20948																		           
TYPE = 0x02  -> Power data from the INA219. Contains bus voltage and current readings, both 2 bytes in length, in that order.       
TYPE = 0x03  -> Send gyro and power data in the same frame                                                                          |
TYPE = 0x04  -> This is the type the Tx receives when the slave gets the data. The slave should send this immediately after		  
																														           
LEN is a 1 byte field, containing the length of the payload.																	       
PAYLOAD is the sensor data, up to 256 bytes																						   
CHECKSUM has a length of 1 byte, and is computed by XORing START ^ TYPE ^ LEN ^ PAYLOAD											   
 

