
// Question5Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Question5.h"
#include "Question5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
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


// CQuestion5Dlg 대화 상자



CQuestion5Dlg::CQuestion5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QUESTION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQuestion5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQuestion5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CQuestion5Dlg 메시지 처리기

BOOL CQuestion5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CQuestion5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CQuestion5Dlg::OnPaint()
{
	CPaintDC dc(this);
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* pbrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 1200, 800);
	dc.SelectObject(&brush);

	// draw playground
	int x1 = -26, x2 = 10;
	int y1 = 46, y2 = 82;
	CPen pen;
	pen.CreatePen(PS_DOT, 2, RGB(100, 100, 100));
	CPen* pg_pen = dc.SelectObject(&pen);
	while(x2 < 1110) {
		x1 += 36;
		x2 += 36;
		dc.Rectangle(x1 + 3, 13, x2 - 3, 43);
		dc.Rectangle(x1 + 3, (10 + 36 * 19) + 3, x2 - 3, (10 + 36 * 20) - 3);
	}
	while (y2 < 700) {
		dc.Rectangle(13, y1 + 3, 43, y2 - 3);
		dc.Rectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
		y1 += 36;
		y2 += 36;
	}
	dc.SelectObject(&pen);

	x1 = -26;
	x2 = 10;
	y1 = 46;
	y2 = 82;
	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(100, 100, 100));
	pbrush = dc.SelectObject(&brush);
	while (x2 < 1110) {
		x1 += 36;
		x2 += 36;
		dc.Rectangle(x1 + 12, 22, x2 - 12, 34);
		dc.Rectangle(x1 + 12, (10 + 36 * 19) + 12, x2 - 12, (10 + 36 * 20) - 12);
	}
	while (y2 < 700) {
		dc.Rectangle(22, y1 + 12, 34, y2 - 12);
		dc.Rectangle(x1 + 12, y1 + 12, x2 - 12, y2 - 12);
		y1 += 36;
		y2 += 36;
	}
	dc.SelectObject(&brush);

	// draw first snake
	Snake* snake = new Snake;
	snake = MySnake.getHead();
	int dir = MySnake.getDir();
	pen.DeleteObject();
	pen.CreatePen(PS_DOT, 2, RGB(0, 255, 0));
	CPen* sPen = dc.SelectObject(&pen);
	dc.SelectObject(&pen);
	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* sBrush = dc.SelectObject(&brush);
	dc.SelectObject(&brush);
	x1 = snake->x1;
	x2 = snake->x2;
	y1 = snake->y1;
	y2 = snake->y2;
	POINT pt[3] = { 0 };
	switch (dir) {
	case 0:
		pt[0] = { (x1 + x2) / 2 , y1 + 7 }; // 높이(y1~y2 (+-3) 변경가능
		pt[1] = { x1 + 7, y2 - 7 };
		pt[2] = { x2 - 7, y2 - 7 };
		break;
	case 1:
		pt[0] = { (x1 + x2) / 2, y2 - 7 };
		pt[1] = { x1 + 7, y1 + 7 };
		pt[2] = { x2 - 7, y1 + 7 };
		break;
	case 2:
		pt[0] = { x1 + 7, (y1 + y2) / 2 };
		pt[1] = { x2 - 7, y1 + 7 };
		pt[2] = { x2 - 7, y2 - 7 };
		break;
	case 3:
		pt[0] = { x2 - 7, (y1 + y2) / 2 };
		pt[1] = { x1 + 7, y1 + 7 };
		pt[2] = { x1 + 7, y2 - 7 };
		break;
	} // draw head
	snake = snake->nextSnake;
	while (snake->nextSnake) {
		x1 = snake->x1;
		x2 = snake->x2;
		y1 = snake->y1;
		y2 = snake->y2;
		dc.Ellipse(x1 + 5, y1 + 5, x2 - 5, y2 - 5);
		dc.Ellipse(x1 + 12, y1 + 12, x2 - 12, y2 - 12); // 크기 알맞은지 확인
		snake = snake->nextSnake;
	} // draw body
	x1 = snake->x1;
	x2 = snake->x2;
	y1 = snake->y1;
	y2 = snake->y2;
	dc.MoveTo(x1 + 7, (y1 + y2) / 2);
	dc.LineTo((x1 + x2 - 6) / 2, y1 + 7);
	dc.MoveTo(x1 + 7, (y1 + y2) / 2);
	dc.LineTo((x1 + x2 - 6) / 2, y2 - 7);
	dc.MoveTo(x2 - 7, (y1 + y2) / 2);
	dc.LineTo((x1 + x2 + 6) / 2, y1 + 7);
	dc.MoveTo(x2 - 7, (y1 + y2) / 2);
	dc.LineTo((x1 + x2 + 6) / 2, y2 - 7);
	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(0, 255, 0));
	CBrush* TBrush = dc.SelectObject(&brush);
	dc.SelectObject(&brush);
	dc.Polygon(pt, 3);
	
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(120, 43, 144));
	dc.SetTextAlign(TA_CENTER);
	dc.TextOutW(10 + 36 * 15, 10 + 36 * 20, _T("Size of Snake : 3"));
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CQuestion5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CQuestion5Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	// where has loop?
	if (pMsg->message == WM_KEYDOWN) {
		if (item.exist == 0) {
			do { // create item
				item.createItem();
			} while (MySnake.checkXY(item.x1, item.y1, 1));

			// draw item
			CClientDC dc(this);
			CBrush brush;
			brush.CreateSolidBrush(RGB(255, 0, 0));
			CBrush* itemBrush = dc.SelectObject(&brush);
			dc.SelectObject(&brush);
			CPen pen;
			pen.CreatePen(PS_DOT, 2, RGB(255, 0, 0));
			CPen* itemPen = dc.SelectObject(&pen);
			dc.SelectObject(&brush);
			int x1, x2, y1, y2;
			x1 = item.x1;
			x2 = item.x2;
			y1 = item.y1;
			y2 = item.y2;
			int mx = (x1 + x2) / 2;
			int my = (y1 + y2) / 2;
			CRect Pie1(x1 + 7, my - (mx - x1) / 2, mx, my + (mx - x1) / 2);
			CRect Pie2(mx, my - (mx - x1) / 2, x2 - 7, my + (mx - x1) / 2);
			POINT pt[3] = {0};
			pt[0] = { x1 + 8, my };
			pt[1] = { x2 - 8, my };
			pt[2] = { mx , y2 - 8 };
			dc.Polygon(pt, 3);
			dc.Pie(Pie1, CPoint(mx, my), CPoint(x1 + 7, my));
			dc.Pie(Pie2, CPoint(x2 - 7, my), CPoint(mx, my));
		}
	
		// set direction
		POINT point;
		int checkDir = MySnake.getDir();
		if (::GetCursorPos(&point)) {
			switch (pMsg->wParam) {
			case VK_LEFT:
				if (checkDir == 3)
					return CDialogEx::PreTranslateMessage(pMsg);
				MySnake.setDirection(2);
				break;
			case VK_RIGHT:
				if (checkDir == 2)
					return CDialogEx::PreTranslateMessage(pMsg);
				MySnake.setDirection(3);
				break;
			case VK_UP:
				if (checkDir == 1)
					return CDialogEx::PreTranslateMessage(pMsg);
				MySnake.setDirection(0);
				break;
			case VK_DOWN:
				if (checkDir == 0)
					return CDialogEx::PreTranslateMessage(pMsg);
				MySnake.setDirection(1);
				break;
			case 'Y':
			case 'y':
				if (die == 1) {
					die = 0;
					item.exist = 0;
					CClientDC dc(this);
					CBrush brush;
					brush.CreateSolidBrush(RGB(0, 0, 0));
					CBrush* pbrush = dc.SelectObject(&brush);
					dc.Rectangle(46, 46, 1090, 690);
					dc.SelectObject(&brush);
					Snake* snake = new Snake;
					snake = MySnake.getHead();
					int x1 = snake->x1, x2 = snake->x2, y1 = snake->y1, y2 = snake->y2;
					dc.Rectangle(x1, y1, x2, y2);
					CPen pen;
					pen.CreatePen(PS_DOT, 2, RGB(100, 100, 100));
					CPen* pg_pen = dc.SelectObject(&pen);
					if (!MySnake.checkXY(x1, y1, 0)) {
					dc.Rectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
					brush.DeleteObject();
					brush.CreateSolidBrush(RGB(100, 100, 100));
					pbrush = dc.SelectObject(&brush);
					dc.Rectangle(x1 + 12, y1 + 12, x2 - 12, y2 - 12);
					}
					MySnake.reset();
					snake = MySnake.getHead();
					int dir = MySnake.getDir();
					pen.DeleteObject();
					pen.CreatePen(PS_DOT, 2, RGB(0, 255, 0));
					CPen* sPen = dc.SelectObject(&pen);
					dc.SelectObject(&pen);
					brush.DeleteObject();
					brush.CreateSolidBrush(RGB(0, 0, 0));
					CBrush* sBrush = dc.SelectObject(&brush);
					dc.SelectObject(&brush);
					x1 = snake->x1;
					x2 = snake->x2;
					y1 = snake->y1;
					y2 = snake->y2;
					POINT pt[3] = { 0 };
					switch (dir) {
					case 0:
						pt[0] = { (x1 + x2) / 2 , y1 + 7 }; // 높이(y1~y2 (+-3) 변경가능
						pt[1] = { x1 + 7, y2 - 7 };
						pt[2] = { x2 - 7, y2 - 7 };
						break;
					case 1:
						pt[0] = { (x1 + x2) / 2, y2 - 7 };
						pt[1] = { x1 + 7, y1 + 7 };
						pt[2] = { x2 - 7, y1 + 7 };
						break;
					case 2:
						pt[0] = { x1 + 7, (y1 + y2) / 2 };
						pt[1] = { x2 - 7, y1 + 7 };
						pt[2] = { x2 - 7, y2 - 7 };
						break;
					case 3:
						pt[0] = { x2 - 7, (y1 + y2) / 2 };
						pt[1] = { x1 + 7, y1 + 7 };
						pt[2] = { x1 + 7, y2 - 7 };
						break;
					} // draw head
					snake = snake->nextSnake;
					while (snake->nextSnake) {
						x1 = snake->x1;
						x2 = snake->x2;
						y1 = snake->y1;
						y2 = snake->y2;
						dc.Ellipse(x1 + 5, y1 + 5, x2 - 5, y2 - 5);
						dc.Ellipse(x1 + 12, y1 + 12, x2 - 12, y2 - 12); // 크기 알맞은지 확인
						snake = snake->nextSnake;
					} // draw body
					x1 = snake->x1;
					x2 = snake->x2;
					y1 = snake->y1;
					y2 = snake->y2;
					dc.MoveTo(x1 + 7, (y1 + y2) / 2);
					dc.LineTo((x1 + x2 - 6) / 2, y1 + 7);
					dc.MoveTo(x1 + 7, (y1 + y2) / 2);
					dc.LineTo((x1 + x2 - 6) / 2, y2 - 7);
					dc.MoveTo(x2 - 7, (y1 + y2) / 2);
					dc.LineTo((x1 + x2 + 6) / 2, y1 + 7);
					dc.MoveTo(x2 - 7, (y1 + y2) / 2);
					dc.LineTo((x1 + x2 + 6) / 2, y2 - 7);
					brush.DeleteObject();
					brush.CreateSolidBrush(RGB(0, 255, 0));
					CBrush* TBrush = dc.SelectObject(&brush);
					dc.SelectObject(&brush);
					dc.Polygon(pt, 3);

					dc.SetBkMode(TRANSPARENT);
					dc.SetTextColor(RGB(120, 43, 144));
					dc.SetTextAlign(TA_CENTER);
					dc.TextOutW(10 + 36 * 15, 10 + 36 * 20, _T("Size of Snake : 3"));

				}
				return CDialogEx::PreTranslateMessage(pMsg);
			default:
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			if (die == 1) {
				return CDialogEx::PreTranslateMessage(pMsg);
			}
			int x1, x2, y1, y2;
			Snake* snake = new Snake;
			snake = MySnake.getHead();
			int dir = MySnake.getDir();

			// erase old snake
			CClientDC dc(this);
			CBrush brush;
			brush.CreateSolidBrush(RGB(0, 0, 0));
			CBrush* Fblink = dc.SelectObject(&brush);
			dc.SelectObject(&brush);
			CPen pen;
			pen.CreatePen(PS_DOT, 2, RGB(0, 0, 0));
			CPen* Lblink = dc.SelectObject(&pen);
			dc.SelectObject(&pen);

			x1 = snake->x1;
			x2 = snake->x2;
			y1 = snake->y1;
			y2 = snake->y2;
			dc.Rectangle(x1, y1, x2, y2);
			while (snake->nextSnake->nextSnake) {
				snake = snake->nextSnake;
			}
			while (snake) {
				x1 = snake->x1;
				x2 = snake->x2;
				y1 = snake->y1;
				y2 = snake->y2;
				dc.Rectangle(x1, y1, x2, y2);
				snake = snake->nextSnake;
			}

			snake = MySnake.getHead();
			x1 = snake->x1;
			x2 = snake->x2;
			y1 = snake->y1;
			y2 = snake->y2;
			if (item.x1 == x1 && item.y1 == y1) {
				MySnake.getItem();
				item.exist = 0;
				int size = MySnake.getSize();
				CString str = _T("Size of Snake : ");
				if (size < 10) {
					str += (char)(size + '0');
				}
				else {
					str += (char)(size / 10 + '0');
					str += (char)(size % 10 + '0');
				}
				dc.Rectangle(10 + 36 * 10, 10 + 36 * 20, 10 + 36 * 20, 10 + 36 * 21);
				dc.SetBkMode(TRANSPARENT);
				dc.SetTextColor(RGB(120, 43, 144));
				dc.SetTextAlign(TA_CENTER);
				dc.TextOutW(10 + 36 * 15, 10 + 36 * 20, str); // 
			}
			else
				MySnake.move();

			// draw new snake
			pen.DeleteObject();
			pen.CreatePen(PS_DOT, 2, RGB(0, 255, 0));
			CPen* sPen = dc.SelectObject(&pen);
			dc.SelectObject(&pen);
			brush.DeleteObject();
			brush.CreateSolidBrush(RGB(0, 0, 0));
			CBrush* sBrush = dc.SelectObject(&brush);
			dc.SelectObject(&brush);
			snake = MySnake.getHead();
			x1 = snake->x1;
			x2 = snake->x2;
			y1 = snake->y1;
			y2 = snake->y2;
			POINT pt[3] = { 0 };
			switch (dir) {
			case 0:
				pt[0] = { (x1 + x2) / 2 , y1 + 7 }; // 높이(y1~y2 (+-3) 변경가능
				pt[1] = { x1 + 7, y2 - 7 };
				pt[2] = { x2 - 7, y2 - 7 };
				break;
			case 1:
				pt[0] = { (x1 + x2) / 2, y2 - 7 };
				pt[1] = { x1 + 7, y1 + 7 };
				pt[2] = { x2 - 7, y1 + 7 };
				break;
			case 2:
				pt[0] = { x1 + 7, (y1 + y2) / 2 };
				pt[1] = { x2 - 7, y1 + 7 };
				pt[2] = { x2 - 7, y2 - 7 };
				break;
			case 3:
				pt[0] = { x2 - 7, (y1 + y2) / 2 };
				pt[1] = { x1 + 7, y1 + 7 };
				pt[2] = { x1 + 7, y2 - 7 };
				break;
			} // draw head
			snake = snake->nextSnake;
			while (snake->nextSnake) {
				x1 = snake->x1;
				x2 = snake->x2;
				y1 = snake->y1;
				y2 = snake->y2;
				dc.Ellipse(x1 + 5, y1 + 5, x2 - 5, y2 - 5);
				dc.Ellipse(x1 + 12, y1 + 12, x2 - 12, y2 - 12); // 크기 알맞은지 확인
				snake = snake->nextSnake;
			} // draw body
			x1 = snake->x1;
			x2 = snake->x2;
			y1 = snake->y1;
			y2 = snake->y2;
			dc.MoveTo(x1 + 7, (y1 + y2) / 2);
			dc.LineTo((x1 + x2 - 6) / 2, y1 + 7);
			dc.MoveTo(x1 + 7, (y1 + y2) / 2);
			dc.LineTo((x1 + x2 - 6) / 2, y2 - 7);
			dc.MoveTo(x2 - 7, (y1 + y2) / 2);
			dc.LineTo((x1 + x2 + 6) / 2, y1 + 7);
			dc.MoveTo(x2 - 7, (y1 + y2) / 2);
			dc.LineTo((x1 + x2 + 6) / 2, y2 - 7);
			brush.DeleteObject();
			brush.CreateSolidBrush(RGB(0, 255, 0));
			CBrush* TBrush = dc.SelectObject(&brush);
		
			dc.SelectObject(&brush);
			dc.Polygon(pt, 3);

			snake = MySnake.getHead();
			x1 = snake->x1;
			x2 = snake->x2;
			y1 = snake->y1;
			y2 = snake->y2;
			if (x2 <= 46 || x1 >= 10 + 36 * 30 || y2 <= 46 || y1 >= 10 + 36 * 19 || MySnake.checkXY(x1, y1, 0)) {
				// 뱀이 죽었음을 나타내는 textbox를 출력하고 종료 여부 묻묻
				dc.SetBkMode(TRANSPARENT);
				dc.SetTextColor(RGB(255, 255, 255));
				dc.SetTextAlign(TA_CENTER);
				dc.TextOutW(10 + 36 * 15, 10 + 36 * 8, _T("Game Over"));
				dc.TextOutW(10 + 36 * 15, 10 + 36 * 10, _T("One more game? y/n"));
				die = 1;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////
// SnakeList Constructor
SnakeList::SnakeList() :sSize(3), direction(0) {
	Snake* head = new Snake;
	head->x1 = 10 + 36 * 14;
	head->x2 = head->x1 + 36;
	head->y1 = 10 + 36 * 9;
	head->y2 = head->y1 + 36;
	head->preSnake = NULL;
	sHead = head;
	Snake* body = new Snake;
	body->x1 = head->x1;
	body->x2 = head->x2;
	body->y1 = head->y2;
	body->y2 = head->y2 + 36;
	body->preSnake = head;
	sHead->nextSnake = body;
	Snake* tail = new Snake;
	tail->x1 = body->x1;
	tail->x2 = body->x2;
	tail->y1 = body->y2;
	tail->y2 = body->y2 + 36;
	tail->preSnake = body;
	tail->nextSnake = NULL;
	body->nextSnake = tail;
}

// SnakeList Destructor
SnakeList::~SnakeList() {
	delete sHead;
}

Snake* SnakeList::getHead()const {
	return sHead;
}

int SnakeList::getDir()const {
	return direction;
}

int SnakeList::getSize()const {
	return sSize;
}

void SnakeList::setDirection(int dir) {
	direction = dir;
}

// move 1 block
void SnakeList::move() {
	Snake* snake = new Snake;
	Snake* preSnake = new Snake;
	snake = sHead;
	while (snake->nextSnake) {
		snake = snake->nextSnake;
	}
	preSnake = snake->preSnake;
	while (preSnake->preSnake) {	
		snake->x1 = preSnake->x1;
		snake->x2 = preSnake->x2;
		snake->y1 = preSnake->y1;
		snake->y2 = preSnake->y2;
		snake = preSnake;
		preSnake = preSnake->preSnake;
	}
	snake->x1 = preSnake->x1;
	snake->x2 = preSnake->x2;
	snake->y1 = preSnake->y1;
	snake->y2 = preSnake->y2;
	switch (direction) {
	case 0:
		sHead->y1 -= 36;
		sHead->y2 -= 36;
		break;
	case 1:
		sHead->y1 += 36;
		sHead->y2 += 36;
		break;
	case 2:
		sHead->x1 -= 36;
		sHead->x2 -= 36;
		break;
	case 3:
		sHead->x1 += 36;
		sHead->x2 += 36;
		break;
	} // Locating head
}

// If sanke gets item, add 1 body
void SnakeList::getItem() {
	Snake* body = new Snake;
	body = sHead->nextSnake;
	Snake* newBody = new Snake;
	newBody->x1 = sHead->x1;
	newBody->x2 = sHead->x2;
	newBody->y1 = sHead->y1;
	newBody->y2 = sHead->y2;
	newBody->nextSnake = sHead->nextSnake;
	sHead->nextSnake = newBody;
	body->preSnake = newBody;
	newBody->preSnake = sHead;
	switch (direction) {
	case 0:
		sHead->y1 -= 36;
		sHead->y2 -= 36;
		break;
	case 1:
		sHead->y1 += 36;
		sHead->y2 += 36;
		break;
	case 2:
		sHead->x1 -= 36;
		sHead->x2 -= 36;
		break;
	case 3:
		sHead->x1 += 36;
		sHead->x2 += 36;
		break;
	}
	sSize++;
}

// player want to replay, do reset
void SnakeList::reset() {
	Snake* reset = new Snake;
	Snake* cur = new Snake;
	cur = sHead;

	while (cur) {
		reset = cur;
		cur = cur->nextSnake;
		delete reset;
	}

	direction = 0;
	Snake* head = new Snake;
	head->x1 = 10 + 36 * 14;
	head->x2 = head->x1 + 36;
	head->y1 = 10 + 36 * 9;
	head->y2 = head->y1 + 36;
	head->preSnake = NULL;
	sHead = head;
	Snake* body = new Snake;
	body->x1 = head->x1;
	body->x2 = head->x2;
	body->y1 = head->y2;
	body->y2 = head->y2 + 36;
	body->preSnake = head;
	sHead->nextSnake = body;
	Snake* tail = new Snake;
	tail->x1 = body->x1;
	tail->x2 = body->x2;
	tail->y1 = body->y2;
	tail->y2 = body->y2 + 36;
	tail->preSnake = body;
	tail->nextSnake = NULL;
	body->nextSnake = tail;
}

// if x1, y1 same as snake's x1 and y1, return 1
bool SnakeList::checkXY(int x1, int y1, int head) {
	Snake* snake = new Snake;
	if (head == 0) {
		snake = sHead->nextSnake;
	} // do not check head
	else {
		snake = sHead;
	} // check head
	while (snake) {
		if (x1 == snake->x1 && y1 == snake->y1)
			return 1;
		snake = snake->nextSnake;
	}
	return 0;
}

Item::Item() :x1(0), x2(0), y1(0), y2(0), exist(0) {}
Item::~Item() {};

// create item
void Item::createItem() {
	srand((unsigned int)(time(NULL)));
	x1 = rand() % 28 + 1;
	x1 = 10 + x1 * 36;
	y1 = rand() % 18 + 1;
	y1 = 10 + y1 * 36;
	x2 = x1 + 36;
	y2 = y1 + 36;
	exist = 1;
}