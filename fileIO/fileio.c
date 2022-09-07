#include "fileio.h"

int read_file_bytes (char *filename, int bytes, char *buffer)
/*
 * Reads byte data from a file
 * Inputs:
 * filename: full path and filename to read
 * bytes: maximum number of bytes to read
 * buffer: where to put the read data (note need bytes+1)
 * Returns: number of bytes read or -1 on error
 */
{
	int file = open(filename, O_RDONLY);
	return read(file, buffer, bytes);
}

int read_file_lines (char *filename, char buffer[MAXLINES][MAXBYTES + 1])
/*
 * Reads lines from a file
 * Inputs:
 * filename: full path and filename to read
 * buffer: where to put the read lines
 * Return value: number of lines read
 */
{
	int j = 0;
	FILE *file = fopen(filename, "r");
	char *file_line = fgets(buffer[0], MAXBYTES, file);

	if (file_line == NULL){
        return j;
    }

	for (j = 1; j < MAXLINES; j++){
		if (file_line != NULL){
			file_line = fgets(buffer[j], MAXBYTES, file);
		}
	}
    
	return j;
}
