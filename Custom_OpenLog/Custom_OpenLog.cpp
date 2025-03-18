#include <Arduino.h>
#include <Wire.h>
#include "Custom_OpenLog.h"

Custom_OpenLog::Custom_OpenLog(uint8_t addr) {
	_address = addr;
	memset(_writeBuffer, 0, 32);
}

bool Custom_OpenLog::begin() {
	Wire.beginTransmission(_address);
	Wire.write(0x05);
	if (Wire.endTransmission() != 0) {
		return false;
	}
	return true;
}

void Custom_OpenLog::getStatus(uint8_t* status) {
	Wire.requestFrom(_address, 1);
	&status = Wire.read();
}

void Custom_OpenLog::createFile(char* filename) {
	
}

void Custom_OpenLog::changeDirectory(char* dir) {
	
}

char* Custom_OpenLog::readFile(char* filename, char* dest, long num) {
	return dest;
}

void Custom_OpenLog::appendFile(char c) {
	
}

void Custom_OpenLog::appendFile(char* str) {
	
}

void Custom_OpenLog::writeFile(char c) {
	
}

void Custom_OpenLog::writeFile(char* str) {
	
}


unsigned long Custom_OpenLog::fileSize(char* filename) {
	
}


char* Custom_OpenLog::list(char* search, char* dest) {
	return dest;
}


void Custom_OpenLog::remove(char* filename) {
	
}

void Custom_OpenLog::removeDirectory(char* dir) {
	
}

char* Custom_OpenLog::readRegister(uint8_t reg, char* data, unsigned long num) {
	Wire.beginTransmission(_address);
	Wire.write(reg);  // I'm guessing this is how the register is accessed.
	Wire.endTransmission();
	
	unsigned long i = 0;
	Wire.requestFrom(_address, num);
	while (Wire.available() && i < num) {
		data[i++] = Wire.read();
	}
	
	return data;
}

char* Custom_OpenLog::readRegister(uint8_t reg, char* dataIn, char* dataOut, unsigned long num) {
	writeRegister(reg, dataIn);
	
	i = 0;
	Wire.requestFrom(_address, num);
	while (Wire.available() && i < num) {
		data[i++] = Wire.read();
	}
	return dataOut;
}

void Custom_OpenLog::writeRegister(uint8_t reg, char* data) {
	unsigned long i = 0;
	Wire.beginTransmission(_address);
	Wire.write(reg);  // I'm guessing this is how the register is accessed.
	while (data[i] != '\0') {
		Wire.write(data[i++]);
	}
	Wire.endTransmission();
}
