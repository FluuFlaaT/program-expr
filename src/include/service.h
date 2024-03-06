typedef struct document{
    char cardNumber[20];
    char password[10];
    int balance;
}document;

void addCard();

void queryCard();

void online();

void offline();

void charge();

void chargeBack();

void querySummary();

void deleteCard();