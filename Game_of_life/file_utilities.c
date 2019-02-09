#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "file_utilities.h"

// read in bytes of file into array of char bytes pointed to by contents parameter
size_t read_file(char* file_name, char** contents) {
	FILE  *fp;
	size_t file_size;
	long   off_end;
	int    rc;

	fp = fopen(file_name, "rb"); // "rb" for reading binary file
	if (NULL == fp) {
		return -1L;
	}

	// seek to end of the file
	rc = fseek(fp, 0L, SEEK_END);
	if (0 != rc) {
		return -1L;
	}

	// get file size
	if (0 > (off_end = ftell(fp))) {
		return -1L;
	}
	file_size = (size_t)off_end;

	// allocate buffer to hold the whole file
	*contents = malloc(file_size);
	if (NULL == *contents) {
		return -1L;
	}

	// rewind file pointer to start of file
	rewind(fp);

	// load file into buffer
	if (file_size != fread(*contents, 1, file_size, fp)) {
		free(*contents);
		return -1L;
	}

	// close file
	if (EOF == fclose(fp)) {
		free(*contents);
		return -1L;
	}

	// return file size
	return (long)file_size;
}

// write byte array to named file 
size_t write_file(char* file_name, char* contents, size_t size) {
	FILE *fp = fopen(file_name, "wb+"); // "wb+" truncate zero length or create write/update binary file
	if (!fp) {
		return -1;
	}
	fwrite(contents, size, 1, fp);
	fclose(fp);
	return 0;
}