//---------------------------------------------------------------------------
#include <stdlib.h>
#include <time.h>
#include <fmx.h>
#include <string>
#include <array>
#include <queue>
#include <fstream>
#include <sstream>
#pragma hdrstop

#include "Quest.h"

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

class Robot{
   public:
   Robot(){
   }
   int getHealth(){
   return healthPoint;
   }
   void addHealth(int heal){
   healthPoint += heal;
   }
   void subtractHealth(int damage){
	healthPoint -= damage;
   }
   int getMAtk(){
   return meleeAttack;
   }
   void setMAtk(int newMAtk){
	meleeAttack = newMAtk;
   }
   int getSAtk(){
   return shootingAttack;
   }
   void setSAtk(int newSAtk){
	shootingAttack = newSAtk;
   }
   int getDefense(){
   return defensePoint;
   }
   void setDefense(int newDefense){
    defensePoint = newDefense;
   }

   AnsiString getMode(){
   return mode;
   }
   void setMode(AnsiString newMode){
   mode = newMode;
   }
   protected:
   int healthPoint;
   int meleeAttack;
   int shootingAttack;
   int defensePoint;

   AnsiString mode;
};
class Player: public Robot{
	public:
    Player(){}
	Player(int healthPoint,int meleeAttack, int shootingAttack,int defensePoint){
	Score = 0;
    maxHealth = healthPoint;
    this->healthPoint = healthPoint;
	this->meleeAttack = meleeAttack;
	this->shootingAttack = shootingAttack;
	this->defensePoint = defensePoint;
	}
	int getMaxHealth(){return maxHealth;}
    void setMaxHealth(int newMaxHealth){maxHealth = newMaxHealth;}
	bool getPhase(){
	return isAttackPhase;
	}
	void setPhase(bool newPhase){
	isAttackPhase = newPhase;
    }
	int getScore(){
	return Score;
	}
	void setScore(int newScore){
    Score = newScore;
    }
	private:
    int maxHealth;
	bool isAttackPhase;
	AnsiString meleeMode;
    AnsiString shootingMode;
	int Score;
};

class Enemy: public Robot{
   public:
   Enemy(){}
   Enemy(int healthPoint,int meleeAttack, int shootingAttack,int defensePoint  ){
	name = "New Enemy";
	this->healthPoint = healthPoint;
	this->meleeAttack = meleeAttack;
	this->shootingAttack = shootingAttack;
	this->defensePoint = defensePoint;
   }
   AnsiString getName(){
   return name;
   }
   void setName(AnsiString name){
	this->name = name;
   }
   private:
   AnsiString name;



};


int healthPoint = 100;
int meleeAttack = 15;
int shootingAttack = 15;
int defensePoint = 15;


Player player(healthPoint,meleeAttack,shootingAttack,defensePoint);



queue<Enemy> LoadEnemies(){
Enemy e1(30,15,15,15);
e1.setName("Bandit");
Enemy e2(40,20,20,20);
e2.setName("Bandit Lieutenant");
Enemy e3(50,25,25,25);
e3.setName("Bandit Commander");
queue<Enemy> enemies;
enemies.push(e1);
enemies.push(e2);
enemies.push(e3);
return enemies;
}



queue<Enemy> enemies;
Enemy currentEnemy;


TQuestForm *QuestForm;


//---------------------------------------------------------------------------
__fastcall TQuestForm::TQuestForm(TComponent* Owner)
	: TForm(Owner)
{

	enemies = LoadEnemies();
    currentEnemy = enemies.front();

    PlayerHealthLabel->Text = player.getHealth();
	PlayerMATKLabel->Text = player.getMAtk();
	PlayerSATKLabel->Text = player.getSAtk();
	PlayerDefenseLabel->Text = player.getDefense();



	EnemyNameLabel->Text = currentEnemy.getName();
	EnemyHealthLabel->Text = currentEnemy.getHealth();
	EnemyMATKLabel->Text = currentEnemy.getMAtk();
	EnemySATKLabel->Text = currentEnemy.getSAtk();
	EnemyDefenseLabel->Text = currentEnemy.getDefense();


	enemies.pop();


}


//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
// RNG Function which returns an int value based on (parameter input-1)
int generateRandomNumber(int limit){
srand(time(NULL));
int randomNumber = rand()%limit;
return randomNumber;
}

void generatePlayerPhase(){
int randomNumber = generateRandomNumber(2);
switch (randomNumber){
	case 0:player.setPhase(true);break;
	case 1:player.setPhase(false);break;
	default: break;
}
}
//---------------------------------------------------------------------------
void generateEnemyMode(){
int randomNumber = generateRandomNumber(2);
switch (randomNumber){
	case 0:currentEnemy.setMode("Melee");break;
	case 1:currentEnemy.setMode("Shooting");break;
	default: break;
}
}


void hitEnemy(int receivedDamage){
   currentEnemy.subtractHealth(receivedDamage);

}
void hitPlayer(int receivedDamage){
   player.subtractHealth(receivedDamage);
}

int calculateRemainingAttack(int attackOutput,int defenseOutput){
	 attackOutput -= defenseOutput;
	 if(attackOutput>0){
        return attackOutput;
	 }
     return 0;
}

