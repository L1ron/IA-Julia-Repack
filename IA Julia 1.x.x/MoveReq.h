#ifndef MoveReq_H
#define MoveReq_H

class cMoveReq
{
public:
    void ResetConfig();
    void Load();
    int GetMapVip(int MapIndex);

    struct sMoveReq
    {
        int Index, Zen, Level, Gate, VIP;
        char MapName1[50], MapName2[50];
        int MapNumber;
    } MoveReqInfo[255];
    int Count;

    struct sGate
    {
        int Index, MapNumber;
        int VIP;
    } Gate[500];
};
extern cMoveReq MoveReq;
#endif