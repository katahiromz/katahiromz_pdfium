//////////////////////////////////////////////////////////////////////////////
// katahiromz_pdfium.h --- PDFium wrapper for Windows
// Copyright (C) 2015-2019 Katayama Hirofumi MZ. All Rights Reserved.
// See License.txt about licensing.
//////////////////////////////////////////////////////////////////////////////

#ifndef KATAHIROMZ_PDFIUM_H
#define KATAHIROMZ_PDFIUM_H

#include "fpdfview.h"

struct katahiromz_pdfium {
    HINSTANCE m_hDLLInstance;

    // pdfium functions:
    typedef void (__stdcall *FN_FPDF_InitLibrary)(VOID);
    typedef void (__stdcall *FN_FPDF_DestroyLibrary)(VOID);
    typedef FPDF_DOCUMENT (__stdcall *FN_FPDF_LoadDocument)(FPDF_STRING, FPDF_BYTESTRING);
    typedef FPDF_PAGE (__stdcall *FN_FPDF_LoadPage)(FPDF_DOCUMENT, int);
    typedef double (__stdcall *FN_FPDF_GetPageWidth)(FPDF_PAGE);
    typedef double (__stdcall *FN_FPDF_GetPageHeight)(FPDF_PAGE);
    typedef void (__stdcall *FN_FPDF_RenderPage)(HDC, FPDF_PAGE, int, int, int, int, int, int);
    typedef void (__stdcall *FN_FPDF_ClosePage)(FPDF_PAGE);
    typedef void (__stdcall *FN_FPDF_CloseDocument)(FPDF_DOCUMENT);
    typedef int (__stdcall *FN_FPDF_GetPageCount)(FPDF_DOCUMENT);
    typedef unsigned long (__stdcall *FN_FPDF_GetLastError)(VOID);
    FN_FPDF_InitLibrary         FPDF_InitLibrary;
    FN_FPDF_DestroyLibrary      FPDF_DestroyLibrary;
    FN_FPDF_LoadDocument        FPDF_LoadDocument;
    FN_FPDF_LoadPage            FPDF_LoadPage;
    FN_FPDF_GetPageWidth        FPDF_GetPageWidth;
    FN_FPDF_GetPageHeight       FPDF_GetPageHeight;
    FN_FPDF_RenderPage          FPDF_RenderPage;
    FN_FPDF_ClosePage           FPDF_ClosePage;
    FN_FPDF_CloseDocument       FPDF_CloseDocument;
    FN_FPDF_GetPageCount        FPDF_GetPageCount;
    FN_FPDF_GetLastError        FPDF_GetLastError;

    katahiromz_pdfium(bool do_load = false) : m_hDLLInstance(NULL) {
        #ifndef NDEBUG
            FPDF_InitLibrary = NULL;
            FPDF_DestroyLibrary = NULL;
            FPDF_LoadDocument = NULL;
            FPDF_LoadPage = NULL;
            FPDF_GetPageWidth = NULL;
            FPDF_GetPageHeight = NULL;
            FPDF_RenderPage = NULL;
            FPDF_ClosePage = NULL;
            FPDF_CloseDocument = NULL;
            FPDF_GetPageCount = NULL;
            FPDF_GetLastError = NULL;
        #endif
        if (do_load) {
            load();
        }
    }

    bool is_loaded() const {
        return m_hDLLInstance != NULL;
    }

    ~katahiromz_pdfium() {
        release();
    }

    template <typename T_FN>
    T_FN get_proc(LPCSTR name) {
        return reinterpret_cast<T_FN>(::GetProcAddress(m_hDLLInstance, name));
    }

