//---------------------------------------------------------------------------
#include <stdlib.h> // for RNG
#include <time.h>   // for RNG
#include <fmx.h>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#pragma hdrstop

#include "Quest.h"
#include "Robot.h"
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

class Robot{
public:
   Robot(){}
   Robot(AnsiString name,int healthPoint,int meleeAttack, int shootingAttack,int defensePoint){
    this->name = name;
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
   int getHealth(){
   return healthPoint;
   }
   void setHealth(int newHealth){
   health = newHealth;
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
   AnsiString name;
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
   Enemy(AnsiString name,int healthPoint,int meleeAttack, int shootingAttack,int defensePoint  ){
	this->name = name;
	this->healthPoint = healthPoint;
	this->meleeAttack = meleeAttack;
	this->shootingAttack = shootingAttack;
	this->defensePoint = defensePoint;
   }





};


int healthPoint = 100;
int meleeAttack = 15;
int shootingAttack = 15;
int defensePoint = 15;






//queue<Enemy> LoadEnemies(){
//Enemy e1("Poring",30,15,15,15);
//e1.setName("Bandit");
//Enemy e2("Mastering",40,20,20,20);
//e2.setName("Bandit Lieutenant");
//Enemy e3("Poring King",50,25,25,25);
//e3.setName("Bandit Commander");
//queue<Enemy> enemies;
//enemies.push(e1);
//enemies.push(e2);
//enemies.push(e3);
//return enemies;
//}





// RNG Function which returns an int value based on (parameter input-1)
int generateRandomNumber(int limit){
srand(time(NULL));
int randomNumber = rand()%limit;
return randomNumber;
}

vector<string> parseCommaDelimitedString(string line){
vector<string> result;
stringstream s_stream(line);
while(s_stream.good()){
string substr;
getline(s_stream,substr,',');
result.push_back(substr);
}
return result;
}

vector<Robot> getRobots(){
vector<Robot> temporaryVector;
fstream robotDB;
robotDB.open("robots.txt",ios::in); //Open the text file containing robots' specifications
if(robotDB.is_open()){  //Upon successful opening,
string line;
while(getline(robotDB,line)){ //For each line,
 vector<string> parsedLine = parseCommaDelimitedString(line); //Divide the line based on comma.
 AnsiString name = parsedLine.at(0).c_str(); //First word is robot's name
 // stoi: converts string to integer
 int healthPoint = stoi(parsedLine.at(1)); //First number is health
 int meleePower = stoi(parsedLine.at(2));  //Second number is melee power
 int shootingPower = stoi(parsedLine.at(3)); //Third number is shooting power
 int defensePower = stoi(parsedLine.at(4));  //Fourth number is defense power
 Robot robot(name,healthPoint,meleePower,shootingPower,defensePower); //Create an object of type Robot
 temporaryVector.push_back(robot);  //temporarily store it
}
}
return temporaryVector;
}

 vector<int> idVector;

vector<Robot> robotVector = getRobots();

//bool validateID(int idNumber){
////Reference: https://www.techiedelight.com/check-vector-contains-given-element-cpp/
//  if(count(idVector.begin(),idVector.end(),idNumber)){  //If the number is found within the vector
//  return false;
//  }
//  return true;
//}
void SaveCard(){
//   int randomID;
//   bool isNumberValid = false;
//   while(!isNumberValid){ //Generate a new random number as long as it's unvalidated
//	randomID = generateRandomNumber(10000);  // is within 10,000
//	if(randomID<1000){randomID+=1000};  //Add another thousand if it's below a thousand
//	isNumberValid = validateID(randomID); //Check for validation to prevent duplicates
//   }
  //To choose a card randomly, use a random index
   int randomIndex = generateRandomNumber(robotVector.size());
   //Access the specified object's getter to set the values of the new card
   AnsiString name = robotVector[randomIndex].getName();
   int health = robotVector[randomIndex].getHealth();
   int melee = robotVector[randomIndex].getMAtk();
   int shooting = robotVector[randomIndex].getSAtk();
   int defense = robotVector[randomIndex].getDefense();

   fstream cardDB;
   cardDB.open("cards.txt",ios::app);

   if(cardDB.is_open()){ //Write the data to the text file
	  cardDB<<name<<","<<<health<<","<<<melee<<","<<<shooting<<","<<<defense<<"\n";
	  cardDB.close();
   }
}



map<string,vector<int>>  LoadCards(){
map<string,vector<int>> temporaryMap;
fstream cardDB;
cardDB.open("cards.txt",ios::in);
if(cardDB.is_open()){
string line;
while( getline(accountDB,line)){
vector<string> parsedLine=parseCommaDelimitedString(line);
//int cardNumber = stoi(parsedLine.at(0));
idVector.push_back(cardNumber); //'List' the card numbers
AnsiString cardName = parsedLine.at(0).c_str();
int cardHealth = stoi(parsedLine.at(1));
int cardMelee = stoi(parsedLine.at(2));
int cardShooting = stoi(parsedLine.at(3));
int cardDefense = stoi(parsedLine.at(4));
vector<int> cardValue = {cardHealth,cardMelee,cardShooting,cardDefense};
temporaryMap.insert({cardName,cardValue});
}
 return temporaryMap;
}

}
map<string,vector<int>> cardMap = LoadCards();




Player player;

Enemy getEnemy(){
   //To choose a new enemy randomly, use a random index
   int randomIndex = generateRandomNumber(robotVector.size());
   //Access the specified object's getter to set the values of the new enemy
   AnsiString enemyName = robotVector[randomIndex].getName();
   int enemyHealth = robotVector[randomIndex].getHealth();
   int enemyMelee = robotVector[randomIndex].getMAtk();
   int enemyShooting = robotVector[randomIndex].getSAtk();
   int enemyDefense = robotVector[randomIndex].getDefense();
   //Create the new enemy based on the values obtained
   Enemy newEnemy(enemyName,enemyHealth,enemyMelee,enemyShooting,enemyDefense);
   return newEnemy;
}
queue<Enemy> LoadEnemies(){
   queue<Enemy> enemies;
   // Create some enemies
   Enemy enemy1 = getEnemy();
   Enemy enemy2 = getEnemy();
   Enemy enemy3= getEnemy();
   // Store them to the queue
   enemies.push(enemy1); enemies.push(enemy2); enemies.push(enemy3);
   return enemies;
}

queue<Enemy> enemies;
Enemy currentEnemy;

TQuestForm *QuestForm;


//---------------------------------------------------------------------------
__fastcall TQuestForm::TQuestForm(TComponent* Owner)
	: TForm(Owner)
{




	enemies = LoadEnemies(); //Create a list of enemy
	currentEnemy = enemies.front(); //Challenge the first one in the queue

    //Display player's current status
    PlayerHealthLabel->Text = player.getHealth();
	PlayerMATKLabel->Text = player.getMAtk();
	PlayerSATKLabel->Text = player.getSAtk();
	PlayerDefenseLabel->Text = player.getDefense();


    //Display current enemy's status information
	EnemyNameLabel->Text = currentEnemy.getName();
	EnemyHealthLabel->Text = currentEnemy.getHealth();
	EnemyMATKLabel->Text = currentEnemy.getMAtk();
	EnemySATKLabel->Text = currentEnemy.getSAtk();
	EnemyDefenseLabel->Text = currentEnemy.getDefense();


	enemies.pop(); //To prevent being called again


}

 void __fastcall TQuestForm:: StartRobot(){
	 AnsiString cardName = CardEdit->Text;
	 if(cardMap.contains(cardName){
	   SetupPanel->Visible=false;
	   CombatPanel->Visible=true;
	   int health = cardMap[cardName][0];
	   int melee = cardMap[cardName][1];
	   int shooting = cardMap[cardName][2];
	   int defense = cardMap[cardName][3];
       player.setName(cardName);
	   player.setHealth(health);
	   player.setMAtk(melee);
       player.setSAtk(shooting);
       player.setDefense(defense);
	 }
	 else{
         MessageLabel->Visible=true;
     }
 }
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------


void generatePlayerPhase(){  //The player starting stance depend on RNG
int randomNumber = generateRandomNumber(2);
switch (randomNumber){
	case 0:player.setPhase(true);break;
	case 1:player.setPhase(false);break;
	default: break;
}
}
//---------------------------------------------------------------------------
void generateEnemyMode(){ //The current enemy attack/defense mode will depend on RNG
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
	 if(attackOutput>0){  //Any remaining attack output will be returned
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
	if(!enemies.empty()){
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
}

void __fastcall TQuestForm::engageInCombat(){
int trueAttack = 0;
//Get the current stance, as well as both parties' chosen mode, attack and defense power
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
	 if(enemyMode=="Melee"){   //Successful melee attack to player
	 hitPlayer(enemyMeleeAttack);
	 }
	 else if(enemyMode=="Shooting"){   //Successful shooting attack to player
     hitPlayer(enemyShootingAttack);
     }
  }
  if(playerMode == enemyMode){  //Player blocks enemy's attack
  // If after reducing attack by defense there are still remaining attack, deal the player using remaining attack
	 if(enemyMode=="Melee" && enemyMeleeAttack>playerDefense){
	  trueAttack = calculateRemainingAttack(enemyMeleeAttack,playerDefense);
	 }
	 else if(enemyMode=="Shooting" && enemyShootingAttack>playerDefense){
      trueAttack = calculateRemainingAttack(enemyShootingAttack,playerDefense);
	 }
     hitPlayer(trueAttack);
  }

}
//  Popup1->Visible=true;

}

















void TQuestForm::switchMode(bool isPlayerAttacking){
// Change the text highlighting both parties' stance and mode based on the player's stance
  if(isPlayerAttacking){
   PlayerStanceLabel->Text = "Attacker";
   EnemyStanceLabel->Text = "Defender";
   MeleeLabel->Text="Shooting";
   ShootingLabel->Text="Melee";
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
  //Once the battle is initiated,
  // remove the confirmation button from sight
  ConfirmCircle->Visible=false;
  ConfirmLabel->Visible=false;
  // and put the battle modes in sight instead
  ShootingCircle->Visible=true;
  MeleeCircle->Visible=true;
  ShootingLabel->Visible=true;
  MeleeLabel->Visible=true;

  generatePlayerPhase();
  // Display both parties stance from the randomly generated phase
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
//Periodically update the status information of health points of both parties
void __fastcall TQuestForm::Timer1Timer(TObject *Sender)
{
 PlayerHealthLabel->Text = player.getHealth();
 EnemyHealthLabel->Text = currentEnemy.getHealth();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




//---------------------------------------------------------------------------






//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TQuestForm::StartButtonClick(TObject *Sender)
{
  StartRobot();
}
//---------------------------------------------------------------------------

