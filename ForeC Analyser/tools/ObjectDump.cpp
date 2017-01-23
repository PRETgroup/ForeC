/*
 *  ObjectDump.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 14/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "ObjectDump.hpp"

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>


namespace global {
	extern std::string architecture;
}

namespace tools {
	void ObjectDump::make(const std::string &sourceName, const std::string &expandedName, const std::string &elfName, const std::string &dumpName) {
		if (global::architecture.compare("microblaze") == 0) {
			ObjectDump::makeMicroBlaze(sourceName, expandedName, elfName, dumpName);
		} else if (global::architecture.compare("ptarm") == 0) {
			ObjectDump::makePtarm(sourceName, expandedName, elfName, dumpName);
		}
	}

	void ObjectDump::makeMicroBlaze(const std::string &sourceName, const std::string &expandedName, const std::string &elfName, const std::string &dumpName) {
		const std::string forecaPath = getenv("FOREC_ANALYSER_PATH");
		if (forecaPath.compare("") == 0) {
			throw std::string("Check your environment for FOREC_ANALYSER_PATH: \"" + forecaPath + "\"");
		}

		const std::string gccPreProcessorCommand = "mb-gcc -E -CC " + sourceName + " -o " + expandedName
												   + " -I\"" + forecaPath + "microblaze/include/\" -I\"" 
												   + forecaPath + "microblaze/drivers/counter_dfsl_v1_00_a/src/\" -I\"" 
												   + forecaPath + "microblaze/drivers/forec_mutex_v1_00_a/src/\"";
		const std::string gccCompileCommand = "mb-gcc -O0 -g " + expandedName + " -o " + elfName
											  + " -mno-xl-soft-mul -mxl-multiply-high -mhard-float -mxl-float-convert -mxl-float-sqrt -mno-xl-soft-div -mcpu=v8.00.b -T forec_linker_script.ld -L\"" 
											  + forecaPath + "microblaze/lib/\" -lm";
		const std::string objectDumpCommand = "mb-objdump -dCrS " + elfName + " > " + dumpName;

		// Perform macro expansion on the ForeC generated C-file.
		int result = system(gccPreProcessorCommand.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makeMicroBlaze: Macro expansion failed (" << result << ')';
			throw output.str();
		}

		// Compile the C-file using MicroBlaze GCC.
		result = system(gccCompileCommand.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makeMicroBlaze: Compilation failed (" << result << ')';
			throw output.str();
		}

		// Dissassemble the generated object file.
		result = system(objectDumpCommand.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makeMicroBlaze: Object dump failed (" << result << ')';
			throw output.str();
		}
	}

	void ObjectDump::makePtarm(const std::string &sourceName, const std::string &expandedName, const std::string &elfName, const std::string &dumpName) {
		std::string forecaPath;
		if (getenv("FOREC_ANALYSER_PATH") == NULL) {
			throw std::string("Check your environment for FOREC_ANALYSER_PATH: \"" + forecaPath + "\"");
		} else {
			forecaPath = getenv("FOREC_ANALYSER_PATH");
		}
		
		std::string gccName;
		if (system("command -v arm-linux-gnueabi-gcc > /dev/null 2>&1 || exit 1") == EXIT_SUCCESS) {
			gccName = "arm-linux-gnueabi-";
		} else if (system("command -v arm-none-eabi-gcc > /dev/null 2>&1 || exit 1") == EXIT_SUCCESS) {
			gccName = "arm-none-eabi-";
		} else {
			std::ostringstream output;
			output << "tools::ObjectDump::makePtarm: Could not find arm-none-eabi-gcc or arm-linux-gnueabi-gcc";
			throw output.str();
		}
		
		if (getenv("OS") != NULL) {
			// Convert forecaPath to Windows style because arm-none-eabi tools doesn't support Linux style directory names.
			forecaPath.replace(forecaPath.find("/cygdrive/c"), std::string("/cygdrive/c").length(), "C:");
			std::replace(forecaPath.begin(), forecaPath.end(), '/', '\\');
		}
	
		const std::string gccStartUpCommand = gccName + "as -march=armv2a \"" + forecaPath + "ptarm/startup.s\" -o \"" + forecaPath + "ptarm/startup.o\"";
		const std::string gccPreProcessorCommand = gccName + "gcc -E -CC " + sourceName + " -o " + expandedName + " -I\"" + forecaPath + "ptarm/include\"";
		const std::string gccCompileCommand1 = gccName + "gcc -O0 -g -march=armv2a -mno-thumb-interwork -c " + expandedName + " -o " + sourceName + ".o";
		const std::string gccCompileCommand2 = gccName + "gcc -O0 -g -Xlinker -T -Xlinker forec_linker_script.ld -Xlinker --fix-v4bx -nostartfiles \"" + forecaPath + "ptarm/startup.o\" " + sourceName + ".o -o " + elfName;
		const std::string objectDumpCommand = gccName + "objdump -marm -dCrS " + elfName + " > " + dumpName;

		// Create the startup routine.
		int result = system(gccStartUpCommand.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makePtarm: Creating startup routine failed (" << result << ')';
			throw output.str();
		}

		// Perform macro expansion on the ForeC generated C-file.
		result = system(gccPreProcessorCommand.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makePtarm: Macro expansion failed (" << result << ')';
			throw output.str();
		}

		// Compile the C-file using ARM GCC.
		result = system(gccCompileCommand1.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makePtarm: Compilation1 failed (" << result << ')';
			throw output.str();
		}

		result = system(gccCompileCommand2.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makePtarm: Compilation2 failed (" << result << ')';
			throw output.str();
		}

		// Dissassemble the generated object file.
		result = system(objectDumpCommand.c_str());
		if (result != EXIT_SUCCESS) {
			std::ostringstream output;
			output << "tools::ObjectDump::makePtarm: Object dump failed (" << result << ')';
			throw output.str();
		}
	}
	
}
