#pragma once

#include"wx/wx.h"
#include"cPanel.h"
#include"IDs.h"

#ifndef _PORTFOLIOLOAN_H_
#define _PORTFOLIOLOAN_H_

/*组合贷款类*/
class PortfolioLoan :public wxDialog
{
public:
	PortfolioLoan(wxFrame *parent);
	~PortfolioLoan();

    wxStaticText* StaticText;
    //选则面积后部件更新
    wxTextCtrl* InputCommercialLoan;
    wxTextCtrl* InputProvidentFund;
    wxTextCtrl* InputPercentagePoint;

    wxTextCtrl* ShowCommercialInterestRate;
    wxTextCtrl* ShowInterstPortfolioRate;

    wxTextCtrl* ShowCommercialInterestRate_Update;
    wxTextCtrl* ShowPoint;
    wxTextCtrl* ShowCommercialInterestRateResult;

    wxCheckBox* CheckRepayByInterest;
    wxCheckBox* CheckRepayByPricipal;



    //按揭年数
    double Months = 360;
    //基点,利率
    double InitialInterest;
    double BasePoint;
    double ResultIntersetRate;

    //results
    double DownRepay;
    double FirstMonthRepay;                             //首月还款
    double MonthlyReduce;                               //每月递减
    double TotalLoan;                                   //总贷款
    double TotalRepay;                                  //总还款
    double TotalInterest;                               //总支付利息

    double DownPayment;                                 //首付
    double MonthInterestRate;                           //月利率
    double MonthPrincipalRepay;                         //每月本金支付
    double EveryMonthRepay;                             //等额本息  
    double FirstMonthInterest;                          //等额本金首月利息


private:

    void OnSetCommercialInterestType(wxCommandEvent& event);
    void OnSetPortfolioInterestType(wxCommandEvent& event);

    void OnSetRepayType(wxCommandEvent& event);


    void OnSetMonth(wxCommandEvent& event);
    void OnSetTotalLoan(wxCommandEvent& event);

    void OnUpdateShowInterest(wxCommandEvent& event);
    void OnUpdateShowPoint(wxCommandEvent& event);
    void OnGetInterestResult();

    void OnActionButton(wxCommandEvent& event);
    void OnClearButton(wxCommandEvent& event);

    void ProcessDataByPrinciple();
    void ProcessDataByInterest();

    void ResultByPricipalDialog();
    void ResultByInterestDialog();

    //异常处理
    void ProcessInputCommercialLoanError();
    void ProcessInputProvidentFundError();
    void ProcessInputPercentagePointError();
    void ProcessCheckBoxError();
    void ProcessInputPercentagePointEmptyError();
    void ProcessInputCommerciallLoanEmptyError();
    void ProcessInputProvidentFundEmptyError();
    void MessageBoxWindowModalClosed(wxWindowModalDialogEvent& event);


    wxBoxSizer* Sizer = new wxBoxSizer(wxVERTICAL);
    wxFrame* Frame;

    wxDECLARE_EVENT_TABLE();
};
#endif // !_PORTFOLIOLOAN_H_
enum 
{
	ID_CHOICE_INTEREST_COMMERCIAL = wxID_HIGHEST + 1,
    ID_CHOICE_INTEREST_PROTFOLIO,
    ID_TEXTCRTL_COMMERCIAL_LOAN,
    ID_TEXTCRTL_PROVIDENT_LOAN,

    ID_TEXTCTRL_CHOSEN_SHOW_INTEREST_COMMERCIAL,
    ID_TEXTCTRL_CHOSEN_SHOW_INTEREST_PROTFOLIO,

    ID_TEXTCTRL_SHOW_COMMERCIAL_INTERESTRATE_UPDATE,
};