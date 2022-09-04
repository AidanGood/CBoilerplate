#include "fileio.h"
/*
 * This program specifically is to read lines, but can be easily modified to read 
 * a number of bytes instead with the read_file_bytes function in fileio.c
 */

int main(int argc, char* argv[])
/*
 * Reads a number of lines from a file up to MAXLINES and MAXBYTES per line
 * Inputs:
 * argv[1]: Name of the file
 * argv[2]: number of lines to read from the file
 * Returns: 0 on success or -1 on error
 */
 {
    int readlines = 10;
    char d_buffer[MAXLINES][MAXBYTES+1];
	
    // Throw Error Too few args
    if (argc < 2){
        printf("Usage %s <filename> [<bytes>]\n", argv[0]);
        exit(-1);
    }

    // Throw Error Want more lines read than supported
    if (argc > 2){
        readlines = atoi(argv[2]);
        if (readlines > MAXLINES){
            printf("Too many lines requested, max supported value is %d!\n", MAXBYTES);
            exit(-1);
        }
    }

    if ( read_file_lines( argv[1], d_buffer) > 0) {
        readlines = atoi(argv[2]);
		int i;
		for (i=0; i < readlines; i++){
			printf("%s\n", d_buffer[i]);
		}
    }

    // Throw Error read_file_lines returned 0 lines read
    else {
        printf("Error: could not read file!\n");
        exit(-1);
    }

    return 0;
}

