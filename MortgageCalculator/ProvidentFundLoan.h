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
    //ѡ������󲿼�����
    wxTextCtrl* InputPrice;
    wxTextCtrl* InputSquare;
    wxTextCtrl* InputTotalLoan;


    wxChoice* Choice_LoanMortgages;

    wxTextCtrl* ChosenType_ShowInterest;

    wxCheckBox* CheckRepayByInterest;
    wxCheckBox* CheckRepayByPricipal;

    bool ChooseByHouse = true;
    bool ChooseByTotalLoan = false;


    //������Ϣ
    double HousePrice = 0;
    double HouseSquare = 0;
    //
    double LoanToValue = 0.8;
    double Months = 360;
    //����
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

    //�쳣����
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

