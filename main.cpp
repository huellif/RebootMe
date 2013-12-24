#include <aknglobalmsgquery.h>

class RStarterSession : public RSessionBase
    {
public:
    IMPORT_C TInt Connect();

public:
    enum TResetReason
        {
        ELanguageSwitchReset = 100,     // A reset due to display language switch.
        };
    IMPORT_C void Reset( const TResetReason aReason );
};

LOCAL_C TAny ExeMainL() //TAny is Symbian's void, however compilers also accept void for native code
{
    CAknGlobalMsgQuery * pDlg = CAknGlobalMsgQuery::NewL();//creating the pointer
    CleanupStack::PushL(pDlg);                      //exception handling
    TRequestStatus iStatus;                         //the app should wait until the user selected an option
    pDlg->ShowMsgQueryL(iStatus,                    //the app should wait until the user selected an option
                        _L("Do you want to reboot your phone?\nPlease save all your documents!"),
                        R_AVKON_SOFTKEYS_YES_NO,    //yes/no dialog buttons from avkon.rsg
                        _L("RebootMe"),             //dialog title
                        KNullDesC,                  //no image
                        0,                          //no icon
                        -1,                         //no icon
                        CAknQueryDialog::ENoTone);  //no sound

    User::WaitForRequest(iStatus);                  //the app should wait until the user selected an option

    CleanupStack::PopAndDestroy(pDlg);              //freeing CleanupStack
    if (iStatus.Int() == EAknSoftkeyYes)            //only if user selected yes
    {
        RStarterSession starter;
        User::LeaveIfError(starter.Connect());
        starter.Reset(RStarterSession::ELanguageSwitchReset);
        starter.Close();
    }
}

GLDEF_C TInt E32Main()
{
    CTrapCleanup* cl=CTrapCleanup::New();           //needed to use CleanupStack
    TRAPD(error, ExeMainL());                       //TRAPD is like a standart C++ try, the error code will be stored in TInt error
    delete cl;                                      //let's stay clean
    return error;
}

