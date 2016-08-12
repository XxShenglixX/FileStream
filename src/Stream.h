#ifndef Stream_H
#define Stream_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <CException.h>

typedef struct OutStream OutStream;

typedef enum {ERR_FAILED_TO_OPEN} ERR;

struct OutStream
{
  char *filename;
  FILE *file;
  int byteToWrite;
  int bitIndex;
};

#define ERR_FILE_OPEN_FAILED    -1

OutStream *initOutStream();
void freeOutStream(OutStream **out);
void *closeOutStream(OutStream *out);

OutStream *openOutStream(char *filename, char *mode, OutStream *out);

void streamWriteBit(OutStream *out, uint8_t bitToWrite);
void streamWriteBits(OutStream *out, uint64_t value, uint8_t bitSize);
void streamWriteDataBlock(OutStream *out,char *buffer);
void streamFlush(OutStream *out);

#endif // Stream_H
