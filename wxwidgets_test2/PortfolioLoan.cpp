#include "PortfolioLoan.h"


BEGIN_EVENT_TABLE(PortfolioLoan, wxDialog)

END_EVENT_TABLE()
PortfolioLoan::PortfolioLoan(wxFrame* parent)
	:wxDialog(parent, wxID_ANY, wxT("PortfolioLoan"))
{
	wxBoxSizer* rowSizer;
    /*计算方式*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString strings_CalculateType;
    strings_CalculateType.Add(wxT("根据面积、单价计算"));
    strings_CalculateType.Add(wxT("根据贷款总额计算"));
    wxComboBox* Choice_CalculateType = new wxComboBox(this, ID_CHOICE_CALCULATE_TYPE,
        wxT("根据面积、单价计算"),
        wxDefaultPosition, wxDefaultSize, strings_CalculateType, wxALIGN_RIGHT | wxCB_DROPDOWN | wxCB_READONLY);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("计算方式: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    Choice_CalculateType->SetSelection(0);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(Choice_CalculateType, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    /*房屋单价*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);

    InputPrice = new wxTextCtrl(this, ID_TEXTCTRL_HOUSE_PRICE,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);//创建输入框//InputPrice->SetExtraStyle(wxWS_EX_PROCESS_UI_UPDATES);//强制二次更新
    InputPrice->SetHint("输入房屋单价(元/平米)");
    InputPrice->SetMaxLength(9);

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("房屋单价: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputPrice, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    /*房屋面积*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    InputSquare = new wxTextCtrl(this, ID_TEXTCTRL_HOUSE_SQUARE,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);//InputSquare->SetExtraStyle(wxWS_EX_PROCESS_UI_UPDATES);//强制二次更新
    InputSquare->SetHint("输入房屋面积(平方米)");
    InputSquare->SetMaxLength(6);

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("房屋面积: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputSquare, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    /*贷款总额*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    InputTotalLoan = new wxTextCtrl(this, ID_TEXTCRTL_TOTAL_LOAN,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);
    InputTotalLoan->SetHint("请输入贷款总额(万元)");

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("贷款总额: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputTotalLoan, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	
}

PortfolioLoan::~PortfolioLoan()
{
}
