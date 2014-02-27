#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <tchar.h>

//Here the ID values of windows are defined
#define IDC_ADD_BUTTON      100
#define IDC_ADD_BUTTON2     102
#define IDC_RESET_BUTTON    103
#define IDC_RESET_BUTTON2   104
#define IDC_RED_BUTTON      105
#define IDC_BLUE_BUTTON     106
#define IDC_INPUT_TEXT      107
#define IDC_OUTPUT_TEXT     108
#define IDC_INPUT_TEXT2     109
#define IDC_OUTPUT_TEXT2    110

//Windows procedure declaration
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
//  Make the class name into a global variable
char szClassName[ ] = "Lab1Class";

//  Create a global handle to an instance variable to be used across different functions
HINSTANCE hProgramInstance;
int  items,items2,focused = 0,focused2 = 0;


int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;                    // This is the handle for our window
    MSG messages;                 // Here messages to the application are saved
    WNDCLASSEX wincl;             // Data structure for the windowclass
    /* The Window Structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof (WNDCLASSEX);
    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);                         // Default icon
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);                       // Default icon
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);                           // Default arrow mouse cursor
    wincl.lpszMenuName = NULL;                                              // No menu
    wincl.cbClsExtra = 0;                                                   // No extra bytes after the window class
    wincl.cbWndExtra = 0;                                                   // Structure or the window instance
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(219,219,219));      //choosing the background color

    // Register the window class, and in case of failure quit the program!
    if(!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx (
        0,                                                                  // Extended possibilites for variation
        szClassName,                                                        // Class name
        "Lab#1",                                                            // Window title
        WS_OVERLAPPEDWINDOW,                                                // Basic window style
        CW_USEDEFAULT, CW_USEDEFAULT,                                       // Set starting point to default value
        490, 340,                                                           // Set the dimensions of the window
        HWND_DESKTOP,                                                       // The window is a child-window to desktop
        NULL,                                                               // No menu
        hThisInstance,                                                      // Program Instance handler
        NULL);                                                              // No Window Creation data

    ShowWindow (hwnd, nCmdShow);                                            //display the window on the screen
    srand(time(NULL));

    // Run the message loop. It will run until GetMessage() returns 0
    while (GetMessage (&messages, NULL, 0, 0))
    {
         // Translate virtual-key messages into character messages
         TranslateMessage(&messages);
        // Send message to WindowProcedure
         DispatchMessage(&messages);
    }

    return messages.wParam;
}
//  This function is called by the Windows function DispatchMessage()
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) //all the handles to different controls
{
    static HWND hwndInputText,hwndInputText2;
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
                35, 270,                                              // the left and top co-ordinates
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
                265, 270,                                             // the left and top co-ordinates
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
                135, 270,                                             // the left and top co-ordinates
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
                365, 270,                                             // the left and top co-ordinates
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
                75, 35,                                               // the left and top co-ordinates
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
                315, 35,                                              // the left and top co-ordinates
                80, 35,                                               // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_BLUE_BUTTON,                               // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            hwndOutputText = CreateWindowEx(
                (DWORD)NULL,                                          // The class name required is edit
                TEXT("edit"),                                         // the caption of the button
                TEXT(""),                                             // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |      // Textbox styles
                ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY,
                20, 80,                                               // the left and top co-ordinates
                200, 150,                                             // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_OUTPUT_TEXT,                               // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            hwndInputText = CreateWindowEx(
                 (DWORD)NULL,
                TEXT("edit"),                                         // The class name required is edit
                TEXT(placeholder),                                    // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER,                    // Textbox styles
                20, 235,                                              // the left and top co-ordinates
                200, 20,                                              // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_INPUT_TEXT,                                // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);

            hwndOutputText2 = CreateWindowEx(
                (DWORD)NULL,                                          // The class name required is edit
                TEXT("edit"),                                         // the caption of the button
                TEXT(""),                                             // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |      // Textbox styles
                ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY,
                250, 80,                                              // the left and top co-ordinates
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
                250, 235,                                             // the left and top co-ordinates
                200, 20,                                              // width and height
                hwnd,                                                 // parent window handle
                (HMENU)IDC_INPUT_TEXT2,                               // the ID of your button
                hProgramInstance,                                     // the instance of your application
                NULL);
            break;

       case WM_COMMAND:
            //Handling button presses
            switch(LOWORD(wParam)) {
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
                    //sending the message from the edit box to the first list box
                    textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                    message[textSize] = _T('\0');

                    if(strlen(message) && strcmp(message, placeholder))
                    {
                        char *item = new char[200];
                        if(items)
                            strcpy(item, "\r\n - ");
                        else
                            strcpy(item, " - ");                                    // Managing the new string
                        strcat(item, message);
                        SendMessage(hwndOutputText, EM_REPLACESEL,
                            TRUE, (LPARAM)item);                                    // Appending a new item in the list
                        SendMessage(hwndInputText, WM_SETTEXT, TRUE,(LPARAM)"");    // RESETing the text input
                        delete [] item;                                             // Managing the memory
                        items += 1;                                                 // Incrementing the number of items
                        SendMessage(
                            hwndInputText,
                            WM_SETTEXT,
                            TRUE,
                            (LPARAM)placeholder);                                   // Recovering the placeholder
                        focused = 0;
                    }
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    break;

                case IDC_ADD_BUTTON2:
                    //sending the message from the edit box to the second list box
                    textSize = SendMessage(hwndInputText2, WM_GETTEXT, 100, (LPARAM)message);
                    message[textSize] = _T('\0');

                    if(strlen(message) && strcmp(message, placeholder))
                    {
                        char *item = new char[200];
                        if(items2)
                            strcpy(item, "\r\n - ");
                        else
                            strcpy(item, " - ");                                    // Managing the new string
                        strcat(item, message);
                        SendMessage(hwndOutputText2, EM_REPLACESEL,
                            TRUE, (LPARAM)item);                                    // Appending a new item in the list
                        SendMessage(hwndInputText2, WM_SETTEXT, TRUE,(LPARAM)"");   // RESETing the text input
                        delete [] item;                                             // Managing the memory
                        items2 += 1;                                                // Incrementing the number of items
                        SendMessage(
                            hwndInputText2,
                            WM_SETTEXT,
                            TRUE,
                            (LPARAM)placeholder);                                   // Recovering the placeholder
                        focused2 = 0;
                    }
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    break;

                case IDC_RESET_BUTTON:
                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)"");
                    break;
                case IDC_RESET_BUTTON2:
                    SendMessage(hwndOutputText2, WM_SETTEXT, 0, (LPARAM)"");
                    break;
                case IDC_RED_BUTTON:
                    if (MessageBox(NULL, TEXT("Are you sure you want to choose the red pill?"), TEXT("Are you sure?"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {
                        return MessageBox(NULL, TEXT("YOU ARE A TRUE SPARTAN !!!"), TEXT("Right choice!"), MB_OK | MB_ICONASTERISK);
                    };
                   break;
                case IDC_BLUE_BUTTON:
                return MessageBox(NULL, TEXT("Good Luck with the report ;)"), TEXT("Wrong choice!"), MB_OK | MB_ICONWARNING);
            }
            break;

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
            SetTextColor(hdc, RGB(0, 0, 0));                                    // Setting the text color to black
            DrawText(hdc, "\n Choose your destiny!", -1, &rect, DT_CENTER | DT_TOP);
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