    bool load(const TCHAR *dll_name = NULL) {
        release();
        if (dll_name)
        {
            m_hDLLInstance = ::LoadLibrary(dll_name);
        }
        else
        {
            #ifdef _WIN64
                m_hDLLInstance = ::LoadLibrary(TEXT("x64\\pdfium.dll"));
                if (m_hDLLInstance == NULL) {
                    m_hDLLInstance = ::LoadLibrary(TEXT("x64\\pdfium64.dll"));
                    if (m_hDLLInstance == NULL) {
                        m_hDLLInstance = ::LoadLibrary(TEXT("pdfium64.dll"));
                        if (m_hDLLInstance == NULL) {
                            m_hDLLInstance = ::LoadLibrary(TEXT("pdfium.dll"));
                        }
                    }
                }
            #else
                m_hDLLInstance = ::LoadLibrary(TEXT("x86\\pdfium.dll"));
                if (m_hDLLInstance == NULL) {
                    m_hDLLInstance = ::LoadLibrary(TEXT("pdfium.dll"));
                }
            #endif
        }

        if (m_hDLLInstance != NULL) {
            #ifdef _WIN64
                FPDF_InitLibrary = get_proc<FN_FPDF_InitLibrary>("FPDF_InitLibrary");
                FPDF_DestroyLibrary = get_proc<FN_FPDF_DestroyLibrary>("FPDF_DestroyLibrary");
                FPDF_LoadDocument = get_proc<FN_FPDF_LoadDocument>("FPDF_LoadDocument");
                FPDF_LoadPage = get_proc<FN_FPDF_LoadPage>("FPDF_LoadPage");
                FPDF_GetPageWidth = get_proc<FN_FPDF_GetPageWidth>("FPDF_GetPageWidth");
                FPDF_GetPageHeight = get_proc<FN_FPDF_GetPageHeight>("FPDF_GetPageHeight");
                FPDF_RenderPage = get_proc<FN_FPDF_RenderPage>("FPDF_RenderPage");
                FPDF_ClosePage = get_proc<FN_FPDF_ClosePage>("FPDF_ClosePage");
                FPDF_CloseDocument = get_proc<FN_FPDF_CloseDocument>("FPDF_CloseDocument");
                FPDF_GetPageCount = get_proc<FN_FPDF_GetPageCount>("FPDF_GetPageCount");
                FPDF_GetLastError = get_proc<FN_FPDF_GetLastError>("FPDF_GetLastError");
            #else
                FPDF_InitLibrary = get_proc<FN_FPDF_InitLibrary>("_FPDF_InitLibrary@0");
                FPDF_DestroyLibrary = get_proc<FN_FPDF_DestroyLibrary>("_FPDF_DestroyLibrary@0");
                FPDF_LoadDocument = get_proc<FN_FPDF_LoadDocument>("_FPDF_LoadDocument@8");
                FPDF_LoadPage = get_proc<FN_FPDF_LoadPage>("_FPDF_LoadPage@8");
                FPDF_GetPageWidth = get_proc<FN_FPDF_GetPageWidth>("_FPDF_GetPageWidth@4");
                FPDF_GetPageHeight = get_proc<FN_FPDF_GetPageHeight>("_FPDF_GetPageHeight@4");
                FPDF_RenderPage = get_proc<FN_FPDF_RenderPage>("_FPDF_RenderPage@32");
                FPDF_ClosePage = get_proc<FN_FPDF_ClosePage>("_FPDF_ClosePage@4");
                FPDF_CloseDocument = get_proc<FN_FPDF_CloseDocument>("_FPDF_CloseDocument@4");
                FPDF_GetPageCount = get_proc<FN_FPDF_GetPageCount>("_FPDF_GetPageCount@4");
                FPDF_GetLastError = get_proc<FN_FPDF_GetLastError>("_FPDF_GetLastError@0");
            #endif
            if (FPDF_InitLibrary != NULL && 
                FPDF_DestroyLibrary != NULL && 
                FPDF_LoadDocument != NULL && 
                FPDF_LoadPage != NULL && 
                FPDF_GetPageWidth != NULL && 
                FPDF_GetPageHeight != NULL && 
                FPDF_RenderPage != NULL && 
                FPDF_ClosePage != NULL && 
                FPDF_CloseDocument != NULL &&
                FPDF_GetPageCount != NULL &&
                FPDF_GetLastError != NULL)
            {
                FPDF_InitLibrary();
                return true;
            }
            release();
        }
        return false;
    }

    void release() {
        if (m_hDLLInstance) {
            FPDF_DestroyLibrary();
            ::FreeLibrary(m_hDLLInstance);
            m_hDLLInstance = NULL;
        }
    }
}; // struct katahiromz_pdfium

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef KATAHIROMZ_PDFIUM_H