//---------------------------------------------------------------------------
void __fastcall TQuestForm::checkDeath(){
int playerHealth = player.getHealth();
int enemyHealth = currentEnemy.getHealth();
if(playerHealth<=0){ //When player is defeated,

   this->Close();
}
if(enemyHealth<=0){ //When enemy is defeated, get the next enemy
    currentEnemy = enemies.front();
    // Display new enemy status
	EnemyNameLabel->Text = currentEnemy.getName();
	EnemyHealthLabel->Text = currentEnemy.getHealth();
	EnemyMATKLabel->Text = currentEnemy.getMAtk();
	EnemySATKLabel->Text = currentEnemy.getSAtk();
	EnemyDefenseLabel->Text = currentEnemy.getDefense();

	enemies.pop();
}
}

void engageInCombat(){
int trueAttack = 0;

bool isPlayerAttacking = player.getPhase();
AnsiString playerMode = player.getMode();
int playerMeleeAttack = player.getMAtk();
int playerShootingAttack = player.getSAtk();
int playerDefense = player.getDefense();

generateEnemyMode();
AnsiString enemyMode = currentEnemy.getMode();
int enemyMeleeAttack = currentEnemy.getMAtk();
int enemyShootingAttack = currentEnemy.getSAtk();
int enemyDefense = currentEnemy.getDefense();

if(isPlayerAttacking){  // Player is attacking,
 if(playerMode != enemyMode && playerMode == "Melee"){ // Successful melee attack to enemy
	hitEnemy(playerMeleeAttack);
}
 else if(playerMode != enemyMode && playerMode == "Shooting"){ // Successfull shooting attack to enemy
	hitEnemy( playerShootingAttack);
 }
 else if (playerMode == enemyMode ){ // Enemy blocks player's attack
    // If after reducing attack by defense there are still remaining attack, deal the enemy using remaining attack
	if(playerMode == "Melee" && playerMeleeAttack >enemyDefense){
	trueAttack = calculateRemainingAttack(playerMeleeAttack ,enemyDefense);
	}
	else if(playerMode == "Shooting" &&  playerShootingAttack >enemyDefense){
	 trueAttack = calculateRemainingAttack( playerShootingAttack,enemyDefense);
	}
	hitEnemy(trueAttack);
 }

 }
else if(!isPlayerAttacking){  // Enemy is attacking,
  if(playerMode != enemyMode ){
	 if(enemyMode=="Melee"){
	 hitPlayer(enemyMeleeAttack);
	 }
	 else if(enemyMode=="Shooting"){
     hitPlayer(enemyShootingAttack);
     }
  }
  if(playerMode == enemyMode){
	 if(enemyMode=="Melee" && enemyMeleeAttack>playerDefense){
	  trueAttack = calculateRemainingAttack(enemyMeleeAttack,playerDefense);
	 }
	 else if(enemyMode=="Shooting" && enemyShootingAttack>playerDefense){
      trueAttack = calculateRemainingAttack(enemyShootingAttack,playerDefense);
	 }
     hitPlayer(trueAttack);
  }
}


}

















void TQuestForm::switchMode(bool isPlayerAttacking){
  if(isPlayerAttacking){
   PlayerStanceLabel->Text = "Attacker";
   EnemyStanceLabel->Text = "Defender";
   ShootingLabel->Text="Melee";
   MeleeLabel->Text="Shooting";
 }
 else if(!isPlayerAttacking){
   PlayerStanceLabel->Text = "Defender";
   EnemyStanceLabel->Text = "Attacker";
   ShootingLabel->Text="Anti Melee";
   MeleeLabel->Text="Anti Shooting";
 }
}


void  TQuestForm::switchPhase(){
bool isPlayerAttacking = player.getPhase();
AnsiString playerMode = player.getMode();
player.setPhase(!isPlayerAttacking);// Switch player phase from attack to defense OR defense to attack

  ShootingCircle->Visible=true;
 MeleeCircle->Visible=true;
 ShootingLabel->Visible=true;
 MeleeLabel->Visible=true;
}



void __fastcall TQuestForm::ShootingCircleClick(TObject *Sender)
{

 player.setMode("Shooting");

 engageInCombat();
 checkDeath();

 switchPhase();
 bool isPlayerAttacking = player.getPhase();
 switchMode(isPlayerAttacking);
}
//---------------------------------------------------------------------------

void __fastcall TQuestForm::MeleeCircleClick(TObject *Sender)
{
 
 player.setMode("Melee");

 engageInCombat();
  checkDeath();

 switchPhase();
 bool isPlayerAttacking = player.getPhase();
 switchMode(isPlayerAttacking);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TQuestForm::ConfirmCircleClick(TObject *Sender)
{
  ConfirmCircle->Visible=false;
  ConfirmLabel->Visible=false;
  ShootingCircle->Visible=true;
  MeleeCircle->Visible=true;
  ShootingLabel->Visible=true;
  MeleeLabel->Visible=true;

  generatePlayerPhase();
  if(player.getPhase()==true){
  PlayerStanceLabel->Text = "Attacker";
  }
  else{
  PlayerStanceLabel->Text = "Defender";
  }
  switchMode(player.getPhase());
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TQuestForm::Timer1Timer(TObject *Sender)
{
 PlayerHealthLabel->Text = player.getHealth();
 EnemyHealthLabel->Text = currentEnemy.getHealth();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

