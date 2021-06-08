#pragma once

/*��ҵ������*/
#include "wx/wx.h"
#include"cPanel.h"
#include"IDs.h"
#ifndef _COMMERCIALLOAN_H_
#define _COMMERCIALLOAN_H_

class CommercialLoan :public wxDialog
{
public:
    CommercialLoan(wxFrame* Frame);
    ~CommercialLoan();



    wxStaticText* StaticText;
    //ѡ������󲿼�����
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

    //������Ϣ
    double HousePrice = 0;
    double HouseSquare = 0;
    //
    double LoanToValue = 0;
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

	void OnSetCalculateType(wxCommandEvent& event);
    void OnSetInterestType(wxCommandEvent& event);
	void OnSetRepayType(wxCommandEvent& event);
    
    void OnSetHousePrice(wxCommandEvent& event);
    void OnSetHouseSquare(wxCommandEvent& event);
    void MessageBoxWindowModalClosed(wxWindowModalDialogEvent& event);
    


    void OnSetLoanToValue(wxCommandEvent& event);
    void OnSetMonth(wxCommandEvent& event);
    void OnSetTotalLoan(wxCommandEvent& event);

    void OnUpdateShowInterest(wxCommandEvent& event);
    void OnUpdateShowPoint(wxCommandEvent& event);
	void OnGetInterestResult();

    void OnActionButton(wxCommandEvent& event);

    void ProcessDataByPrinciple();
    void ProcessDataByInterest();

    void ResultByPricipalDialog();
    void ResultByInterestDialog();
    wxBoxSizer* Sizer = new wxBoxSizer(wxVERTICAL);
    wxFrame* Frame;
    
    wxDECLARE_EVENT_TABLE();

};
#endif // !_COMMERCIALLOAN_H_
