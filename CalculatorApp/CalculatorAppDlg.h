// CalculatorDlg.h - Calculator dialog header
#pragma once

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
    // Construction
public:
    CCalculatorDlg(CWnd* pParent = nullptr);

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

protected:
    void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
    {
        CDialogEx::DoDataExchange(pDX);

        // Link controls to variables
        DDX_Control(pDX, IDC_BTN_INVERSE, m_btnInverse);
        DDX_Control(pDX, IDC_BTN_SQUARE, m_btnSquare);
        DDX_Control(pDX, IDC_EDIT_DISPLAY, m_editDisplay);
        DDX_Control(pDX, IDC_BTN_SQRT, m_btnSqrt);
        DDX_Control(pDX, IDC_BTN_PERCENT, m_btnPercent);
        DDX_Control(pDX, IDC_BTN_SIGN, m_btnSign);

    }

    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:
    // Member variables following Hungarian notation
    CEdit m_editDisplay;          // Edit control for display
    CString m_strCurrentNumber;   // Current number being entered
    CString m_strPreviousNumber;  // Previous number for operations
    CString m_strOperator;        // Current operator
    double m_dblResult;           // Calculation result
    BOOL m_bNewNumber;            // Flag for new number entry
    BOOL m_bOperatorPressed;      // Flag for operator state
    BOOL m_bEqualPressed;         // Flag for equal button state

    // Button controls
    CButton m_btnNumbers[10];     // Number buttons 0-9
    CButton m_btnOperators[5];    // +, -, *, /, =
    CButton m_btnClear;           // Clear button
    CButton m_btnClearEntry;      // Clear Entry button
    CButton m_btnDecimal;         // Decimal point button
    CButton m_btnBackspace;       // Backspace button
    CButton m_btnSqrt;
    CButton m_btnPercent;
    CButton m_btnInverse;
    CButton m_btnSquare;
    CButton m_btnSign;

   


   


    // Private helper methods
    void InitializeControls();
    void CreateButtons();
    void PositionControls();
    double PerformCalculation(double dblLeft, double dblRight, const CString& strOp);
    void UpdateDisplay();
    void ClearAll();
    void ClearEntry();
    BOOL ValidateInput(const CString& strInput);

    // Message handlers
    afx_msg void OnNumberClick(UINT nID);
    afx_msg void OnOperatorClick(UINT nID);
    afx_msg void OnEqualClick();
    afx_msg void OnClearClick();
    afx_msg void OnClearEntryClick();
    afx_msg void OnDecimalClick();
    afx_msg void OnBackspaceClick();
    afx_msg void OnSqrtClick();
    afx_msg void OnPercentClick();
    afx_msg void OnInverseClick();
    afx_msg void OnSquareClick();
    afx_msg void OnSignClick();
};
