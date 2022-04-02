#ifndef _WX_MY_FRAME_H_
#define _WX_MY_FRAME_H_

#include <wx/frame.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnSize(wxSizeEvent &event);
    void OnButtonOK(wxCommandEvent &event);

private:
    DECLARE_EVENT_TABLE()
};

#endif /* _WX_MY_FRAME_H_ */
