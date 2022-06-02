//---------------------------------------------------------------------------

#include <fmx.h>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#pragma hdrstop

#include "Quest.h"

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

class Player{
public:
char* name;
int* health;
int* armor;
int* damage;
Player();
Player(char *name, int* health,int* armor,int* damage);
};

class Enemy{
public:
char* name;
int* health;
int* armor;
int* damage;
Enemy();
Enemy(char *name, int* health,int* armor,int* damage);

};

TQuestForm *QuestForm;
//---------------------------------------------------------------------------
__fastcall TQuestForm::TQuestForm(TComponent* Owner)
	: TForm(Owner)
{

}


//---------------------------------------------------------------------------


