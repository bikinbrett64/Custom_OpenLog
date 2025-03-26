#ifndef CUSTOM_OPENLOG_CPP
#define CUSTOM_OPENLOG_CPP

#include <Arduino.h>
#include <Wire.h>
#include "Custom_OpenLog.h"

Custom_OpenLog::Custom_OpenLog(uint8_t addr) {
	_address = addr;
	memset(_writeBuffer, 0, 32);
}

bool Custom_OpenLog::begin() {
	Wire.beginTransmission(_address);
	Wire.write(INIT_REG);
	if (Wire.endTransmission() != 0) {
		return false;
	}
	return true;
}

void Custom_OpenLog::getStatus(char* status) {
	//Wire.requestFrom(_address, 1);
	//&status = Wire.read();
	
	(void)readRegister(STATUS_REG, status, 1);
}

void Custom_OpenLog::createFile(char* filename) {
	writeRegister(NEW_FILE_REG, filename);
}

void Custom_OpenLog::changeDirectory(char* dir) {
	writeRegister(CHANGE_DIRECTORY_REG, dir);
}

char* Custom_OpenLog::readFile(char* filename, char* dest, unsigned long num) {
	return readRegister(READ_FILE_REG, filename, dest, num);
}

void Custom_OpenLog::openFile(char* filename) {
	writeRegister(OPEN_FILE_REG, filename);
}

void Custom_OpenLog::writeFile(char* str) {
	writeRegister(WRITE_FILE_REG, str);
}


unsigned long Custom_OpenLog::fileSize(char* filename) {
	unsigned long result = 0;
	char output[4];
	memset(output, 0, 4);
	(void)readRegister(FILE_SIZE_REG, filename, output, 4);
	for (int i = 3; i >= 0; i--) {
		result = result | (output[i] << ((3 - i) * 8));  // Translating four consecutive bytes into a long.
	}
	return result;
}


char* Custom_OpenLog::list(char* search, char* dest) {
	return readRegister(LIST_REG, search, dest, 10000);
}


void Custom_OpenLog::remove(char* filename) {
	writeRegister(REMOVE_FILE_REG, filename);
}

void Custom_OpenLog::removeDirectory(char* dir) {
	writeRegister(REMOVE_DIRECTORY_REG, dir);
}

bool Custom_OpenLog::exists(char* filename) {
	char output[12];
	memset(output, 0, 12);
	(void)readRegister(LIST_REG, filename, output, 12);
	return output[0] > 0;
}

char* Custom_OpenLog::readRegister(uint8_t reg, char* dataOut, unsigned long num) {
	Wire.beginTransmission(_address);
	Wire.write(reg);  // I'm guessing this is how the register is accessed.
	Wire.endTransmission();
	
	unsigned long i = 0;
	Wire.requestFrom(_address, num);
	while (Wire.available() && i < num) {
		dataOut[i++] = Wire.read();
	}
	
	return dataOut;
}

char* Custom_OpenLog::readRegister(uint8_t reg, char* dataIn, char* dataOut, unsigned long num) {
	writeRegister(reg, dataIn);
	
	delay(15);
	
	unsigned long i = 0;
	Wire.requestFrom(_address, num);
	while (Wire.available() && i < num) {
		dataOut[i++] = Wire.read();
	}
	return dataOut;
}

void Custom_OpenLog::writeRegister(uint8_t reg, char* dataIn) {
	unsigned long i = 0;
	Wire.beginTransmission(_address);
	Wire.write(reg);  // I'm guessing this is how the register is accessed.
	while (dataIn[i] != '\0') {
		Wire.write(dataIn[i++]);
	}
	Wire.endTransmission();
}

#endif
