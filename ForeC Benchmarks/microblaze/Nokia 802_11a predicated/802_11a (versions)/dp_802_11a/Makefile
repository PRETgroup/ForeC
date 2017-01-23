INST_DIR = ../../../install
#INST_DIR = /home/local/install/
INSTALL_DIR=${INST_DIR}
LIB_DIR=${INSTALL_DIR}/lib64
INCLUDE_DIR=${INSTALL_DIR}/include

CC = ${INSTALL_DIR}/bin/gcc
OBJECTS = freq_sync_correl_2STS.o frequency_sync_slidsum.o arctan.o cordic_turn.o fine_time_sync.o bf2_fifo_stage0.o bf2_fifo_stage1.o bf2_fifo_stage2.o bf2_fifo_stage3.o bf2_fifo_stage4.o bf2_fifo_stage5.o twiddle_mult43.o twiddle_mult21.o bf2i.o bf2ii.o mstream_demux.o fft64.o mark_GI_data.o scale_reorder_removeGB.o CHE.o CHC.o sync_fft_che_top_tb.o
COMPOPTIONS = -Wall -std=c99 -O3 -ffast-math -msse2 -msse -msse3 -Wl,-rpath,$(INST_DIR)/lib64 -g -L${LIB_DIR} -fopenmp -lm -rdynamic -Wl,-rpath,$(LIB_DIR) -pedantic -I${INCLUDE_DIR} -fdump-tree-ompexp-all

%.o : %.c
	${CC} -c ${COMPOPTIONS} ${LIBS} $< 

main: ${OBJECTS}
	${CC} ${OBJECTS} ${COMPOPTIONS} -Wl,-lm -o $@ 

run:	main
	main

depend:
	depend --makefile ${OBJECTS}

clean:
	rm -Rf *.o main *.log main main.exe *~ Makefile.old acotrace* main.prv main.1.* main.bin main.txt plainC_SimOutput/*  *.c.*

freq_sync_correl_2STS.o: freq_sync_correl_2STS.c
frequency_sync_slidsum.o: frequency_sync_slidsum.c
arctan.o: arctan.c
cordic_turn.o: cordic_turn.c
fine_time_sync.o: fine_time_sync.c
bf2_fifo_stage0.o: bf2_fifo_stage0.c
bf2_fifo_stage10.o: bf2_fifo_stage10.c
bf2_fifo_stage1.o: bf2_fifo_stage1.c
bf2_fifo_stage2.o: bf2_fifo_stage2.c
bf2_fifo_stage3.o: bf2_fifo_stage3.c
bf2_fifo_stage4.o: bf2_fifo_stage4.c
bf2_fifo_stage5.o: bf2_fifo_stage5.c
bf2i.o: bf2i.c
bf2ii.o: bf2ii.c
twiddle_mult21.o: twiddle_mult21.c
twiddle_mult43.o: twiddle_mult43.c
mstream_demux.o: mstream_demux.c
fft64.o: fft64.c
mark_GI_data.o: mark_GI_data.c
scale_reorder_removeGB.o: scale_reorder_removeGB.c
CHE.o: CHE.c
CHC.o: CHC.c
sync_fft_che_top_tb.o: sync_fft_che_top_tb.c
	$(CC) -c  ${COMPOPTIONS} $< -o $@ 

