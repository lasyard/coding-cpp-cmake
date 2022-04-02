#include <wx/button.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>

#include "my_frame.h"

MyFrame::MyFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title)
{
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

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
EVT_SIZE(MyFrame::OnSize)
EVT_BUTTON(wxID_OK, MyFrame::OnButtonOK)
END_EVENT_TABLE()

void MyFrame::OnAbout([[maybe_unused]] wxCommandEvent &event)
{
    wxMessageBox(
        _("Hello and welcome to ") + wxVERSION_STRING + _("."), _("About MyApp"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit([[maybe_unused]] wxCommandEvent &event)
{
    Close();
}

void MyFrame::OnSize([[maybe_unused]] wxSizeEvent &event)
{
    // event.Skip();
}

void MyFrame::OnButtonOK([[maybe_unused]] wxCommandEvent &event)
{
}
