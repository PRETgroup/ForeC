/*
 *  Program Title: lzss Text File Archiver
 *  Author's Name: Simon Yuan
 *  Student ID: 3415420
 *  Date written: 09/05/2004
 *  Description: This program compresses and extracts text files using
 *               Lempel-Ziv Storer Szymanski (LZSS) algorithm.
 *  Operating condition: This is a Command Line Interface based program, must be
 *                       run under a command shell.
 *  Bugs discovered: None.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

typedef struct _Fifo {
    char *data;
    unsigned size;
    unsigned written_size;
    int begin;
    int end;
} Fifo;

void Fifo_init(Fifo*, unsigned);
void Fifo_destroy(Fifo*);
int Fifo_push_front(Fifo*, char);
int Fifo_push_back(Fifo*, char);
char Fifo_pop_front(Fifo*);
char Fifo_pop_back(Fifo*);
char Fifo_at(const Fifo, unsigned);
void Fifo_print(const Fifo);

const int NUM_THREADS = 1;
const int WINLENGTH = 131072;
const int LKLENGTH = 32;

/******************************************
 * Start of global variable declarations. *
 ******************************************/
char **p_argv;
int offset;
int matches = 0;
int offset_thread[4];
int matches_thread[4];


/* It is more sensible to group all the information about the file requested into.
   a structure. */
struct fileStats {
    FILE *p_file;
    char filenameArray[512];
    char *filename;
    int filesize;
    int totalSize;
    int isDir;
} fileInfo, archiveInfo;

Fifo window, lookAhead;

/*************************************
 * Functions required for archiving. *
 *************************************/
void printhelp(void);
//void createArchive(int);
void createDescriptor(void);
void storeFileInfo(void);
//void compressFile(void);
void longestMatch(const Fifo, const Fifo, int);
void writeToArchive(const Fifo);
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
void obtainFileInfo(struct fileStats *);

/******************************
 * Start of the lzss program. *
 ******************************/
int main(int argc, char *argv[])
{
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	//- - - -

    p_argv = argv;  // Make argv globally accessible.

    if (argc>1 && !strcmp(argv[1], "-h"))
    {
        printhelp();
        exit(0);
    } else if (argc>3 && !strcmp(argv[1],"-c")) { // must specify files to be archived.
		int count;
	
		archiveInfo.filename = p_argv[2];
		fileInfo.totalSize = 0;
		
		if ((archiveInfo.p_file=fopen(archiveInfo.filename, "w")) == NULL)
		{
			fprintf(stderr, "Error writing to file '%s'.", archiveInfo.filename);
			exit(1);
		}
		
		for (count = 3; count < argc; count++) // Filelist start from the 4th argument.
		{
			fileInfo.filename = p_argv[count];
			obtainFileInfo(&fileInfo);
			
			if ((fileInfo.p_file=fopen(fileInfo.filename, "r")) == NULL)
				fprintf(stderr, "Error opening file '%s', ignored.\n", fileInfo.filename);
			else if (fileInfo.isDir)
				fprintf(stderr, "'%s' is a directory, ignored.\n", fileInfo.filename);
			else
			{
				printf("Compressing '%s'....", fileInfo.filename);
				fflush(stdout);
				createDescriptor();

				Fifo_init(&window, WINLENGTH);
				Fifo_push_back(&window, fgetc(fileInfo.p_file)); // No point to search the window when there's nothing.
				writeToArchive(window);  // Same reason here, the first character should always get copied to the archive.
				Fifo_init(&lookAhead, LKLENGTH);
				Fifo_push_back(&lookAhead, fgetc(fileInfo.p_file));
				
				while (lookAhead.written_size < LKLENGTH) // Fill the look ahead buffer up.
					Fifo_push_back(&lookAhead, fgetc(fileInfo.p_file));
				
				int count;
				while (!feof(fileInfo.p_file))
				{
					longestMatch(window, lookAhead, 0);
				//	longestMatch(window, lookAhead, 1);
				//	longestMatch(window, lookAhead, 2);
				//	longestMatch(window, lookAhead, 3);

					writeToArchive(lookAhead);
					count = 1;
					do
					{
						// This loop will transfer the first node from look ahead buffer to window for 'matches' times.
						// The node from look ahead buffer will be transfered to window at least once.
						if (window.written_size >= WINLENGTH)
							Fifo_pop_front(&window);
						// Transfer the first character from look ahead buffer to end of window.
						Fifo_push_back(&window, Fifo_pop_front(&lookAhead));
						// Fill back up the look ahead buffer.
						Fifo_push_back(&lookAhead, fgetc(fileInfo.p_file));
					} while (count++ < matches);
				}
				
				// Write the remaining characters in the buffer to the archive.				
				int i;
				for (i = 0; i < NUM_THREADS; i++) {
					matches_thread[i] = 0;
				}
				
				for (count = 0; count < LKLENGTH - 1 && Fifo_at(lookAhead, 0) != EOF; count++)
				{
					writeToArchive(lookAhead);
					Fifo_pop_front(&lookAhead);
				}
				
				fclose(fileInfo.p_file);

				printf(" Done\n");
			}
		}
		
		fclose(archiveInfo.p_file);
		printResult();

    } else if (argc>2 && !strcmp(argv[1],"-d"))  // must specify file to be extracted.
        unpackArchive();
    else
    {
        printhelp();
        exit(1);
    }
	
	//- - - -
	gettimeofday(&endTime,0);
	long seconds = endTime.tv_sec - startTime.tv_sec;
	int microseconds = endTime.tv_usec - startTime.tv_usec;
	if (microseconds < 0) {
		microseconds += 1000000;
		seconds--;
	}
	
	printf("Runtime: %ld.%.6d\r\n", seconds, microseconds);

    return 0;
}

