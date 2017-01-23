#include <ptarm_types.h>
#include <ptarm_hw_thread.h>
#include <ptarm_io.h>
#include <ptarm_foremc.h>

Task one = {.receiveBuffers = { NULL }};


int main() {
	// Only hardware thread 0 is allowed to execute this test.
	unsigned int hwThreadId;
	PTARM_THREAD_GET_ID(hwThreadId);
	if (hwThreadId != 0) {
		return 0;
	}
	
	printf("ForeMC buffer test\n");
	
	// Define and declare the buffer.
	FORECMC_BUFFER(int, 4, buffer);
		
	// Read the last buffered data for the receiver.
	printf(utoa(FOREMC_BUFFER_READ_COUNT(buffer))); printf(":"); printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, FOREMC_BUFFER_READ_COUNT(buffer)))); printf("\n");

	// Write data into the buffer
	FOREMC_BUFFER_SEND(buffer, 10);
	FOREMC_BUFFER_SEND(buffer, 20);

	// Read the last buffered data for the receiver.
	printf(utoa(FOREMC_BUFFER_READ_COUNT(buffer))); printf(":"); printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, FOREMC_BUFFER_READ_COUNT(buffer)))); printf("\n");

	// Swap the buffers.
	FOREMC_BUFFER_RELEASE(&buffer);

	// Read the last (latest) buffered data for the receiver.
	printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, FOREMC_BUFFER_BOUND(-1, buffer)))); printf("\n");
	
	int i;
	for (i = 0; i < FOREMC_BUFFER_READ_COUNT(buffer); i++) {
		printf(utoa(FOREMC_BUFFER_READ_COUNT(buffer))); printf(":"); printf(utoa(FOREMC_BUFFER_AT_INDEX(buffer, i))); printf("\n");
	}

	return 0;
}

