#include <stdio.h>
#include <string.h>

const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

void encodeBase64(const char *input)
{
    int i = 0;
    unsigned char currentChar = input[i];
    unsigned char nextChar = input[i + 1];
    unsigned char thirdChar = input[i + 2];

    // 1. create the first chunk, 6 leftmost bits
    unsigned char firstChunk = currentChar >> 2;
    // 2. 2nd chunk, last 2 bit of first character + 4 first bit of 2nd character
    unsigned char secondChunk = (currentChar & 0b00000011) << 4 | (nextChar & 0b11110000) >> 4;
    // 3. 3rd chunk, last 4 bit of 2nd character + first 2 bit of third character
    unsigned char thirdChunk = ((nextChar & 0b00001111) << 2) | ((thirdChar & 0b11000000) >> 6);
    // 4. 4th chunk, last 6 bit of 3rd character
    unsigned char fourthChunk = thirdChar & (0b00111111);

    char firstChunkTranslated = base64Table[firstChunk];
    char secondChunkTranslated = base64Table[secondChunk];
    char thirdChunkTranslated = base64Table[thirdChunk];
    char fourthChunkTranslated = base64Table[fourthChunk];

    printf("result: %c %c %c %c \n", firstChunkTranslated, secondChunkTranslated, thirdChunkTranslated, fourthChunkTranslated);

}


int main()
{
    const char *args = "abcdef";
    printf("Input: %s\n", args);

    printf("Encoded: ");
    encodeBase64(args);
    return 0;
}