#!/bin/bash

name=$2

if [ "$1" = "--clean" ]
then
	rm -f *.dot *.txt *.pdf *.xml *.c *.dump
	rm -f forecc.*
	rm -f foreca.*
	for allocation in *.elf
	do
		rm -f $allocation
	done
	
fi

if [ "$1" = "--compile" ]
then
	> forecc.out
	
	echo "Compiling for all *.foreh files"

	for allocation in *.foreh
	do
		elfName=${allocation%*.foreh}
		
		echo "forecc $name.forec $allocation"
		forecc -d1 $name.forec $allocation >> forecc.out
		mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
		mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"
	done
	
	echo "MatrixMultiply original"
	name=MatrixMultiply
	mb-gcc -E -CC ./original/$name.c -o ./original/${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ./original/${name}_expanded.c -o $name.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

fi

if [ "$1" = "--compileTimed" ]
then
	> forecc.out
	
	echo "Compiling for all *.foreh files"

	name=MatrixMultiply
	
	count=1
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t33095 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

	count=2
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t16769 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

	count=3
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t12809 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

	count=4
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t8839 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

	count=5
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t9049 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

	count=6
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t9329 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

	count=7
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t9554 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

	count=8
	echo $name $count
	elfName=$name.$count
	forecc -d1 -t5719 $name.forec $name.$count.foreh >> forecc.out
	mb-gcc -E -CC $name.c -o ${name}_expanded.c -I"${FOREC_ANALYSER_PATH}microblaze/include/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/counter_dfsl_v1_00_a/src/" -I"${FOREC_ANALYSER_PATH}microblaze/drivers/forec_mutex_v1_00_a/src/"
	mb-gcc -O0 -g ${name}_expanded.c -o $elfName.elf -mno-xl-soft-mul -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L"${FOREC_ANALYSER_PATH}microblaze/lib/"

fi

if [ "$1" = "--analysis" ]
then
	> forecc.out
	
	> foreca.reachability.out
	> foreca.reachability.merge_b.out
	> foreca.reachability.merge_g.out
	> foreca.reachability.merge_bg.out
	
	> foreca.maxplus.out
	> foreca.maxplus.merge_b.out
	> foreca.maxplus.merge_g.out
	> foreca.maxplus.merge_bg.out

	> foreca.maxplus_i.out
	> foreca.maxplus_i.merge_b.out
	> foreca.maxplus_i.merge_g.out
	> foreca.maxplus_i.merge_bg.out
	
	echo "Running analysis on all *.foreh files"

	for allocation in *.foreh
	do
		echo "forecc $name.forec $allocation"
		forecc $name.forec $allocation >> forecc.out
	
		echo "foreca $name.c information.xml"
		foreca           -reachability $name.c information.xml >> foreca.reachability.out
		foreca -merge-b  -reachability $name.c information.xml >> foreca.reachability.merge_b.out
		foreca -merge-g  -reachability $name.c information.xml >> foreca.reachability.merge_g.out
		foreca -merge-bg -reachability $name.c information.xml >> foreca.reachability.merge_bg.out
		
		foreca           -maxplus $name.c information.xml >> foreca.maxplus.out
		foreca -merge-b  -maxplus $name.c information.xml >> foreca.maxplus.merge_b.out
		foreca -merge-g  -maxplus $name.c information.xml >> foreca.maxplus.merge_g.out
		foreca -merge-bg -maxplus $name.c information.xml >> foreca.maxplus.merge_bg.out

		foreca           -maxplus-i $name.c information.xml >> foreca.maxplus_i.out
		foreca -merge-b  -maxplus-i $name.c information.xml >> foreca.maxplus_i.merge_b.out
		foreca -merge-g  -maxplus-i $name.c information.xml >> foreca.maxplus_i.merge_g.out
		foreca -merge-bg -maxplus-i $name.c information.xml >> foreca.maxplus_i.merge_bg.out
	done
fi

if [ "$1" = "--simulate" ]
then	
	echo "Running simulator on all *.elf files"

	trap ":" SIGINT

	for elf in $name.*.elf
	do
		numberOfCores=${elf#*.}
		numberOfCores=${numberOfCores%*.elf}
		numberOfCores=`expr $numberOfCores + 0`

		echo "mb-sim $numberOfCores $elf"
		mb-sim $numberOfCores $elf
	done
fi

if [ "$1" == "--memory" ]
then
	> forecc.valgrind.out
	> foreca.valgrind.out

	echo "Checking memory usage for analysis on all *.foreh files"

	for allocation in *.foreh
	do
		echo "forecc $name.forec $allocation"
		forecc $name.forec $allocation >> forecc.valgrind.out
	
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -reachability $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -reachability $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.reachability.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-b -reachability $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-b -reachability $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.reachability.merge_b.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-g -reachability $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-g -reachability $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.reachability.merge_g.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-bg -reachability $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-bg -reachability $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.reachability.merge_bg.valgrind

		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -maxplus $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -maxplus $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-b -maxplus $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-b -maxplus $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus.merge_b.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-g -maxplus $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-g -maxplus $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus.merge_g.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-bg -maxplus $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-bg -maxplus $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus.merge_bg.valgrind

		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -maxplus-i $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -maxplus-i $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus_i.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-b -maxplus-i $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-b -maxplus-i $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus_i.merge_b.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-g -maxplus-i $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-g -maxplus-i $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus_i.merge_g.valgrind
		echo "valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=$allocation.valgrind foreca -merge-bg -maxplus-i $name.c information.xml"
		valgrind --quiet --tool=massif --depth=1 --max-snapshots=10 --massif-out-file=temp foreca -merge-bg -maxplus-i $name.c information.xml >> foreca.valgrind.out
		ms_print temp > $allocation.maxplus_i.merge_bg.valgrind
	done
	
	rm temp
fi
	
