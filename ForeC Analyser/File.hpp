/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef FOREC_LOADER_HPP
#define FOREC_LOADER_HPP

#include <fstream>
#include <ostream>
#include <regex.h>

#include "ScannerMicroBlaze.hpp"
#include "ScannerPtarm.hpp"

#include "cfg/Root.hpp"

namespace forec {
	class File {
		public:
			// Instantiate with either a file name or an already open stream
			static void read(const std::string &fileName, const std::string &architecture, forec::cfg::Root &rootNode) throw(std::string);
			static void read(std::istream &stream, const std::string &architecture, forec::cfg::Root &rootNode) throw(std::string);

			// Distinguish between a source line, assembly line and annotation
			static std::string scrub(std::istream &stream) throw(std::string);

			static void write(const std::string &fileName, const std::ostringstream &output) throw(std::string);

		private:
			// supress default constructor
			File();
			
			// supress default copy constructor
			File(File const &rhs);
			
			// supress default assignment operator
			File &operator=(File const &rhs);
	};

	/**
	 * Open and parse a file
	 */
	void File::read(const std::string &fileName, const std::string &architecture, forec::cfg::Root &rootNode) throw(std::string) {
		std::ifstream inFile(fileName.c_str());
		if (!inFile.good()) {
			throw std::string("File::read: Unable to open file \"" + fileName + "\".");
		}
		
		std::istringstream scrubbedInFile(File::scrub(inFile).c_str());
		inFile.close();

		if (architecture.compare("microblaze") == 0) {
			loader::ScannerMicroBlaze scanner(&scrubbedInFile);
			loader::ParserMicroBlaze parser(scanner, rootNode);
			parser.parse();
		} else if (architecture.compare("ptarm") == 0) {
			loader::ScannerPtarm scanner(&scrubbedInFile);
			loader::ParserPtarm parser(scanner, rootNode);
			parser.parse();
		} else {
			throw std::string("File::read: Unsupported architecture: " + architecture);
		}
	}

	/**
	 * Parse an already open stream
	 */
	void File::read(std::istream &stream, const std::string &architecture, forec::cfg::Root &rootNode) throw(std::string) {
		std::istringstream scrubbedInFile(File::scrub(stream).c_str());

		if (architecture.compare("microblaze") == 0) {
			loader::ScannerMicroBlaze scanner(&scrubbedInFile);
			loader::ParserMicroBlaze parser(scanner, rootNode);
			parser.parse();
		} else if (architecture.compare("ptarm") == 0) {
			loader::ScannerPtarm scanner(&scrubbedInFile);
			loader::ParserPtarm parser(scanner, rootNode);
			parser.parse();
		} else {
			throw std::string("File::read: Unsupported architecture: " + architecture);
		}
	}

	/**
	 * Scrub a stream
	 */
	std::string File::scrub(std::istream &stream) throw(std::string) {
		std::ostringstream output;
		regex_t assembly;
		regex_t annotation;
		
		/* Compile the regular expressions */
		if (regcomp(&assembly, "(^[[:blank:]]*[[:xdigit:]]+:\t[[:xdigit:]]{8})|(^[[:xdigit:]]{8} <[_[:alnum:]]+>:)|(^[[:blank:]]*$)", REG_EXTENDED)) {
			throw std::string("File::scrub: Could not compile regex");
		}

		if (regcomp(&annotation, "^[[:blank:]]*// forec:", REG_EXTENDED)) {
			throw std::string("File::scrub: Could not compile regex");
		}

		std::string line;
		while (std::getline(stream, line)) {
			bool isAssembly;
			bool isAnnotation;

			line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
			line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
						
			/* Execute the regular expressions */
			isAssembly = regexec(&assembly, line.c_str(), 0, NULL, 0);
			isAnnotation = regexec(&annotation, line.c_str(), 0, NULL, 0);
			if (isAssembly == 0) {
				// Assembly
				output << line << std::endl;
			} else if (isAssembly == REG_NOMATCH) {
				if (isAnnotation == 0) {
					// ForeC annotation
			        output << '+' << line << std::endl;				
				} else if (isAnnotation == REG_NOMATCH) {
					// Source code
               		output << '-' << line << std::endl;
				} else {
					char msgbuf[100];
				    regerror(isAnnotation, &annotation, msgbuf, sizeof(msgbuf));
				    throw std::string("Regex match failed: " + std::string(msgbuf));
           		}
			} else {
				char msgbuf[100];
	            regerror(isAssembly, &assembly, msgbuf, sizeof(msgbuf));
	            throw std::string("File::scrub: Regex match failed: " + std::string(msgbuf));
			}
		}

		/* Free compiled regular expressions if you want to use the regex_t again */
		regfree(&assembly);
		regfree(&annotation);
		
		return output.str();
	}

	void File::write(const std::string &fileName, const std::ostringstream &output) throw(std::string) {
		std::ofstream outFile(fileName.c_str());
		if (!outFile.good()) {
			throw std::string("File::write: Unable to create file.");
		}

		outFile << output.str() << std::endl;
		outFile.close();
	}

}

#endif // FOREC_LOADER_HPP
