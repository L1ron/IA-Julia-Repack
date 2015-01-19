#ifndef HappyHour_h
#define HappyHour_h

#include "User.h"

class cHappyHour
{
public:
    void ResetConfig();
    void Load();
    void TickTimerHappyHour();
    int IsHappyHour(int Map);
    void CheckNeedMessage(int i);

    int HappyHoursNumber;
    int HappyHourEnabled;

    struct
    {
        int MapNum;
        int P_Zen;
        int P_Drop;
        int P_Exp;
        int S_WeekDay;
        int S_Hour;
        int S_Min;
        int T_Delay;

        int C_WeekDay;
        int C_Hour;
        int C_Min;
        bool Started;
    } HappyStruct[128];

    int MessageTimeBefore[64];
    int MessageTimeBeforeCount;
    int MessageTimeAfter[64];
    int MessageTimeAfterCount;
};

extern cHappyHour HappyHour;

#endif