#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstring>


template <class T> class CircularBuffer {
private:
	T* readPointer;
	T* writePointer;
	T* buffer;
	int size;
	int writePosition;
	int readPosition;
	bool firstWrite = true;
public:
	CircularBuffer(int size) {
		this->size = size;
		this->writePosition = 0;
		this->readPosition = 0;
		this->buffer = new T[size]();
		this->readPointer = buffer;
		this->writePointer = buffer;
	}
	~CircularBuffer() {
		delete[] buffer;
		buffer = nullptr;
		readPointer = nullptr;
		writePointer = nullptr;
	}

	void addFrames(T* buffer, int numOfFrames) {
		if (firstWrite) {
			memcpy(this->writePointer, buffer, sizeof(T)*numOfFrames);
			writePosition = (writePosition + numOfFrames) % size;
			this->writePointer = (this->writePointer + numOfFrames) % size;
			firstWrite = false;
		}
		else {
			if (size - writePosition >= numOfFrames) {
				memcpy(this->writePointer, buffer, sizeof(T)*numOfFrames);
				writePosition = (writePosition + numOfFrames) % size;
				this->writePointer = (this->writePointer + numOfFrames) % size;
				this->readPosition = (readPosition + numOfFrames) % size;
				this->readPointer = (this->readPointer + numOfFrames) % size;
			}
			else {
				amount = size - writePosition;
				remain = numOfFrames - amount;
				memcpy(this->writePointer, buffer, sizeof(T)*amount);
				this->writePointer = (this->writePointer + amount) % size;
				memcpy(this->writePointer, buffer, sizeof(T)*remain);
				this->writePosition = (writePosition + numOfFrames) % size;
				this->writePointer = (this->writePointer + remain) % size;
				this->readPosition = (readPosition + numOfFrames) % size;
				this->readPointer = (this->readPointer + numOfFrames) % size;

			}
		}
	}
	void getFramesWithDelay(T* buffer, int delay, int numOfFrames) {
		if (delay >= numOfFrames && delay =< size) {
			if (readPosition - delay > 0) {
				memcpy(buffer, (this->readPointer - delay), sizeof(T)*numOfFrames);
				readPosition = (readPosition + numOfFrames) % size;
				this->readPointer = (this->readPointer + numOfFrames) % size;

			}
			else {
				start = size + (readPosition - delay);
				T* delayPointer = readPointer + (start - readPosition);
				amount = size - start;
				remain = numOfFrames - amount;
				memcpy(buffer, delayPointer, sizeof(T)*amount);
				delayPointer = readPointer - remain;
				memcpy((buffer+amount), delayPointer, sizeof(T)*remain);
			}
		}
	}

};