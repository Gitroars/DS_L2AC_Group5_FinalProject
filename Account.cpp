

#include <fmx.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#pragma hdrstop

#include "Account.h"
#include "Quest.h"
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
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

const char* convertCharPtr(AnsiString ansiStr){
return ansiStr.c_str();
}



void __fastcall TForm1::RegistrationButtonClick(TObject *Sender)
{
fstream accountDB;
  accountDB.open("registeredUsers.txt",ios::app);
if(accountDB.is_open()){
AnsiString username = RegistrationUsernameEdit->Text;
AnsiString password = RegistrationPasswordEdit->Text;
accountDB<<username<<","<<password<<"\n";
accountDB.close();
RegistrationPanel->Visible=false;
LoginPanel->Visible=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoginPageButtonClick(TObject *Sender)
{
 RegistrationPanel->Visible=false;
 LoginPanel->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoginButtonClick(TObject *Sender)
{
 fstream accountDB;
accountDB.open("registeredUsers.txt",ios::in);
if(accountDB.is_open()){
string line;
while( getline(accountDB,line)){
vector<string> parsedLine=parseCommaDelimitedString(line);

const char* username = parsedLine.at(0).c_str();
AnsiString editUsername = LoginUsernameEdit->Text;
const char* usernameString = convertCharPtr(editUsername);
bool validUsername = false;

const char* password = parsedLine.at(1).c_str();
AnsiString editPassword = LoginPasswordEdit->Text;
const char* passwordString = convertCharPtr(editPassword);
bool validPassword = false;

if(strcmp(username,usernameString)==0){validUsername = true;}
if(strcmp(password,passwordString)==0){validPassword = true;}
if(validUsername && validPassword){
   LoginButton->Enabled=false;
   RegistrationPageButton->Enabled=false;
   QuestForm->Show();

}

}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
}
void __fastcall TForm1::RegistrationPageButtonClick(TObject *Sender)
{
RegistrationPanel->Visible=true;
 LoginPanel->Visible=false;
}
