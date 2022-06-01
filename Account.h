//---------------------------------------------------------------------------

#ifndef AccountH
#define AccountH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *RegistrationUsernameEdit;
	TEdit *RegistrationPasswordEdit;
	TEdit *LoginUsernameEdit;
	TEdit *LoginPasswordEdit;
	TPanel *LoginPanel;
	TPanel *RegistrationPanel;
	TButton *RegistrationButton;
	TButton *LoginPageButton;
	TButton *LoginButton;
	TButton *RegistrationPageButton;
	
	void __fastcall RegistrationButtonClick(TObject *Sender);
	void __fastcall LoginPageButtonClick(TObject *Sender);
	void __fastcall LoginButtonClick(TObject *Sender);
	void __fastcall RegistrationPageButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
