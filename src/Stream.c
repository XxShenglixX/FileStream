#include "Stream.h"

/** 
 *   brief  : Initialise OutStream and allocate memory for it
 * 
 *   Return : return pointer to allocted memory for initalised OutStream
 *   
 */
OutStream *initOutStream()
{
  OutStream *outStream = malloc(sizeof(OutStream));
  
  outStream->file = NULL;
  outStream->byteToWrite = 0;
  outStream->bitIndex = 0;

  return outStream;
}

/** 
 *   brief  : Free the allocted memory for OutStream and set it to NULL
 *  
 *   Input  : outStream is a pointer to pointer of OutStream
 *    
 */
void freeOutStream(OutStream **outStream)
{
  free(*outStream);
  *outStream = NULL ;
}

/** 
 *   brief  : Open the selected files in selected mode for OutStream
 *  
 *   Input  : filename        is the name of the file to be opened
 *   Input  : mode            is the file operation mode 
 *            Possible value
 *            "r"             read mode. File must exist
 *            "w"             write mode. Create an empty file if the file initially does not exist or discard the contents if the file initially exist 
 *            "a"             open for appending
 *  
 *   Input  : outStream       is the pointer to the OutStream
 *  
 *   Return : return          the OutStream with opened file
 *  
 *  
 */ 
OutStream *openOutStream(char *filename, char *mode, OutStream *outStream)
{
  outStream->file = fopen( filename, mode);
    
  if(outStream->file == NULL)
    Throw(ERR_FILE_OPEN_FAILED);
    
  outStream->filename = filename;

  return outStream;
}

/** 
 *   brief  : Close the file inside the OutStream and flush any remaing unwritten data
 *  
 *   Input  : outStream   is the pointer to the OutStream
 *  
 */ 
void *closeOutStream(OutStream *outStream)
{
  if (outStream->bitIndex != 0)
    streamFlush(outStream);

  fclose(outStream->file);
}

/** 
 *   brief  : Write 1 bit of data into OutStream 
 *  
 *   Input  : outStream   is the pointer to the OutStream
 *   Input  : bitToWrite  is the value of the bit to be written either 1 or 0
 *  
 */
void streamWriteBit(OutStream *outStream,uint8_t bitToWrite)
{
  outStream->byteToWrite |= (bitToWrite << outStream->bitIndex) ; //write lSB first
  outStream->bitIndex ++ ;
}

/** 
 *   brief  : Write multiple bits of the specified data into OutStream and flushed into file stream if necessary
 *  
 *   Input  : outStream   is the pointer to the OutStream
 *   Input  : value       is the value to be written
 *   Input  : bitSize     is the number of bits for the value to be written
 *    
 */ 
void streamWriteBits(OutStream *outStream, uint64_t value, uint8_t bitSize)
{
  uint8_t bitToWrite, index ;

  for ( index = 0 ; index < bitSize ; index ++) //write value to buffer
  {
    if (outStream->bitIndex == 8)
      streamFlush(outStream);

    bitToWrite = value & (1 << index ) ;

    if (bitToWrite != 0 )
      bitToWrite = 1 ;
    else
      bitToWrite = 0 ;

    streamWriteBit(outStream,bitToWrite);
  }
}

/** 
 *   brief  : Write whole data block into file stream if necessary
 *  
 *   Input  : outStream   is the pointer to the OutStream
 *   Input  : buffer      is the data block to be written into file stream
 *    
 */
void streamWriteDataBlock(OutStream *outStream,char *buffer)
{
  fwrite(buffer,1,strlen(buffer),outStream->file);
}

/** 
 *   brief  : Flush byteToWrite in OutStream to file stream
 *  
 *   Input  : outStream   is the pointer to the OutStream 
 *  
 */ 
void streamFlush(OutStream *outStream)
{
  fwrite(&(outStream->byteToWrite),1,1,outStream->file);

  outStream->byteToWrite = 0;
  outStream->bitIndex = 0 ;
}
