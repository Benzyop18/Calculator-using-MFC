// CalculatorDlg.cpp - Dialog implementation
#include "pch.h"
#include "framework.h"
#include "CalculatorApp.h"
#include "CalculatorAppDlg.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{

    CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CCalculatorDlg dialog
CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
    , m_strCurrentNumber(_T("0"))
    , m_strPreviousNumber(_T(""))
    , m_strOperator(_T(""))
    , m_dblResult(0.0)
    , m_bNewNumber(TRUE)
    , m_bOperatorPressed(FALSE)
    , m_bEqualPressed(FALSE)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CEdit m_editDisplay;



BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_COMMAND_RANGE(IDC_BTN_0, IDC_BTN_9, &CCalculatorDlg::OnNumberClick)
    ON_COMMAND_RANGE(IDC_BTN_PLUS, IDC_BTN_DIVIDE, &CCalculatorDlg::OnOperatorClick)
    ON_COMMAND(IDC_BTN_EQUAL, &CCalculatorDlg::OnEqualClick)
    ON_COMMAND(IDC_BTN_CLEAR, &CCalculatorDlg::OnClearClick)
    ON_COMMAND(IDC_BTN_CE, &CCalculatorDlg::OnClearEntryClick)
    ON_COMMAND(IDC_BTN_DECIMAL, &CCalculatorDlg::OnDecimalClick)
    ON_COMMAND(IDC_BTN_BACKSPACE, &CCalculatorDlg::OnBackspaceClick)
    ON_COMMAND(IDC_BTN_SQRT, &CCalculatorDlg::OnSqrtClick)
    ON_COMMAND(IDC_BTN_PERCENT, &CCalculatorDlg::OnPercentClick)
    ON_COMMAND(IDC_BTN_INVERSE, &CCalculatorDlg::OnInverseClick)
    ON_COMMAND(IDC_BTN_SQUARE, &CCalculatorDlg::OnSquareClick)
    ON_COMMAND(IDC_BTN_SIGN, &CCalculatorDlg::OnSignClick)



END_MESSAGE_MAP()

// CCalculatorDlg message handlers
BOOL CCalculatorDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Add "About..." menu item to system menu.
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // Initialize calculator
    InitializeControls();
    CreateButtons();
    PositionControls();
    UpdateDisplay();

    return TRUE;  // return TRUE unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void CCalculatorDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// Initialize calculator controls
void CCalculatorDlg::InitializeControls()
{
    // Set display properties
    m_editDisplay.SetReadOnly(TRUE);

    // Set display font
    CFont* pFont = new CFont();
    pFont->CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
    m_editDisplay.SetFont(pFont);
}