void printhelp()
{
    printf("lzss is a text file archiver.\n\n"
           "Usage:\n    lzss [OPTION] [FILE]...\n\n"
           "Examples:\n"
           "   lzss -c archive.lzs file1 file2  # Create archive.lzs from files file1 and file2\n"
           "   lzss -d archive.lzs              # Extract all files from archive.lzs\n\n"
           "Options:\n"
           "   -c <filename>   compress files\n"
           "   -d <file>       extract file\n"
           "   -h              print this help\n\n");
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

void obtainFileInfo(struct fileStats *fileInfo)
{
    struct stat filestats;
    stat(fileInfo->filename, &filestats);
    fileInfo->filesize = (int) filestats.st_size;
    fileInfo->isDir = S_ISDIR(filestats.st_mode);
    if (!fileInfo->isDir)
        fileInfo->totalSize += fileInfo->filesize;
}

void storeFileInfo(void)
{
    // Length of string plus 1 to take account of the null character.
    fwrite(fileInfo.filename, 1, strlen(fileInfo.filename)+1, archiveInfo.p_file);
    fwrite(&(fileInfo.filesize), 4, 1, archiveInfo.p_file);
}

void longestMatch(const Fifo win, const Fifo lk, int begin)
{
    int _matches = 0;
    matches_thread[begin] = 0;
    int i, j, k, _offset;
    for (i = begin; i < win.written_size && Fifo_at(win, i); i += NUM_THREADS)
    {
        _matches = 0;
        j = 0;

        _offset = i;
        for (k = i; j < LKLENGTH && Fifo_at(win, k) == Fifo_at(lk, j);)
        {
            _matches++;
            j++;
            k++;
            if (k == win.written_size) k = 0;
        }

        if (_matches > matches_thread[begin])
        {
            matches_thread[begin] = _matches;
            offset_thread[begin] = _offset;
        }
    }
}

void writeToArchive(const Fifo fifo)
{
	matches = 0;
	int i;
	for (i = 0; i < NUM_THREADS; i++) {
		if (matches_thread[i] > matches) {
			matches = matches_thread[i];
			offset = offset_thread[i];
		}
	}

    int encode=0x800000;
    encode += (offset << 6) + (matches - 1); // 0 matches will actually mean 1 match, matches range from 0~15, 4 bits.

    if (matches > 2) {
        fputc(encode >> 16, archiveInfo.p_file); // Write the MSByte first so the MSbit can be read easily
        fputc(encode >> 8, archiveInfo.p_file);
        fputc(encode, archiveInfo.p_file);
    } else if (Fifo_at(fifo, 0) != EOF) {
        fputc(Fifo_at(fifo, 0), archiveInfo.p_file);
        if (matches == 2 && Fifo_at(fifo, 1) != EOF)
            fputc(Fifo_at(fifo, 1), archiveInfo.p_file);
    }
}

void printResult(void)
{
    obtainFileInfo(&archiveInfo);
    printf("\nFiles compressed successfully.\n"
           "Ratio %.3f:1  Saved %d%%\n", (float) fileInfo.totalSize/archiveInfo.filesize,
           (int) (100.0*(1.0-(float) archiveInfo.filesize/fileInfo.totalSize)+0.5));  // +0.5 is for rounding.
    fflush(stdout);
}


/*******************************************************
 * Start of functions definitions for unpacking files. *
 *******************************************************/
void unpackArchive()
{
    int countFiles = 0;

    archiveInfo.filename = p_argv[2];
    obtainFileInfo(&archiveInfo);

    if ((archiveInfo.p_file=fopen(archiveInfo.filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file '%s'.\n", archiveInfo.filename);
        exit(1);
    } else if (archiveInfo.isDir) {
        fprintf(stderr, "'%s' is a directory, not a lzss archive.\n", archiveInfo.filename);
        exit(1);
    }

    /* feof() doesn't return true until the end of file character is read, this ensures the loop ends
       right before the end of file character is reached. */
    while (ftell(archiveInfo.p_file) < archiveInfo.filesize) {
        countFiles++;
        processDescriptor();
        printf("Decompressing '%s'....", fileInfo.filename);
        fflush(stdout);
        decompressFile();
        printf(" Done\n");
    }

    fclose(archiveInfo.p_file);
    printf("\nFiles decompressed successfully.\n%d files were extracted.\n", countFiles);
}

void processDescriptor(void)
{
    char c;
    int count = 0;

	fileInfo.filenameArray[count++] = 'r';
	fileInfo.filenameArray[count++] = 'e';
	fileInfo.filenameArray[count++] = 's';
	fileInfo.filenameArray[count++] = 'u';
	fileInfo.filenameArray[count++] = 'l';
	fileInfo.filenameArray[count++] = 't';
	fileInfo.filenameArray[count++] = '_';

    while ((c = fgetc(archiveInfo.p_file)) != 0)
        fileInfo.filenameArray[count++] = c;

    fileInfo.filenameArray[count] = 0; // 'filename' must be a NULL terminated string.
    fileInfo.filename = fileInfo.filenameArray;
    fread(&(fileInfo.filesize), 4, 1, archiveInfo.p_file);
}


/****************************************************
 * Start of function definitions for decompression. *
 ****************************************************/
void decompressFile(void)
{
    int sizeCount = 1; // Size of the file start at 1 because the first character is guaranteed to be written to the file.
    char *p_slashPos, *p_stringStart = fileInfo.filename;

    /* Create directories if it doesn't already exist.
       If the files are inside more than one level of directory, the following loop will create those
       directories in order. */
    while ((p_slashPos=strchr(p_stringStart, '/')) != NULL)
    {
        *p_slashPos = 0; // Terminate the filename string here
        mkdir(fileInfo.filename, 0777);
        *p_slashPos = '/'; // Put the slash back so directories inside the current one can be created correctly.
        p_stringStart = ++p_slashPos;  // New string starting point to search for the next occurance of a slash
    }

    if ((fileInfo.p_file=fopen(fileInfo.filename, "w")) == NULL)
    {
        fprintf(stderr, "Error writing to file '%s'.", fileInfo.filename);
        exit(1);
    }
	
	Fifo window;
    Fifo_init(&window, WINLENGTH);
    Fifo_push_back(&window, fgetc(archiveInfo.p_file));

    // Prevent someone who has decided to compress an empty file.
    if (Fifo_at(window, 0) != EOF) {
        // First character shall be written to the file, same reason as in compression.
        fputc(Fifo_at(window, 0), fileInfo.p_file);
    }

    while (sizeCount < fileInfo.filesize)
        decode(&window, &sizeCount);

    fclose(fileInfo.p_file);
}

void decode(Fifo *win, int *sizeCount)
{
    int count, encoded;
    char buffer[LKLENGTH];
    char c = fgetc(archiveInfo.p_file);

    if (feof(archiveInfo.p_file))
        return;

    if (c >> 7) {
        encoded = c << 16; // Put the MSByte of the encoding into the second byte of the encode integer.
        encoded += fgetc(archiveInfo.p_file) << 8;
        encoded += fgetc(archiveInfo.p_file); // LSByte of the encoding is placed in the first byte.
        matches = (encoded & 0x3F) + 1; /* &0x0F will cause only the least 4 significant bits to be reserved.
                                           Add 1 back because 0~15 was used to represent 1~16. */
        offset = (encoded & 0x7FFFFF) >> 6;

        int i;
        for (count = 0, i = offset; count < matches; count++)  {
            fputc(Fifo_at(*win, i), fileInfo.p_file);
            // Save the matching characters need to be appended to the window for later matchings.
            buffer[count] = Fifo_at(*win, i);
            i++;
            if (i == win->written_size) i = 0;
        }

        // Append matching characters from buffer to the end of the window.
        for (count = 0; count < matches; count++)
        {
            if (win->written_size >= WINLENGTH)
                Fifo_pop_front(win);
            Fifo_push_back(win, buffer[count]);
        }

        *sizeCount += matches;
    } else {
        fputc(c, fileInfo.p_file);
        if (win->written_size >= WINLENGTH)
            Fifo_pop_front(win);
        Fifo_push_back(win, c);
        (*sizeCount)++;
    }
}

/**********************************/


void Fifo_init(Fifo *fifo, unsigned size) {
    fifo->begin = 0;
    fifo->end = 0;
    fifo->size = size;
    fifo->written_size = 0;
    fifo->data = (char*) malloc(size);
	
    if (!fifo->data) {
        fputs("Fifo: out of memory\n", stderr);
        exit(1);
    }
}

void Fifo_destroy(Fifo *fifo) {
    free(fifo->data);
}

int Fifo_push_front(Fifo *fifo, char c) {
    if (fifo->written_size == 0)
        Fifo_push_back(fifo, c);
    else if (fifo->written_size >= fifo->size)
        return -1;
	
    fifo->begin--;
    if (fifo->begin < 0)
        fifo->begin = fifo->size - 1;
    fifo->data[fifo->begin] = c;
    fifo->written_size++;
	
	return 0;
}

int Fifo_push_back(Fifo *fifo, char c) {
    if (fifo->written_size >= fifo->size)
        return -1;
	
    fifo->written_size++;
    fifo->data[fifo->end] = c;
    fifo->end++;
    if (fifo->end == fifo->size)
        fifo->end = 0;
	
	return 0;
}

char Fifo_pop_front(Fifo *fifo) {
    if (fifo->written_size == 0)
        return -1;
	
    char c = fifo->data[fifo->begin];
    fifo->written_size--;
    fifo->begin++;
    if (fifo->begin == fifo->size)
        fifo->begin = 0;
    return c;
}

char Fifo_pop_back(Fifo *fifo) {
    if (fifo->written_size == 0)
        return -1;
	
    fifo->written_size--;
    fifo->end--;
    if (fifo->end < 0)
        fifo->end = fifo->size - 1;
    return fifo->data[fifo->end];
}

char Fifo_at(const Fifo fifo, unsigned i) {
    if (i < fifo.written_size) {
        return fifo.data[(fifo.begin + i) % fifo.size];
    } else {
        return -1;
    }
}

void Fifo_print(const Fifo fifo) {
    int i, j;
    for (i = fifo.begin, j = 0; j < fifo.written_size; i++, j++) {
        if (i == fifo.size)
            i = 0;
        putchar(fifo.data[i]);
    }
}





