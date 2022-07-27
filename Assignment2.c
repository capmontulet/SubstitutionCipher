#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definitions for readability
#define alphabetLength 26
#define cipher "AOYQO ALI YUNPUKPX SH BPUWPF YU 1939, ALI LU PTPQKFYQLT BEKEF-XFYNPU QYVOPF BLQOYUP YUKPUXPX PNPUKJLTTH KE FPVTLQP KOP IKLUXLFX PUYZBL. KOP IZ-39 OLX L"


//forward declaration of functions
void doFrequencyAnalysis(char *ciphertext, int *charfreq);
void sortFrequencyAddresses(int *pcharfreq, int **pAlphasort);
int compare(const void *x_void, const void *y_void);
void displayFrequencyAnalysis(int **pAlpha, int *charFreq, char *cipherText);
void swapCipherTextChars(char *pCipherText);


int main(void){
//text to be decrypted, pointer to char array
char cipherText[] = cipher;
char *pCipherText = cipherText;

/* char freq used to store the number of occurrences of each character 
*  found in the cipherText[] array during each iteration of the decryption process.
*  e.g. num of A's is stored in [0], num of B's is stored in [1]
*/
int charFreq[alphabetLength]={0}, *pCharFreq = charFreq;

/* An array of pointers to ints stored in charFreq[].
*  [0] stores the address of the charfreq element that contains the highest number.
*/
int* alphaSort[alphabetLength] = {'\0'};


while(1){
    displayFrequencyAnalysis(alphaSort, pCharFreq, pCipherText);
    //loops between displaying and replacing
    swapCipherTextChars(pCipherText);
}


}

void doFrequencyAnalysis(char *pCipherText, int *pCharFreq){
    char letterCompare = 'A';
    int count = 0;
    //loop 26 times for number of alphabet chars
    for(int i = 0; i<alphabetLength; i++){
        //loops length of the cipher 26 times
        for(int j = 0; j<strlen(pCipherText);j++){
            if(letterCompare == *(pCipherText+j)){
                count++;
            }
        }
        *(pCharFreq + i) = count;
        //increment char to compare to
        letterCompare++;
        //reset count each loop
        count=0;
    }
}


void sortFrequencyAddresses(int *pCharFreq, int **alphaSort){
    char letterCompare = 'A';
    
    //temporary array to leave charFreq unchanged
    int temp[alphabetLength]={0}, *pTemp = temp;
    for(int i=0;i<alphabetLength;i++){
        *(pTemp+i)=*(pCharFreq+i);
    }
    //cloning temp to alphaSort
    for(int i = 0; i<alphabetLength;i++){
        *(alphaSort+i)=(pTemp+i);
    }
    //sorting alphasort addresses
    qsort(alphaSort, alphabetLength, sizeof(int *), compare);

    //printing 
    for(int i = 0; i<alphabetLength; i++){
        printf("Frequency of %c: %d\t", letterCompare, *(pCharFreq+i));
        letterCompare++;

        //i had to look up the ascii table to get correct output. I have an offset of decimal number 48. I do not know why.
        printf("Letters Descending: %c\t%d\n", (*(alphaSort+i)-pCharFreq)+'A'+48, **(alphaSort+i));
    }


}

//qsort function sorts by descending values
int compare(const void *x_void, const void *y_void){
    int *x = *(int **)x_void;
    int *y = *(int **)y_void;
    return *y-*x;
}


void displayFrequencyAnalysis(int **alphaSort, int *pCharFreq, char *pCipherText){
    doFrequencyAnalysis(pCipherText, pCharFreq);
    sortFrequencyAddresses(pCharFreq, alphaSort);
    printf("\nHint, most commonly used letters are ETAOIN SHRDLU\n");
    printf("\nCipher: %s", pCipherText);
    

}


void swapCipherTextChars(char *pCipherText){
    char subChar =' ';
    char swapChar=' ';
    printf("\nEnter char to substitute: ");
    scanf(" %c", &subChar);
    printf("\nSwap with this character: ");
    scanf(" %c", &swapChar);
    fflush(stdin);
    
    //loops through the cipher, if it encounters either chars to be swapped, it swaps them
    for(int i = 0; i<strlen(pCipherText);i++){
        if(*(pCipherText+i)==subChar){
            *(pCipherText+i)=swapChar;
        }else if(*(pCipherText+i)==swapChar){
            *(pCipherText+i)=subChar;
        }
    }
    system("clear");
}
