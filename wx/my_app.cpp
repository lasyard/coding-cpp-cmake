#include <wx/frame.h>

#include "my_app.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame(nullptr, wxID_ANY, "Hello, wxWidgets");
    SetTopWindow(frame);
    frame->Show(true);
    return true;
}
