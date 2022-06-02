//---------------------------------------------------------------------------

#ifndef QuestH
#define QuestH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TQuestForm : public TForm
{
__published:	// IDE-managed Components
	TPopup *Popup1;
private:	// User declarations
public:		// User declarations
	__fastcall TQuestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuestForm *QuestForm;
//---------------------------------------------------------------------------
#endif
