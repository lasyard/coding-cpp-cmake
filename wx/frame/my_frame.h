#ifndef _FRAME_MY_FRAME_H_
#define _FRAME_MY_FRAME_H_

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

    virtual void OnExit(wxCommandEvent &event);
    virtual void OnClose(wxCloseEvent &event);
    virtual void OnAbout(wxCommandEvent &event);
    virtual void OnSize(wxSizeEvent &event);
    virtual void OnButtonOK(wxCommandEvent &event);

private:
    const wxChar *TM() const
    {
        return GetClassInfo()->GetClassName();
    };
};

#endif /* _FRAME_MY_FRAME_H_ */
