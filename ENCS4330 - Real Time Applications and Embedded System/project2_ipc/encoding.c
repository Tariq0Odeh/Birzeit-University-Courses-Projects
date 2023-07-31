#include "local.h"

void encoding(int linesNum,int colNum,char ** fullColumn);
void decoding(int linesNum,int colNum,char ** fullColumn);

int main(int argc, char **argv) {
    int colnum = 1; // this value come from the sender procces
    encoding(argc,colnum,argv);
    for(int i=1;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    decoding(argc,colnum,argv);
    for(int i=1;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    return 0;
}
/*
    This method is used to encode the Full column
    all details is the opposite of the decoding method  
*/
void encoding(int linesNum,int colNum,char **fullColumn){
    // go through all the words in the column
    for(int i=1;i<linesNum;i++){
        // here we multiply by 7, because the digit 0 will be converted to 1,000,000 (7 characters)
        char* tempString = (char*)malloc(sizeof(char) * strlen(fullColumn[i]) * 7);
        // go through all characters in each word
        for(int j=0;j<strlen(fullColumn[i]);j++){
            int flag = 0;
            int tmp;
            // if the char was Upper case alphabet
            if(fullColumn[i][j]>=65 && fullColumn[i][j] <= 90){
                tmp = fullColumn[i][j];
                tmp = 65 + (tmp-65+(j+1)*colNum)%26;
            }
            // if the char was Lower case alphabet
            else if(fullColumn[i][j]>=97 && fullColumn[i][j] <= 122){
                tmp = fullColumn[i][j];
                tmp = 97 + (tmp-97+(j+1)*colNum)%26;
            }
            // if the char was digit
            else if(fullColumn[i][j]>=48 && fullColumn[i][j] <= 57){
                tmp = fullColumn[i][j]-48;
                tmp = 1000000-tmp;
                flag = 1;
            }
            // if the char was other 6 possible characters (%?,!;:)
            else {
                switch(fullColumn[i][j]) {
                    case '!':
                        tmp = 48 + 1;
                    break;
                    case '?':
                        tmp = 48 + 2;
                    break;
                    case ',':
                        tmp = 48 + 3;
                    break;
                    case ';':
                        tmp = 48 + 4;
                    break;
                    case ':':
                        tmp = 48 + 5;
                    break;
                    case '%':
                        tmp = 48 + 6;
                    break;
                    default:
                        tmp = 32 ;
                }
            }
            // any case except the digit case, because each digit will be 6 digits or even 7
            if(!flag){
                char result[2] ;
                sprintf(result, "%c", tmp);
                strcat(tempString, result);
            }
            // if the char was a digit
            else {
                sprintf(tempString,"%s%d",tempString,tmp);
            }
        }
        // to save back the encoded result in the orignal text
        fullColumn[i] = tempString;
    }
}
/*
    This method is used to decode the Full column
    all details is the opposite of the encoding method  
*/
void decoding(int linesNum,int colNum,char ** fullColumn){
    // go through all the words in the column
    for(int i=1;i<linesNum;i++){
        char* tempString = (char*)malloc(sizeof(char) * strlen(fullColumn[i]));
        // go through all characters in each word
        int counter = 1;
        for(int j=0;j<strlen(fullColumn[i]);j++){
            int tmp;
            // if the char was Upper case alphabet
            if(fullColumn[i][j]>=65 && fullColumn[i][j] <= 90){
                tmp = fullColumn[i][j];
                tmp = 65 + (((tmp-65-counter*colNum)%26)+26)%26;
            }
            // if the char was Lower case alphabet
            else if(fullColumn[i][j]>=97 && fullColumn[i][j] <= 122){
                tmp = fullColumn[i][j];
                tmp = 97 + (((tmp-97-counter*colNum)%26)+26)%26;
            }
            // if the char was 9, which means it was a digit so we will go to the +5 character and 
            // check the orignal value
            else if(fullColumn[i][j] == 57){
                tmp = 58-fullColumn[i][j+5]+48;
                j+=5;
            }
            // if the char was 1 and the next char is 0, it means the value is 1,000,000. 
            // which means it was 0 digit
            else if(fullColumn[i][j] == 49 && j+1<strlen(fullColumn[i]) && fullColumn[i][j+1] == 48){
                tmp = 48;
                j+=6;
            }
            // if the char was other 6 possible characters (%?,!;:)
            else {
                switch(fullColumn[i][j]) {
                    case '1':
                        tmp = 33;
                    break;
                    case '2':
                        tmp = 63;
                    break;
                    case '3':
                        tmp = 44;
                    break;
                    case '4':
                        tmp = 59;
                    break;
                    case '5':
                        tmp = 58;
                    break;
                    case '6':
                        tmp = 37;
                    break;
                    default:
                        tmp = 32 ;
                }
            }
            char result[2] ;
            sprintf(result, "%c", tmp);
            strcat(tempString, result);
            counter++;
        }
        
        // to save back the encoded result in the orignal text
        fullColumn[i] = tempString;
    }
}