/**
 * @file billing.c
 * @author Anurag Tiwari (anuragrkt46@gmail.com)
 * @brief Billing System to keep the record of a customer 
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

 void input();
 void writefile();
 void search();
 void output();

 struct date{
       int month;
       int day;
       int year;
       };

  struct account {
    int number;
    char name[100];
    int acct_no;
    float mobile_no;
    char street[100];
    char city[100];
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    struct date lastpayment;
  }customer;
  int tl,sl,ts;
 void main()
    {
      int i,n;
      char ch;
      system("cls");

      printf("\e[?25l");
      printf("   CUSTOMER BILLING SYSTEM:\n\n");
      printf("===============================\n");
      printf("\n1:    to add account on list\n");
      printf("2:    to search customer account\n");
      printf("3:    exit\n");
      printf("\n================================\n");
      do{
           printf("\nselect what do you want to do?");
           ch=getche();
      }while(ch<='0' || ch>'3');
      switch(ch){
        case '1':
            system("cls");
            printf("\nhow many customer accounts?");
            scanf("%d",&n);
            for(i=0;i<n;i++){
                input();
                if(customer.payment>0)
                    customer.acct_type=(customer.payment<0.1*customer.oldbalance)? 'O': 'D';
                else
                    customer.acct_type=(customer.oldbalance>0)?'D' : 'C';
                customer.newbalance=customer.oldbalance - customer.payment;
                writefile();
            }
            main();
        case '2':
            system("cls");
            printf("search by what?\n");
            printf("\n1 --- search by customer number\n");
            printf("2 --- search by customer name\n");
            search();
            ch=getche();
            main();
        case '3':
            system("cls");
            printf("/033[0;31m");
            void gotoxy(int x, int y)
{
            COORD c = { 25, 25};  
            SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}
            _cprintf("\nA PROJECT BY ANURAG TIWARI");
            exit(1);
      }
 }

   void input()
    {
      FILE *fp=fopen("bidur.dat","rb");
      fseek (fp,0,SEEK_END);
      tl=ftell(fp);
      sl=sizeof(customer);
      ts=tl/sl;
      fseek(fp,(ts-1)*sl,SEEK_SET);
      fread(&customer,sizeof(customer),1,fp);
      printf("\ncustomer no:%d\n",++customer.number);
      fclose(fp);
      printf("         Account number:");
      scanf("%d",&customer.acct_no);
      printf("\n       Name:");
      scanf("%s",customer.name);
      printf("\n       mobile no:");
      scanf("%f",&customer.mobile_no);
      printf("         Street:");
      scanf("%s",customer.street);
      printf("         City:");
      scanf("%s",customer.city);
      printf("         Previous balance:");
      scanf("%f",&customer.oldbalance);
      printf("         Current payment:");
      scanf("%f",&customer.payment);
      printf("         Payment date(mm/dd/yyyy):");
      scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
      return;
   }

   void writefile()
   {
      FILE *fp;
      fp=fopen("bidur.dat","ab");
      fwrite(&customer,sizeof(customer),1,fp);
      fclose(fp);
      return;
   }

   void search()
   {
     char ch;
     char nam[100];
     int n,i,m=1;
     FILE *fp;
     fp=fopen("bidur.dat","rb");
     do{
        printf("\nenter your choice:");
        ch=getche();
     }while(ch!='1' && ch!='2');
     switch(ch){
          case '1':
            fseek(fp,0,SEEK_END);
            tl=ftell(fp);
            sl=sizeof(customer);
            ts=tl/sl;
            do{
            printf("\nchoose customer number:");
            scanf("%d",&n);
            if(n<=0 || n>ts)
            printf("\nenter correct\n");
            else{
                fseek(fp,(n-1)*sl,SEEK_SET);
                fread(&customer,sl,1,fp);
                output();
            }
            printf("\n\nagain?(y/n)");
            ch=getche();
            }while(ch=='y');
            fclose(fp);
            break;
          case '2':
            fseek(fp,0,SEEK_END);
            tl=ftell(fp);
            sl=sizeof(customer);
            ts=tl/sl;
            fseek(fp,(ts-1)*sl,SEEK_SET);
            fread(&customer,sizeof(customer),1,fp);
            n=customer.number;

            do{
            printf("\nenter the name:");
            scanf("%s",nam);
            fseek(fp,0,SEEK_SET);
            for(i=1;i<=n;i++)
            {
                 fread(&customer,sizeof(customer),1,fp);
                 if(strcmp(customer.name,nam)==0)
                 {
                output();
                m=0;
                break;
                 }
            }
            if(m!=0)
            printf("\n\ndoesn't exist\n");
            printf("\nanother?(y/n)");
            ch=getche();
            }while(ch=='y');
            fclose(fp);
          }
          return;
     }


   void output()
     {
       printf("\n\n    Customer no    :%d\n",customer.number);
       printf("    Name        :%s\n",customer.name);
       printf("    Mobile no      :%.f\n",customer.mobile_no);
       printf("    Account number :%d\n",customer.acct_no);
       printf("    Street         :%s\n",customer.street);
       printf("    City           :%s\n",customer.city);
       printf("    Old balance    :%.2f\n",customer.oldbalance);
       printf("    Current payment:%.2f\n",customer.payment);
       printf("    New balance    :%.2f\n",customer.newbalance);
       printf("    Payment date   :%d/%d/%d\n\n",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year);
       printf("    Account status :");
       switch(customer.acct_type)
          {
          case 'C':
         _cprintf("CURRENT\n\n");
         break;
          case 'O':
         _cprintf("OVERDUE\n\n");
         break;
          case 'D':
         _cprintf("DELINQUENT\n\n");
         break;
          default:
         _cprintf("ERROR\\n\n");
          }
          printf("\033[0;37m");
          return;
       }
