#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

void printChunk(char input)
{
    printf("%c", input);
}


bool checkEndOfChar(char input)
{
    if (input == '\0')
        return true;
    return false;
}


/**
 * first char 6 bit
 */
void createFirstChunk(char firstChar)
{
    unsigned char firstChunk = firstChar >> 2;
    char chunkTranslated = base64Table[firstChunk];

    printChunk(chunkTranslated);
}

/**
 * first char 2 bit
 * second char 4 bit
 */
void createSecondChunk(char firstChar, char secondChar)
{
    unsigned char firstCharChunk = (firstChar & 0b00000011) << 4;
    unsigned char secondCharChunk = checkEndOfChar(secondChar) ? 0b00 : (secondChar & 0b11110000) >> 4;

    unsigned char chunk = firstCharChunk | secondCharChunk;
    char chunkTranslated = base64Table[chunk];

    printChunk(chunkTranslated);
}

/**
 * second char 4 bit
 * third char 2 bit
 */
void createThirdChunk(char secondChar, char thirdChar)
{
    if (checkEndOfChar(secondChar))
    {
        printChunk('=');
        return;
    }
    else
    {
        
        unsigned char secondCharChunk = (secondChar & 0b00001111) << 2;
        unsigned char thirdCharChunk = checkEndOfChar(thirdChar) ? 0b00 : ((thirdChar & 0b11000000) >> 6);

        unsigned char chunk = secondCharChunk | thirdCharChunk;
        char chunkTranslated = base64Table[chunk];

        printChunk(chunkTranslated);
    }
}

void createFourthChunk(char secondChar, char thirdChar)
{
    if (checkEndOfChar(secondChar) || checkEndOfChar(thirdChar))
    {
        printChunk('=');
    }
    else
    {
        char thirdCharChunk = thirdChar & 0b00111111;
        char chunkTranslated = base64Table[thirdCharChunk];
        printChunk(chunkTranslated);
    }
}

void encodeBase64Chunk(const char *input)
{
    int i = 0;
    unsigned char firstChar = input[i];
    unsigned char secondChar = input[i + 1];
    unsigned char thirdChar = input[i + 2];
    
    createFirstChunk(firstChar);
    createSecondChunk(firstChar, secondChar);
    createThirdChunk(secondChar, thirdChar);
    createFourthChunk(secondChar, thirdChar);
}

void encodeBase64(const char *input)
{
    encodeBase64Chunk(input);   
}

int main()
{
    const char *args = "abc";
    const char *args2 = "xyz";

    printf("Encoded: ");
    encodeBase64(args);
    encodeBase64(args2);
    return 0;
}