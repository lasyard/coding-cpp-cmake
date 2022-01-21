#ifndef _WX_MY_APP_H_
#define _WX_MY_APP_H_

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

DECLARE_APP(MyApp)

#endif /* _WX_MY_APP_H_ */
