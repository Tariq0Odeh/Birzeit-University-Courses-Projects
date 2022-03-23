#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    int is_armstrong(int num);
    int is_magical (int num);


    int main()
{
   FILE *in, *out;
   int n , mag, arm ;

   in = fopen("numbers.txt","r");
        if (in == NULL)
        {
        printf("The files does not exist\n");
        exit(0);
        }

   out = fopen("outfile.txt","w");


   while(fscanf(in,"%d",&n) != EOF)
        {
            arm = is_armstrong(n);
            mag = is_magical(n);

    if (arm==1 && mag==1)
         fprintf(out," (%d) is armstrong and magical number\n",n);
    else if (arm==1)
         fprintf(out," (%d) is armstrong number\n",n);
    else if (mag==1)
         fprintf(out," (%d) is magical number\n",n);
    else
         fprintf(out," (%d) is neither armstrong nor magical number\n",n);
        }

    return 0;
}

    int is_armstrong(int num)
{
    int rem ,c;
    int counter=0 , sum=0;
    int temp= num;
    int x =num;

    while (x!=0)
        {
        x = x/10;
        counter++;
        }

    while (num!=0)
        {
        rem= num%10;
        c= pow(rem,counter);
        sum =sum+c;
        num =num/10;
        }

    if (sum == temp)
        return (1);
    else
        return (0);
}



    int is_magical (int num)
{
    int a= num ;
    int r,sum ;

    while(1)
    {
        sum =0 ;
    while( a != 0)
    {
        r = a%10;
        sum = sum + r;
        a = a /10 ;
    }

    if (sum<=9&&sum>=0)
        break ;
    else
        a = sum ;

    }

    if (sum==1)
        return (1);
    else
        return (0);
}
