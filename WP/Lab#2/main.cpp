#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <tchar.h>
#include "resource.h"


int MinWindowHeight = 530;
int MinWindowWidth  = 590;

//Windows procedure declaration
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
BOOL        CALLBACK ColorScrDlg(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);
HWND hDlgModeless;
//  Make the class name into a global variable
char szClassName[ ] = "Lab1Class";

//  Create a global handle to an instance variable to be used across different functions
HINSTANCE hProgramInstance;
int  items,items2,focused = 0,focused2 = 0;


int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;                    // This is the handle for our window
    MSG messages;                 // Here messages to the application are saved
    WNDCLASSEX wincl;             // Data structure for the windowclass

    hProgramInstance = hThisInstance;
    /* The Window Structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof (WNDCLASSEX);
    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_WARNING);                         // Default icon
    wincl.hIconSm = LoadIcon(hThisInstance, MAKEINTRESOURCE(IDI_ICON1));    // Custom  icon
    wincl.hCursor = LoadCursor (hProgramInstance, MAKEINTRESOURCE(IDC_CURSOR1)); // Custom arrow mouse cursor
    wincl.lpszMenuName = NULL;                                              // No menu
    wincl.cbClsExtra = 0;                                                   // No extra bytes after the window class
    wincl.cbWndExtra = 0;                                                   // Structure or the window instance
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(219,219,219));      //choosing the background color

    // Register the window class, and in case of failure quit the program!
    if(!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx (
        0,                                                                  // Extended possibilites for variation
        szClassName,                                                        // Class name
        "Lab#2",                                                            // Window title
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,                              // Basic window style
        CW_USEDEFAULT, CW_USEDEFAULT,                                       // Set starting point to default value
        720, 460,                                                           // Set the dimensions of the window
        HWND_DESKTOP,                                                       // The window is a child-window to desktop
        NULL,                                                               // No menu
        hThisInstance,                                                      // Program Instance handler
        NULL);                                                              // No Window Creation data

    ShowWindow (hwnd, nCmdShow);                                            //display the window on the screen
    UpdateWindow(hwnd);
    hDlgModeless = CreateDialog(hThisInstance, "ColorScrDlg", hwnd, ColorScrDlg);
    srand(time(NULL));

    // Run the message loop. It will run until GetMessage() returns 0
    while (GetMessage (&messages, NULL, 0, 0))
    {
    if(hDlgModeless == 0 || !IsDialogMessage(hDlgModeless, &messages))
        {
        // Translate virtual-key messages into character messages
        TranslateMessage(&messages);
        // Send message to WindowProcedure
        DispatchMessage(&messages);
        }
    }

    return messages.wParam;
}
//  This function is called by the Windows function DispatchMessage()
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) //all the handles to different controls
{
    static HWND hwndInputText,hwndInputText2,hwndRemoveButton,hwndHeightScroll,hwndWidthScroll,hwndLabel1,hwndLabel2;
    static HWND hwndOutputText,hwndOutputText2;
    LRESULT textSize;
    char * message = new char[100];
    char * placeholder = new char[26];
    placeholder = "Please enter your name...";
    HBRUSH color;
    int iScreenW;                                //characters ave width of string
    int iScreenH;                                //characters ave height of string
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc;                                     //device context handle

    // Size and position variables
    int SysWidth;
    int SysHeight;
    int WinWidth;
    int WinHeight;
    int index;

    int Width  = 60;   // Button width
    int Height = 30;   // Button height
    int x;
    int y;

    int i;




    // Menu & menu items
    HMENU hMenu;
    HMENU hSubMenu;

    // Text size
    int cxChar;
    int cyChar;

    // String
    char* szText;
    int TextLength;

     // Paint and size structs
    TEXTMETRIC tm;
    SCROLLINFO si;



    hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight;
    ReleaseDC(hwnd, hdc);

    switch(msg) // handle the messages
    {

        case WM_CREATE:
            //Getting information about the average height and width of a letter
            iScreenW = GetSystemMetrics(SM_CXSCREEN);
            iScreenH = GetSystemMetrics(SM_CYSCREEN);

            //Getting the dimensions of the client area
            GetWindowRect(hwnd, &rect);
            SetWindowPos(
                hwnd, 0,
                (iScreenW - rect.right)/2,
                (iScreenH - rect.bottom)/2,
                0, 0,
                SWP_NOZORDER|SWP_NOSIZE);

            CreateWindowEx(
               (DWORD)NULL,
                TEXT("button"),                                       // The class name required is button
                TEXT("Add"),                                          // the caption of the button
                WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON,                 // the styles
                95, 270,                                              // the left and top co-ordinates
                60, 20,                                               // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_ADD_BUTTON,                                // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            CreateWindowEx(
               (DWORD)NULL,
                TEXT("button"),                                       // The class name required is button
                TEXT("Add"),                                          // the caption of the button
                WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON,                 // the styles
                405, 270,                                             // the left and top co-ordinates
                60, 20,                                               // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_ADD_BUTTON2,                               // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),                                       // The class name required is button
                TEXT("Reset"),                                        // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,                // the styles
                195, 270,                                             // the left and top co-ordinates
                60, 20,                                               // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_RESET_BUTTON,                              // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),                                       // The class name required is button
                TEXT("Reset"),                                        // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,                // the styles
                505, 270,                                             // the left and top co-ordinates
                60, 20,                                               // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_RESET_BUTTON2,                             // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),                                       // The class name required is button
                TEXT("Red pill"),                                     // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, // the styles
                135, 35,                                               // the left and top co-ordinates
                80, 35,                                               // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_RED_BUTTON,                                // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),                                       // The class name required is button
                TEXT("Blue pill"),                                    // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, // the styles
                455, 35,                                              // the left and top co-ordinates
                80, 35,                                               // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_BLUE_BUTTON,                               // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            hwndOutputText = CreateWindowEx(
             (DWORD)NULL,
                TEXT("ListBox"),
                NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER |
                LBS_NOTIFY | LBS_WANTKEYBOARDINPUT,
                80, 80, 200, 150,
                hwnd,
                (HMENU)IDC_OUTPUT_TEXT,
                hProgramInstance,
                NULL);

            hwndInputText = CreateWindowEx(
                 (DWORD)NULL,
                TEXT("edit"),                                         // The class name required is edit
                TEXT(placeholder),                                    // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER,                    // Textbox styles
                80, 235,                                              // the left and top co-ordinates
                200, 20,                                              // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_INPUT_TEXT,                                // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            hwndOutputText2 = CreateWindowEx(
                (DWORD)NULL,                                          // The class name required is edit
                TEXT("ListBox"),                                         // the caption of the button
                TEXT(""),                                             // Default text.
                 WS_CHILD | WS_VISIBLE | WS_BORDER |
                LBS_NOTIFY | LBS_WANTKEYBOARDINPUT,
                390, 80,                                              // the left and top co-ordinates
                200, 150,                                             // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_OUTPUT_TEXT2,                              // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            hwndInputText2 = CreateWindowEx(
                 (DWORD)NULL,
                TEXT("edit"),                                         // The class name required is edit
                TEXT(placeholder),                                    // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER,                    // Textbox styles
                390, 235,                                             // the left and top co-ordinates
                200, 20,                                              // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_INPUT_TEXT2,                               // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            hwndRemoveButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Remove"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                290, 100,
                70, 30,
                hwnd,
                (HMENU)IDC_REMOVE_BUTTON,
                hProgramInstance,
                NULL);

            hwndRemoveButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Remove"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                600, 100,
                70, 30,
                hwnd,
                (HMENU)IDC_REMOVE_BUTTON2,
                hProgramInstance,
                NULL);

            hwndLabel1 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Width"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                40, 300, 100, 17,
                hwnd,
                (HMENU)IDC_LABEL1,
                hProgramInstance,
                NULL);

            hwndLabel2 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Height"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                40, 340, 100, 17,
                hwnd,
                (HMENU)IDC_LABEL2,
                hProgramInstance,
                NULL);

            hwndWidthScroll = CreateWindow(
                "Scrollbar",
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                40, 322, 300, 15,
                 hwnd,
                (HMENU)IDC_WIDTH_SCROLL,
                hProgramInstance,
                NULL);
            SetScrollRange(hwndWidthScroll, SB_CTL, 0, 100, TRUE);

            hwndHeightScroll = CreateWindow(
                "Scrollbar",
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                40, 362, 300, 15,
                 hwnd,
                (HMENU)IDC_HEIGHT_SCROLL,
                hProgramInstance,
                NULL);
            SetScrollRange(hwndHeightScroll, SB_CTL, 0, 100, TRUE);

            // Create menu
            hMenu = CreateMenu();

            // Add "File" menu, with "Exit" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
            AppendMenu(hSubMenu, MF_STRING, IDC_FILE_EXIT, "&Exit");

            // Add "View" menu, with 4 submenus
              hSubMenu = CreatePopupMenu();
              AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&View");
              AppendMenu(hSubMenu, MF_STRING, IDC_RESET_BUTTON , "&Reset the first list");
              AppendMenu(hSubMenu, MF_STRING, IDC_RESET_BUTTON2 , "&Reset the second list");
              AppendMenu(hSubMenu, MF_STRING, IDC_RED_BUTTON , "&Choose the Red Pill            Ctrl+F1");
              AppendMenu(hSubMenu, MF_STRING, IDC_BLUE_BUTTON ,"&Choose the Blue Pill           Ctrl+F2");

            // Add "Help" menu, with "About" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");
            AppendMenu(hSubMenu, MF_STRING, IDC_HELP_ABOUT, "&About");

            // Set the menu
            SetMenu(hwnd, hMenu);
            break;

       case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(LoadCursor(hProgramInstance, MAKEINTRESOURCE(IDC_CURSOR1)));
            return TRUE;
        }
        break;

       case WM_SIZE:
            Width  = LOWORD(lParam);
            Height = HIWORD(lParam);

            // Set vertical scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((MinWindowHeight - 80) / cyChar);
            si.nPage = Height / cyChar;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            // Set horizontal scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((MinWindowWidth - 20) / cxChar);
            si.nPage = Width / cxChar;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);


            // CHILD WINDOWS REPOSITION END

            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Set width scrollbar position
            SetScrollPos(hwndWidthScroll, SB_CTL, (WinWidth * 100 / SysWidth), TRUE);

            // Set height scrollbar position
            SetScrollPos(hwndHeightScroll, SB_CTL, (WinHeight * 100 / SysHeight), TRUE);
            break;

        case WM_VSCROLL:
            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);

            // Save the position for later comparison
            y = si.nPos;

            switch(LOWORD(wParam)) {
                case SB_TOP:
                    si.nPos = si.nMin;
                    break;

                case SB_BOTTOM:
                    si.nPos = si.nMax;
                    break;

                case SB_LINEUP:
                    si.nPos -= max(si.nMin, si.nPos-1);
                    break;

                case SB_LINEDOWN:
                    si.nPos += min(si.nMax,si.nPos+1);
                    break;

                case SB_PAGEDOWN:
                    si.nPos -= 15;
                    break;

                case SB_PAGEUP:
                    si.nPos += 15;
                    break;

                case SB_THUMBTRACK:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }

            // Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
            GetScrollInfo(hwnd, SB_VERT, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != y) {
                ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
                UpdateWindow(hwnd);
            }
            break;

        case WM_HSCROLL:
            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);
            if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_WIDTH_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndWidthScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndWidthScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window width
                MoveWindow(hwnd, rect.left, rect.top, (si.nPos * SysWidth / 100), WinHeight, TRUE);
                break;
            }

            if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_HEIGHT_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndHeightScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndHeightScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window height
                MoveWindow(hwnd, rect.left, rect.top, WinWidth, (si.nPos * SysHeight / 100), TRUE);
                break;
            }

            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_HORZ, &si);

            // Save the position for later comparison
            x = si.nPos;
            switch(LOWORD(wParam)) {
                case SB_LINELEFT:
                    si.nPos -= 1;
                    break;

                case SB_LINERIGHT:
                    si.nPos += 1;
                    break;

                case SB_PAGELEFT:
                    si.nPos -= si.nPage;
                    break;

                case SB_PAGERIGHT:
                    si.nPos += si.nPage;
                    break;

                case SB_THUMBPOSITION:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }
            // Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            GetScrollInfo(hwnd, SB_HORZ, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != x) {
                ScrollWindow(hwnd, cxChar * (x - si.nPos), 0, NULL, 0);
                UpdateWindow(hwnd);
            }
            break;
       case WM_COMMAND:
            //Handling button presses
            switch(LOWORD(wParam)) {

                case IDC_OUTPUT_TEXT:

                    switch (HIWORD(wParam))
                    {
                        case LBN_DBLCLK:
                            index = SendMessage(hwndOutputText, LB_GETCURSEL, 0, 0);
                            SendMessage(hwndOutputText, LB_DELETESTRING, (WPARAM)index, 0);
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                            break;
                    }
                    break;

                case IDC_OUTPUT_TEXT2:

                    switch (HIWORD(wParam))
                    {
                        case LBN_DBLCLK:
                            index = SendMessage(hwndOutputText2, LB_GETCURSEL, 0, 0);
                            SendMessage(hwndOutputText2, LB_DELETESTRING, (WPARAM)index, 0);
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                            break;
                    }
                    break;

                case IDC_INPUT_TEXT:
                    if(HIWORD(wParam) == EN_SETFOCUS)
                    {
                        textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, placeholder))
                        {
                            SendMessage(hwndInputText, WM_SETTEXT, TRUE,(LPARAM)"");     // Reseting the text input
                            focused = 1;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    else if(HIWORD(wParam) == EN_KILLFOCUS)
                    {
                        textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, ""))
                        {
                            SendMessage(
                                hwndInputText,
                                WM_SETTEXT,
                                TRUE,
                                (LPARAM)placeholder);                                   // Recovering the placeholder
                            focused = 0;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    break;

                case IDC_INPUT_TEXT2:
                    if(HIWORD(wParam) == EN_SETFOCUS)
                    {
                        textSize = SendMessage(hwndInputText2, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, placeholder))
                        {
                            SendMessage(hwndInputText2, WM_SETTEXT, TRUE,(LPARAM)"");     // Reseting the text input
                            focused2 = 1;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    else if(HIWORD(wParam) == EN_KILLFOCUS)
                    {
                        textSize = SendMessage(hwndInputText2, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, ""))
                        {
                            SendMessage(
                                hwndInputText2,
                                WM_SETTEXT,
                                TRUE,
                                (LPARAM)placeholder);                                   // Recovering the placeholder
                            focused2 = 0;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    break;

                case IDC_ADD_BUTTON:

                    TextLength = SendMessage(hwndInputText, WM_GETTEXTLENGTH, 0, 0);
                    szText = (char*)malloc(TextLength+1);
                    SendMessage(hwndInputText, WM_GETTEXT, TextLength+1, (LPARAM)szText);
                    SendMessage(hwndOutputText, LB_ADDSTRING, 0, (LPARAM)szText);
                    SendMessage(hwndInputText, WM_SETTEXT, 0, (LPARAM)"");
                    free(szText);
                    break;

                case IDC_ADD_BUTTON2:

                    TextLength = SendMessage(hwndInputText2, WM_GETTEXTLENGTH, 0, 0);
                    szText = (char*)malloc(TextLength+1);
                    SendMessage(hwndInputText2, WM_GETTEXT, TextLength+1, (LPARAM)szText);
                    SendMessage(hwndOutputText2, LB_ADDSTRING, 0, (LPARAM)szText);
                    SendMessage(hwndInputText2, WM_SETTEXT, 0, (LPARAM)"");
                    free(szText);
                    break;

                case IDC_RESET_BUTTON:
                    SendMessage(hwndOutputText, LB_RESETCONTENT, 0, 0);
                    break;

                case IDC_RESET_BUTTON2:

                    SendMessage(hwndOutputText2, LB_RESETCONTENT, 0, 0);
                    break;

                case IDC_RED_BUTTON:
                    if (MessageBox(NULL, TEXT("Are you sure you want to choose the red pill?"), TEXT("Are you sure?"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {
                        return MessageBox(NULL, TEXT("YOU ARE A TRUE SPARTAN !!!"), TEXT("Right choice!"), MB_OK | MB_ICONASTERISK);
                    };
                   break;
                case IDC_BLUE_BUTTON:
                return MessageBox(NULL, TEXT("Good Luck with the report ;)"), TEXT("Wrong choice!"), MB_OK | MB_ICONWARNING);

                case IDC_REMOVE_BUTTON:
                    i = SendMessage(hwndOutputText, LB_GETCURSEL, 0, 0);
                    if(i != LB_ERR) {
                        SendMessage(hwndOutputText, LB_DELETESTRING, i, 0);
                    }
                    break;

                case IDC_REMOVE_BUTTON2:
                    i = SendMessage(hwndOutputText2, LB_GETCURSEL, 0, 0);
                    if(i != LB_ERR) {
                        SendMessage(hwndOutputText2, LB_DELETESTRING, i, 0);
                    }
                    break;

                case IDC_HELP_ABOUT:
                    return DialogBox(hProgramInstance, MAKEINTRESOURCE(IDD_ABOUT), NULL, (DLGPROC)DialogProcedure);
                    break;

                case IDC_FILE_EXIT:
                    SendMessage(hwnd, WM_DESTROY, 0, 0);
                    break;
            }
            break;

        case WM_KEYDOWN:
            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Color window in white on Shift + "/?" for US
            if((wParam == VK_F1)&&(HIBYTE(GetKeyState(VK_CONTROL)) > 1)) {
                 if (MessageBox(NULL, TEXT("Are you sure you want to choose the red pill?"), TEXT("Are you sure?"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {
                        return MessageBox(NULL, TEXT("YOU ARE A TRUE SPARTAN !!!"), TEXT("Right choice!"), MB_OK | MB_ICONASTERISK);
                    };
                   break;
            }
            // Color window in green on Shift + "'"" for US
            if((wParam == VK_F2)&&(HIBYTE(GetKeyState(VK_CONTROL)) > 1)) {
                return MessageBox(NULL, TEXT("Good Luck with the report ;)"), TEXT("Wrong choice!"), MB_OK | MB_ICONWARNING);
            }

        case WM_CTLCOLOREDIT:
                if(GetDlgCtrlID((HWND)lParam) == IDC_INPUT_TEXT)
          {
                hdc = (HDC)wParam;                                              //Get handles
                if(focused)
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(0, 0, 0));                            // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }
                else
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(150, 150, 150));                      // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }

                return (LONG)color;                                             // Paint it
            }
                if(GetDlgCtrlID((HWND)lParam) == IDC_INPUT_TEXT2)
          {
                hdc = (HDC)wParam;                                              //Get handles
                if(focused2)
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(0, 0, 0));                            // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }
                else
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(150, 150, 150));                      // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }

                return (LONG)color;                                             // Paint it
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);                                         // Getting coordinates of window client area
            SetBkMode(hdc, TRANSPARENT);                                        // Set the background to be transparent
            SetTextColor(hdc, RGB(0, 0, 0));
            EndPaint(hwnd, &ps);
            break;



        case WM_DRAWITEM:
            if ((UINT)wParam == IDC_RED_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szRedBtnText[5];

                strcpy(szRedBtnText, "Red Pill");
                GetTextExtentPoint32(lpdis->hDC, szRedBtnText, strlen(szRedBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(250, 250, 250));
                SetBkColor(lpdis->hDC, RGB(200, 50, 50));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szRedBtnText,
                    strlen(szRedBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);
                return TRUE;
            }
            else if ((UINT)wParam == IDC_BLUE_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szRedBtnText[5];

                strcpy(szRedBtnText, "Blue Pill");
                GetTextExtentPoint32(lpdis->hDC, szRedBtnText, strlen(szRedBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(250, 250, 250));
                SetBkColor(lpdis->hDC, RGB(24, 116, 205));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szRedBtnText,
                    strlen(szRedBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);
                return TRUE;
            }

            break;

        case WM_SYSCOMMAND:
            switch(wParam) {
                case SC_MAXIMIZE:
                    return MessageBox(NULL, TEXT("Congratulations!You clicked the Maximize Button..."), TEXT("Maximize "), MB_OK | MB_ICONASTERISK);

                case SC_CLOSE:
                     if(MessageBox(hwnd, "Do you really want to quit?", "Lab#1", MB_OKCANCEL) == IDOK)
                DestroyWindow(hwnd);
                break;

                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage (0);
            break;

        default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }

    return 0;
}

BOOL CALLBACK ColorScrDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
     {
      static int iColor[3];
      HWND hwndParent, hCtrl;
      int iCtrlID, iIndex;

      switch(msg)
         {
          case WM_CLOSE:
                DestroyWindow(hDlg);
          case WM_INITDIALOG :
              for(iCtrlID = 10; iCtrlID < 13; iCtrlID++)
                  {
                   hCtrl = GetDlgItem(hDlg, iCtrlID);
                   SetScrollRange(hCtrl, SB_CTL, 0, 255, FALSE);
                   SetScrollPos (hCtrl, SB_CTL, 0, FALSE);
                  }
            return TRUE;

          case WM_VSCROLL :
               hCtrl =(HWND) lParam;
               iCtrlID = GetWindowLong(hCtrl, GWL_ID);
               iIndex = iCtrlID - 10;
               hwndParent = GetParent(hDlg);

               switch(LOWORD(wParam))
                    {
                    case SB_PAGEDOWN :
                         iColor[iIndex] += 15; // fall through
                    case SB_LINEDOWN :
                         iColor[iIndex] = min(255, iColor[iIndex] + 1);
                         break;
                    case SB_PAGEUP :
                         iColor[iIndex] -= 15; // fall through
                    case SB_LINEUP :
                         iColor[iIndex] = max(0, iColor[iIndex] - 1);
                         break;
                    case SB_TOP :
                         iColor[iIndex] = 0;
                         break;
                    case SB_BOTTOM :
                         iColor[iIndex] = 255;
                         break;
                    case SB_THUMBPOSITION :

                    case SB_THUMBTRACK :
                         iColor[iIndex] = HIWORD(wParam);
                         break;
                    default :
                        return FALSE;
                    }
SetScrollPos (hCtrl, SB_CTL, iColor[iIndex], TRUE);
SetDlgItemInt(hDlg, iCtrlID + 3, iColor[iIndex], FALSE);

DeleteObject( (HGDIOBJ) SetClassLong(hwndParent, GCL_HBRBACKGROUND,
                  (LONG) CreateSolidBrush(
                       RGB(iColor[0], iColor[1], iColor[2]))));
       InvalidateRect(hwndParent, NULL, TRUE);
       return TRUE;
       }
return FALSE;
}

BOOL CALLBACK DialogProcedure(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
        case WM_INITDIALOG:
            return TRUE;


        case WM_CLOSE:
            EndDialog(hwndDlg, 0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case IDOK:
                case IDCANCEL:
                    EndDialog(hwndDlg, 0);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}
