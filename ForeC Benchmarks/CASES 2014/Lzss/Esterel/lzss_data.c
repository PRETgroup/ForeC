// #include <stdio.h>
// #include <string.h>
// #include <sys/stat.h>
#include "lzss_data.h"
#include "lzss.h"
#include "fifo.h"
#include "file.h"
#include "embed.h"

FileStats fileInfo, archiveInfo;
char **p_argv;
int offset_t1;
int offset_t2;
int offset_t3;
int offset_t4;
int matches_t1 = 0;
int matches_t2 = 0;
int matches_t3 = 0;
int matches_t4 = 0;
int matches = 0;

Fifo window, lookAhead;
char window_buf[WINLENGTH];
char lookAhead_buf[LKLENGTH];

boolean openFile(string fileName)
{
    archiveInfo.fileaddr = archive;
    fileInfo.totalSize = 0;
    fileInfo.bytesProcessed = 0;
    fileInfo.fileaddr = embedded;
    fileInfo.p_file = embedded;
    obtainFileInfo(&fileInfo);
//    print("Compressing file...\n");
    createDescriptor();
    compressFile();
    return 1;
}

integer getFileSize(void)
{
    return fileInfo.totalSize;
}

integer getBytesProcessed(void)
{
    if (fileInfo.bytesProcessed < fileInfo.totalSize)
        return fileInfo.bytesProcessed;
    else
        return fileInfo.totalSize;
}

void slideWindow(void)
{
    int count = 1;
    do {
        // This loop will transfer the first node from look ahead buffer to window for 'matches' times.
        // The node from look ahead buffer will be transfered to window at least once.
        if (window.written_size >= WINLENGTH)
            Fifo_pop_front(&window);
        // Transfer the first character from look ahead buffer to end of window.
        Fifo_push_back(&window, Fifo_pop_front(&lookAhead));
        // Fill back up the look ahead buffer.
        Fifo_push_back(&lookAhead, mgetc(&fileInfo.p_file));
    } while (count++ < matches);
}

void searchWindow1(void)
{
    longestMatch1(&window, &lookAhead);
}

void searchWindow2(void)
{
    longestMatch2(&window, &lookAhead);
}

void searchWindow3(void)
{
    longestMatch3(&window, &lookAhead);
}

void searchWindow4(void)
{
    longestMatch4(&window, &lookAhead);
}

void writeToArchive(void)
{
    _writeToArchive(&lookAhead);
}

/********************************************************
 * Start of function definitions for compressing files. *
 ********************************************************/
void createDescriptor(void)
{
    /* obtainFileInfo() has been moved into createArchive() since obtainFileInfo() now obtains useful information
       about the file requested, it is useful to provide extra information to createArchive() such as whether the
       file is a directory. */
    storeFileInfo();
}

void obtainFileInfo(FileStats *fileInfo)
{
    fileInfo->filesize = (size_t) FILE_SIZE;
    fileInfo->totalSize = fileInfo->filesize;
}

void storeFileInfo(void)
{
    mwrite(&(fileInfo.filesize), 4, 1, &archiveInfo.p_file);
}

void compressFile(void)
{
    Fifo_init(&window, WINLENGTH, window_buf);

    // Dirty workaround
    // Write the first character into the archive then clear the window
    Fifo_push_back(&window, mgetc(&fileInfo.p_file));
    _writeToArchive(&window);
    fileInfo.p_file = fileInfo.fileaddr;

    Fifo_pop_back(&window);
    Fifo_init(&lookAhead, LKLENGTH, lookAhead_buf);
// xil_printf("fileInfo.p_file = %08x\n", fileInfo.p_file);
    while (lookAhead.written_size < LKLENGTH) // Fill the look ahead buffer up.
        Fifo_push_back(&lookAhead, mgetc(&fileInfo.p_file));
// xil_printf("fileInfo.p_file = %08x\n", fileInfo.p_file);
}

void longestMatch1(Fifo *win, Fifo *lk)
{
    int _matches = 0;
    matches_t1 = 0;
    int i, j, k, _offset;
    for (i = 0; i < win->written_size && Fifo_at(win, i);)
    {
        j = 0;

        _offset = i;
        for (k = i; j < LKLENGTH && Fifo_at(win, k) == Fifo_at(lk, j);)
        {
            _matches++;
            j++;
            k++;
            if (k == win->written_size) k = 0;
        }

        if (_matches > matches_t1)
        {
            matches_t1 = _matches;
            offset_t1 = _offset;
        }

        i += 4;
        _matches = 0;
    }
// printf("longestMatch1() matches = %d, offset = %d, i = %d\n", matches_t1, offset_t1, i);
}

