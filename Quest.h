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
	void __fastcall ShootingCircleClick(TObject *Sender);
	void __fastcall MeleeCircleClick(TObject *Sender);

	void __fastcall ConfirmCircleClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall switchPhase();
    void __fastcall checkDeath();
	void __fastcall switchMode(bool isPlayerAttacking);






private:	// User declarations
public:		// User declarations
	__fastcall TQuestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuestForm *QuestForm;
//---------------------------------------------------------------------------
#endif
