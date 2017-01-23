#ifndef LZSS_DATA_H
#define LZSS_DATA_H

#include <stdio.h>
#include "fifo.h"
#include "lzss.h"

//#define WINLENGTH 131072
// #define WINLENGTH 64
// #define LKLENGTH 4
#define WINLENGTH 256
#define LKLENGTH 16
#define FILE_SIZE_ADDR 0x88000000
#define FILE_ADDR 0x88000004
#define ARCHIVE_SIZE_ADDR 0x88100000
#define ARCHIVE_ADDR 0x88100004

typedef struct _FileStats {
    char *p_file;
    char *fileaddr;
    int filesize;
    int totalSize;
    int bytesProcessed;
} FileStats;

boolean openFile(string);
integer getFileSize(void);
integer getBytesProcessed(void);
void slideWindow(void);
void searchWindow1(void);
void searchWindow2(void);
void searchWindow3(void);
void searchWindow4(void);
void writeToArchive(void);

/*************************************
 * Functions required for archiving. *
 *************************************/
void createDescriptor(void);
void storeFileInfo(void);
void compressFile(void);
void longestMatch1(Fifo*, Fifo*);
void longestMatch2(Fifo*, Fifo*);
void longestMatch3(Fifo*, Fifo*);
void longestMatch4(Fifo*, Fifo*);
void _writeToArchive(Fifo*);
void printResult(void);

/*************************************
 * Functions required for unpacking. *
 *************************************/
void unpackArchive(void);
void processDescriptor(void);
void decompressFile(void);
void decode(Fifo*, int*);

/********************************************************
 * Functions required both for archiving and unpacking. *
 ********************************************************/
void obtainFileInfo(FileStats*);

#endif
