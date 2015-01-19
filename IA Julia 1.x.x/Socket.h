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
