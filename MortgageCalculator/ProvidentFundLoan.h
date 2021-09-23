#pragma once
#include "wx/wx.h"
#include"IDs.h"
class ProvidentFundLoan :
    public wxDialog
{
public:
    ProvidentFundLoan(wxFrame*Frame);
    ~ProvidentFundLoan();


    wxStaticText* StaticText;
    //选则面积后部件更新
    wxTextCtrl* InputPrice;
    wxTextCtrl* InputSquare;
    wxTextCtrl* InputTotalLoan;


    wxChoice* Choice_LoanMortgages;

    wxTextCtrl* ChosenType_ShowInterest;

    wxCheckBox* CheckRepayByInterest;
    wxCheckBox* CheckRepayByPricipal;

    bool ChooseByHouse = true;
    bool ChooseByTotalLoan = false;


    //房子信息
    double HousePrice = 0;
    double HouseSquare = 0;
    //
    double LoanToValue = 0.8;
    double Months = 360;
    //利率
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

    void OnSetCalculateType(wxCommandEvent& event);
    void OnSetInterestType(wxCommandEvent& event);
    void OnSetRepayType(wxCommandEvent& event);

    void OnSetHousePrice(wxCommandEvent& event);
    void OnSetHouseSquare(wxCommandEvent& event);



    void OnSetLoanToValue(wxCommandEvent& event);
    void OnSetMonth(wxCommandEvent& event);
    void OnSetTotalLoan(wxCommandEvent& event);

    void OnGetInterestResult();

    void OnActionButton(wxCommandEvent& event);
    void OnClearButton(wxCommandEvent& event);

    void ProcessDataByPrinciple();
    void ProcessDataByInterest();

    void ResultByPricipalDialog();
    void ResultByInterestDialog();

    //异常处理
    void ProcessInputPriceError();
    void ProcessInputSquareError();
    void ProcessInputTotalLoanError();
    void ProcessCheckBoxError();
    void ProcessInputPriceEmptyError();
    void ProcessInputSquareEmptyError();
    void ProcessInputTotalLoanEmptyError();
    void MessageBoxWindowModalClosed(wxWindowModalDialogEvent& event);


    wxBoxSizer* Sizer = new wxBoxSizer(wxVERTICAL);
    wxFrame* Frame;

    wxDECLARE_EVENT_TABLE();

};

