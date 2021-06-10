#pragma once

#include"wx/wx.h"
#include"cPanel.h"
#include"IDs.h"

#ifndef _PORTFOLIOLOAN_H_
#define _PORTFOLIOLOAN_H_

/*��ϴ�����*/
class PortfolioLoan :public wxDialog
{
public:
	PortfolioLoan(wxFrame *parent);
	~PortfolioLoan();

    wxStaticText* StaticText;
    //ѡ������󲿼�����
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



    //��������
    double Months = 360;
    //����,����
    double InitialInterest;
    double BasePoint;
    double ResultIntersetRate;

    //results
    double DownRepay;
    double FirstMonthRepay;                             //���»���
    double MonthlyReduce;                               //ÿ�µݼ�
    double TotalLoan;                                   //�ܴ���
    double TotalRepay;                                  //�ܻ���
    double TotalInterest;                               //��֧����Ϣ

    double DownPayment;                                 //�׸�
    double MonthInterestRate;                           //������
    double MonthPrincipalRepay;                         //ÿ�±���֧��
    double EveryMonthRepay;                             //�ȶϢ  
    double FirstMonthInterest;                          //�ȶ��������Ϣ


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

    //�쳣����
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