// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#include "PortfolioLoan.h"
#include"cPanel.h"

#include "wx/choice.h"
#include "wx/stattext.h"
#include "wx/statline.h"
#include "wx/grid.h"

#include <wx/numformatter.h>                                    //设置精度

#include<cctype>
#include<string>
#include<cmath>

BEGIN_EVENT_TABLE(PortfolioLoan, wxDialog)
EVT_COMBOBOX(ID_CHOICE_INTEREST_TYPE, PortfolioLoan::OnSetInterestType)


EVT_COMBOBOX(ID_CHOICE_LTY, PortfolioLoan::OnSetMonth)

EVT_TEXT(ID_TEXTCRTL_TOTAL_LOAN, PortfolioLoan::OnSetTotalLoan)
EVT_TEXT(ID_TEXTCTRL_CHOSEN_TYPE_SHOW_INTEREST, PortfolioLoan::OnUpdateShowInterest)
EVT_TEXT(ID_TEXTCTRL_PERCENTAGE_POINT, PortfolioLoan::OnUpdateShowPoint)

EVT_CHECKBOX(ID_CHECKBOX_REPAYTYPE_PRINCIPAL_INTEREST, PortfolioLoan::OnSetRepayType)
EVT_CHECKBOX(ID_CHECKBOX_REPAYTYPE_PRINCIPAL, PortfolioLoan::OnSetRepayType)

EVT_BUTTON(ID_BUTTON_ACTION, PortfolioLoan::OnActionButton)
EVT_BUTTON(ID_BUTTON_CLEAR, PortfolioLoan::OnClearButton)
END_EVENT_TABLE()
PortfolioLoan::PortfolioLoan(wxFrame* Frame)
    :wxDialog(Frame, wxID_ANY,
        wxT("PortfolioLoan"),
        wxDefaultPosition, wxDefaultSize,
        wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)

