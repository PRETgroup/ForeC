/*
 * Scratchpad MMU - ELF reader
 * Copyright (C) Jack Whitham 2009
 * http://www.jwhitham.org.uk/c/smmu.html
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * (version 2.1 of the License only).
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef MICROBLAZE_ELF_HPP
#define MICROBLAZE_ELF_HPP

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>


#ifndef off64_t
#define off64_t int64_t
#endif

#include <libelf.h>
#include <gelf.h>

class MicroBlaze;

class MicroBlazeElf {
	// Static
	public:
		static const char * readElf ( MicroBlaze * core, const char * fname ) ;
		static const char * __Read_Elf ( MicroBlaze * core, Elf * e , int fd ) ;
};

#endif /* MICROBLAZE_ELF_HPP */
