#include <time.h>

typedef struct Time
{
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;
    unsigned long timestamp;
}Time;

typedef struct document{
    char cardNumber[20];
    char password[10];
    float balance;
    Time date;
    int Flag_Illegal;
    float summary; // Summary of amount
    int usedTime;
    struct document * next;
    int cardNum;
    int nStatus; // 0 -> Not Checkout ; 1 -> Checkout
    int nDel; // 0 -> Exist ; 1 -> Deleted
}document, *cardList, *pointer;

typedef struct Billing
{
    char cardNumber[20];

    long int tStart;
    long int tEnd;
    float fAmount;
    int nStatus;
    int nDel;
    int billingNum;
    struct Billing * next;
}Billing, *BillingList;

extern cardList Card;
extern cardList TAIL;
extern char CardFilename[];
extern char BillingFilename[];
extern int debugFlag;

extern BillingList BList;
extern BillingList BListTAIL;
