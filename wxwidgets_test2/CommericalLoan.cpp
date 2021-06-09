#include "CommercialLoan.h"
#include"cPanel.h"

#include "wx/choice.h"
#include "wx/stattext.h"
#include "wx/statline.h"
#include "wx/grid.h"

#include <wx/numformatter.h>                                    //设置精度

#include<cctype>
#include<string>
#include<cmath>
#define isDigit(c) c<='9'&&c>='0'

BEGIN_EVENT_TABLE(CommercialLoan,wxDialog)
    EVT_COMBOBOX(ID_CHOICE_CALCULATE_TYPE,                      CommercialLoan::OnSetCalculateType)
    EVT_COMBOBOX(ID_CHOICE_INTEREST_TYPE,                       CommercialLoan::OnSetInterestType)
    

    EVT_COMBOBOX(ID_CHOICE_LTV,                                 CommercialLoan::OnSetLoanToValue)
    EVT_COMBOBOX(ID_CHOICE_LTY,                                 CommercialLoan::OnSetMonth)        

	EVT_TEXT(ID_TEXTCTRL_HOUSE_SQUARE,                          CommercialLoan::OnSetHouseSquare)
    EVT_TEXT(ID_TEXTCTRL_HOUSE_PRICE,                           CommercialLoan::OnSetHousePrice)   
    EVT_TEXT(ID_TEXTCRTL_TOTAL_LOAN,                            CommercialLoan::OnSetTotalLoan)               
    EVT_TEXT(ID_TEXTCTRL_CHOSEN_TYPE_SHOW_INTEREST,             CommercialLoan::OnUpdateShowInterest)
    EVT_TEXT(ID_TEXTCTRL_PERCENTAGE_POINT,                      CommercialLoan::OnUpdateShowPoint)

    EVT_CHECKBOX(ID_CHECKBOX_REPAYTYPE_PRINCIPAL_INTEREST,      CommercialLoan::OnSetRepayType)
    EVT_CHECKBOX(ID_CHECKBOX_REPAYTYPE_PRINCIPAL,               CommercialLoan::OnSetRepayType)

    EVT_BUTTON(ID_BUTTON_ACTION,                                CommercialLoan::OnActionButton)
    EVT_BUTTON(ID_BUTTON_CLEAR,                                 CommercialLoan::OnClearButton)
END_EVENT_TABLE()
CommercialLoan::CommercialLoan(wxFrame*Frame)
	:wxDialog(Frame, wxID_ANY, "CommercialLoan",
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)

