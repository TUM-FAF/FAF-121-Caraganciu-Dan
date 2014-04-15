#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define ID_TIMER 201
#define WINDOW_W 900
#define WINDOW_H 800
#define PACMAN_W 85
#define PACMAN_H 50
#define PACMAN2_W 85
#define PACMAN2_H 50

typedef struct BALL
{
    HBITMAP hBitmap;                  //the elipse will be transformed in a bitmap
    COLORREF cr;                      //ball's collor
    int cxClient,
        cyClient,                     //window size                                         //
        xCenter,
        yCenter,                      //ball's start
        cxTotal,
        cyTotal,                      //dimension for non border passing
        cxRadius,
        cyRadius,                     //ellispe diameter
        cxMove,
        cyMove;                       //pixeel to move
}BALL;

BALL ball[10];                        //max number of balls 10
HBRUSH hBrush;
HDC hdcMem, hdc;
int speed = 1;                        //animation speed
BITMAP bitmap;
PAINTSTRUCT ps;
int width = 900,height = 800;         //initial window size

LRESULT CALLBACK WindowProcedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void ReDraw(void);
void PACMAN(HDC hdc, int direction, int XOff, int YOff);
void PACMAN2(HDC hdc, int direction2, int XOff2, int YOff);
void DrawNyan(HDC hdc);
int X_INC=5;
int X_INC2=4;
int counter=0;
int counter2=0;
HWND hwnd=NULL;
int Y_OFFSET=550;
int Y_OFFSET2=550;
int curX=0;
int curX2=160;
int direction = 1;
int direction2=1;
int timer = 100;
bool flipped = false;
bool flipped2= false;
COLORREF PacManColor = RGB(255, 118, 0);
COLORREF PacMan2Color = RGB(0, 0, 255);
HBITMAP nyan[6];
HBITMAP rainbow;
int nyanXPos = 0;
int rainbowPos;
bool rainbowUp = false;

