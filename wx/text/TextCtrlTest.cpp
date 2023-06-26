#include <wx/app.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

class TextCtrlTestFrame : public wxFrame
{
public:
    TextCtrlTestFrame() : wxFrame(nullptr, wxID_ANY, "Test wxTextCtrl")
    {
        auto sizer = new wxBoxSizer(wxVERTICAL);
        SetSizer(sizer);
        auto text = new wxTextCtrl(
            this,
            wxID_ANY,
            "\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\t14\t15\t16\t17\t18\t19\t20",
            wxDefaultPosition,
            wxDefaultSize,
            wxTE_DONTWRAP | wxTE_MULTILINE | wxTE_PROCESS_TAB
        );
        sizer->Add(text, wxSizerFlags(1).Expand().Border(wxALL, 1));
        SetSize(500, 200);
    }
};

class TextCtrlTestApp : public wxApp
{
public:
    bool OnInit() override
    {
        auto frame = new TextCtrlTestFrame();
        SetTopWindow(frame);
        frame->Show();
        return true;
    }
};

IMPLEMENT_APP(TextCtrlTestApp)
