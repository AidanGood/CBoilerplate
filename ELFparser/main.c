#include "helper.h"

/*
 * This program will parse through an ELF file and return the number of executable insructions it contains
 */
int main(int argc, char *argv[])
/*
 * Inputs:
 * argv[1]: Name of the ELF file
 * Returns: 0 on success or -1 on error
 */
 {
    // Check for too few/many args
    if (argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(-1);
    }

    // Ensure file exist
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        printf("Error, could not read file %s", argv[1]);
        exit(-1);
    }

    // Convert file pointer to descriptor for pread()
    int fd;
    fd = fileno(file);

    unsigned char e_ident[1];        // Byte for 32/64 file format
    unsigned char e_entry[8];        // Address of process entry point
    unsigned char e_shoff[8];        // Offset of section header
    unsigned char e_shentsize[2];    // Size of each section header entry
    unsigned char e_shnum[2];        // Number of entries in section header

    // Offsets to parse file header for 64-bit format
    int FILE_OFF64[] = {0x04, 0x18, 0x28, 0x3A, 0x3C};

    // Get the needed info from elf header
    pread(fd, e_ident, 1, FILE_OFF64[0]);
    pread(fd, e_entry, 8, FILE_OFF64[1]);
    pread(fd, e_shoff, 8, FILE_OFF64[2]);
    pread(fd, e_shentsize, 2, FILE_OFF64[3]);
    pread(fd, e_shnum, 2, FILE_OFF64[4]);


    unsigned long secHeader = char_to_long(e_shoff, 8);     // Section header address
    unsigned long numSection = char_to_long(e_shnum, 2);     // Number of section headers

    printf("Section header offset: %lu\n", secHeader);
    printf("Section header count: %lu\n", numSection);

    

    /*  This part is for debugging. It prints out the requested bytes i.
    unsigned char buff[1];
    for (int i = 0; i < 20; i++){
        if (i%2==0) printf(" ");
        if (i%10==0) printf("\n");
        pread(fd, buff, 1, i);
        printf("%02x", buff[0]);
    }
    */
    
    unsigned char sh_addr[8];
    unsigned char sh_offset[8];
    unsigned char sh_size[8];
    unsigned char sh_flags[8];

    // Offsets to parse section headers for 64-bit format
    int SEC_OFF64[] = {0x08, 0x10, 0x18, 0x20};

    int header_tracker = 0;
    int exec_track = 0;
    unsigned int flags;

    // unsigned long secFlag;
    // unsigned long secAddress;
    // unsigned long secOffset;
    // unsigned long secSize;

    unsigned char offset_arr[numSection][8];
    unsigned char size_arr[numSection][8];

    /* Print out all section headers
    
    unsigned char buff[1];
    unsigned long i;
    int j = 1;
    for (i = secHeader; i < (secHeader + 1400); i++){
        pread(fd, buff, 1, i);
        printf("%02x", buff[0]);
        if (j%2==0) printf(" ");
        if (j%10==0) printf("\n");
        if (j%64==0){
            j = 0;
            printf("\nNext Section\n");
        }
        j++;
    }
    */


    // Loop through all section headers and record the offset and size of the executable sections
    int b = 0;
    do{
        pread(fd, sh_flags, 8, secHeader + SEC_OFF64[0]);
        pread(fd, sh_addr, 8, secHeader + SEC_OFF64[1]);
        pread(fd, sh_offset, 8, secHeader + SEC_OFF64[2]);
        pread(fd, sh_size, 8, secHeader + SEC_OFF64[3]);

        // secFlag = char_to_long(sh_flags, 8);
        // secAddress = char_to_long(sh_addr, 8);
        // secOffset = char_to_long(sh_offset, 8);
        // secSize = char_to_long(sh_size, 8);
        // printf("Flag: %lx, Add: %lx, Off: %lx, Size: %lx\n", secFlag, secAddress, secOffset, secSize);

        flags = sh_flags[0];
        flags = flags & 0x0F;    // Get last 4 bits
        // Executable flag can have min value of 0x04 and max value of 0x07
        // If executable flag, get info of where executable instructions are located

        if (flags < 0x08 && flags > 0x03){
            for (int i = 0; i < 8; i++){
                offset_arr[exec_track][i] = sh_offset[i];
                size_arr[exec_track][i] = sh_size[i];
            }
            exec_track++;
        }

        secHeader += 0x40;      // 64-bit section headers are 0x40 bytes
        header_tracker++;
        b++;
    } while (header_tracker != numSection);

    printf("Num of Exec Sections: %d\n", exec_track);

    unsigned long progLength;
    unsigned long progOffset;
    int exec_count = 0;

    // Loop through executable sections and print out bytes
    int x = 0;
    while (exec_count != exec_track){
        progOffset = char_to_long(offset_arr[x], 8);
        progLength = char_to_long(size_arr[x], 8);

        int i = 0;
        unsigned char buff[1];    
        while (i < progLength){
            if (i%2==0) printf(" ");
            if (i%8==0) printf("\n");
            pread(fd, buff, 1, progOffset);
            printf("%02x", buff[0]);
            i++;
            progOffset++;
        }
        printf("\nOffset: %lu Size: %lu\n", progOffset, progLength);
        printf("Prog Break\n");
        exec_count++;
        x++;
    }



    

    exit(0);
 }