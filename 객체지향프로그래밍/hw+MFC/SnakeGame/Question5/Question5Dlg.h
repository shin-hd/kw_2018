
// Question5Dlg.h: 헤더 파일
//

#pragma once
//#include <conio.h>

#include <iostream>
#include "stdafx.h"

// Item struct
class Item {
public:
	int x1, y1;
	int x2, y2;
	int exist; // If item is already exist in playground, exist is 1

	Item();
	~Item();
	
	void createItem();
};

// Snake Node
class Snake {
public:
	int x1, x2;
	int y1, y2;
	Snake* preSnake;
	Snake* nextSnake;
};

// SnakeList class
class SnakeList {
private:
	Snake * sHead;
	int sSize;
	int direction;

public:
	SnakeList();
	~SnakeList();	
	
	virtual Snake* getHead()const;
	virtual int getDir()const;
	virtual int getSize()const;
	virtual void setDirection(int dir);
	virtual void move(); // move to direction
	virtual void getItem(); // +1 size
	virtual void reset(); // reset
	
						  // head is 0, check x1 and y1 in snake without head
	// head is 1, check x1 and y1 in snake
	virtual bool checkXY(int x1, int y1, int head);
};


// CQuestion5Dlg 대화 상자
class CQuestion5Dlg : public CDialogEx
{
// 생성입니다.
public:
	CQuestion5Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	SnakeList MySnake; // generates MySnake
	Item item;
	int die;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUESTION5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static UINT TimeThread(LPVOID _mothod);
};