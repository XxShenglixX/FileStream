#ifndef Stream_H
#define Stream_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <CException.h>

typedef enum {ERR_FAILED_TO_OPEN} ERR;

typedef struct InStream InStream;
typedef struct OutStream OutStream;

struct InStream
{
  char *filename;
  FILE *file;
  uint8_t byteToRead;
  uint8_t bitIndex;
};

struct OutStream
{
  char *filename;
  FILE *file;
  uint8_t byteToWrite;
  uint8_t bitIndex;
};

InStream *initInStream();
OutStream *initOutStream();

void freeInStream(InStream **inStream);
void freeOutStream(OutStream **outStream);

void closeInStream(InStream *inStream);
void closeOutStream(OutStream *outStream);

InStream *openInStream(char *filename, char *mode, InStream *inStream);
OutStream *openOutStream(char *filename, char *mode, OutStream *outStream);

uint8_t  streamReadBit(InStream *inStream);
uint64_t streamReadBits(InStream *inStream, uint8_t bitSize);

void streamWriteBit(OutStream *outStream, uint8_t bitToWrite);
void streamWriteBits(OutStream *outStream, uint64_t value, uint8_t bitSize);
void streamWriteDataBlock(OutStream *outStream,char *buffer);

void streamFlush(OutStream *outStream);

uint8_t checkEndOfFile(InStream *inStream);
#endif // Stream_H
