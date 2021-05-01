#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

/* Monotonic system-wide clock.  */
#undef CLOCK_MONOTONIC
clockid_t CLOCK_MONOTONIC = 1;

char radioInput;
char spiInput;
double servoOutputs[4];

int terminate = 0;
int isSafe = 1;
double decision = 0.0;
int _1Hz = 0;
int _20Hz = 0;

const int MAX_DOWN_TIME = 100;

const char INVALID = '0';
const char VALID = '1';
const int MANUAL = 0;
const int AUTOMATIC = 1;

FILE* inputFile;
FILE* outputFile;

long long radioDownTime;
long long spiDownTime;

int getMode(const int communicationInput);
double autopilot(const int mode, const int communicationInput);
void computation(void);

void flight(void);
void servo(void);
void servo0(void);
void servo1(void);
void servo2(void);
void servo3(void);
void timer(void);
void failsafe(void);

int main(int argc, char* argv[]) {
	struct timespec ts_start;
	struct timespec ts_end;
	//- - - -

	int NUM_TO_AVERAGE;
	printf("Number of iterations to average: ");
	scanf("%d", &NUM_TO_AVERAGE);

	int procNumber = omp_get_max_threads();
	printf("Number of threads: %d\n ", procNumber);
	omp_set_num_threads(procNumber); 
	
	float summation = 0;
	int i;
	for(i = 0; i < NUM_TO_AVERAGE; i++) {

		clock_gettime(CLOCK_MONOTONIC, &ts_start);

		inputFile = fopen("input.dat", "r");
		outputFile = fopen("output.txt", "w");

		terminate = 0;
		isSafe = 1;
		
		servoOutputs[0] = 0.0;
		servoOutputs[1] = 0.0;
		servoOutputs[2] = 0.0;
		servoOutputs[3] = 0.0;

		radioDownTime = 0;
		spiDownTime = 0;
	
		while (!terminate) {
		
			if (isSafe) {
				timer();
				flight();
				servo();
				failsafe();
			} else {
				timer();
				flight();
				servo();
				failsafe();
			}
			 
		}

		clock_gettime(CLOCK_MONOTONIC, &ts_end);

		fclose(inputFile);
		fclose(outputFile);

		long seconds = ts_end.tv_sec - ts_start.tv_sec;
		int nanoseconds = ts_end.tv_nsec - ts_start.tv_nsec;
		if(nanoseconds < 0) {
			nanoseconds += 1000000000;
			seconds--;
		}

		float microseconds = (float)nanoseconds/1000000000;
		float runtime = (float)seconds + microseconds;

		summation += runtime;

		printf("Runtime = %f \n", runtime);
		printf("------######--------\n");
	
	}
	
	float average = summation/NUM_TO_AVERAGE;
	printf("\nAverage runtime = %f\n\n", average);
	
	return 0;
}

void flight(void) {
	int mode;
	if (getMode(radioInput) != VALID) {
		mode = getMode(radioInput);
	}
	
	decision = autopilot(mode, radioInput);
}

void servo(void) {
	servo0();
	servo1();
	servo2();
	servo3();
	
	computation();
}

void servo0(void) {
	computation();
	computation();
	computation();
	servoOutputs[0] = 0;
}

void servo1(void) {
	computation();
	computation();
	computation();
	servoOutputs[1] = 1;
}

void servo2(void) {
	computation();
	computation();
	computation();
	servoOutputs[2] = 2;
}

void servo3(void) {
	computation();
	computation();
	computation();
	servoOutputs[3] = 3;
}

void timer(void) {
	if (_1Hz++ > 60) {
		computation();
		_1Hz = 0;
	}

	if (_20Hz++ > 3) {
		computation();
		_20Hz = 0;
	}

	radioInput = fgetc(inputFile);
	spiInput = fgetc(inputFile);
	
	char newLine = fgetc(inputFile);
	while (newLine == '\n' || newLine == '\r') {
		newLine = fgetc(inputFile);
	}
	ungetc(newLine, inputFile);
	
	if (radioInput == EOF || spiInput == EOF) {
		terminate = 1;
	}
}

void failsafe(void) {
	computation();
	computation();
	computation();
	computation();
	
	if (radioInput == INVALID) {
		radioDownTime++;
	} else {
		radioDownTime = 0;
	}
	
	computation();
	computation();
	computation();
	computation();
	if (spiInput == INVALID) {
		spiDownTime++;
	} else {
		spiDownTime = 0;
	}
	
	isSafe = (radioDownTime < MAX_DOWN_TIME) || (spiDownTime < MAX_DOWN_TIME);
	fprintf(outputFile, "%d\n", isSafe);
}

int getMode(const int communicationInput) {
	const int mask = (communicationInput & 0x02) > 1;
//	computation();
//	computation();	
	
	switch (mask) {
		case (0):	return MANUAL;
		
		case (1):	return AUTOMATIC;
		
		default:
					break;
	}
	
	return AUTOMATIC;
}

double autopilot(const int mode, const int communicationInput) {
	computation();
	computation();
	computation();
	computation();
	computation();
	computation();
	computation();
	computation();

	return (double)(communicationInput * mode);
}

void computation(void) {
	double result = 1.0;
	
	int i;
	#pragma omp parallel for reduction(+:result)
	for (i = 1; i < 2000; i++) {
		result += (double)((int)result % i) * (result / result);
	}
}

