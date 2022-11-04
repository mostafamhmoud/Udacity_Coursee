#include "card.h"
#include "terminal.h"

#ifndef SERVER_H
#define SERVER_H

typedef enum EN_serverError_t
{
	OK3, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transStat_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction;


EN_transStat_t recieveTransactionData(ST_transaction* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction* transData);

void save_ST_transaction(ST_cardData_t* cardData, ST_terminalData_t* termData, ST_transaction* transData);

float current_balance;


//ST_accountsDB_t accounts[14] = { {50000.0 , "9487356400059680428"},
//							{60000.0 ,      "0914447474043488801"},
//							{70000.0 ,      "0964815387529318634"},
//							{80000.0 ,      "9066247151149104958"},
//							{90000.0 ,      "0367038827463011329"},
//							{100000.0 ,     "3835980950073486792"},
//							{150000.0 ,     "6868412942323229877"},
//							{200000.0 ,     "6590286638054832752"},
//							{250000.0 ,     "7976316762341054036"},
//							{400000.0 ,     "6182323512056359755"},
//							{40000.0 ,      "2034028783206245179"},
//							{35000.0 ,      "7641457489025692005"},
//							{450000.0 ,     "3310043318515717206"},
//							{350000.0 ,     "9243418609240196255"}, };
//
//uint8_t index;
//ST_cardData_t* temp_cardData;



#endif // !SERVER_H
