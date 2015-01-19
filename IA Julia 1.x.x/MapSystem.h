#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

class cMapSystem
{
	public:
		void ResetConfig();
		void Load();

		int Enabled;
		struct Conf
		{
			int Zen;
			int Drop;
			int Exp;
			int PVP;
		} Maps[255];
};

extern cMapSystem MapSystem;

#endif