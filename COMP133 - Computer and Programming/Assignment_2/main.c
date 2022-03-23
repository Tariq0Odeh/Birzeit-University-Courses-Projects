#include <stdio.h>


    #define THE_HEIGHT 8
    #define THE_WIDTH  1


int main()                                                  //1190695
                                                            //Yazan Hakawati
{
    FILE *in;

      double x;
      int a;
      int b;

    in=fopen("test.txt", "r");

    if (in == NULL)
    {
        printf("The files does nor exist\n");
        exit(0);
    }

    printf("Reading input from text file\n");

    int charge;

    for(a =0 ; a < THE_HEIGHT ; a++){
        for (b = 0 ; b < THE_WIDTH ; b++){
            fscanf(in ,"%lf" , &x);


    }
  }
}
