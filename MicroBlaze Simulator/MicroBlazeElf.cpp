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

#include "MicroBlazeElf.hpp"

#include "MicroBlaze.hpp"
#include "System.hpp"

const char * MicroBlazeElf::readElf ( MicroBlaze * core, const char * fname ) {
    Elf *           e ;
    const char *    out = NULL ;
    int             fd ;

    if ( elf_version ( EV_CURRENT ) == EV_NONE ) {
        return "libelf version check failed." ;
    }
    fd = open ( fname , O_RDONLY ) ;
    if ( fd < 0 ) {
        return "readElf open() failed." ;
    }

    e = elf_begin ( fd , ELF_C_READ , NULL ) ;
    if ( e == NULL ) {
        close ( fd ) ;
        return "elf_begin() failed." ;
    }

    out = __Read_Elf ( core, e , fd ) ;
    elf_end ( e ) ;
    close ( fd ) ;
    return out ;
}

const char * MicroBlazeElf::__Read_Elf ( MicroBlaze * core, Elf * e , int fd ) {
    Elf_Kind        ek ;
    GElf_Ehdr       ehdr ;
    GElf_Phdr       phdr ;
    size_t          i , n = 0 , loaded = 0 ;
    off_t           cur_pos ;

    ek = elf_kind ( e ) ;
    if ( ek != ELF_K_ELF ) {
        return "unrecognised kind of ELF object." ;
    }
    if ( gelf_getehdr ( e , & ehdr ) == NULL ) {
        return "unable to read ELF header." ;
    }
    if ( gelf_getclass ( e ) != ELFCLASS32 ) {
        return "ELF object is not 32-bit." ;
    }
    if ( ehdr . e_type != ET_EXEC ) {
        return "ELF type is not a plain executable." ;
    }
    if ( ehdr . e_machine != 0xbaab ) {
        return "Machine for this ELF is not Microblaze." ;
    }
#ifdef elf_getphnum
    /* This function isn't in every libelf - it's in the Slackware
     * version and the one bundled with M5, but not the Red Hat one */
    if ( elf_getphnum ( e , & n ) == 0 ) {
        return "elf_getphnum() failed: no program header?" ;
    }
#else
    n = ehdr . e_phnum ;
#endif
    for ( i = 0 ; i < n ; i ++ ) {
        if ( gelf_getphdr ( e , i , & phdr ) != & phdr ) {
            return "gelf_getphdr() failed." ;
        }
        if ( phdr . p_type != PT_LOAD ) {
            continue ;
        }
        cur_pos = lseek ( fd , 0 , SEEK_CUR ) ;
        if ( (unsigned)lseek ( fd , phdr . p_offset , SEEK_SET ) != phdr . p_offset ) {
            return "lseek() failed." ;
        }

        core -> system -> MB_Write_From_File ( (unsigned) phdr . p_paddr , fd , (unsigned) phdr . p_filesz ) ;
        lseek ( fd , cur_pos , SEEK_SET ) ;
        loaded ++ ;
    }
    if ( loaded == 0 ) {
        return "ELF contains no loadable sections?" ;
    }
    
    core -> jump ( (unsigned) ehdr . e_entry ) ;

    /* success */
    return NULL ;
}



