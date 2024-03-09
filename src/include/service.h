#include <time.h>

typedef struct Date{
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;
}Date;

typedef struct document{
    char cardNumber[20];
    char password[10];
    int balance;
    int status;
    __uint64_t summarySpent;
    Date lastTimeUsed;
}document;

void addCard(char[]);

void queryCard(char[]);

void online();

void offline();

void charge();

void chargeBack();

void querySummary();

void deleteCard();