{
    wxBoxSizer* rowSizer;
    /*商业贷款总额*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    InputCommercialLoan = new wxTextCtrl(this, ID_TEXTCRTL_TOTAL_LOAN,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);
    InputCommercialLoan->SetHint("请输入商业贷款额(万元)");

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("商业贷款总额: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputCommercialLoan, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    /*                         ____    ____   ____
    //商业利率方式----双控件  |____|: |____| |___%|
    */
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_InterestType = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("利率方式: "), wxDefaultPosition, wxDefaultSize);
    sizer_InterestType->Add(StaticText);

    wxBoxSizer* sizer_InterestChoose_CommercialLoan = new wxBoxSizer(wxHORIZONTAL);//分成两个grid控件,由父grid空间帮助调整
    wxArrayString string_IT;
    string_IT.Add(wxT("最新报价利率（LPR）"));
    string_IT.Add(wxT("基准利率"));
    string_IT.Add(wxT("基准利率下限（7折）"));
    string_IT.Add(wxT("基准利率上限（1.1倍）"));
    string_IT.Add(wxT("基准利率上限（1.05倍）"));
    string_IT.Add(wxT("基准利率下限（85折）"));
    wxComboBox* Choice_InteresetType = new wxComboBox(this, ID_CHOICE_INTEREST_TYPE, wxT("最新报价利率（LPR）"),
        wxDefaultPosition, wxDefaultSize, string_IT, wxCB_DROPDOWN | wxCB_READONLY);
    ChosenType_ShowInterest_Commercial = new wxTextCtrl(this, ID_TEXTCTRL_CHOSEN_TYPE_SHOW_INTEREST, "4.65", wxDefaultPosition, wxDefaultSize);
    ChosenType_ShowInterest_Commercial->SetMaxLength(3);


    sizer_InterestChoose_CommercialLoan->SetMinSize(wxSize(100, StaticText->GetMinHeight()));
    sizer_InterestChoose_CommercialLoan->Add(Choice_InteresetType);
    sizer_InterestChoose_CommercialLoan->Add(20, 0);
    sizer_InterestChoose_CommercialLoan->Add(ChosenType_ShowInterest_Commercial);
    sizer_InterestChoose_CommercialLoan->Add(new wxStaticText(this, wxID_ANY, "(%)"));

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(sizer_InterestType);//添加双控件
    rowSizer->Add(sizer_InterestChoose_CommercialLoan, 1, wxEXPAND);
	Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    /*公积金贷款总额*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    ProvidentFund = new wxTextCtrl(this, ID_TEXTCRTL_TOTAL_LOAN,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);
    ProvidentFund->SetHint("请输入公积金贷款额(万元)");

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("公积金贷款总额: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(ProvidentFund, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    /*                           ____    ____   ____
    //公积金利率方式----双控件  |____|: |____| |___%|
    */
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_InterestType_ProvidentFundInterestRate = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("公积金利率: "), wxDefaultPosition, wxDefaultSize);
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
    ChosenType_ShowInterest_Commercial = new wxTextCtrl(this, ID_TEXTCTRL_CHOSEN_TYPE_SHOW_INTEREST, "4.65", wxDefaultPosition, wxDefaultSize);
    ChosenType_ShowInterest_Commercial->SetMaxLength(3);


    sizer_InterestChoose_CommercialLoan->SetMinSize(wxSize(100, StaticText->GetMinHeight()));
    sizer_InterestChoose_CommercialLoan->Add(Choice_InteresetType);
    sizer_InterestChoose_CommercialLoan->Add(20, 0);
    sizer_InterestChoose_CommercialLoan->Add(ChosenType_ShowInterest_Commercial);
    sizer_InterestChoose_CommercialLoan->Add(new wxStaticText(this, wxID_ANY, "(%)"));

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(sizer_InterestType);//添加双控件
    rowSizer->Add(sizer_InterestChoose_CommercialLoan, 1, wxEXPAND);
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
        wxDefaultPosition, wxDefaultSize, strings_LTY, wxCB_DROPDOWN | wxCB_READONLY);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("按揭年数: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(choice_LTY, 1);

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
    rowSizer->Add(InputPercentagePoint, 1);

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
    ShowPoint = new wxTextCtrl(this, ID_TEXTCTRL_SHOW_POINT,
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

    //分割线
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
PortfolioLoan::~PortfolioLoan()
{
}

void PortfolioLoan::OnSetInterestType(wxCommandEvent& event)
{

    if (event.GetSelection() == 0) {
        InputPercentagePoint->Enable(true);
        ShowInterest->Enable(true);
        ShowPoint->Enable(true);

        ChosenType_ShowInterest_Commercial->SetValue("4.65");                              //string_IT.Add(wxT("最新报价利率（LPR）"));
    }
    else if (event.GetSelection() >= 1) {
        InputPercentagePoint->Clear();
        InputPercentagePoint->Enable(false);                                    //禁用并清空InputPoint
        ShowInterest->Enable(false);                                            //禁用ShowInterest
        ShowPoint->Clear();                                                     //禁用并清空ShowPoint
        ShowPoint->Enable(false);

        ShowInterestResult->Clear();
        ShowInterestResult->Enable(false);                                      //禁用并清空ShowInterestResult

        switch (event.GetSelection()) {
        case 1:

            ChosenType_ShowInterest_Commercial->SetValue("4.9");                       //string_IT.Add(wxT("基准利率"));
            break;
        case 2:
            ChosenType_ShowInterest_Commercial->SetValue("3.43");                      //string_IT.Add(wxT("基准利率下限（7折）"));
            break;
        case 3:
            ChosenType_ShowInterest_Commercial->SetValue("5.39");                      //string_IT.Add(wxT("基准利率上限（1.1倍）"));
            break;
        case 4:
            ChosenType_ShowInterest_Commercial->SetValue("5.15");                      //string_IT.Add(wxT("基准利率上限（1.05倍）"));
            break;
        case 5:
            ChosenType_ShowInterest_Commercial->SetValue("4.17");                      //string_IT.Add(wxT("基准利率下限（85折）"));
            break;
        default:
            break;
        }
    }
}

void PortfolioLoan::OnSetRepayType(wxCommandEvent& event)
{
    static bool ChooseInterest = false;
    static bool ChoosePrinciple = false;
    //调整避免复选
    if (event.GetId() == ID_CHECKBOX_REPAYTYPE_PRINCIPAL_INTEREST) {                                             //等额本金
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
    else if (event.GetId() == ID_CHECKBOX_REPAYTYPE_PRINCIPAL) {                                                //等额本息
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

void PortfolioLoan::OnSetTotalLoan(wxCommandEvent& event)
{
    if (InputCommercialLoan->IsEmpty()) {
        event.Skip();
    }

    wxString InputTotalLoan_string = InputCommercialLoan->GetLineText(0);
    for (int i = 0; i < InputCommercialLoan->GetLineLength(0); i++) {
        if (!wxIsxdigit(InputTotalLoan_string[i])) {                                                        //输入不合法
            InputCommercialLoan->Clear();                                                                        //清空输入
            ProcessInputTotalLoanError();
        }
    }
    if (!InputCommercialLoan->IsEmpty() && !InputCommercialLoan->GetLineText(0).ToDouble(&TotalLoan)) {               //输入合法，将数据送入指定变量
        /*error*/
    }

}

void PortfolioLoan::OnSetMonth(wxCommandEvent& event)                                                      //还款次数
{                                                                                                           //还款期限（month）
    double InitialValue = 360;
    Months = InitialValue - 12 * event.GetSelection();
}

void PortfolioLoan::OnUpdateShowInterest(wxCommandEvent& event) {                                          //显示利率方式
    ShowInterest->SetValue(
        ChosenType_ShowInterest_Commercial->GetLineText(0)
    );
}

void PortfolioLoan::OnUpdateShowPoint(wxCommandEvent& event)                                               //显示基点
{
    if (InputPercentagePoint->IsEmpty()) {
        event.Skip();
    }
    wxString InputPercentagePoint_string = InputPercentagePoint->GetLineText(0);
    for (int i = 0; i < InputPercentagePoint->GetLineLength(0); i++) {                                      //基点输入异常处理
        if (!wxIsdigit(InputPercentagePoint_string[i])) {
            InputPercentagePoint->Clear();
            ProcessInputPercentagePointError();
        }
    }
    if (!InputPercentagePoint->IsEmpty()) {                                                                 //正常输入存入数据
        if (!InputPercentagePoint->GetLineText(0).ToDouble(&BasePoint)) {
            /*error*/
        }
        BasePoint /= 100.0;

        int accurracy = 2;
        ShowPoint->SetValue(wxNumberFormatter::ToString(BasePoint, accurracy));

		OnGetInterestResult();                                                                              //输入基点后计算年利率
    }
}

void PortfolioLoan::OnGetInterestResult()                                                                  //显示计算所得年利率
{
    if (!ShowInterest->GetLineText(0).ToDouble(&InitialInterest)) {
        /*error*/
    }
    ResultIntersetRate = BasePoint + InitialInterest / 100;

    int accurracy = 2;
    ShowInterestResult->SetValue(wxNumberFormatter::ToString(ResultIntersetRate, accurracy));

}

void PortfolioLoan::OnActionButton(wxCommandEvent& event)
{
    ///*处理checkbox异常*/
    //if (!CheckRepayByPricipal->IsChecked() || !CheckRepayByInterest->IsChecked()) {                       //异常处理，防止用户没有选择checkbox
    //    ProcessCheckBoxError();
    //}
    /*checkbox选择后可进行操作*/
    if (CheckRepayByPricipal->IsChecked()) {
        if (ChooseByHouse) {                                                                                //选择按房屋计算但并没有填入数据
			if (InputPercentagePoint->IsEmpty()) {
                ProcessInputPercentagePointEmptyError();
            }
            else {
                ProcessDataByPrinciple();
                ResultByPricipalDialog();
            }
        }
        else if (ChooseByTotalLoan) {
            if (InputCommercialLoan->IsEmpty()) {
                ProcessInputTotalLoanEmptyError();
            }
            else {
                ProcessDataByPrinciple();
                ResultByPricipalDialog();
            }
        }
    }
    else if (CheckRepayByInterest->IsChecked()) {
        if (ChooseByHouse) {                                                                                //选择按房屋计算但并没有填入数据
			if (InputPercentagePoint->IsEmpty()) {
                ProcessInputPercentagePointEmptyError();
            }
            else {                                                                                          //异常结束
                ProcessDataByInterest();
                ResultByInterestDialog();
            }
        }
        else if (ChooseByTotalLoan) {
            if (InputCommercialLoan->IsEmpty()) {
                ProcessInputTotalLoanEmptyError();
            }
            else {
                ProcessDataByInterest();
                ResultByInterestDialog();
            }
        }
    }
}

void PortfolioLoan::OnClearButton(wxCommandEvent& event)
{
    InputCommercialLoan->Clear();
    InputPercentagePoint->Clear();
}

void PortfolioLoan::ProcessDataByPrinciple()
{


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

void PortfolioLoan::ProcessDataByInterest()                                            //等额本息
{

    MonthInterestRate = ResultIntersetRate / Months;                                    //月利率
    EveryMonthRepay = TotalLoan * MonthInterestRate *
        pow(1 + MonthInterestRate, Months) / (pow(1 + MonthInterestRate, Months) - 1);  //每月付款
    TotalInterest = EveryMonthRepay * Months - TotalLoan;                               //全部利息
    TotalRepay = EveryMonthRepay * Months;                                              //全部还款
}
void PortfolioLoan::ResultByPricipalDialog()
{
    wxDialog* ReaultDialog = new wxDialog(this, wxID_ANY,
        wxT("结果"), wxDefaultPosition, wxDefaultSize);
    wxBoxSizer* colSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rowSizer;
    int accurracy = 2;
    //
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("结果：(*以下结果仅供参考)"));

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
    rowSizer->Add(OutputFirstMonthRepay, 1);//(wxNumberFormatter::ToString(ResultIntersetRate, accurracy)

    colSizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    //每月递减
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("每月递减: "), wxDefaultPosition, wxDefaultSize);

    wxTextCtrl* OutputMonthlyReduce = new wxTextCtrl(ReaultDialog, wxID_ANY, wxNumberFormatter::ToString(MonthlyReduce, accurracy), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(OutputMonthlyReduce, 1);

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
    colSizer->SetSizeHints(ReaultDialog);
    ReaultDialog->ShowModal();

}
//等额本息
void PortfolioLoan::ResultByInterestDialog()
{
    wxDialog* ReaultDialog = new wxDialog(this, wxID_ANY,
        wxT("结果"), wxDefaultPosition, wxDefaultSize);
    wxBoxSizer* colSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rowSizer;
    int accurracy = 2;
    //
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("结果：(*以下结果仅供参考)"));

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

    StaticText = new wxStaticText(ReaultDialog, wxID_ANY, wxT("每月月供: "), wxDefaultPosition, wxDefaultSize);
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
    colSizer->SetSizeHints(ReaultDialog);
    ReaultDialog->ShowModal();
}


void PortfolioLoan::ProcessInputTotalLoanError()
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
        &PortfolioLoan::MessageBoxWindowModalClosed, this);
    dialog_NotInputTotalLoan->ShowWindowModal();
}
void PortfolioLoan::ProcessInputPercentagePointError()
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
        &PortfolioLoan::MessageBoxWindowModalClosed, this);
    dialog_NotInputTotalLoan->ShowWindowModal();
}
void PortfolioLoan::ProcessCheckBoxError()
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
        &PortfolioLoan::MessageBoxWindowModalClosed, this);
    dialog_NotSelectCheckBox->ShowWindowModal();
}


