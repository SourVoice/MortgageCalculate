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
    wxTextCtrl* InputPrice;
    wxTextCtrl* InputSquare;
    wxTextCtrl* InputTotalLoan;


    wxChoice* Choice_LoanMortgages;

    wxTextCtrl* InputPercentagePoint;
    wxTextCtrl* ShowInterest;
    wxTextCtrl* ShowPoint;
    wxTextCtrl* ChosenType_ShowInterest;
    wxTextCtrl* ShowInterestResult;

    wxCheckBox* CheckRepayByInterest;
    wxCheckBox* CheckRepayByPricipal;

    bool ChosenBySquare;
    bool ChosenByPrice;
    bool FirstChosenCaculateType;

    //房子信息
    double HousePrice = 0;
    double HouseSquare = 0;
    //
    double Value;
    double Months = 360;
    //基点,利率
    double InitialInterest;
    double BasePoint;
    double ResultIntersetRate;

    //results
    double DownRepay;
    double FirstMonthRepay;
    double MonthlyReduce;
    double TotalLoan;

    double TotalRepay;

    double MonthInterestRate;
    double MonthPrincipalRepay;
    double MonthlyRepay;
    double FirstMonthInterest;
    double TotalInterest;


private:

    void OnSetCalculateType(wxCommandEvent& event);
    void OnSetInterestType(wxCommandEvent& event);
    void OnSetRepayType(wxCommandEvent& event);

    void OnSetValue(wxCommandEvent& event);
    void OnSetMonth(wxCommandEvent& event);
    void OnSetTotalLoan(wxCommandEvent& event);

    void OnUpdateShowInterest(wxCommandEvent& event);
    void OnUpdateShowPoint(wxCommandEvent& event);
    void OnGetInterestResult();

    void OnActionButton(wxCommandEvent& event);

    void ProcessDataByPrinciple();
    void ProcessDataByInterest();

    void CreateResultDialog();

    wxBoxSizer* Sizer = new wxBoxSizer(wxVERTICAL);
    wxFrame* Frame;

    wxDECLARE_EVENT_TABLE();

};
#endif // !_PORTFOLIOLOAN_H_
