#include "helper.h"

int char_to_long (unsigned char *ptr, int bytes){
/*
 * Takes a char array of bytes and converts them into a long. Assumes little endian 
 * Inputs:
 * *ptr: pointer to start of char array of bytes
 * bytes: how many bytes are in the array.
 * Return value: number of lines read
 */
    unsigned long num = 0;
    for( int i = bytes; --i >= 0; ){
        // printf("Num B: %lu. I: %d. Ptr: %x\n", num, i, ptr[i]);
        // printf("Test: %lu\n", num << 8);
        num = (num << 8) | ptr[i];
    }
    return num;
}