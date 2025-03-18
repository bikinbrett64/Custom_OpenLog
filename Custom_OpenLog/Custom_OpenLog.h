/*
	Custom_OpenLog.h
	
	For interfacing with the SparkFun Qwiic OpenLog microSD card reader.
	
	Created specifically for my Zenith rocket.
	
	Author: Brett Warren
*/

#include <Arduino.h>
#include <Wire.h>

class Custom_OpenLog {
	private:
		uint8_t _address;
		uint8_t _writeBuffer[32];
		char* readRegister(uint8_t reg, char* data, unsigned long num);
		char* readRegister(uint8_t reg, char* dataIn, char* dataOut, unsigned long num);
		void writeRegister(uint8_t reg, char* data);
		
	public:
		Custom_OpenLog(uint8_t addr = 0x2A);
		bool begin();
		
		void getStatus(uint8_t* status);
		
		void createFile(char* filename);
		void makeDirectory(char* name);
		void changeDirectory(char* dir);
		char* readFile(char* filename, char* dest, long num);
		
		void appendFile(char c);
		void appendFile(char* str);
		
		void writeFile(char c);
		void writeFile(char* str);
		
		unsigned long fileSize(char* filename);
		
		char* list(char* search, char* dest);
		
		void remove(char* filename);
		void removeDirectory(char* dir);
};