#include <stdio.h>
#include <string.h>
//#include <string.h>
#include "std_header.h"
#include "app.h"

#ifndef STOLLEN_CARD
#define STOLLEN_CARD "6868412942323229877"
#endif // !1

// name = pppppppppppppppppppppp
// expire date = 11/25  
// // pan          = 9066247151149104958   ,  6868412942323229877 , 2034028783206245179 = amount 3000
// tansaction date = 12/06/2022



void main()
{


	/*appStart();*/
	ST_cardData_t card_data;
	ST_terminalData_t terminal_data;
	ST_transaction transaction;

	ST_cardData_t* ptr_card = &card_data;
	ST_terminalData_t* ptr_terminal = &terminal_data;
	ST_transaction* ptr_transaction = &transaction;






	// get  card data 
	while ((getCardHolderName(ptr_card) == WRONG_NAME) == 1)
	{
		puts(" wrong NAME , please enter right NAME ");
	}

	while (getCardExpiryDate(ptr_card) == WRONG_EXP_DATE)
	{
		puts(" wrong EXPIRYDATE , please enter right EXPRE DATE ");
	}

	while (getCardPAN(ptr_card) == WRONG_PAN)
	{
		puts(" wrong PAN , please enter right PAN ");
	}

	// get terminal data
	while ((getTransactionDate(ptr_terminal) == WRONG_DATE) == 1)
	{
		puts(" wrong DATE , please enter right DATE ");
	}

	if (isCardExpired(card_data, terminal_data) != EXPIRED_CARD)
	{
		if (strcmp(STOLLEN_CARD, ptr_card->primaryAccountNumber) == 0)
		{
			printf(" declined transaction , stolen card ") ;
		}
		else
		{
			setMaxAmount(ptr_terminal);
			if (getTransactionAmount(ptr_terminal) == OK)
			{
				if (isBelowMaxAmount(ptr_terminal) == EXCEED_MAX_AMOUNT)
				{
					puts(" exeed max amount , transaction declined");
				}

				else
				{
					save_ST_transaction(ptr_card, ptr_terminal, ptr_transaction);

					if (recieveTransactionData(ptr_transaction) == APPROVED)
					{
						printf(" transaction approved , current balance = %f", current_balance);
					}

					else if (recieveTransactionData(ptr_transaction) == INTERNAL_SERVER_ERROR)
					{
						printf(" INTERNAL_SERVER_ERROR ");
					}

					else if (recieveTransactionData(ptr_transaction) == DECLINED_STOLEN_CARD)
					{
						printf(" DECLINED_STOLEN_CARD ");
					}

					else if (recieveTransactionData(ptr_transaction) == DECLINED_INSUFFECIENT_FUND)
					{
						printf(" DECLINED_INSUFFECIENT_FUND ");
					}
				}


			}
		}
	}
	else
	{
		puts(" Card Expired , declined transaction ");
	}

}