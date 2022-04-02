#include "my_app.h"
#include "my_frame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    auto frame = new MyFrame("Hello, wxWidgets");
    SetTopWindow(frame);
    frame->Show(true);
    return true;
}
