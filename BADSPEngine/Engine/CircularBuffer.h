#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "fftw3.h"


template <class T> class CircularBuffer {
private:
	T* writePointer;
	T* buffer;
	int size;
	int writePosition;
public:
	CircularBuffer(int size) {
		this->size = size;
		this->writePosition = 0;
		this->buffer = new T[size];
		memset(buffer, 0, sizeof(T)*size);
		this->writePointer = buffer;
	}
	~CircularBuffer() {
		delete[] buffer;
		buffer = nullptr;
		writePointer = nullptr;
	}

	void addFrames(T* buffer, int numOfFrames) {
			if (size - writePosition >= numOfFrames) {
				memcpy(this->writePointer, buffer, sizeof(T)*numOfFrames);
				writePosition = (writePosition + numOfFrames) % size;
				this->writePointer = (this->buffer + this->writePosition);
			}
			else {
				int amount = size - writePosition;
				int remain = numOfFrames - amount;
				memcpy(this->writePointer, buffer, sizeof(T)*amount);
				this->writePointer = (this->buffer);
				memcpy(this->writePointer, buffer, sizeof(T)*remain);
				this->writePosition = (writePosition + numOfFrames) % size;
				this->writePointer = (this->buffer + this->writePosition);

		}
	}
	void getFramesWithDelay(T* buffer, int delay, int numOfFrames) {
		if (delay <= size && delay > 0 && numOfFrames <= delay) {
			if (writePosition - delay >= 0) {
				memcpy(buffer, (this->writePointer - delay), sizeof(T)*numOfFrames);
			}
			else {
				int amount = 0;
				int remain = 0;
				int start = size + (writePosition - delay);
				T* delayPointer = this->buffer + start;
				if (numOfFrames <= size - start) {
					amount = numOfFrames;
				}
				else {
					amount = numOfFrames - (size - start);
					remain = numOfFrames - amount;
				}
				memcpy(buffer, delayPointer, sizeof(T)*amount);
				delayPointer = this->buffer;
				if (remain > 0) {
					memcpy((buffer + amount), delayPointer, sizeof(T)*remain);
				}
				
			}
		}
	}

};

