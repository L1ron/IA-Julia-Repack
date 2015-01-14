// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //


#ifndef SOCKET_H
#define SOCKET_H

class cSocket
{
public:
    void Load();
    void ResetConfig();

    struct sConfig
    {
        int Type;
        int Index;
    } Items[255];
    int Count;

};
extern cSocket Socket;
BYTE CheckItemType(int iItemNumber);
#endif
