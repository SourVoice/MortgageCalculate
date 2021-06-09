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
    wxTextCtrl* ProvidentFund;
    wxTextCtrl* InputPercentagePoint;
    wxTextCtrl* ShowInterest;
    wxTextCtrl* ShowPoint;
    wxTextCtrl* ChosenType_ShowInterest_Commercial;
    wxTextCtrl* ShowInterestResult;

    wxCheckBox* CheckRepayByInterest;
    wxCheckBox* CheckRepayByPricipal;

    bool ChooseByHouse = true;
    bool ChooseByTotalLoan = false;


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

    void OnSetInterestType(wxCommandEvent& event);
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
    void ProcessInputTotalLoanError();
    void ProcessInputPercentagePointError();
    void ProcessCheckBoxError();
    void ProcessInputPercentagePointEmptyError();
    void ProcessInputTotalLoanEmptyError();
    void MessageBoxWindowModalClosed(wxWindowModalDialogEvent& event);


    wxBoxSizer* Sizer = new wxBoxSizer(wxVERTICAL);
    wxFrame* Frame;

    wxDECLARE_EVENT_TABLE();
};
#endif // !_PORTFOLIOLOAN_H_