void PortfolioLoan::ProcessInputPercentagePointEmptyError()
{
    wxMessageDialog* dialog_NotInputPercentagePoint = new wxMessageDialog(this,                             //给予用户提示
        "This is a message box",
        "Message box text",
        wxCENTER |
        wxNO_DEFAULT | wxYES_NO | wxCANCEL |
        wxICON_INFORMATION);

    wxString extmsg;
    if (dialog_NotInputPercentagePoint->SetYesNoCancelLabels
    (
        "Answer &Yes",
        "Answer &No",
        "Refuse to answer"
    ))
    {
        extmsg = "You didn't Input The Percentage Point,\n"
            "Please Input The Number.";
    }
    else
    {
        extmsg = "Custom button labels are not supported on this platform,\n"
            "so the default \"Yes\"/\"No\"/\"Cancel\" buttons are used.";
    }
    dialog_NotInputPercentagePoint->SetExtendedMessage(extmsg);
    dialog_NotInputPercentagePoint->Bind(wxEVT_WINDOW_MODAL_DIALOG_CLOSED,
        &PortfolioLoan::MessageBoxWindowModalClosed, this);
    dialog_NotInputPercentagePoint->ShowWindowModal();
}

void PortfolioLoan::ProcessInputTotalLoanEmptyError()
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
        extmsg = "You didn't Input The Total Loan,\n"
            "Please Input The Number.";
    }
    else
    {
        extmsg = "Custom button labels are not supported on this platform,\n"
            "so the default \"Yes\"/\"No\"/\"Cancel\" buttons are used.";
    }
    dialog_NotInputTotalLoan->SetExtendedMessage(extmsg);
    dialog_NotInputTotalLoan->Bind(wxEVT_WINDOW_MODAL_DIALOG_CLOSED,
        &PortfolioLoan::MessageBoxWindowModalClosed, this);
    dialog_NotInputTotalLoan->ShowWindowModal();
}

void PortfolioLoan::MessageBoxWindowModalClosed(wxWindowModalDialogEvent& event)
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
