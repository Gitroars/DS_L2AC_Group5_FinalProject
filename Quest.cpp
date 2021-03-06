//---------------------------------------------------------------------------
#include <chrono>  // to measure execution time
#include <thread>  // to measure execution time
#include <stdlib.h> // for RNG
#include <time.h>   // for RNG
#include <fmx.h>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include<list>
#include <map>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#pragma hdrstop

#include "Quest.h"

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
   void setHealth(int health){
   healthPoint = health;
   }
   int getMaxHealth(){
   return maxHealthPoint;
   }
   void setMaxHealth(int maxHealth){
     maxHealthPoint = maxHealth;
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
   int maxHealthPoint;
   int meleeAttack;
   int shootingAttack;
   int defensePoint;

   AnsiString mode;
};
class Player: public Robot{
	public:
	Player(){}
	Player(int healthPoint,int meleeAttack, int shootingAttack,int defensePoint){
	Score = 1;
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















// RNG Function which returns an int value based on (parameter input-1)
int generateRandomNumber(int limit){
srand(time(NULL));
int randomNumber = rand()%limit;
return randomNumber;
}
// Seperate a string by commas and put the seperated strings into vector
vector<string> parseCommaDelimitedString(string line){
//std::this_thread::sleep_for(std::chrono::seconds (3));
vector<string> result;
stringstream s_stream(line);
while(s_stream.good()){
string substr;
getline(s_stream,substr,',');
result.push_back(substr);
}
return result;
}



vector<Robot> LoadRobots(){

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


vector<Robot> robotVector ;



map<AnsiString,vector<int>> GenerateCard(){
   map<AnsiString,vector<int>> temporaryMap;
  //To choose a card randomly, use a random index
   int randomIndex = generateRandomNumber(robotVector.size());
   //Access the specified object's getter to set the values of the new card
   AnsiString cardName= robotVector.at(randomIndex).getName();
   int cardHealth = robotVector.at(randomIndex).getHealth();
   int cardMelee = robotVector.at(randomIndex).getMAtk();
   int cardShooting = robotVector.at(randomIndex).getSAtk();
   int cardDefense = robotVector.at(randomIndex).getDefense();
   vector<int> cardValue = {cardHealth,cardMelee,cardShooting,cardDefense};
   temporaryMap.insert({cardName,cardValue});
   return temporaryMap;
}



map<AnsiString,vector<int>>  LoadCards(){ //loading owned cards
//std::this_thread::sleep_for(std::chrono::seconds (3));
map<AnsiString,vector<int>> temporaryMap;
fstream cardDB;
cardDB.open("cards.txt",ios::in);
if(cardDB.is_open()){
string line;
while( getline(cardDB,line)){
vector<string> parsedLine=parseCommaDelimitedString(line);
AnsiString cardName = parsedLine.at(0).c_str();
int cardHealth = stoi(parsedLine.at(1));
int cardMelee = stoi(parsedLine.at(2));
int cardShooting = stoi(parsedLine.at(3));
int cardDefense = stoi(parsedLine.at(4));
vector<int> cardValue = {cardHealth,cardMelee,cardShooting,cardDefense};
temporaryMap.insert({cardName,cardValue});
}

}
return temporaryMap;
}
map<AnsiString,vector<int>> cardMap;
map<AnsiString,vector<int>>:: iterator cardIt; // Create an iterator of cardmap




Player player;




queue<Enemy> enemies;
list<Enemy> enemyList;
Enemy currentEnemy;
int currentStage=1;
TQuestForm *QuestForm;


//---------------------------------------------------------------------------
 __fastcall TQuestForm::TQuestForm(TComponent* Owner)
 : TForm(Owner)
{

robotVector = LoadRobots();

    StageLabel->Text=currentStage;
//Create a list of enemy

	Enemy e1("Bandit",15,10,10,10);
	Enemy e2("Bandit Lieutenant",20,12,12,12);
	Enemy e3("Bandit Captain",25,15,15,15);

//auto start = std::chrono::high_resolution_clock::now();
//std::this_thread::sleep_for(std::chrono::seconds (3));
//	enemyList.push_back(e1); enemyList.push_back(e2); enemyList.push_back(e3);
//	currentEnemy = enemyList.front();
//	enemyList.pop_front();

    enemies.push(e1);enemies.push(e2);enemies.push(e3);
	currentEnemy = enemies.front(); //Challenge the first one in the queue
	enemies.pop(); //To prevent being called again
//	auto end = std::chrono::high_resolution_clock::now();
//	 std::chrono::duration<double, std::milli> float_ms = end - start;
// fstream logDB;
//   logDB.open("ListLog.txt",ios::app);
//
//   if( logDB.is_open()){ //Write the data to the text file
//	   logDB<<float_ms.count()<<"\n";
//	   logDB.close();
//   }




    //Display current enemy's status information
	EnemyNameLabel->Text = currentEnemy.getName();
	EnemyHealthLabel->Text = currentEnemy.getHealth();
	EnemyMATKLabel->Text = currentEnemy.getMAtk();
	EnemySATKLabel->Text = currentEnemy.getSAtk();
	EnemyMeleeDefenseLabel->Text = currentEnemy.getDefense();
    EnemyRangeDefenseLabel->Text = currentEnemy.getDefense();




}
 
 void __fastcall TQuestForm:: StartRobot(){
// auto start = std::chrono::high_resolution_clock::now();
//std::this_thread::sleep_for(std::chrono::seconds (3));
	 AnsiString rawName= CardEdit->Text; //Get user input from editable text field

	 cardIt = cardMap.find(rawName);
	 //Find reference: https://thispointer.com/how-check-if-a-given-key-exists-in-a-map-c/
	 
	  // Find the element with key [cardName]
	 // Check whether it exists in the cardMap or not
	 if(cardIt!= cardMap.end()){
	 //Element is found
	 vector<int> cardValue = cardMap.at(rawName);  //Access the value from iterator
     //Retrieve the data
	 int health = cardValue[0];
	 int melee = cardValue[1];
	 int shooting = cardValue[2];
	 int defense = cardValue[3];
	 //Set player's status value
	 player.setName(rawName);
	 player.setHealth(health);
     player.setMaxHealth(health);
	 player.setMAtk(melee);
	 player.setSAtk(shooting);
	 player.setDefense(defense);
	 //Display the status on text labels
     PlayerNameLabel->Text = player.getName();
	 PlayerHealthLabel->Text = player.getHealth();
	 PlayerMATKLabel->Text = player.getMAtk();
	 PlayerSATKLabel->Text = player.getSAtk();
	 PlayerMeleeDefenseLabel->Text = player.getDefense();
     PlayerRangeDefenseLabel->Text = player.getDefense();
     //Change displayed panel screen to Combat
	 SetupPanel->Visible=false;
	 CombatPanel->Visible=true;
	 }
	 else{ //Warns the user of invalid card ownership
      MessageLabel->Visible=true;
	 }
//     	auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> float_ms = end - start;
// fstream logDB;
//   logDB.open("StartRobotLog.txt",ios::app);
//
//   if( logDB.is_open()){ //Write the data to the text file
//	   logDB<<float_ms.count()<<"\n";
//	   logDB.close();
//   }





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

   CombatPanel->Visible=false;
   LosePanel->Visible=true;
}
if(enemyHealth<=0){ //When enemy is defeated, get the next enemy
	if(!enemies.empty()){
    currentStage++; //increase stage level's number
	currentEnemy = enemies.front();
	// Display new enemy status
	EnemyNameLabel->Text = currentEnemy.getName();
	EnemyHealthLabel->Text = currentEnemy.getHealth();
	EnemyMATKLabel->Text = currentEnemy.getMAtk();
	EnemySATKLabel->Text = currentEnemy.getSAtk();
	EnemyMeleeDefenseLabel->Text = currentEnemy.getDefense();
    EnemyRangeDefenseLabel->Text = currentEnemy.getDefense();

	enemies.pop();  //remove enemy from queue to prevent being used again

	player.setHealth(player.getMaxHealth()); //Restore to full health

    StageLabel->Text = currentStage;
	}
	else{  //When there's no more enemy,
       CombatPanel->Visible=false;
       WinPanel->Visible=true;
    }

}
}

void __fastcall TQuestForm::InvisibleStatus(){ //Set all attack or defense success or failure confirmation to be hidden
AtkWinImage->Visible=false;
AtkLoseImage->Visible=false;
DefWinImage->Visible=false;
DefLoseImage->Visible=false;
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

InvisibleStatus();
if(isPlayerAttacking){  // Player is attacking,
 if(playerMode != enemyMode && playerMode == "Melee"){ // Successful melee attack to enemy
	hitEnemy(playerMeleeAttack); AtkWinImage->Visible = true;

}
 else if(playerMode != enemyMode && playerMode == "Shooting"){ // Successfull shooting attack to enemy
	hitEnemy( playerShootingAttack); AtkWinImage->Visible = true;
 }
 else if (playerMode == enemyMode ){ // Enemy blocks player's attack
    AtkLoseImage->Visible = true;
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
     DefLoseImage->Visible=true;
	 if(enemyMode=="Melee"){   //Successful melee attack to player
	 hitPlayer(enemyMeleeAttack);
	 }
	 else if(enemyMode=="Shooting"){   //Successful shooting attack to player
     hitPlayer(enemyShootingAttack);
     }
  }
  if(playerMode == enemyMode){  //Player blocks enemy's attack
     DefWinImage->Visible=true;
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


}

















void TQuestForm::switchMode(bool isPlayerAttacking){
// Change the text highlighting both parties' stance and mode based on the player's stance
  if(isPlayerAttacking){
   PlayerStanceLabel->Text = "Attacker";
   EnemyStanceLabel->Text = "Defender";
   MeleeImage->Visible=true;
   RangeImage->Visible=true;
   AntiMeleeImage->Visible=false;
   AntiRangeImage->Visible=false;
 }
 else if(!isPlayerAttacking){
   PlayerStanceLabel->Text = "Defender";
   EnemyStanceLabel->Text = "Attacker";
   MeleeImage->Visible=false;
   RangeImage->Visible=false;
   AntiMeleeImage->Visible=true;
   AntiRangeImage->Visible=true;
 }
}


void  TQuestForm::switchPhase(){
bool isPlayerAttacking = player.getPhase();
AnsiString playerMode = player.getMode();
player.setPhase(!isPlayerAttacking);// Switch player phase from attack to defense OR defense to attack

  
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

//Periodically update the status information of health points of both parties
void __fastcall TQuestForm::Timer1Timer(TObject *Sender)
{
 PlayerHealthLabel->Text = player.getHealth();
 EnemyHealthLabel->Text = currentEnemy.getHealth();
}


void __fastcall TQuestForm::StartButtonClick(TObject *Sender)
{
  StartRobot();

}
//---------------------------------------------------------------------------




void __fastcall TQuestForm::StartPanelClick(TObject *Sender)
{
//   auto start = std::chrono::high_resolution_clock::now();
   map<AnsiString,vector<int>> newCardMap = GenerateCard();

   map<AnsiString,vector<int>>:: iterator newCardIt = newCardMap.begin(); // Iterate through all elements in map
   AnsiString newCardName;
   int newCardHealth,newCardMelee,newCardShooting,newCardDefense;
   while(newCardIt!=newCardMap.end()){
	 newCardName = newCardIt->first; //Retrieve key
	 vector<int> newCardValue = newCardIt->second; //Retrieve value
	 //Set object value
	  newCardHealth = newCardValue.at(0);
	  newCardMelee = newCardValue.at(1);
	  newCardShooting = newCardValue.at(2);
	  newCardDefense = newCardValue.at(3);
	  newCardIt++;
   }


//	  auto end = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double, std::milli> float_ms = end - start;
// fstream logDB;
//   logDB.open("StartPanelGenerateCardLog.txt",ios::app);
//
//   if( logDB.is_open()){ //Write the data to the text file
//	   logDB<<float_ms.count()<<"\n";
//	   logDB.close();
//   }
   //Display the status information

   CardNameLabel->Text=newCardName;
   CardHealthLabel->Text=newCardHealth;
   CardMeleeLabel->Text=newCardHealth;
   CardShootingLabel->Text=newCardShooting;
   CardMeleeDefenseLabel->Text=newCardDefense;
   CardShootingDefenseLabel->Text=newCardDefense;
   //Save the card in 'inventory' text file
   fstream cardDB;
   cardDB.open("cards.txt",ios::app);

   if(cardDB.is_open()){ //Write the data to the text file
	  cardDB<<newCardName<<","<<newCardHealth<<","<<newCardMelee<<","<<newCardShooting<<","<<newCardDefense<<"\n";
	  cardDB.close();
   }
   //Load all owned cards to map
//    auto start = std::chrono::high_resolution_clock::now();
   cardMap = LoadCards();
//   auto end = std::chrono::high_resolution_clock::now();
// std::chrono::duration<double, std::milli> float_ms = end - start;
// fstream logDB;
//   logDB.open("LoadCardsLog.txt",ios::app);

//   if( logDB.is_open()){ //Write the data to the text file
//	   logDB<<float_ms.count()<<"\n";
//	   logDB.close();
//   }
   //Switch the panel screen being displayed to card details
  StartPanel->Visible=false;
  CardPanel->Visible=true;

}
//---------------------------------------------------------------------------







void __fastcall TQuestForm::CardPanelClick(TObject *Sender)
{
 CardPanel->Visible=false;
 SetupPanel->Visible=true;

}
//---------------------------------------------------------------------------







void __fastcall TQuestForm::BattleImageClick(TObject *Sender)
{
//Once the battle is initiated, remove button from sight
  BattleImage->Visible=false;
// Put combat buttons in sight
  MeleeImage->Visible=true;
  RangeImage->Visible=true;
  AntiMeleeImage->Visible=true;
  AntiRangeImage->Visible=true;

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


void __fastcall TQuestForm::MeleeImageClick(TObject *Sender)
{
   player.setMode("Melee");
   engageInCombat();
   checkDeath();
   switchPhase();
   switchMode(player.getPhase());
}
//---------------------------------------------------------------------------

void __fastcall TQuestForm::RangeImageClick(TObject *Sender)
{
   player.setMode("Shooting");
   engageInCombat();
   checkDeath();
   switchPhase();
   switchMode(player.getPhase());
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TQuestForm::AntiMeleeImageClick(TObject *Sender)
{
  player.setMode("Melee");
  engageInCombat();
  checkDeath();
   switchPhase();
   switchMode(player.getPhase());
}
//---------------------------------------------------------------------------

void __fastcall TQuestForm::AntiRangeImageClick(TObject *Sender)
{
   player.setMode("Shooting");
  engageInCombat();
  checkDeath();
   switchPhase();
   switchMode(player.getPhase());
}
//---------------------------------------------------------------------------



void __fastcall TQuestForm::LosePanelClick(TObject *Sender)
{
   this->Close();  //close app
}
//---------------------------------------------------------------------------

void __fastcall TQuestForm::WinPanelClick(TObject *Sender)
{
   this->Close();  //close app
}
//---------------------------------------------------------------------------

