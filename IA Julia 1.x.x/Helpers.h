#ifndef HELPERS_H
#define HELPERS_H

#include "User.h"

class cHelpers
{
	public:
		void Load();

		void HelperEllenClick(LPOBJ gObj, LPOBJ gObjNPC);
		void HelperLukeClick(LPOBJ gObj, LPOBJ gObjNPC);
		void HelperLeoClick(LPOBJ gObj, LPOBJ gObjNPC);

		struct sConfig
		{
			int EnableEllen;
			int EnableLuke;
			int EnableLeo;
		} Config;
	
};

extern cHelpers Helpers;

#endif