#include "terminal.h"
#include <stdio.h>



#define MAX_AMOUNT 5000.0

getTransactionDate(ST_terminalData_t* termData)
{

    puts(" enter transaction date in form DD/MM/YY : ");
    gets(termData->transactionDate);
    if (isTransactionDate_Valid(termData->transactionDate) == NOT_VALID) return WRONG_DATE;

    return OK;

	//uint8_t t_date[11];
 //   int month, day, year;
 //   uint8_t flag1 = 0;
     //gets(t_date);

    

 //   if ((t_date[2] != '/') | (t_date[5] != '/'))
 //   {
 //       printf("im here line 14");
 //       flag1 = 1;
 //   }

 //   for (int i = 0; i < 11; i++)
 //   {
 //       t_date[i] = t_date[i] - 48;
 //   }

 //   day = 10 * t_date[0] + t_date[1];
 //   if ((day < 0) | (day > 30))
 //   {
 //       printf("im here line 25");
 //       flag1 = 1;
 //   }
 //   month = 10 * t_date[3] + t_date[4];
 //   if ((month < 0) | (month > 12))
 //   {
 //       printf("im here line 31");
 //       flag1 = 1;
 //   }
 //   year = 1000 * t_date[6] + 100 * t_date[7] + 10 * t_date[8] + t_date[9];
 //

 //   for (int i = 0; i < 11; i++)
 //   {
 //       if ((t_date[i] == NULL))
 //       {
 //           // check for invalid year 
 //           for (uint8_t a = 6; a < 9; a++)
 //           {
 //               if (t_date[6] != 2)
 //               {
 //                   flag1 = 1;
 //                   printf("im here line 41");
 //               }
 //               else if((t_date[a + 1] < 0) | (t_date[a + 1] > 9))
 //               {
 //                   flag1 = 1 ;
 //                   printf("im here line 45");
 //               }
 //           }

 //           if (( i != 10) | (flag1 == 1 ) )
 //           {
 //               return WRONG_DATE;
 //           }
 //           else
 //           {
 //               return OK;
 //           }
 //       }
 //   }

 

}

isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
        // we are here , we made sure that expire date and trasaction date are legal
       // example : trasaction date : 22/09/2022 , expred date = 05/24
    if (cardData.cardExpirationDate[4] < termData.transactionDate[8])
    {   
        return EXPIRED_CARD;
    }

    else if (cardData.cardExpirationDate[4] == termData.transactionDate[8]) // if in the same year we compare months 
    {
        uint8_t tran_month, expired_month;
        
        tran_month = 10 * termData.transactionDate[3] + termData.transactionDate[4];
        expired_month = 10 * cardData.cardExpirationDate[0] + cardData.cardExpirationDate[1];
        
        if (expired_month < tran_month)
        {
            return EXPIRED_CARD;
        }
    }

    else
    {
        return OK;
    }
}

getTransactionAmount(ST_terminalData_t* termData)
{
    puts(" enter transaction amount : ");
    scanf_s("%f", &termData->transAmount);
    if (termData->transAmount <= 0) return INVALID_AMOUNT;
    else
    {
        return OK;
    }
}

isBelowMaxAmount(ST_terminalData_t* termData)
{
    if ((termData->transAmount) > (termData->maxTransAmount)) return EXCEED_MAX_AMOUNT;
    else
    {
        return OK;
    }
}


setMaxAmount(ST_terminalData_t* termData)
{
    float max_amount = MAX_AMOUNT;
    puts(" note : max amount is 5000 ");
    /*scanf_s("%f", &max_amount);*/
    if (max_amount <= 0) return INVALID_MAX_AMOUNT;
    else
    {
        termData->maxTransAmount = max_amount;
        return OK;
    }
}



uint8_t isTransactionDate_Valid(uint8_t* ptr)
{
    uint8_t date[11], month, day, flag = 0;
    int year;

    // copy data to work with
    for (uint8_t i = 0; i < 11; i++) date[i] = ptr[i];

    if ((date[2] != '/') & (date[5] != '/'))
    {
        return NOT_VALID;
    }
    // convert Ascii to int to deal with
    for (uint8_t i = 0; i < 11; i++)
    {
        date[i] = date[i] - 48;
    }
    // make sure that day , month and year are numbers

    for (uint8_t i = 0; i < 10; i++)
    {
        if ((i != 2) & (i != 5))
        {
            if ((date[i] >= 0) & (date[i] <= 9))
            {

            }
            else
            {
                return NOT_VALID;

            }
        }
    }

    day = 10 * date[0] + date[1];
    if ((day > 30) | (day < 0))
    {
        return NOT_VALID;
    }
    month = 10 * date[3] + date[4];
    if ((month > 12) | (month < 0))
    {
        return NOT_VALID;
    }

    return VALID;

}

isValidCardPAN(ST_cardData_t* cardData)
{
    for (uint8_t i = 0; i < 20; i++)
    {
        if (cardData->primaryAccountNumber[i] != NULL)
        {
            if ((cardData->primaryAccountNumber[i] >= 48) & (cardData->primaryAccountNumber[i] <= 57) == 0)
            {
                return INVALID_CARD;
            }
        }
        else
        {
            return OK;
        }
    }
}