#include "my_app.h"
#include "my_frame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxLog::AddTraceMask(TM());
    wxLogTrace(TM(), "\"%s\" called.", __WXFUNCTION__);
    auto frame = new MyFrame("Hello, wxWidgets");
    SetTopWindow(frame);
    frame->Show(true);
    return true;
}

int MyApp::OnExit()
{
    wxLogTrace(TM(), "\"%s\" called.", __WXFUNCTION__);
    return 0;
}
