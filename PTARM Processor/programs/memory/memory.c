#include <ptarm_hw_thread.h>
#include <ptarm_io.h>

// Variable whose address is at the end of the program binary.
// Defined in the linker script.
extern unsigned int addr_stack_limit;

// Variable whose address is at the end of the PTARM hardware threads' stacks.
// Defined in the linker script.
extern unsigned int addr_stack_end;

int main() {
	// Only hardware thread 0 is allowed to execute this test.
	unsigned int hwThreadId;
	PTARM_THREAD_GET_ID(hwThreadId);
	if (hwThreadId != 0) {
		return 0;
	}

	printf("Memory test\n");
	printf("-----------\n");
	printf("Memory range: 0x");
	printf(hex((unsigned int)&addr_stack_limit));
	printf(" to 0x");
	printf(hex((unsigned int)&addr_stack_end));
	printf(" (");
	printf(utoa(1 + ((unsigned int)&addr_stack_end - (unsigned int)&addr_stack_limit)/sizeof(unsigned int)));
	printf(" ");
	printf(utoa(sizeof(unsigned int)));
	printf(" byte memory locations).\n");

	printf("* Writing phase ... ");
	unsigned int counter = 0;
	unsigned int *address;
	for (address = &addr_stack_limit; address <= &addr_stack_end; address++) {
		*address = counter;
		counter++;
	}
	printf(utoa(counter));
	printf(" ");
	printf(utoa(sizeof(unsigned int)));
	printf(" byte memory locations.\n");

	printf("* Reading phase ... ");
	counter = 0;
	for (address = &addr_stack_limit; address <= &addr_stack_end; address++) {
		unsigned int value = *address;

		if (value != counter) {
			printf("  address = ");
			printf(hex((unsigned int)address));

			printf(", value = ");
			printf(utoa(value));

			printf(", counter = ");
			printf(utoa(counter));

			printf(".\n");
		}

		counter++;
	}
	printf(utoa(counter));
	printf(" ");
	printf(utoa(sizeof(unsigned int)));
	printf(" byte memory locations.\n");

	printf("Completed. ");

	return 0;
}

