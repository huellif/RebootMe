#include <aknglobalmsgquery.h>

class RestartSys //found in Symbian^3 sources
    {
public:
    IMPORT_C static TInt RestartSystem();
    };

LOCAL_C TAny ExeMainL() //TAny is Symbian's void, however compilers also accept void for native code
{
    CAknGlobalMsgQuery * pDlg = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL(pDlg);
    TRequestStatus iStatus;
    pDlg->ShowMsgQueryL(iStatus,                    //the app should wait until the user selected an options
                        _L("Do you want to reboot your phone?\nPlease save all your documents!"),
                        R_AVKON_SOFTKEYS_YES_NO,    //dialog buttons from avkon.rsg
                        _L("RebootMe"),             //dialog title
                        KNullDesC,                  //no image
                        0,                          //no icon
                        -1,                         //no icon
                        CAknQueryDialog::ENoTone);  //no sound
    User::WaitForRequest(iStatus);
    CleanupStack::PopAndDestroy(pDlg);
    if (iStatus.Int() == EAknSoftkeyYes)
    {
        RestartSys::RestartSystem();
    }
}

GLDEF_C TInt E32Main()
{
    CTrapCleanup* cl=CTrapCleanup::New(); //needed to use CleanupStack
    TRAPD(error, ExeMainL()); //TRAPD is like a C++ try, the error code will be stored in TInt error
    delete cl; //let's stay clean ;)
    return error;
}

