#include <stdio.h>
#include "card.h"


getCardHolderName(ST_cardData_t* cardData)
{
	puts("please  enter name note: name must be in range 20 to 24 character: ");
 	gets(cardData->cardHolderName);
    

	for (uint8_t i = 0; i < 35 ; i++)
	{
		if (cardData->cardHolderName[i] == 0)
		{
			if ((i == 0) | (i < 20) | (i > 24))
			{
				return WRONG_NAME;
			}
			else 
			{
				return OK;
			}
		}
	}

}

getCardExpiryDate(ST_cardData_t* cardData)
{
	 uint8_t year, month;
	puts("please enter card expiry date in form MM/YY");
	gets(cardData->cardExpirationDate);
 

			month = 10 * (cardData->cardExpirationDate[0] -48) + (cardData->cardExpirationDate[1] -48);
			year = 10 * (cardData->cardExpirationDate[3] - 48) + (cardData->cardExpirationDate[4] - 48);

			if ((month <= 12) & (month != 0) & (year > 0) & (cardData->cardExpirationDate[2] == '/') & (cardData->cardExpirationDate[5] == NULL ))
			{
				return OK;
			}

			else
			{
				return WRONG_EXP_DATE;
			}
}

  getCardPAN(ST_cardData_t* cardData)
{
	  puts("please enter card PAN ");
	  gets(cardData->primaryAccountNumber);

	  for (uint8_t i = 0; i < 20; i++)
	  {
		  if (cardData->primaryAccountNumber[i] == NULL)
		  {
			  if ((i == 0) | (i < 16) | (i > 19))
			  {
				  return WRONG_PAN;
			  }
			  else
			  {
				  return OK;
			  }
		  }

	  }
	


}

	

