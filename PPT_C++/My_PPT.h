#pragma once
#include "CApplication.h"
#include "CSlides.h"
#include "CSlide.h"
#include "CPresentation.h"
#include "CPresentations.h"
#include "CSlideShowSettings.h"
#include "CShape.h"
#include "CShapes.h"
#include "CTextFrame.h"
#include "CTextRange.h"
#include "CTable0.h"
#include "CCell.h"
#include "CFillFormat.h"
#include "CColorFormat.h"
#include "CFonts.h"
#include "CFont0.h"
#include "CColumn.h"
#include "CColumns0.h"
#include "CRow.h"
#include "CRows.h"
#include <string>
#include <vector>

using namespace std;

class CMyPPT
{
public:
	CMyPPT();
	~CMyPPT();

	//�½�PPT
	bool CreateNewPPT();

	//�½�ģ��PPT
	bool CreatePPTofTemplate(string inTemplateFileName);

	//��PPT
	bool OpenPPT(string inFileName, bool isVisible = true, bool isOnlyReadbool = false);

	//����PPT	�Ƿ�ȫ����isFullScreen
	bool PlayPPT(bool isFullScreen);
	
	//���ҳPPT	λ�ã�inIndex	��ʽ��inLayout
	bool AddSlide(int inIndex, int inLayout = 1);

	//ɾ��ҳPPT
	bool DeleteSlide(int inIndex);

	//�����ı���
	CTextFrame InsertTextBox(int inIndex, string inTextString, float inLeft, float inTop, float inWidth = 1000.0, float inHeight = 1000.0);

	//�ı��ı��������
	bool ChangeTextBox(int inIndex, string inBoxName, string inTextString);

	//��ȡ�����������
	bool ReadTablePPT(int inIndex, string inTableName, int inRow, int inColumn, std::vector<std::vector<std::string>> &outTableInfor);

	//��ȡ���ָ����Ԫ����
	string ReadTablePPT(int inIndex, string inTableName, int inRow, int inColumn);

	//������PPT
	CTable0 InsertTablePPT(int inIndex, int inRow, int inColumn, float inLeft, float inTop, float inWidth = 150.0, float inHeight = 20.0);
	
	//�ı���ָ����Ԫ����
	bool ChangeCellColor(int inIndex, string inTableName, int inRow, int inColumn, string inRGBY);

	//�ı���ָ����Ԫ��������ɫ
	bool ChangeCellTextColor(int inIndex, string inTableName, int inRow, int inColumn, string inRGBY);

	//����д����Ԫ
	bool WriteStringToTable(int inIndex, string inTableName, int inRow, int inColumn, string inString);

	//������һ��
	bool AddRowToTable(int inIndex, string inTableName, int inRow = -1);

	//������һ��
	bool AddColumnToTable(int inIndex, string inTableName, int inColumn = -1);

	//����ͼƬPPT
	CShape InsertPicture(int inIndex, string inPicturePath, float inLeft, float inTop, float inWidth = 400.0, float inHeight = 300.0);

	//�滻ͼƬPPT
	CShape ReplacePicture(int inIndex, string inOldPicturePath, string inNewPicturePath);
	CShape ReplacePicture(int inIndex, CShape inShape, string inNewPicturePath);

	//ɾ��ָ����Shape
	bool DeleteShape(int inIndex, string inShapeName);

	//����PPT
	bool SavePPT();

	//���PPT
	bool SaveAsPPT(string inFullName);

	//�ر�PPT
	bool ClosePPT();

	//�ر�PPT(ֱ�ӹرգ�������)
	bool KillPPT();

private:
	CApplication		m_PPTApp;
	CSlides				m_Slides;
	CSlide				m_curSlide;
	CPresentation		m_Presentaion;
	CPresentations		m_Presentaions;
	CSlideShowSettings	m_slideshow;

	string m_filename;
	bool m_isvisible;
	int m_slidesnum;

	//��ʼ��
	bool InitPPT();

};