void longestMatch2(Fifo *win, Fifo *lk)
{
    int _matches = 0;
    matches_t2 = 0;
    int i, j, k, _offset;
    for (i = 1; i < win->written_size && Fifo_at(win, i);)
    {
        j = 0;

        _offset = i;
        for (k = i; j < LKLENGTH && Fifo_at(win, k) == Fifo_at(lk, j);)
        {
            _matches++;
            j++;
            k++;
            if (k == win->written_size) k = 0;
        }

        if (_matches > matches_t2)
        {
            matches_t2 = _matches;
            offset_t2 = _offset;
        }

        i += 4;
        _matches = 0;
    }
// printf("longestMatch2() matches = %d, offset = %d, i = %d\n", matches_t2, offset_t2, i);
}

void longestMatch3(Fifo *win, Fifo *lk)
{
    int _matches = 0;
    matches_t3 = 0;
    int i, j, k, _offset;
    for (i = 2; i < win->written_size && Fifo_at(win, i);)
    {
        j = 0;

        _offset = i;
        for (k = i; j < LKLENGTH && Fifo_at(win, k) == Fifo_at(lk, j);)
        {
            _matches++;
            j++;
            k++;
            if (k == win->written_size) k = 0;
        }

        if (_matches > matches_t3)
        {
            matches_t3 = _matches;
            offset_t3 = _offset;
        }

        i += 4;
        _matches = 0;
    }
// printf("longestMatch2() matches = %d, offset = %d, i = %d\n", matches_t2, offset_t2, i);
}

void longestMatch4(Fifo *win, Fifo *lk)
{
    int _matches = 0;
    matches_t4 = 0;
    int i, j, k, _offset;
    for (i = 3; i < win->written_size && Fifo_at(win, i);)
    {
        j = 0;

        _offset = i;
        for (k = i; j < LKLENGTH && Fifo_at(win, k) == Fifo_at(lk, j);)
        {
            _matches++;
            j++;
            k++;
            if (k == win->written_size) k = 0;
        }

        if (_matches > matches_t4)
        {
            matches_t4 = _matches;
            offset_t4 = _offset;
        }

        i += 4;
        _matches = 0;
    }
// printf("longestMatch2() matches = %d, offset = %d, i = %d\n", matches_t2, offset_t2, i);
}

void _writeToArchive(Fifo *fifo)
{
    int offset;
    int encode=0x800000;

    matches = 0;
    if (matches_t1 > matches) {
        matches = matches_t1;
        offset = offset_t1;
    }
    if (matches_t2 > matches) {
        matches = matches_t2;
        offset = offset_t2;
    }
    if (matches_t3 > matches) {
        matches = matches_t3;
        offset = offset_t3;
    }
    if (matches_t4 > matches) {
        matches = matches_t4;
        offset = offset_t4;
    }

    encode += (offset << 5) + (matches - 1); // 0 matches will actually mean 1 match, matches range from 0~15, 4 bits.

    if (matches > 2) {
        fileInfo.bytesProcessed += matches;
        mputc(encode >> 16, &archiveInfo.p_file); // Write the MSByte first so the MSbit can be read easily
        mputc(encode >> 8, &archiveInfo.p_file);
        mputc(encode, &archiveInfo.p_file);
    } else if (Fifo_at(fifo, 0) != EOF) {
        fileInfo.bytesProcessed++;
        mputc(Fifo_at(fifo, 0), &archiveInfo.p_file);
        if (matches == 2 && Fifo_at(fifo, 1) != EOF) {
            fileInfo.bytesProcessed++;
            mputc(Fifo_at(fifo, 1), &archiveInfo.p_file);
        }
    }
// printf("_writeToArchive(): %d/%d bytes processed\n", fileInfo.bytesProcessed, fileInfo.totalSize);
    if (fileInfo.bytesProcessed >= fileInfo.totalSize) {
        int count;
        slideWindow();
        matches = 0;
        for (count = 0; count < LKLENGTH - 1 && Fifo_at(&lookAhead, 0) != EOF; count++) {
            mputc(Fifo_at(&lookAhead, 0), &archiveInfo.p_file);
            Fifo_pop_front(&lookAhead);
        }
    }
}

void printResult(void)
{
    obtainFileInfo(&archiveInfo);
    xil_printf("\nFiles compressed successfully.\n");
}


/*******************************************************
 * Start of functions definitions for unpacking files. *
 *******************************************************/
void unpackArchive()
{
}

void processDescriptor(void)
{
}


/****************************************************
 * Start of function definitions for decompression. *
 ****************************************************/
void decompressFile(void)
{
}

void decode(Fifo *win, int *sizeCount)
{
}
