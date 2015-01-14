// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://mu.raklion.ru/						# //
// ================================================== //

#ifndef NEWS_H
#define NEWS_H

void NewsSystem(void * lpParam);
void FreeVersionAdv(void * lpParam);
class cNews
{
public:
    void ResetConfig();
    void Load();

    int Sections;
    struct sNews
    {
        char MSG[3][50];
        int Time;
        int Type;
    };

    struct sConfig
    {
        int IsNews;
    };

    sNews NewsSys[100];
    sConfig Config;
};
extern cNews News;
#endif