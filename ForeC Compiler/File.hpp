/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef FORECLOADER_HPP
#define FORECLOADER_HPP

#include <fstream>
#include <ostream>
#include "Scanner.hpp"

namespace forec {
	class File {
		public:
			// can instantiate with either a file name or an already open stream
			static void read(const std::string &fileName, forec::ast::Root &rootNode) throw(std::string);
			static void read(std::istream &stream, forec::ast::Root &rootNode) throw(std::string);

			static void write(const std::string &fileName, forec::ast::Root &rootNode) throw(std::string);

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
	void File::read(const std::string &fileName, forec::ast::Root &rootNode) throw(std::string) {
		std::ifstream inFile(fileName.c_str());
		if (!inFile.good()) {
			throw std::string("File::read: Unable to open file \"" + fileName + "\".");
		}

		loader::Scanner scanner(&inFile);
		loader::Parser parser(scanner, rootNode);
		parser.parse();

		inFile.close();
	}

	/**
	 * Parse an already open stream
	 */
	void File::read(std::istream &stream, forec::ast::Root &rootNode) throw(std::string) {
		loader::Scanner scanner(&stream);
		loader::Parser parser(scanner, rootNode);
		parser.parse();
	}

	void File::write(const std::string &fileName, forec::ast::Root &rootNode) throw(std::string) {
		std::ofstream outFile((fileName + ".c").c_str());
		if (!outFile.good()) {
			throw std::string("File::write: Unable to create file.");
		}

		outFile << rootNode << std::endl;
		outFile.close();
	}

}

#endif // FORECLOADER_HPP
