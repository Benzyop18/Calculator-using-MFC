// CalculatorApp.h - Main application header
#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"

// CCalculatorApp - Main application class
class CCalculatorApp : public CWinApp
{
public:
    CCalculatorApp() noexcept;

    // Overrides
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    // Implementation
    DECLARE_MESSAGE_MAP()
};

extern CCalculatorApp theApp;