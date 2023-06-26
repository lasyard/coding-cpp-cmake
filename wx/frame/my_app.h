#ifndef _FRAME_MY_APP_H_
#define _FRAME_MY_APP_H_

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
    virtual int OnExit() override;

private:
    const wxChar *TM() const
    {
        return GetClassInfo()->GetClassName();
    };
};

DECLARE_APP(MyApp)

#endif /* _FRAME_MY_APP_H_ */
