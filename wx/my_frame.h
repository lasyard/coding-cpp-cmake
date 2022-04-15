#ifndef _WX_MY_FRAME_H_
#define _WX_MY_FRAME_H_

#include <wx/frame.h>

class MyFrame : public wxFrame
{
    DECLARE_DYNAMIC_CLASS(MyFrame)
    DECLARE_EVENT_TABLE()

public:
    MyFrame() : wxFrame()
    {
    }

    MyFrame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnSize(wxSizeEvent &event);
    void OnButtonOK(wxCommandEvent &event);
};

#endif /* _WX_MY_FRAME_H_ */
