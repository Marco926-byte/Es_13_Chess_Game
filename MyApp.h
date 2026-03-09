#ifndef MYAPP_H
#define MYAPP_H

#include "wx/wx.h"
#include "Es13.h"
#include "wx/image.h"
#include <list>

class MyApp: public wxApp
{
private:
    /* data */
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);

#endif //MYAPP_H