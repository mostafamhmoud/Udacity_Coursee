#include "server.h"

uint8_t index;
ST_cardData_t* temp_cardData;

// name = pppppppppppppppppppppp
// expire date = 11/25  
// // pan          = 9066247151149104958   ,  6868412942323229877
// tansaction date = 12/06/2022




ST_accountsDB_t accounts[14] = { {50000.0 , "9487356400059680428"},
							{60000.0 ,      "0914447474043488801"},
							{70000.0 ,      "0964815387529318634"},
							{80000.0 ,      "9066247151149104958"},
							{90000.0 ,      "0367038827463011329"},
							{100000.0 ,     "3835980950073486792"},
							{150000.0 ,     "6868412942323229877"},
							{200000.0 ,     "6590286638054832752"},
							{250000.0 ,     "7976316762341054036"},
							{400000.0 ,     "6182323512056359755"},
							{3000 ,      "2034028783206245179"},
							{35000.0 ,      "7641457489025692005"},
							{450000.0 ,     "3310043318515717206"},
							{350000.0 ,     "9243418609240196255"}, };


ST_transaction ST_TransactionDB[255] = { 0 };

recieveTransactionData(ST_transaction* transData)
{
	ST_terminalData_t* ptr_terminal;
	ST_cardData_t* ptr_card;
	ptr_card = &transData->cardHolderData;
	ptr_terminal = &transData->terminalData;



	if (saveTransaction(transData) == SAVING_FAILED)
	{
		return INTERNAL_SERVER_ERROR;
	}

	if (isValidAccount(ptr_card) != OK)
	{
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(ptr_terminal) != OK)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}

	accounts[index].balance = accounts[index].balance - transData->terminalData.transAmount;
	current_balance = accounts[index].balance;
	
	return APPROVED;
}

isValidAccount(ST_cardData_t* cardData)
{
	uint8_t i = 0, j = 0;

		while (j != 14)   // 14 is number of data base in our global array 
		{
			while (cardData->primaryAccountNumber[i] != 0)
			{
				if (cardData->primaryAccountNumber[i] != accounts[j].primaryAccountNumber[i])
				{
					break;  // if any number in primaryAccountNumber doesn't equal will break the closest while loop 
				}

				else if (cardData->primaryAccountNumber[i] == accounts[j].primaryAccountNumber[i])
				{
					// if all numbers are equal and the  next character is NULL which is end of string 

					if (cardData->primaryAccountNumber[i + 1] == 0)
					{
						index = j; // we use index to mark this PIN so we will not search again in function isAmountAvailable
						return OK;
					}
				}
				i++;
			}
			j++;
		}
	
	return DECLINED_STOLEN_CARD;

}

isAmountAvailable(ST_terminalData_t* termData)
{
		if ((termData->transAmount) <= (accounts[index].balance))
		{
			return OK;
		}
		else
		{
			return LOW_BALANCE;
		}
	
}

saveTransaction(ST_transaction* transData)
{
	
	ST_terminalData_t* ptr_terminal;
	ST_cardData_t* ptr_card;
	ptr_card = &transData->cardHolderData;
	ptr_terminal = &transData->terminalData;

	if ((isValidAccount(ptr_card) == OK) & (isTransactionDate_Valid(ptr_terminal->transactionDate) == VALID))
	{
		 
			// save card data
			for (uint8_t i = 0; i < 25; i++)
			{
				ST_TransactionDB[index].cardHolderData.cardHolderName[i] = transData->cardHolderData.cardHolderName[i];
			}

			for (uint8_t i = 0; i < 6; i++)
			{
				ST_TransactionDB[index].cardHolderData.cardExpirationDate[i] = transData->cardHolderData.cardExpirationDate[i];
			}

			for (uint8_t i = 0; i < 20; i++)
			{
				ST_TransactionDB[index].cardHolderData.primaryAccountNumber[i] = transData->cardHolderData.primaryAccountNumber[i];
			}

			// save terminal data

			ST_TransactionDB[index].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
			ST_TransactionDB[index].terminalData.transAmount = transData->terminalData.transAmount;
			for (uint8_t i = 0; i < 11; i++)
			{
				ST_TransactionDB[index].terminalData.transactionDate[i] = transData->terminalData.transactionDate;
			}

			if (isAmountAvailable(ptr_terminal) == OK)
			{
				ST_TransactionDB[index].transState = APPROVED;
				static increment = 1000;
				ST_TransactionDB[index].transactionSequenceNumber = increment;
				increment++;
				return OK;
			}
			else
			{
				ST_TransactionDB[index].transState = DECLINED_INSUFFECIENT_FUND;
			}


	}

	else
	{
		return SAVING_FAILED;
	}
}

getTransaction(uint32_t transactionSequenceNumber, ST_transaction* transData)
{
	for (uint8_t i = 0; i < 14 ; i++)
	{
		if (ST_TransactionDB[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			return OK;
		}

	}

	return TRANSACTION_NOT_FOUND;
}


void save_ST_transaction(ST_cardData_t* cardData, ST_terminalData_t* termData, ST_transaction* transData)
{
	// save card data
	for (uint8_t i = 0; i < 25; i++)
	{
		transData->cardHolderData.cardHolderName[i] = cardData->cardHolderName[i];
	}

	for (uint8_t i = 0; i < 6; i++)
	{
		transData->cardHolderData.cardExpirationDate[i] = cardData->cardExpirationDate[i];
	}

	for (uint8_t i = 0; i < 20; i++)
	{
		transData->cardHolderData.primaryAccountNumber[i] = cardData->primaryAccountNumber[i];
	}

	// save terminal data

	transData->terminalData.maxTransAmount = termData->maxTransAmount;
	transData->terminalData.transAmount = termData->transAmount;
	for (uint8_t i = 0; i < 11; i++)
	{
		transData->terminalData.transactionDate[i] = termData->transactionDate[i];
	}
}
	 









