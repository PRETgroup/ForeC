CC		= mb-gcc
CFLAGS	= -O0 -Wall -g

OBJDUMP	= mb-objdump
OFLAGS	= -dCrSt

SIM		= mb-sim
SFLAGS	= 4

MBFLAGS	= -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b
SOURCES	= main.c MatrixMultiply_data.c MatrixMultiply.c
MB_ROOT	= ${FOREC_ANALYSER_PATH}
INCLUDE	= -I"$(MB_ROOT)microblaze/include/" -I"$(MB_ROOT)microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"$(MB_ROOT)microblaze/drivers/esterel_mutex_v1_00_a/src/" -I"$(MB_ROOT)microblaze/drivers/thread_queue_v1_00_a/src/" -L"$(MB_ROOT)microblaze/lib/"
LSCRIPT	= -T ../../forec_linker_script.ld
BIN		= executable

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN) $(MBFLAGS) $(LSCRIPT) $(INCLUDE)
	$(OBJDUMP) $(OFLAGS) $(BIN) > $(BIN).dump

run:
	$(SIM) $(SFLAGS) $(BIN)

clean:
	rm -rf $(BIN) $(BIN).dump