LPSTR szClassName = "Lab4Class";
HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    WNDCLASSEX wnd;
    MSG msg;
    hInst = hInstance;

    /* The Window Structure */
    wnd.hInstance = hInst;
    wnd.lpszClassName = szClassName;
    wnd.lpfnWndProc = WindowProcedure;
    wnd.style = NULL;
    wnd.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);                                // Default icon
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);                              // Default icon
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);                                  // Default arrow mouse cursor
    wnd.lpszMenuName = NULL;                                                    // No menu
    wnd.cbClsExtra = 0;                                                         // No extra bytes after the window class
    wnd.cbWndExtra = 0;                                                         //  structure or the window instance

    wnd.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH );

    if(!RegisterClassEx(&wnd))                                                  // Register the WNDCLASSEX
    {
        MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        (DWORD)NULL,
        szClassName,
        "Lab#4",                                                                // Window title
        WS_OVERLAPPEDWINDOW,                                                    // Basic window style
        CW_USEDEFAULT, CW_USEDEFAULT,                                           // Set starting point to default value
        WINDOW_W, WINDOW_H,                                                               // Set all the dimensions to default value
        NULL,                                                                   //no parent window
        NULL,                                                                   //no menu
        hInst,
        NULL);                                                                  //no parameters to pass

    ShowWindow(hwnd, SW_SHOWNORMAL);                                            //display the window on the screen
    SetActiveWindow(hwnd);
    UpdateWindow(hwnd);                                                         //make sure the window is updated correctly
    SetTimer(hwnd, ID_TIMER, timer, NULL);

    while(GetMessage(&msg, NULL, 0, 0))                                         //message loop
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
    void set_ball_params(LPARAM lParam, int nr) {
        ball[nr].cxClient = width;
        ball[nr].cyClient = height;
        ball[nr].xCenter =rand() % 850;
        ball[nr].yCenter = rand() % 390+30;
        srand (time(NULL));
        ball[nr].cxMove = rand()%20;
        ball[nr].cyMove = rand()%20;
        ball[nr].cr = RGB(rand()%256,rand()%256,rand()%256);
        ball[nr].cxRadius = 20;
        ball[nr].cyRadius = 20;
        ball[nr].cxTotal = 2 *(ball[nr].cxRadius + ball[nr].cxMove);
        ball[nr].cyTotal = 2 *(ball[nr].cyRadius + ball[nr].cyMove);
}

    void create(HWND nhwnd, LPARAM lParam, int nr)
    {
        set_ball_params(lParam, nr);
        if (ball[nr].hBitmap){                                                      //erases the previous image of ball
        DeleteObject(ball[nr].hBitmap);
        }
        hdc = GetDC(nhwnd);
        hdcMem = CreateCompatibleDC(hdc);
        ball[nr].hBitmap = CreateCompatibleBitmap(hdc, ball[nr].cxTotal, ball[nr].cyTotal);
        ReleaseDC(nhwnd, hdc);
        SelectObject(hdcMem, ball[nr].hBitmap);
        Rectangle(hdcMem, -1, -1, ball[nr].cxTotal + 1, ball[nr].cyTotal + 1);      //define space for ball
        hBrush = CreateSolidBrush(ball[nr].cr);
        SelectObject(hdcMem, hBrush);
        SetBkColor(hdcMem, RGB(0, 0, 0));
        Ellipse(hdcMem, ball[nr].cxMove, ball[nr].cyMove,
                        ball[nr].cxTotal - ball[nr].cxMove,
                        ball[nr].cyTotal - ball[nr].cyMove);                        //draw ball with specified values
        DeleteDC(hdcMem);
        DeleteObject(hBrush);
    }


    void moove(HWND nhwnd, int nr)
    {
        if(!ball[nr].hBitmap) {                                                     //if there are balls, return
            return;
        }
        hdc = GetDC(nhwnd);
        hdcMem = CreateCompatibleDC(hdc);                                           // Create a memory device compatible with the above DC variable
        SelectObject(hdcMem, ball[nr].hBitmap);
        BitBlt(hdc, ball[nr].xCenter - ball[nr].cxTotal / 2,
                    ball[nr].yCenter - ball[nr].cyTotal / 2,
                    ball[nr].cxTotal, ball[nr].cyTotal, hdcMem, 0, 0, SRCCOPY);     // Copy the bits from the memory DC into the current dc
        ReleaseDC(nhwnd, hdc);
        DeleteDC(hdcMem);                                                           // Restore the old bitmap

        ball[nr].xCenter += ball[nr].cxMove;                                        //ball move
        ball[nr].yCenter += ball[nr].cyMove;
        if ((ball[nr].xCenter + ball[nr].cxRadius >= ball[nr].cxClient) ||
           (ball[nr].xCenter - ball[nr].cxRadius <= 0)) {
            ball[nr].cxMove = -ball[nr].cxMove;
        }
        if ((ball[nr].yCenter + ball[nr].cyRadius >= ball[nr].cyClient-320) ||
           (ball[nr].yCenter - ball[nr].cyRadius <= 0)) {
            ball[nr].cyMove = -ball[nr].cyMove;
           }
    }


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  static RECT UpdateRect = {0, Y_OFFSET-100, PACMAN_W, Y_OFFSET+PACMAN_H+1};
  static RECT UpdateRect2 = {0, Y_OFFSET2-100,PACMAN2_W,Y_OFFSET2+PACMAN2_H+1};
   BOOL newBall = true;
    static int nrBalls = 0;
  switch (message)
  {
    case WM_CREATE:
      for(int i = 0; i < 6; i++)
      {
        char str[11];
        sprintf(str, "%d.bmp", i+1);
        nyan[i] = (HBITMAP)LoadImage(hInst, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
      }
      rainbow = (HBITMAP)LoadImage(hInst, "colors.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
      return 0;

    case WM_SIZE :
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            if (newBall){
                create(hwnd, lParam, nrBalls);
                newBall = false;
            }
            for (int i = 0; i < nrBalls; i++) {
                ball[i].cxClient = width;
                ball[i].cyClient = height;
                ball[i].xCenter =width/ 2;
                ball[i].yCenter = height/ 2;
            }
            return 0;

    case WM_LBUTTONDOWN :
            if(nrBalls < 9){                                                   //max number of 20 balls
                nrBalls++;
                create(hWnd, lParam, nrBalls);
            }
            return 0;

    case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    case WM_SYSCOMMAND:
        switch(wParam) {
            case SC_MAXIMIZE:
            return MessageBox(NULL, TEXT("You don't wanna do this ;)"), TEXT("Maximize "), MB_OK | MB_ICONASTERISK);

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;


    case WM_CTLCOLORSTATIC:
            return (LRESULT)GetStockObject( WHITE_BRUSH );

    case WM_PAINT:
            ReDraw();
            return 0;

    case WM_TIMER:

        for (int i = 0; i <= nrBalls; i++)
            {
                moove(hWnd, i);
            }
        if (wParam == ID_TIMER )
        {
        curX += X_INC * direction;
        curX2+= X_INC2 * direction2;

        if (curX > WINDOW_W - PACMAN_W && counter<8)
        {
        curX = WINDOW_W - PACMAN_W-160;
        Y_OFFSET=Y_OFFSET-50;
        direction = -1;
        flipped = true;
        X_INC--;
        counter=counter+2;
        }

        if (curX2 > WINDOW_W - PACMAN2_W && counter<8)
        {
        curX2 = WINDOW_W - PACMAN2_W;
        Y_OFFSET2=Y_OFFSET2-50;
        direction2 = -1;
        X_INC2++;
        counter=counter+2;
        }

        if (curX < 0 && counter<8)
        {
        curX = 0;
        Y_OFFSET=Y_OFFSET-50;
        direction = 1;
        X_INC++;
        counter=counter+2;
        }

        if (curX2 < 0 && counter<8)
        {
        curX2 = 160;
        Y_OFFSET2=Y_OFFSET2-50;
        direction2 = 1;
        flipped2 = true;
        X_INC2--;
        counter=counter+2;
        }

        if (curX > WINDOW_W - PACMAN_W && counter>=8)
        {
        curX = WINDOW_W - PACMAN_W-160;
        Y_OFFSET=Y_OFFSET+50;
        direction = -1;
        flipped = true;
        X_INC--;
        counter++;
        }

        if (curX2 > WINDOW_W - PACMAN2_W && counter>=8)
        {
        curX2 = WINDOW_W - PACMAN2_W;
        Y_OFFSET2=Y_OFFSET2+50;
        direction2 = -1;
        X_INC2++;
        counter++;
        }

        if (curX < 0 && counter>=8)
        {
        curX = 0;
        Y_OFFSET=Y_OFFSET+50;
        direction = 1;
        X_INC++;
        counter++;
        }

        if (curX2 < 0 && counter>=8)
        {
        curX2 = 160;
        Y_OFFSET2=Y_OFFSET2+50;
        direction2 = 1;
        flipped2 = true;
        X_INC2--;
        counter=0;
        }
        InvalidateRect(hwnd, &UpdateRect, 1);
        InvalidateRect(hwnd, &UpdateRect2, 1);
        UpdateWindow(hwnd);
        UpdateRect2.left = curX2;
        UpdateRect.left = curX;
        UpdateRect2.right = curX2 + PACMAN2_W + 1;
        UpdateRect.right = curX + PACMAN_W + 1;
        InvalidateRect(hwnd, &UpdateRect, 1);
        InvalidateRect(hwnd, &UpdateRect2, 1);
        UpdateWindow( hwnd );
      }
      return 0;

    case WM_MOUSEWHEEL:
      // Changing the animation speed.
      if(GET_WHEEL_DELTA_WPARAM(wParam) < 0)
      {
          if(timer < 500)
            timer += 5;
          else
            return 0;
      }
      else
      {
          if(timer > 5)
            timer -= 5;
          else
            return 0;
      }
      KillTimer(hwnd, ID_TIMER);
      SetTimer(hwnd, ID_TIMER, timer, NULL);
      return 0;
  }
  return (DefWindowProc(hWnd, message, wParam, lParam));
}

void PACMAN(HDC hdc, int direction, int XOff, int YOff)
{
  HPEN gpen, wpen,oldpen;
  HBRUSH gbrush, wbrush, oldbrush;
  POINT mouth[3] = {{65, 20}, {85, 30}, {85, 10}};

  srand (time(NULL));

  int i;
  if (direction < 0)
  {
    for (i=0; i<3; i++)
    {

      mouth[i].x = PACMAN_W - mouth[i].x;
    }
  }

  for (i=0; i<3; i++)
  {

    mouth[i].x += XOff;
    mouth[i].y += YOff;
  }

  if(flipped)
  {
    PacManColor = RGB(rand() % 156, rand() % 156, rand() % 156);
    flipped = false;
  }

  gpen = CreatePen(PS_SOLID, 1, PacManColor);
  oldpen = (HPEN)SelectObject(hdc, gpen);
  gbrush = CreateSolidBrush(PacManColor);
  wbrush = (HBRUSH)GetStockObject( WHITE_BRUSH );
  wpen = (HPEN)GetStockObject( WHITE_PEN );
  oldbrush = (HBRUSH)SelectObject(hdc, gbrush);

  if (direction < 0)
    Ellipse(hdc, XOff, 0 + YOff, 50 + XOff, 40 + YOff);
  else
    Ellipse(hdc, 35 + XOff, 0 + YOff, 85 + XOff, 40 + YOff);


  SelectObject(hdc, wpen);
  SelectObject(hdc, wbrush);
  Polygon(hdc, (CONST POINT *)&mouth, 3);


    if (direction < 0)
      Ellipse(hdc, 20 + XOff, 6 + YOff, 25 + XOff, 12 + YOff);
    else
      Ellipse(hdc, 60 + XOff, 6 + YOff, 65 + XOff, 12 + YOff);


  SelectObject(hdc, oldpen);
  DeleteObject( (HGDIOBJ)gpen );
  SelectObject(hdc, oldbrush);
  DeleteObject( (HGDIOBJ)gbrush );
}

void PACMAN2(HDC hdc, int direction2, int XOff2, int YOff)
{
  HPEN gpen, wpen,oldpen;
  HBRUSH gbrush, wbrush, oldbrush;
  POINT mouth[3] = {{65, 20}, {85, 30}, {85, 10}};

  srand (time(NULL));

  int i;
  if (direction2 < 0)
  {
    for (i=0; i<3; i++)
    {

      mouth[i].x = PACMAN2_W - mouth[i].x;
    }
  }

  for (i=0; i<3; i++)
  {

    mouth[i].x += XOff2;
    mouth[i].y += YOff;
  }

  if(flipped2)
  {
    PacMan2Color = RGB(rand() % 256, rand() % 256, rand() % 256);
    flipped2 = false;
  }

  gpen = CreatePen(PS_SOLID, 1, PacMan2Color);
  oldpen = (HPEN)SelectObject(hdc, gpen);
  gbrush = CreateSolidBrush(PacMan2Color);
  wbrush = (HBRUSH)GetStockObject( WHITE_BRUSH );
  wpen = (HPEN)GetStockObject( WHITE_PEN );
  oldbrush = (HBRUSH)SelectObject(hdc, gbrush);

  if (direction2 < 0)
    Ellipse(hdc, XOff2, 0 + YOff, 50 + XOff2, 40 + YOff);
  else
    Ellipse(hdc, 35 + XOff2, 0 + YOff, 85 + XOff2, 40 + YOff);


  SelectObject(hdc, wpen);
  SelectObject(hdc, wbrush);
  Polygon(hdc, (CONST POINT *)&mouth, 3);


    if (direction2 < 0)
      Ellipse(hdc, 20 + XOff2, 6 + YOff, 25 + XOff2, 12 + YOff);
    else
      Ellipse(hdc, 60 + XOff2, 6 + YOff, 65 + XOff2, 12 + YOff);


  SelectObject(hdc, oldpen);
  DeleteObject( (HGDIOBJ)gpen );
  SelectObject(hdc, oldbrush);
  DeleteObject( (HGDIOBJ)gbrush );
}

void DrawNyan(HDC hdc)
{
  RECT rect;
  rect.top = 100;
  rect.left = 0;
  rect.bottom = 281;
  rect.right = nyanXPos;
  HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
  hdc = GetDC(hwnd);
  hdcMem = CreateCompatibleDC(hdc);

  if(nyanXPos > WINDOW_W)
  {
    nyanXPos = 0;
    rect.right = WINDOW_W;
    FillRect(hdc, &rect, hBrush);
  }

  int rainDir = (rainbowUp)?-1:1;
  SelectObject (hdcMem, rainbow);

  if((nyanXPos % 50) == 0)
    rainbowPos += rainDir;

  if(rainbowPos > 3)
    rainbowUp = true;
  else if (rainbowPos < 0)
    rainbowUp = false;

  BitBlt(hdc, nyanXPos - 5, 630 + rainbowPos * 5, 5, 96, hdcMem, 0, 0, SRCCOPY);

  SelectObject (hdcMem, nyan[ (nyanXPos/5) % 6 ]);
  BitBlt(hdc, nyanXPos, 600, 260, 181, hdcMem, 0, 0, SRCCOPY);
  ReleaseDC(hwnd, hdc);
  DeleteDC(hdcMem);

  DeleteObject(hBrush);
  nyanXPos += 5;
}

void ReDraw()
{
  HDC hdc;
  PAINTSTRUCT ps;

  hdc = BeginPaint(hwnd, (LPPAINTSTRUCT)&ps);
  PACMAN2(hdc, direction2, curX2, Y_OFFSET2);
  PACMAN(hdc, direction, curX, Y_OFFSET);
  DrawNyan(hdc);
  EndPaint(hwnd, (LPPAINTSTRUCT)&ps);
}
