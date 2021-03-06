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
#include <FMX.Ani.hpp>
//---------------------------------------------------------------------------
class TQuestForm : public TForm
{
__published:	// IDE-managed Components
	TButton *StrikeButton;
	TLabel *EnemyNameLabel;
	TLabel *EnemyHealthLabel;
	TLabel *EnemyMATKLabel;
	TLabel *EnemyMeleeDefenseLabel;
	TLabel *EnemySATKLabel;
	TLabel *StageLabel;
	TLabel *PlayerMATKLabel;
	TLabel *PlayerSATKLabel;
	TLabel *PlayerMeleeDefenseLabel;
	TLabel *PlayerHealthLabel;
	TLabel *PlayerNameLabel;
	TLabel *MeleeLabel;
	TTimer *Timer1;
	TLabel *PlayerStanceLabel;
	TLabel *EnemyStanceLabel;
	TPanel *CombatPanel;
	TPanel *SetupPanel;
	TEdit *CardEdit;
	TLabel *Label5;
	TButton *StartButton;
	TLabel *MessageLabel;
	TPanel *StartPanel;
	TLabel *InstructionLabel;
	TLabel *TitleLabel;
	TLabel *CardShootingLabel;
	TLabel *CardMeleeDefenseLabel;
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
	TLabel *Label12;
	TImage *AntiMeleeImage;
	TImage *AntiRangeImage;
	TRectAnimation *RectAnimation1;
	TImage *MeleeImage;
	TImage *RangeImage;
	TImage *BattleImage;
	TImage *Image1;
	TImage *Image2;
	TLabel *CardShootingDefenseLabel;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TLabel *PlayerRangeDefenseLabel;
	TLabel *EnemyRangeDefenseLabel;
	TPanel *LosePanel;
	TPanel *WinPanel;
	TLabel *Label1;
	TLabel *Label2;
	TImage *AtkWinImage;
	TImage *DefWinImage;
	TImage *AtkLoseImage;
	TImage *DefLoseImage;
	void __fastcall ShootingCircleClick(TObject *Sender);
	void __fastcall MeleeCircleClick(TObject *Sender);


	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall switchPhase();
	void __fastcall checkDeath();
	void __fastcall switchMode(bool isPlayerAttacking);
	void __fastcall engageInCombat();

	void __fastcall StartButtonClick(TObject *Sender);
    void __fastcall  StartRobot();
	void __fastcall StartPanelClick(TObject *Sender);
	void __fastcall CardPanelClick(TObject *Sender);
	void __fastcall BattleImageClick(TObject *Sender);
	void __fastcall MeleeImageClick(TObject *Sender);
	void __fastcall RangeImageClick(TObject *Sender);

	void __fastcall AntiMeleeImageClick(TObject *Sender);
	void __fastcall AntiRangeImageClick(TObject *Sender);
	void __fastcall LosePanelClick(TObject *Sender);
	void __fastcall WinPanelClick(TObject *Sender);
    void __fastcall InvisibleStatus();







private:	// User declarations
public:		// User declarations
	__fastcall TQuestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuestForm *QuestForm;
//---------------------------------------------------------------------------
#endif
