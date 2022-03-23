#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define len 8
#define tax 0.15


    typedef struct
{ 	    int e_num;
        char name[10];
        float hours;
        float rate;
        float total_salary;
        float tax_amount;
}       employee_record;


    FILE *data;
    FILE *out;

    void calculate(employee_record AR[]);
    void sort (employee_record AR []);


   int main()
{

        data = fopen("employees.txt","r");
        out = fopen("report.txt","w");
        employee_record AR[len];

            int c;
            if (!feof(data))
            {
                for (c = 0 ; c < len ; c++)
                {
                fscanf(data , "%d" , &AR[c].e_num);
                }
                fscanf(data , "\n");


                char before[111];
                    fgets(before , sizeof before , data);
                char *after=strtok(before , " ;,\n");

                int x , t;

                for( x = 0 ; x < len ; x++)
                    {strcpy(AR[x].name , after);
                    after = strtok(NULL , " ;,\n");}

                     for ( t = 0 ; t < len ; t++)
                {fscanf(data, "%f", &AR[t].hours);}

                     for ( t = 0; t < len ; t++)
                {fscanf(data, "%f", &AR[t].rate);}
            }


            calculate(AR);
            sort(AR);


            float net_Salary[len];
            int i;
            for( i = 0 ; i < len ; i++)
                {net_Salary[i] = AR[i].total_salary - AR[i].tax_amount;}

                fprintf(out,"  |Employee_Name|    |Total_Salary|    |Tax_Amount|    |Net_Salary|\n");
                fprintf(out,"  ***************    **************    ************    ************\n");

            for(int n =0 ; n < len ; n++)
                {fprintf(out,"%10s\t\t%.2f\t\t%.2f\t\t%.2f\n",AR[n].name,AR[n].total_salary,AR[n].tax_amount,net_Salary[n]);}


        fclose(data);
        fclose(out);

   return 0;
}


    void calculate(employee_record AR[])
{
        int x;
        for ( x = 0 ; x < len ; x++)
            {if (AR[x].hours <= 40)
            {
                AR[x].total_salary = AR[x].hours * AR[x].rate;
            }
            else
            {
                AR[x].total_salary = 40*AR[x].rate + (AR[x].hours-40)*AR[x].rate*1.5;
            }

                AR[x].tax_amount = tax * AR[x].total_salary;
            }
}


    void sort (employee_record AR [])
{
        int a , b;
        char name[10];
        float v;
        int z = len+1;
            for(a = 0 ; a < z ; a++){
                for(b = 0 ; b < z ; b++){
                    if(strcmp(AR[b].name,AR[b+1].name) > 0)
                    {
                    strcpy(name,AR[b].name);
                    strcpy(AR[b].name,AR[b+1].name);
                    strcpy(AR[b+1].name,name);

                    v = AR[b].total_salary;
                    AR[b].total_salary = AR[b+1].total_salary;
                    AR[b+1].total_salary = v;

                    v = AR[b].tax_amount;
                    AR[b].tax_amount = AR[b+1].tax_amount;
                    AR[b+1].tax_amount = v;}
                    }}
}