// Create calculator buttons dynamically
void CCalculatorDlg::CreateButtons()
{
    // Button dimensions and spacing
    const int nButtonWidth = 60;
    const int nButtonHeight = 40;
    const int nSpacing = 5;
    const int nStartX = 20;
    const int nStartY = 100;

    // Create number buttons (0-9)
    for (int i = 0; i <= 9; i++)
    {
        CString strText;
        strText.Format(_T("%d"), i);

        int nRow, nCol;
        if (i == 0)
        {
            nRow = 3; nCol = 1; // Bottom row, middle
        }
        else
        {
            nRow = 2 - (i - 1) / 3; // Rows 0, 1, 2 for 1-9
            nCol = (i - 1) % 3;     // Columns 0, 1, 2
        }

        int nX = nStartX + nCol * (nButtonWidth + nSpacing);
        int nY = nStartY + nRow * (nButtonHeight + nSpacing);

        m_btnNumbers[i].Create(strText, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            CRect(nX, nY, nX + nButtonWidth, nY + nButtonHeight),
            this, IDC_BTN_0 + i);
    }

    // Create operator buttons
    CString strOperators[] = { _T("+"), _T("-"), _T("*"), _T("/") };
    for (int i = 0; i < 4; i++)
    {
        int nX = nStartX + 3 * (nButtonWidth + nSpacing);
        int nY = nStartY + i * (nButtonHeight + nSpacing);

        m_btnOperators[i].Create(strOperators[i], WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            CRect(nX, nY, nX + nButtonWidth, nY + nButtonHeight),
            this, IDC_BTN_PLUS + i);
    }

    // Create equal button
    int nEqualX = nStartX + 2 * (nButtonWidth + nSpacing);
    int nEqualY = nStartY + 3 * (nButtonHeight + nSpacing);
    m_btnOperators[4].Create(_T("="), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        CRect(nEqualX, nEqualY, nEqualX + nButtonWidth, nEqualY + nButtonHeight),
        this, IDC_BTN_EQUAL);

    // Create decimal button
    int nDecimalX = nStartX;
    int nDecimalY = nStartY + 3 * (nButtonHeight + nSpacing);
    m_btnDecimal.Create(_T("."), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        CRect(nDecimalX, nDecimalY, nDecimalX + nButtonWidth, nDecimalY + nButtonHeight),
        this, IDC_BTN_DECIMAL);

    // Create clear buttons
    int nClearY = nStartY - (nButtonHeight + nSpacing);
    m_btnClear.Create(_T("C"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        CRect(nStartX, nClearY, nStartX + nButtonWidth, nClearY + nButtonHeight),
        this, IDC_BTN_CLEAR);

    m_btnClearEntry.Create(_T("CE"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        CRect(nStartX + (nButtonWidth + nSpacing), nClearY,
            nStartX + 2 * nButtonWidth + nSpacing, nClearY + nButtonHeight),
        this, IDC_BTN_CE);

    // Create backspace button
    m_btnBackspace.Create(_T("⌫"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        CRect(nStartX + 2 * (nButtonWidth + nSpacing), nClearY,
            nStartX + 3 * nButtonWidth + 2 * nSpacing, nClearY + nButtonHeight),
        this, IDC_BTN_BACKSPACE);
}

// Position controls properly
void CCalculatorDlg::PositionControls()
{
    // Position display at top
    m_editDisplay.SetWindowPos(nullptr, 20, 20, 250, 35, SWP_NOZORDER);

    // Resize dialog to fit all controls
    SetWindowPos(nullptr, 0, 0, 300, 300, SWP_NOMOVE | SWP_NOZORDER);
}

// Handle number button clicks
void CCalculatorDlg::OnNumberClick(UINT nID)
{
    int nNumber = nID - IDC_BTN_0;
    CString strNumber;
    strNumber.Format(_T("%d"), nNumber);

    if (m_bNewNumber || m_bEqualPressed)
    {
        m_strCurrentNumber = strNumber;
        m_bNewNumber = FALSE;
        m_bEqualPressed = FALSE;
    }
    else
    {
        if (m_strCurrentNumber == _T("0"))
            m_strCurrentNumber = strNumber;
        else
            m_strCurrentNumber += strNumber;
    }

    m_bOperatorPressed = FALSE;
    UpdateDisplay();
}

// Handle operator button clicks
void CCalculatorDlg::OnOperatorClick(UINT nID)
{
    CString strNewOperator;
    switch (nID)
    {
    case IDC_BTN_PLUS:
        strNewOperator = _T("+");
        break;
    case IDC_BTN_MINUS:
        strNewOperator = _T("-");
        break;
    case IDC_BTN_MULTIPLY:
        strNewOperator = _T("*");
        break;
    case IDC_BTN_DIVIDE:
        strNewOperator = _T("/");
        break;
    }

    if (!m_bOperatorPressed && !m_strPreviousNumber.IsEmpty())
    {
        // Perform calculation with previous operation
        double dblCurrent = _tstof(m_strCurrentNumber);
        double dblPrevious = _tstof(m_strPreviousNumber);
        m_dblResult = PerformCalculation(dblPrevious, dblCurrent, m_strOperator);

        m_strCurrentNumber.Format(_T("%.10g"), m_dblResult);
        UpdateDisplay();
    }

    m_strPreviousNumber = m_strCurrentNumber;
    m_strOperator = strNewOperator;
    m_bNewNumber = TRUE;
    m_bOperatorPressed = TRUE;
    m_bEqualPressed = FALSE;
}

// Handle equal button click
void CCalculatorDlg::OnEqualClick()
{
    if (!m_strOperator.IsEmpty() && !m_strPreviousNumber.IsEmpty())
    {
        double dblCurrent = _tstof(m_strCurrentNumber);
        double dblPrevious = _tstof(m_strPreviousNumber);

        m_dblResult = PerformCalculation(dblPrevious, dblCurrent, m_strOperator);

        m_strCurrentNumber.Format(_T("%.10g"), m_dblResult);
        m_strPreviousNumber.Empty();
        m_strOperator.Empty();

        UpdateDisplay();
        m_bEqualPressed = TRUE;
        m_bNewNumber = TRUE;
    }
}

// Handle clear button click
void CCalculatorDlg::OnClearClick()
{
    ClearAll();
}

// Handle clear entry button click
void CCalculatorDlg::OnClearEntryClick()
{
    ClearEntry();
}

// Handle decimal point button click
void CCalculatorDlg::OnDecimalClick()
{
    if (m_bNewNumber || m_bEqualPressed)
    {
        m_strCurrentNumber = _T("0.");
        m_bNewNumber = FALSE;
        m_bEqualPressed = FALSE;
    }
    else if (m_strCurrentNumber.Find(_T('.')) == -1)
    {
        m_strCurrentNumber += _T(".");
    }

    UpdateDisplay();
}

// Handle backspace button click
void CCalculatorDlg::OnBackspaceClick()
{
    if (!m_bNewNumber && m_strCurrentNumber.GetLength() > 1)
    {
        m_strCurrentNumber = m_strCurrentNumber.Left(m_strCurrentNumber.GetLength() - 1);
    }
    else
    {
        m_strCurrentNumber = _T("0");
        m_bNewNumber = TRUE;
    }

    UpdateDisplay();
}

// Perform mathematical calculations
double CCalculatorDlg::PerformCalculation(double dblLeft, double dblRight, const CString& strOp)
{
    double dblResult = 0.0;

    if (strOp == _T("+"))
    {
        dblResult = dblLeft + dblRight;
    }
    else if (strOp == _T("-"))
    {
        dblResult = dblLeft - dblRight;
    }
    else if (strOp == _T("*"))
    {
        dblResult = dblLeft * dblRight;
    }
    else if (strOp == _T("/"))
    {
        if (dblRight != 0.0)
        {
            dblResult = dblLeft / dblRight;
        }
        else
        {
            // Handle division by zero
            AfxMessageBox(_T("Cannot divide by zero"));
            dblResult = 0.0;
        }
    }

    return dblResult;
}

// Update display with current number
void CCalculatorDlg::UpdateDisplay()
{
    m_editDisplay.SetWindowText(m_strCurrentNumber);
}

// Clear all calculator state
void CCalculatorDlg::ClearAll()
{
    m_strCurrentNumber = _T("0");
    m_strPreviousNumber.Empty();
    m_strOperator.Empty();
    m_dblResult = 0.0;
    m_bNewNumber = TRUE;
    m_bOperatorPressed = FALSE;
    m_bEqualPressed = FALSE;
    UpdateDisplay();
}

// Clear current entry only
void CCalculatorDlg::ClearEntry()
{
    m_strCurrentNumber = _T("0");
    m_bNewNumber = TRUE;
    UpdateDisplay();
}
void CCalculatorDlg::OnSqrtClick()
{
    double dblValue = _tstof(m_strCurrentNumber);
    if (dblValue >= 0.0)
    {
        m_dblResult = sqrt(dblValue);
        m_strCurrentNumber.Format(_T("%.10g"), m_dblResult);
        UpdateDisplay();
    }
    else
    {
        AfxMessageBox(_T("Invalid input for square root"));
    }
    m_bNewNumber = TRUE;
}

void CCalculatorDlg::OnPercentClick()
{
    double dblValue = _tstof(m_strCurrentNumber);
    m_dblResult = dblValue / 100.0;
    m_strCurrentNumber.Format(_T("%.10g"), m_dblResult);
    UpdateDisplay();
    m_bNewNumber = TRUE;
}


// Validate input string
BOOL CCalculatorDlg::ValidateInput(const CString& strInput)
{
    // Check for valid number format
    int nDecimalCount = 0;
    for (int i = 0; i < strInput.GetLength(); i++)
    {
        TCHAR ch = strInput.GetAt(i);
        if (ch == _T('.'))
        {
            nDecimalCount++;
            if (nDecimalCount > 1)
                return FALSE;
        }
        else if (!_istdigit(ch) && ch != _T('-') && ch != _T('+'))
        {
            return FALSE;
        }
    }
    return TRUE;
}

void CCalculatorDlg::OnInverseClick()
{
    double dblValue = _tstof(m_strCurrentNumber);
    if (dblValue != 0.0)
    {
        m_dblResult = 1.0 / dblValue;
        m_strCurrentNumber.Format(_T("%.10g"), m_dblResult);
        UpdateDisplay();
    }
    else
    {
        AfxMessageBox(_T("Cannot divide by zero"));
    }
    m_bNewNumber = TRUE;
}

void CCalculatorDlg::OnSquareClick()
{
    double dblValue = _tstof(m_strCurrentNumber);
    m_dblResult = dblValue * dblValue;
    m_strCurrentNumber.Format(_T("%.10g"), m_dblResult);
    UpdateDisplay();
    m_bNewNumber = TRUE;
}
void CCalculatorDlg::OnSignClick()
{
    if (m_strCurrentNumber.IsEmpty() || m_strCurrentNumber == _T("0"))
        return;


    if (m_strCurrentNumber[0] == _T('-'))
    {
        m_strCurrentNumber = m_strCurrentNumber.Mid(1);
    }
    else
    {
        m_strCurrentNumber = _T("-") + m_strCurrentNumber;
       
    }

    UpdateDisplay();
}
