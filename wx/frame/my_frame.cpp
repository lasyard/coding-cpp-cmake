#include <wx/button.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/wx.h>

#include "my_frame.h"

IMPLEMENT_DYNAMIC_CLASS(MyFrame, wxFrame)

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_CLOSE(MyFrame::OnClose)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_SIZE(MyFrame::OnSize)
EVT_BUTTON(wxID_OK, MyFrame::OnButtonOK)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    wxLog::AddTraceMask(TM());
    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, _("&About...\tF1"), _("Show about dialog"));
    fileMenu->Append(wxID_EXIT, _("E&xit\tAlt-X"), _("Quit this program"));
    auto menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _("&File"));
    menuBar->Append(helpMenu, _("&Help"));
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    SetStatusText(_("Welcome to ") + wxVERSION_STRING + _("."));
    [[maybe_unused]] auto button = new wxButton(this, wxID_OK, _("OK"), wxPoint(100, 100));
}

void MyFrame::OnAbout([[maybe_unused]] wxCommandEvent &event)
{
    wxMessageBox(
        _("Hello and welcome to ") + wxVERSION_STRING + _("."),
        _("About MyApp"),
        wxOK | wxICON_INFORMATION,
        this
    );
}

void MyFrame::OnExit([[maybe_unused]] wxCommandEvent &event)
{
    wxLogTrace(TM(), "\"%s\" called.", __WXFUNCTION__);
    Close();
}

void MyFrame::OnClose([[maybe_unused]] wxCloseEvent &event)
{
    wxLogTrace(TM(), "\"%s\" called.", __WXFUNCTION__);
    Destroy();
}

void MyFrame::OnSize([[maybe_unused]] wxSizeEvent &event)
{
    wxLogTrace(TM(), "\"%s\" called.", __WXFUNCTION__);
    event.Skip();
}

void MyFrame::OnButtonOK([[maybe_unused]] wxCommandEvent &event)
{
    wxLogTrace(TM(), "\"%s\" called.", __WXFUNCTION__);
}
