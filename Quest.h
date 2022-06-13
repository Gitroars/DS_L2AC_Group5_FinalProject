//---------------------------------------------------------------------------

#ifndef QuestH
#define QuestH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Media.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Filter.Effects.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class TQuestForm : public TForm
{
__published:	// IDE-managed Components
	TButton *StrikeButton;
	TLabel *EnemyNameLabel;
	TLabel *EnemyHealthLabel;
	TLabel *EnemyMATKLabel;
	TLabel *EnemyDefenseLabel;
	TLabel *EnemySATKLabel;
	TLabel *StageLabel;
	TLabel *PlayerMATKLabel;
	TLabel *PlayerSATKLabel;
	TLabel *PlayerDefenseLabel;
	TLabel *PlayerHealthLabel;
	TLabel *PlayerNameLabel;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Z;
	TLabel *Label4;
	TCircle *ShootingCircle;
	TLabel *MeleeLabel;
	TLabel *ShootingLabel;
	TCircle *MeleeCircle;
	TCircle *ConfirmCircle;
	TLabel *ConfirmLabel;
	TTimer *Timer1;
	TLabel *PlayerStanceLabel;
	TLabel *EnemyStanceLabel;
	TLabel *Label3;
	TPanel *CombatPanel;
	TCalloutPanel *CalloutPanel1;
	TPanel *SetupPanel;
	TEdit *CardEdit;
	TLabel *Label5;
	TButton *StartButton;
	TLabel *MessageLabel;
	TPanel *StartPanel;
	TLabel *InstructionLabel;
	TLabel *TitleLabel;
	TLabel *CardShootingLabel;
	TLabel *CardDefenseLabel;
	TLabel *CardHealthLabel;
	TLabel *CardNameLabel;
	TLabel *CardMeleeLabel;
	TPanel *CardPanel;
	TLabel *LootLabel;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	void __fastcall ShootingCircleClick(TObject *Sender);
	void __fastcall MeleeCircleClick(TObject *Sender);

	void __fastcall ConfirmCircleClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall switchPhase();
	void __fastcall checkDeath();
	void __fastcall switchMode(bool isPlayerAttacking);
	void __fastcall engageInCombat();

	void __fastcall StartButtonClick(TObject *Sender);
    void __fastcall  StartRobot();
	void __fastcall StartPanelClick(TObject *Sender);
	void __fastcall CardPanelClick(TObject *Sender);









private:	// User declarations
public:		// User declarations
	__fastcall TQuestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuestForm *QuestForm;
//---------------------------------------------------------------------------
#endif
