/*
	Custom_OpenLog.h
	
	For interfacing with the SparkFun Qwiic OpenLog microSD card reader.
	
	Created specifically for my Zenith rocket.
	
	Note that this library is intended for use with the address pads shorted
	together so that the I2C address is always 0x29.
	
	Note also that the code does not yet respect the Wire library's 32-byte
	write buffer.
	
	Author: Brett Warren
*/

#ifndef CUSTOM_OPENLOG_H
#define CUSTOM_OPENLOG_H

#include <Arduino.h>
#include <Wire.h>

#define STATUS_REG 0x01
#define INIT_REG 0x05
#define NEW_FILE_REG 0x06
#define NEW_DIRECTORY_REG 0x07
#define CHANGE_DIRECTORY_REG 0x08
#define READ_FILE_REG 0x09
#define OPEN_FILE_REG 0x0B
#define WRITE_FILE_REG 0x0C
#define FILE_SIZE_REG 0x0D
#define LIST_REG 0x0E
#define REMOVE_FILE_REG 0x0F
#define REMOVE_DIRECTORY_REG 0x10

class Custom_OpenLog {
	private:
		uint8_t _address;
		char _writeBuffer[32];
		char* readRegister(uint8_t reg, char* dataOut, unsigned long num);
		char* readRegister(uint8_t reg, char* dataIn, char* dataOut, unsigned long num);
		void writeRegister(uint8_t reg, char* dataIn);
		
	public:
		Custom_OpenLog(uint8_t addr = 0x29);
		bool begin();
		
		void getStatus(char* status);
		
		void createFile(char* filename);
		void makeDirectory(char* name);
		void changeDirectory(char* dir);
		char* readFile(char* filename, char* dest, unsigned long num);
		
		void openFile(char* filename);
		
		void writeFile(char* str);
		
		unsigned long fileSize(char* filename);
		
		char* list(char* search, char* dest);
		
		void remove(char* filename);
		void removeDirectory(char* dir);
		
		bool exists(char* filename);
};

#endif