#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
    cApp();
    ~cApp();

private:
    cMain *m_framel = nullptr;

public:
    virtual bool OnInit();
};
