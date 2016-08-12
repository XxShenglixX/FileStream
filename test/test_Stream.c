#include "unity.h"
#include "Stream.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initOutStream_should_malloc_correctly(void)
{
  OutStream *out = initOutStream();
  TEST_ASSERT_NOT_NULL(out);
	TEST_ASSERT_EQUAL(0, out->bitIndex);
	TEST_ASSERT_EQUAL(0, out->byteToWrite);
  freeOutStream(&out);
}

void test_streamWriteBit_1time_given_input_1_should_write_1_to_byteToWrite_and_increment_bitIndex_to_1()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    freeOutStream(&out);
}

void test_streamWriteBit_2time_given_input_1_0_byteToWrite_should_contain_01_and_increment_bitIndex_to_2()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    streamWriteBit(out,0);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(2,out->bitIndex);
    
    freeOutStream(&out);
}

void test_streamWriteBit_3time_given_input_1_0_1_should_write_1_0_1_to_byteToWrite_and_increment_bitIndex_to_3()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    streamWriteBit(out,0);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(2,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(5,out->byteToWrite);
    TEST_ASSERT_EQUAL(3,out->bitIndex);
       
    freeOutStream(&out);
}

void test_streamWriteBits_given_value_8_bitSize_3_should_write_0_to_byteToWrite_return_bitIndex_3()
{
    OutStream *out = initOutStream();
    
    streamWriteBits(out,8,3);

    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(3,out->bitIndex);
    
    freeOutStream(&out);
    
}

void test_streamWriteBits_given_value_8_bitSize_4_should_write_8_to_byteToWrite_return_bitIndex_4()
{
    OutStream *out = initOutStream();
    
    streamWriteBits(out,8,4);

    TEST_ASSERT_EQUAL(8,out->byteToWrite);
    TEST_ASSERT_EQUAL(4,out->bitIndex);
    
    freeOutStream(&out);
}

void test_streamWriteBits_given_A_bitSize_8_should_flush_A_during_closeOutStream()
{
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/test_streamWriteBits.txt", "wb" , out);
    
    streamWriteBits(out,'A',8);
    
    TEST_ASSERT_EQUAL('A',out->byteToWrite);
    TEST_ASSERT_EQUAL(8,out->bitIndex);
    
    closeOutStream(out);
   
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    freeOutStream(&out);
}


void test_streamWriteBits_given_ABCDEFGH_bitSize_64_should_flush_ABCDEFGH()
{
    char *string = "ABCDEFGH  IJKLMN\n AA\n\n\n" ;
    
    int i ;
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/test_streamWriteBits_1.txt", "wb" , out);

    for( i = 0 ; i < strlen(string) ; i ++ )
        streamWriteBits(out,string[i],8);

    closeOutStream(out);
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    freeOutStream(&out);
}

void test_streamWriteDatablock()
{
  OutStream *out = initOutStream();
  
  char buffer[1048576] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" ;
  
  out = openOutStream("test/support/test_streamWriteDatablock.txt", "wb" , out);
  
  streamWriteDataBlock(out,buffer);
  
  closeOutStream(out);
  freeOutStream(&out);
}