{
	wxBoxSizer* rowSizer ;
    /*计算方式*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString strings_CalculateType;
    strings_CalculateType.Add(wxT("根据面积、单价计算"));
	strings_CalculateType.Add(wxT("根据贷款总额计算"));
	wxComboBox* Choice_CalculateType = new wxComboBox(this, ID_CHOICE_CALCULATE_TYPE,
        wxT("根据面积、单价计算"),
		wxDefaultPosition, wxDefaultSize, strings_CalculateType, wxALIGN_RIGHT|wxCB_DROPDOWN|wxCB_READONLY);
	StaticText = new wxStaticText(this, wxID_ANY,
		wxT("计算方式: "),
		wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    Choice_CalculateType->SetSelection(0);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
	rowSizer->Add(StaticText);
    rowSizer->Add(Choice_CalculateType,1);
    
    Sizer->Add(rowSizer, 1, wxEXPAND| wxLEFT | wxRIGHT | wxTOP, 10);
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
	rowSizer->Add(InputPrice,1);
    
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
    rowSizer->Add(InputSquare,1);
    
    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    
    /*贷款总额*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    InputTotalLoan = new wxTextCtrl(this, ID_TEXTCRTL_TOTAL_LOAN,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);
    InputTotalLoan->SetHint("请输入贷款总额(万元)");
    InputTotalLoan->Enable(false);                                                          //初始设定为不可用

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("贷款总额: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputTotalLoan, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    /*按揭成数*/
	rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString strings_LTV;
    strings_LTV.Add(wxT("8成"));
    strings_LTV.Add(wxT("7.5成"));
    strings_LTV.Add(wxT("7成"));
    strings_LTV.Add(wxT("6.5成"));
    strings_LTV.Add(wxT("6成"));
    strings_LTV.Add(wxT("5.5成"));
    strings_LTV.Add(wxT("5成"));
    strings_LTV.Add(wxT("4.5成"));
    strings_LTV.Add(wxT("4成"));
    strings_LTV.Add(wxT("3.5成"));
    strings_LTV.Add(wxT("3.0成"));
    strings_LTV.Add(wxT("2.5成"));
    strings_LTV.Add(wxT("2成"));
    Choice_LoanMortgages = new wxComboBox(this, ID_CHOICE_LTV,wxT("8"),
		wxDefaultPosition, wxDefaultSize, strings_LTV, wxALIGN_RIGHT|wxCB_DROPDOWN | wxCB_READONLY);
	Choice_LoanMortgages->SetSelection(0);//Choice_LoanMortgages->SetExtraStyle(wxWS_EX_PROCESS_UI_UPDATES);//强制二次更新

    StaticText = new wxStaticText(this, wxID_ANY,
		wxT("按揭成数: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(Choice_LoanMortgages,1);
    
    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    
    /*按揭年数*/
	rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString strings_LTY;
    strings_LTY.Add(wxT("1年(12期)"));
    strings_LTY.Add(wxT("2年(24期)"));
    strings_LTY.Add(wxT("3年(36期)"));
    strings_LTY.Add(wxT("4年(48期)"));
    strings_LTY.Add(wxT("5年(60期)"));
    strings_LTY.Add(wxT("6年(72期)"));
    strings_LTY.Add(wxT("7年(84期)"));
    strings_LTY.Add(wxT("8年(96期)"));
    strings_LTY.Add(wxT("9年(108期)"));
    strings_LTY.Add(wxT("10年(120期)"));
    strings_LTY.Add(wxT("11年(132期)"));
    strings_LTY.Add(wxT("12年(144期)"));
    strings_LTY.Add(wxT("13年(156期)"));
    strings_LTY.Add(wxT("14年(168期)"));
    strings_LTY.Add(wxT("15年(180期)"));
    strings_LTY.Add(wxT("16年(192期)"));
    strings_LTY.Add(wxT("17年(204期)"));
    strings_LTY.Add(wxT("18年(216期)"));
    strings_LTY.Add(wxT("19年(228期)"));
    strings_LTY.Add(wxT("20年(240期)"));
    strings_LTY.Add(wxT("21年(252期)"));
    strings_LTY.Add(wxT("22年(264期)"));
    strings_LTY.Add(wxT("23年(276期)"));
    strings_LTY.Add(wxT("24年(288期)"));
    strings_LTY.Add(wxT("25年(300期)"));
    strings_LTY.Add(wxT("26年(312期)"));
    strings_LTY.Add(wxT("27年(324期)"));
    strings_LTY.Add(wxT("28年(336期)"));
	strings_LTY.Add(wxT("29年(348期)"));
    strings_LTY.Add(wxT("30年(360期)"));
    wxComboBox* choice_LTY = new wxComboBox(this, ID_CHOICE_LTY, wxT("30年(360期)"),
        wxDefaultPosition, wxDefaultSize, strings_LTY, wxCB_DROPDOWN|wxCB_READONLY );
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("按揭年数："),
		wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(choice_LTY,1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    /*                     ____    ____   ____
    //利率方式----双控件  |____|: |____| |___%|
    */
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_InterestType = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("利率方式: "), wxDefaultPosition, wxDefaultSize);
    sizer_InterestType->Add(StaticText);

    wxBoxSizer* sizer_InterestChoose = new wxBoxSizer(wxHORIZONTAL);//分成两个grid控件,由父grid空间帮助调整
    wxArrayString string_IT;
	string_IT.Add(wxT("最新报价利率（LPR）"));
    string_IT.Add(wxT("基准利率"));
    string_IT.Add(wxT("基准利率下限（7折）"));
    string_IT.Add(wxT("基准利率上限（1.1倍）"));
    string_IT.Add(wxT("基准利率上限（1.05倍）"));
    string_IT.Add(wxT("基准利率下限（85折）"));
	wxComboBox* Choice_InteresetType = new wxComboBox(this, ID_CHOICE_INTEREST_TYPE, wxT("最新报价利率（LPR）"),
		wxDefaultPosition, wxDefaultSize, string_IT, wxCB_DROPDOWN | wxCB_READONLY);
    ChosenType_ShowInterest = new wxTextCtrl(this, ID_TEXTCTRL_CHOSEN_TYPE_SHOW_INTEREST, "4.65", wxDefaultPosition, wxDefaultSize);
    ChosenType_ShowInterest->SetMaxLength(3);
    

    sizer_InterestChoose->SetMinSize(wxSize(100, StaticText->GetMinHeight()));
    sizer_InterestChoose->Add(Choice_InteresetType);
    sizer_InterestChoose->Add(20, 0);
    sizer_InterestChoose->Add(ChosenType_ShowInterest);
    sizer_InterestChoose->Add(new wxStaticText(this, wxID_ANY, "(%)"));

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(sizer_InterestType);//添加双控件
    rowSizer->Add(sizer_InterestChoose,1, wxEXPAND);
    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //基点    
	rowSizer = new wxBoxSizer(wxHORIZONTAL);
    InputPercentagePoint = new wxTextCtrl(this, ID_TEXTCTRL_PERCENTAGE_POINT,
		wxEmptyString, wxDefaultPosition, wxDefaultSize);
    InputPercentagePoint->SetHint("BP(‱)");
    InputPercentagePoint->SetMaxLength(4);

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("基点: "), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
	rowSizer->Add(25, 0);
    rowSizer->Add(InputPercentagePoint,1);
    
	Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    
    
    /*                     ____    ____   ____   _____
      计算利率----双控件  |____|: |____|+|____|=|_____|
    */
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_Text = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("商业利率: "), wxDefaultPosition, wxDefaultSize);
    sizer_Text->Add(StaticText);

    wxBoxSizer* sizer_ShowInterest = new wxBoxSizer(wxHORIZONTAL);
    ShowInterest = new wxTextCtrl(this, ID_TEXTCTRL_SHOW_INTEREST,
        wxT("4.65"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    sizer_ShowInterest->Add(ShowInterest);
    
    sizer_ShowInterest->Add(new wxStaticText(this, wxID_ANY,
        wxT("(%)+"), wxDefaultPosition, wxDefaultSize));
    ShowPoint= new wxTextCtrl(this, ID_TEXTCTRL_SHOW_POINT,
        wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    
    sizer_ShowInterest->Add(ShowPoint);
    sizer_ShowInterest->Add(new wxStaticText(this, wxID_ANY,
        wxT("(%)="), wxDefaultPosition, wxDefaultSize));
    
    ShowInterestResult = new wxTextCtrl(this, ID_TEXTCTRL_SHOW_RESULT,
		wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	sizer_ShowInterest->Add(ShowInterestResult);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(sizer_Text);
    rowSizer->Add(sizer_ShowInterest);

	Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    //还款方式
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_Text_Repay = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("还款方式: "), wxDefaultPosition, wxDefaultSize);
    sizer_Text_Repay->Add(StaticText);

    CheckRepayByInterest = new wxCheckBox(this, ID_CHECKBOX_REPAYTYPE_PRINCIPAL_INTEREST, wxT("等额本息"));
    CheckRepayByPricipal = new wxCheckBox(this, ID_CHECKBOX_REPAYTYPE_PRINCIPAL, wxT("等额本金"));
    wxBoxSizer* sizer_CheckBox = new wxBoxSizer(wxHORIZONTAL);
    sizer_CheckBox->SetMinSize(wxSize(100, StaticText->GetMinHeight()));
    sizer_CheckBox->Add(CheckRepayByInterest);
    sizer_CheckBox->Add(CheckRepayByPricipal);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(sizer_Text_Repay);
    rowSizer->Add(sizer_CheckBox);
    
    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    
    //
    Sizer->Add(
        new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(3, 3), wxHORIZONTAL),
        wxSizerFlags().Expand());
    //计算按钮
    rowSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* ActionButton = new wxButton(this, ID_BUTTON_ACTION, "开始计算");
    wxButton* ClearButton = new wxButton(this, ID_BUTTON_CLEAR, "清空重填");

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(ActionButton);
    rowSizer->Add(ClearButton);

    Sizer->Add(rowSizer, wxSizerFlags().Center());

    //适配母框架
    this->SetSizer(Sizer);
    Sizer->SetSizeHints(this);

    this->SetSize(60, 240);
    this->Centre();
    this->ShowModal();

}
CommercialLoan::~CommercialLoan()
{
}
void CommercialLoan::OnSetCalculateType(wxCommandEvent& event)
{
    if (event.GetSelection() == 0) {                            //选择按房屋计算
        InputPrice->Enable(true);
        InputSquare->Enable(true);

        InputTotalLoan->Clear();
        InputTotalLoan->Enable(false);                          //禁用并清空InoutTotalLoan
        Choice_LoanMortgages->Enable(true);
        
        ChooseByHouse = true;
        ChooseByTotalLoan = false;
        TotalLoan = 0;
    }
    else if (event.GetSelection() == 1) {                       //选择按总额计算
        InputPrice->Clear();
        InputPrice->Enable(false);
        InputSquare->Clear();
        InputSquare->Enable(false);                             //禁用并清空面积和单价输入


        InputTotalLoan->Enable(true);
        Choice_LoanMortgages->Enable(false);

        ChooseByTotalLoan = true;
        ChooseByHouse = false;

        HousePrice = 0;
        HouseSquare = 0;
        DownPayment = 0;
	}
}
void CommercialLoan::OnSetInterestType(wxCommandEvent& event)
{

    if (event.GetSelection() == 0) {
        InputPercentagePoint->Enable(true);
        ShowInterest->Enable(true);
        ShowPoint->Enable(true);

        ChosenType_ShowInterest->SetValue("4.65");                              //string_IT.Add(wxT("最新报价利率（LPR）"));
	}
    else if (event.GetSelection() >= 1){
        InputPercentagePoint->Clear();
        InputPercentagePoint->Enable(false);                                    //禁用并清空InputPoint
        ShowInterest->Enable(false);                                            //禁用ShowInterest
        ShowPoint->Clear();                                                     //禁用并清空ShowPoint
        ShowPoint->Enable(false);

        ShowInterestResult->Clear();        
        ShowInterestResult->Enable(false);                                      //禁用并清空ShowInterestResult
                                                                                
        switch (event.GetSelection()) {
            case 1:
             
                ChosenType_ShowInterest->SetValue("4.9");                       //string_IT.Add(wxT("基准利率"));
                break;
            case 2:
                ChosenType_ShowInterest->SetValue("3.43");                      //string_IT.Add(wxT("基准利率下限（7折）"));
                break;
            case 3:
                ChosenType_ShowInterest->SetValue("5.39");                      //string_IT.Add(wxT("基准利率上限（1.1倍）"));
                break;
            case 4:
                ChosenType_ShowInterest->SetValue("5.15");                      //string_IT.Add(wxT("基准利率上限（1.05倍）"));
                break;
            case 5:
                ChosenType_ShowInterest->SetValue("4.17");                      //string_IT.Add(wxT("基准利率下限（85折）"));
                break;
            default:
                break;
        }
    }
}

void CommercialLoan::OnSetRepayType(wxCommandEvent& event)
{
    static bool ChooseInterest = false;
    static bool ChoosePrinciple = false;
    //调整避免复选
    if (event.GetId()== ID_CHECKBOX_REPAYTYPE_PRINCIPAL_INTEREST) {                             //等额本金
        if (!ChooseInterest) {
            CheckRepayByPricipal->Enable(false);
            ChooseInterest = true;
        }
        else if (ChooseInterest) {
            CheckRepayByInterest->Enable(true);
            CheckRepayByPricipal->Enable(true);
            ChooseInterest = false;
        }
    }
    else if(event.GetId() == ID_CHECKBOX_REPAYTYPE_PRINCIPAL){                                  //等额本息
        if (!ChoosePrinciple) {
            CheckRepayByInterest->Enable(false);
            ChoosePrinciple = true;
        }
        else if (ChoosePrinciple) {
            CheckRepayByInterest->Enable(true);
            CheckRepayByPricipal->Enable(true);
            ChoosePrinciple = false;
        }
    }
}

void CommercialLoan::OnSetHousePrice(wxCommandEvent& event)
{
    if (InputPrice->IsEmpty()) {
        event.Skip();
    }

    wxString InputPrice_string = InputPrice->GetLineText(0);
    for (int i = 0; i < InputPrice->GetLineLength(0); i++) {
        if (!wxIsxdigit(InputPrice_string[i])) {                                                    //输入不合法
            InputPrice->Clear();                                                                    //清空输入
            ProcessInputPriceError();
        }
    }
    if (!InputPrice->IsEmpty() && !InputPrice->GetLineText(0).ToDouble(&HousePrice)) {              //输入合法，将数据送入指定变量
        /*error*/
    }

}

void CommercialLoan::OnSetHouseSquare(wxCommandEvent& event)
{
    if (InputSquare->IsEmpty()) {
        event.Skip();
    }
    wxString InputSquare_string = InputSquare->GetLineText(0);
    for (int i = 0; i<InputSquare->GetLineLength(0); i++) {
        if (!wxIsxdigit(InputSquare_string[i])) {                                                   //输入不合法
            InputSquare->Clear();                                                                   //清空输入
            ProcessInputSquareError();

        }
    }
    if (!InputSquare->IsEmpty()&&!InputSquare->GetLineText(0).ToDouble(&HouseSquare)) {             //输入合法，将数据送入指定变量
        /*error*/
    }
    
}
void CommercialLoan::OnSetTotalLoan(wxCommandEvent& event)
{
    if (InputTotalLoan->IsEmpty()) {
        event.Skip();
    }

    wxString InputTotalLoan_string = InputTotalLoan->GetLineText(0);
    for (int i = 0; i < InputTotalLoan->GetLineLength(0); i++) {
        if (!wxIsxdigit(InputTotalLoan_string[i])) {                                                    //输入不合法
            InputTotalLoan->Clear();                                                                    //清空输入
            ProcessInputTotalLoanError();
        }
    }
    if (!InputTotalLoan->IsEmpty() && !InputTotalLoan->GetLineText(0).ToDouble(&TotalLoan)) {          //输入合法，将数据送入指定变量
        /*error*/
    }

}

void CommercialLoan::OnSetLoanToValue(wxCommandEvent& event)                                            //按揭成数
{
    double InitialValue = 0.8;
    LoanToValue = InitialValue - 0.05 * event.GetSelection();
}

void CommercialLoan::OnSetMonth(wxCommandEvent& event)                                                  //还款次数
{
    double InitialValue = 360;
	Months = InitialValue - 12 * event.GetSelection();
}



void CommercialLoan::OnUpdateShowInterest(wxCommandEvent& event) {
    ShowInterest->SetValue(
        ChosenType_ShowInterest->GetLineText(0)
    );
}

void CommercialLoan::OnUpdateShowPoint(wxCommandEvent& event)                            //显示基点
{   
    if (InputPercentagePoint->IsEmpty()) {
        event.Skip();
    }
    wxString InputPercentagePoint_string = InputPercentagePoint->GetLineText(0);
	for (int i = 0; i < InputPercentagePoint->GetLineLength(0); i++) {                  //基点输入异常处理
        if (!wxIsdigit(InputPercentagePoint_string[i])) {
            InputPercentagePoint->Clear();
            ProcessInputPercentagePointError();
        }
    }
    if (!InputPercentagePoint->IsEmpty()) {                                             //正常输入存入数据
        if (!InputPercentagePoint->GetLineText(0).ToDouble(&BasePoint)) {
			/*error*/
        }
        BasePoint /= 100.0;

        int accurracy = 2;
        ShowPoint->SetValue(wxNumberFormatter::ToString(BasePoint, accurracy));

		OnGetInterestResult();
    }
}

void CommercialLoan::OnGetInterestResult()                                                                  //显示计算所得年利率
{
    if (!ShowInterest->GetLineText(0).ToDouble(&InitialInterest)) {
        /*error*/
    }
    ResultIntersetRate = BasePoint + InitialInterest;
    
    int accurracy = 2;
    ShowInterestResult->SetValue(wxNumberFormatter::ToString(ResultIntersetRate, accurracy));

}

void CommercialLoan::OnActionButton(wxCommandEvent& event)
{
    ///*处理checkbox异常*/
    //if (!CheckRepayByPricipal->IsChecked() || !CheckRepayByInterest->IsChecked()) {                       //异常处理，防止用户没有选择checkbox
    //    ProcessCheckBoxError();
    //}
    /*checkbox选择后可进行操作*/
	 if (CheckRepayByPricipal->IsChecked()) {
         if (ChooseByHouse) {                                                                                //选择按房屋计算但并没有填入数据
             if (InputPrice->IsEmpty()) {
                 ProcessInputPriceEmptyError();
             }
             else if (InputSquare->IsEmpty()) {
                 ProcessInputSquareEmptyError();
             }
             else if (InputPercentagePoint->IsEmpty()) {
                 ProcessInputPercentagePointEmptyError();
             }
             else {
                 ProcessDataByPrinciple();
                 ResultByPricipalDialog();
			 }
		 }
         else if (ChooseByTotalLoan) {
             if (InputTotalLoan->IsEmpty()) {
                 ProcessInputTotalLoanEmptyError();
             }
         }
	 }
    else if (CheckRepayByInterest->IsChecked()) {
        ProcessDataByInterest();
		ResultByInterestDialog();
    }
}

void CommercialLoan::OnClearButton(wxCommandEvent& event)
{
    InputPrice->Clear();
    InputSquare->Clear();
    InputTotalLoan->Clear();
	InputPercentagePoint->Clear();
}

void CommercialLoan::ProcessDataByPrinciple()                                          
{
    if (HouseSquare != 0 && HousePrice != 0) {                                                          //等额本金
        TotalLoan = HouseSquare * HousePrice * LoanToValue;
		DownPayment = HouseSquare * HousePrice - TotalLoan;
    }

    MonthInterestRate = ResultIntersetRate / Months;                                    //月利率

    MonthPrincipalRepay = TotalLoan / Months;                                           //当月本金还款 = 本金/还款次数,    还款次数 = 期数
	FirstMonthInterest = TotalLoan * (1 - (1 - 1) / Months) * MonthInterestRate;        //当月利息 = (本金-已还本金)*月利率 = 本金*{ [ 1- (还款月数 - 1)/还款次数 ] }*月利率     还款月数:第一月为1,...                                                    
	FirstMonthRepay = MonthPrincipalRepay + FirstMonthInterest;                         //首月月供 = 本金还款+月利息
                                                                                        //每月月供 = 本金还款+月利息
    double SecondMonthInterest = TotalLoan * (1 - (2 - 1) / Months) * MonthInterestRate;//第二月利息
    double SecondMonthRepay = MonthPrincipalRepay + FirstMonthInterest;                 //第二月月供

    MonthlyReduce = FirstMonthRepay - SecondMonthInterest;                              //每月递减
	TotalInterest = TotalLoan * MonthInterestRate * (Months + 1) / 2;                   //总利息=总贷款数×月利率×（还款次数＋1）÷2
    TotalRepay = TotalInterest + TotalLoan;
}

void CommercialLoan::ProcessDataByInterest()                                            //等额本息
{
    if (HouseSquare != 0 && HousePrice != 0) {                                          
        TotalLoan = HouseSquare * HousePrice * LoanToValue;
		DownPayment = HouseSquare * HousePrice - TotalLoan;
    }
    MonthInterestRate = ResultIntersetRate / Months;                                    //月利率
    EveryMonthRepay = TotalLoan * MonthInterestRate *
		pow(1 + MonthInterestRate, Months) / (pow(1 + MonthInterestRate, Months) - 1);  //每月付款
    TotalInterest = EveryMonthRepay * Months - TotalLoan;                               //全部利息
    TotalRepay = EveryMonthRepay * Months;                                              //全部还款
}
void CommercialLoan::ResultByPricipalDialog()
{
    wxDialog* ReaultDialog = new wxDialog(this, wxID_ANY,
        wxT("结果"), wxDefaultPosition, wxDefaultSize);
    wxBoxSizer* colSizer= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rowSizer;
    int accurracy = 2;
    //
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("结果："));

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //首付
    if (ChooseByHouse) {
        rowSizer = new wxBoxSizer(wxHORIZONTAL);

        StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("首付: "), wxDefaultPosition, wxDefaultSize);
        wxTextCtrl* OutputDownPayment = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(DownPayment, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

        rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
        rowSizer->Add(StaticText);
		rowSizer->Add(25, 0);
        rowSizer->Add(OutputDownPayment, 1);//(wxNumberFormatter::ToString(ResultIntersetRate, accurracy)

		colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    }
	//首月月供
    rowSizer = new wxBoxSizer(wxHORIZONTAL);

    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("首月月供: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputFirstMonthRepay = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(FirstMonthRepay, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputFirstMonthRepay,1);//(wxNumberFormatter::ToString(ResultIntersetRate, accurracy)

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //每月递减
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("每月递减: "), wxDefaultPosition, wxDefaultSize);

    wxTextCtrl* OutputMonthlyReduce = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(MonthlyReduce, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputMonthlyReduce,1);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //贷款总额
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("贷款总额: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputTotalLoan = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(TotalLoan, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputTotalLoan,1);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //支付利息
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("支付利息: "), wxDefaultPosition, wxDefaultSize);
	wxTextCtrl* OutputTotalInterest = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(TotalInterest, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputTotalInterest,1);
    
    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //还款总额
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("还款总额: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputTotalRepay = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(TotalRepay, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputTotalRepay,1);
    
    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //还款月数
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("还款月数: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputMonths = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(Months, 0), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputMonths,1);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    //

    ReaultDialog->SetSizer(colSizer);
    ReaultDialog->ShowModal();

}
//等额本息
void CommercialLoan::ResultByInterestDialog()
{
    wxDialog* ReaultDialog = new wxDialog(this, wxID_ANY,
        wxT("结果"), wxDefaultPosition, wxDefaultSize);
    wxBoxSizer* colSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rowSizer;
    int accurracy = 2;
    //
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("结果："));

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //首付
    if (ChooseByHouse) {
        rowSizer = new wxBoxSizer(wxHORIZONTAL);

        StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("首付: "), wxDefaultPosition, wxDefaultSize);
        wxTextCtrl* OutputDownPayment = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(DownPayment, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

        rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
        rowSizer->Add(StaticText);
        rowSizer->Add(25, 0);
        rowSizer->Add(OutputDownPayment, 1);//(wxNumberFormatter::ToString(ResultIntersetRate, accurracy)

        colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    }
    //每月月供：
    rowSizer = new wxBoxSizer(wxHORIZONTAL);

    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("每月月供："), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputEveryMonthRepay = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(EveryMonthRepay, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputEveryMonthRepay, 1);//(wxNumberFormatter::ToString(ResultIntersetRate, accurracy)

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    //贷款总额
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("贷款总额: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputTotalLoan = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(TotalLoan, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputTotalLoan, 1);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //支付利息
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("支付利息: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputTotalInterest = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(TotalInterest, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputTotalInterest, 1);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //还款总额
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("还款总额: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputTotalRepay = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(TotalRepay, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputTotalRepay, 1);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //还款月数
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("还款月数: "), wxDefaultPosition, wxDefaultSize);
    wxTextCtrl* OutputMonths = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(Months, 0), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputMonths, 1);

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    //

    ReaultDialog->SetSizer(colSizer);
	ReaultDialog->ShowModal();
}


void CommercialLoan::ProcessInputPriceError()
{
    wxMessageDialog* dialog_NotInputHousePrice = new wxMessageDialog(this,                         //给予用户提示
        "This is a message box",
        "Message box text",
        wxCENTER |
        wxNO_DEFAULT | wxYES_NO | wxCANCEL |
        wxICON_INFORMATION);

    wxString extmsg;
    if (dialog_NotInputHousePrice->SetYesNoCancelLabels
    (
        "Answer &Yes",
        "Answer &No",
        "Refuse to answer"
    ))
    {
        extmsg = "You have just input an ilegal char,\n"
            "Please input a digit .";
    }
    else
    {
        extmsg = "Custom button labels are not supported on this platform,\n"
            "so the default \"Yes\"/\"No\"/\"Cancel\" buttons are used.";
    }
    dialog_NotInputHousePrice->SetExtendedMessage(extmsg);
    dialog_NotInputHousePrice->Bind(wxEVT_WINDOW_MODAL_DIALOG_CLOSED,
        &CommercialLoan::MessageBoxWindowModalClosed, this);
    dialog_NotInputHousePrice->ShowWindowModal();
}

void CommercialLoan::ProcessInputSquareError()
{
    wxMessageDialog* dialog_NotInputHouseSquare = new wxMessageDialog(this,                         //用户提示信息
        "This is a message box",
        "Message box text",
        wxCENTER |
        wxNO_DEFAULT | wxYES_NO | wxCANCEL |
        wxICON_INFORMATION);

    wxString extmsg;
    if (dialog_NotInputHouseSquare->SetYesNoCancelLabels
    (
        "Answer &Yes",
        "Answer &No",
        "Refuse to answer"
    ))
    {
        extmsg = "You have just input an ilegal char,\n"
            "Please input a digit .";
    }
    else
    {
        extmsg = "Custom button labels are not supported on this platform,\n"
            "so the default \"Yes\"/\"No\"/\"Cancel\" buttons are used.";
    }
    dialog_NotInputHouseSquare->SetExtendedMessage(extmsg);
    dialog_NotInputHouseSquare->Bind(wxEVT_WINDOW_MODAL_DIALOG_CLOSED,
        &CommercialLoan::MessageBoxWindowModalClosed, this);
    dialog_NotInputHouseSquare->ShowWindowModal();
}

void CommercialLoan::ProcessInputTotalLoanError()
{
    wxMessageDialog* dialog_NotInputTotalLoan = new wxMessageDialog(this,                             //给予用户提示
        "This is a message box",
        "Message box text",
        wxCENTER |
        wxNO_DEFAULT | wxYES_NO | wxCANCEL |
        wxICON_INFORMATION);

    wxString extmsg;
    if (dialog_NotInputTotalLoan->SetYesNoCancelLabels
    (
        "Answer &Yes",
        "Answer &No",
        "Refuse to answer"
    ))
    {
        extmsg = "You have just input an ilegal char,\n"
            "Please input a digit .";
    }
    else
    {
        extmsg = "Custom button labels are not supported on this platform,\n"
            "so the default \"Yes\"/\"No\"/\"Cancel\" buttons are used.";
    }
    dialog_NotInputTotalLoan->SetExtendedMessage(extmsg);
    dialog_NotInputTotalLoan->Bind(wxEVT_WINDOW_MODAL_DIALOG_CLOSED,
        &CommercialLoan::MessageBoxWindowModalClosed, this);
    dialog_NotInputTotalLoan->ShowWindowModal();
}
void CommercialLoan::ProcessInputPercentagePointError()
{
    wxMessageDialog* dialog_NotInputTotalLoan = new wxMessageDialog(this,                             //给予用户提示
        "This is a message box",
        "Message box text",
        wxCENTER |
        wxNO_DEFAULT | wxYES_NO | wxCANCEL |
        wxICON_INFORMATION);

    wxString extmsg;
    if (dialog_NotInputTotalLoan->SetYesNoCancelLabels
    (
        "Answer &Yes",
        "Answer &No",
        "Refuse to answer"
    ))
    {
        extmsg = "You have just input an ilegal char,\n"
            "Please input a digit .";
    }
    else
    {
        extmsg = "Custom button labels are not supported on this platform,\n"
            "so the default \"Yes\"/\"No\"/\"Cancel\" buttons are used.";
    }
    dialog_NotInputTotalLoan->SetExtendedMessage(extmsg);
    dialog_NotInputTotalLoan->Bind(wxEVT_WINDOW_MODAL_DIALOG_CLOSED,
        &CommercialLoan::MessageBoxWindowModalClosed, this);
	dialog_NotInputTotalLoan->ShowWindowModal();
}
void CommercialLoan::ProcessCheckBoxError()
{
    wxMessageDialog* dialog_NotSelectCheckBox = new wxMessageDialog(this,                             //给予用户提示
        "This is a message box",
        "Message box text",
        wxCENTER |
        wxNO_DEFAULT | wxYES_NO | wxCANCEL |
        wxICON_INFORMATION);

    wxString extmsg;
    if (dialog_NotSelectCheckBox->SetYesNoCancelLabels
    (
        "Answer &Yes",
        "Answer &No",
        "Refuse to answer"
    ))
    {
        extmsg = "You didn't Select The CheckBox,\n"
            "Please Select One.";
    }
    else
    {
        extmsg = "Custom button labels are not supported on this platform,\n"
            "so the default \"Yes\"/\"No\"/\"Cancel\" buttons are used.";
    }
    dialog_NotSelectCheckBox->SetExtendedMessage(extmsg);
    dialog_NotSelectCheckBox->Bind(wxEVT_WINDOW_MODAL_DIALOG_CLOSED,
        &CommercialLoan::MessageBoxWindowModalClosed, this);
	dialog_NotSelectCheckBox->ShowWindowModal();
}

void CommercialLoan::ProcessInputPriceEmptyError()
{
}

void CommercialLoan::ProcessInputSquareEmptyError()
{
}

void CommercialLoan::ProcessInputPercentagePointEmptyError()
{
}

void CommercialLoan::ProcessInputTotalLoanEmptyError()
{
}

void CommercialLoan::MessageBoxWindowModalClosed(wxWindowModalDialogEvent& event)
{
    wxDialog* dialog = event.GetDialog();
    switch (dialog->GetReturnCode())
    {
    case wxID_YES:
        wxLogStatus("You pressed \"Yes\"");
        break;

    case wxID_NO:
        wxLogStatus("You pressed \"No\"");
        break;

    case wxID_CANCEL:
        wxLogStatus("You pressed \"Cancel\"");
        break;

    default:
        wxLogError("Unexpected wxMessageDialog return code!");
    }
    delete dialog;
}
