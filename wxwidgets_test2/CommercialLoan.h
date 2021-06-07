/*商业贷款类*/
#include "wx/wx.h"

#include"cPanel.h"
class CommercialLoan :public wxDialog
{
public:
    CommercialLoan(wxFrame* Frame);
    ~CommercialLoan();



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
enum {
    ID_TEXTCTRL_HOUSE_PRICE = 201,
    ID_TEXTCTRL_HOUSE_SQUARE,
    ID_TEXTCRTL_TOTAL_LOAN,
    ID_TEXTCTRL_PERCENTAGE_POINT,

    ID_CHOICE_LTV,
    ID_CHOICE_LTY,
    ID_CHOICE_CALCULATE_TYPE,
    ID_CHOICE_INTEREST_TYPE,
    
    ID_TEXTCTRL_CHOSEN_TYPE_SHOW_INTEREST,
    ID_TEXTCTRL_SHOW_INTEREST,
    ID_TEXTCTRL_SHOW_POINT,
    ID_TEXTCTRL_SHOW_RESULT,

    ID_CHECKBOX_REPAYTYPE_PRINCIPAL_INTEREST,   //等额本息
	ID_CHECKBOX_REPAYTYPE_PRINCIPAL,            //等额本金

    ID_BUTTON_ACTION,
    ID_BUTTON_CLEAR,

    ID_INTEREST,
};
