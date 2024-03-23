typedef struct Time
{
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;
}Time;

typedef struct document{
    char cardNumber[20];
    char password[10];
    int balance;
    Time date;
    int Flag_Illegal;
    int summary;
    int usedTime;
    struct document * next;
    int cardNum;
}document, *cardList, *pointer;

extern cardList Card;
extern cardList TAIL;