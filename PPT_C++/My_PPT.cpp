#include "stdafx.h"
#include "My_PPT.h"
#include <io.h>
using namespace std;

//�ı������ʽ
enum MyEnum1
{
	msoTextOrientationHorizontal = 1,			//ˮƽ
	msoTextOrientationUpward,					//����
	msoTextOrientationDownward,					//����
	msoTextOrientationVerticalFarEast ,			//��������֧������Ĵ�ֱ
	msoTextOrientationVertical,					//��ֱ
	msoTextOrientationHorizontalRotatedFarEast	//��������֧�������ˮƽ����ת
};

//�½��õ�Ƭ�İ�ʽ
enum MyEnum2
{
	ppLayoutTitle = 1,							//����õ�Ƭ
	ppLayoutText = 2,							//���� + �ı�
	ppLayoutTwoColumnText = 3,					//���� + ����
	ppLayoutTable = 4,							//���� + ���
	ppLayoutTextAndChart = 5,					//���� + �ı� + ͼ��
	ppLayoutChartAndText = 6,					//���� + ͼ�� + �ı�
	ppLayoutOrgchart = 7,						//���� + �ṹͼ
	ppLayoutChart = 8,							//���� + ͼ��
	ppLayoutTextAndClipart = 9,					//���� + �ı� + ͼƬ
	ppLayoutClipartAndText = 10,
	ppLayoutTitleOnly = 11,
	ppLayoutBlank = 12,
	ppLayoutTextAndObject = 13,
	ppLayoutObjectAndText = 14,
	ppLayoutLargeObject = 15,
	ppLayoutObject = 16,
	ppLayoutTextAndMediaClip = 17,
	ppLayoutMediaClipAndText = 18,
	ppLayoutObjectOverText = 19,
	ppLayoutTextOverObject = 20,
	ppLayoutTextAndTwoObjects = 21,
	ppLayoutTwoObjectsAndText = 22,
	ppLayoutTwoObjectsOverText = 23,
	ppLayoutFourObjects = 24,
	ppLayoutVerticalText = 25,
	ppLayoutClipArtAndVerticalText = 26,
	ppLayoutVerticalTitleAndText = 27,
	ppLayoutVerticalTitleAndTextOverChart = 28,
	ppLayoutTwoObjects = 29,
	ppLayoutObjectAndTwoObjects = 30,
	ppLayoutTwoObjectsAndObject = 31,
	ppLayoutCustom = 32,
	ppLayoutSectionHeader = 33,
	ppLayoutComparison = 34,
	ppLayoutContentWithCaption = 35,
	ppLayoutPictureWithCaption = 36,
};

CMyPPT::CMyPPT()
{
	m_PPTApp = NULL;
	m_Slides = NULL;
	m_curSlide = NULL;
	m_Presentaion = NULL;
	m_Presentaions = NULL;
	m_slideshow = NULL;
	m_filename = "";
	m_isvisible = false;
}

CMyPPT::~CMyPPT()
{
	m_PPTApp = NULL;
	m_Slides = NULL;
	m_curSlide = NULL;
	m_Presentaion = NULL;
	m_Presentaions = NULL;
	m_slideshow = NULL;
	m_filename = "";
	m_isvisible = false;
}

bool CMyPPT::CreateNewPPT()
{
	if (m_PPTApp == NULL)
	{
		if (CMyPPT::InitPPT())
		{
			m_Presentaions.AttachDispatch(m_PPTApp.get_Presentations());
			m_Presentaion = m_Presentaions.Add(true);
			return true;
		}
	}
	return false;
}

bool CMyPPT::CreatePPTofTemplate(string inTemplateFileName)
{
	if (m_PPTApp == NULL)
	{
		if (CMyPPT::InitPPT())
		{
			//�ж��ļ��Ƿ����
			if (_access(inTemplateFileName.c_str(), 0) == -1)
			{
				m_PPTApp.Quit();
				m_PPTApp = NULL;
				MessageBoxA(NULL, "ָ��ģ���ļ�������!", "��ʾ", MB_ICONEXCLAMATION);
				return false;
			}
			//�ж��ļ��Ƿ���д��Ȩ��
			if (_access(inTemplateFileName.c_str(), 2) == -1)
			{
				m_PPTApp.Quit();
				m_PPTApp = NULL;
				MessageBoxA(NULL, "ָ��ģ���ļ�û��д��Ȩ��!", "��ʾ", MB_ICONEXCLAMATION);
				return false;
			}
			m_Presentaions.AttachDispatch(m_PPTApp.get_Presentations());
			m_Presentaion = m_Presentaions.Open(inTemplateFileName.c_str(), false, false, true);
			m_Slides = m_Presentaion.get_Slides();//�õ����лõ�Ƭ
			m_curSlide = m_Slides.Item(COleVariant((long)1));//��ǰ�õ�Ƭҳ
			m_slideshow = m_Presentaion.get_SlideShowSettings();
			this->m_slidesnum = m_Slides.get_Count();
			return true;
		}
	}
	return false;
}

bool CMyPPT::InitPPT()
{	
	COleException exception;
	LPCSTR str = "Powerpoint.Application";
	if (!m_PPTApp.CreateDispatch(str, &exception))
	{
		AfxMessageBox(exception.m_sc, MB_SETFOREGROUND);
		return false;
	}
	//m_PPTApp.put_Visible(true);
	return true;
}

bool CMyPPT::OpenPPT(string inFileName, bool isVisible, bool isOnlyRead)
{
	if (m_PPTApp == NULL)
	{	
		if (CMyPPT::InitPPT())
		{
			//�ж��ļ��Ƿ����
			if (_access(inFileName.c_str(), 0) == -1)
			{
				m_PPTApp.Quit();
				m_PPTApp = NULL;
				MessageBoxA(NULL, "ָ���򿪵��ļ�������!", "��ʾ", MB_ICONEXCLAMATION);
				return false;
			}
			//�ж��ļ��Ƿ���д��Ȩ��
			if (_access(inFileName.c_str(), 2) == -1)
			{
				m_PPTApp.Quit();
				m_PPTApp = NULL;
				MessageBoxA(NULL, "ָ���򿪵��ļ�û��д��Ȩ��!", "��ʾ", MB_ICONEXCLAMATION);
				return false;
			}

			this->m_filename = inFileName;
			this->m_isvisible = isVisible;

			m_Presentaions.AttachDispatch(m_PPTApp.get_Presentations());
			m_Presentaion.AttachDispatch(m_Presentaions.Open(CString(inFileName.c_str()), isOnlyRead, 0, isVisible));
			m_Slides = m_Presentaion.get_Slides();//�õ����лõ�Ƭ
			m_curSlide = m_Slides.Item(COleVariant((long)1));//��ǰ�õ�Ƭҳ
			m_slideshow = m_Presentaion.get_SlideShowSettings();
			this->m_slidesnum = m_Slides.get_Count();
			return true;
		}
	}
	return false;
}

bool CMyPPT::PlayPPT(bool isFullScreen)
{
	if (m_slideshow != NULL)
	{
		m_slideshow.put_AdvanceMode(2);
		m_slideshow.put_LoopUntilStopped(TRUE); //����ѭ����ӳ
		if (isFullScreen)
		{
			m_slideshow.put_ShowType(1);//1 ȫ��PPT��ӳ
		}
		else
		{
			m_slideshow.put_ShowType(0);//0 ԭʼPPT��С
		}
		m_slideshow.Run();
		return true;
	}
	return false;
}

bool CMyPPT::AddSlide(int inIndex, int inLayout)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Add(inIndex, long(inLayout));
			return true;
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ������ֵ�����õ�Ƭ�ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

bool CMyPPT::DeleteSlide(int inIndex)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));//��ǰ�õ�Ƭҳ
			m_curSlide.Delete();
			return true;
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ������ֵ�����õ�Ƭ�ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

CTextFrame CMyPPT::InsertTextBox(int inIndex, string inTextString, float inLeft, float inTop, float inWidth, float inHeight)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			CShape curShape = Shapes.AddTextbox(msoTextOrientationHorizontal, inLeft, inTop, inWidth, inHeight);
			CTextFrame textFrame = curShape.get_TextFrame();
			CTextRange textRange = textFrame.get_TextRange();
			textRange.put_Text(inTextString.c_str());
			return textFrame;
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return NULL;
}

bool CMyPPT::ChangeTextBox(int inIndex, string inBoxName, string inTextString)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape = Shapes.Item(COleVariant(i));
				CString name = shape.get_Name();
				if (name.Compare(CString(inBoxName.c_str())) == 0)
				{
					CTextFrame textFrame = shape.get_TextFrame();
					CTextRange textRange = textFrame.get_TextRange();
					CString txt = textRange.get_Text();
					textRange.put_Text(inTextString.c_str());
					return true;
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

bool CMyPPT::ReadTablePPT(int inIndex, string inTableName, int inRow, int inColumn, std::vector<std::vector<string>> &outTableInfor)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape1 = Shapes.Item(COleVariant(i));
				CString name = shape1.get_Name();
				if (name.Compare(CString(inTableName.c_str())) == 0)
				{
					CTable0 table = shape1.get_Table();
					for (int j = 1; j <= inRow; j++)
					{
						std::vector<string> columns_string = {};
						for (int k = 1; k <= inColumn; k++)
						{
							CCell cell = table.Cell(j, k);
							CShape shape2 = cell.get_Shape();
							CTextFrame textFrame = shape2.get_TextFrame();
							CTextRange textRange = textFrame.get_TextRange();
							CString txt = textRange.get_Text();
							
							columns_string.push_back(txt.GetString());
						}
						outTableInfor.push_back(columns_string);
					}
					return true;
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

string CMyPPT::ReadTablePPT(int inIndex, string inTableName, int inRow, int inColumn)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape1 = Shapes.Item(COleVariant(i));
				CString name = shape1.get_Name();
				if (name.Compare(CString(inTableName.c_str())) == 0)
				{
					CTable0 table = shape1.get_Table();
					CCell cell = table.Cell(inRow, inColumn);
					CShape shape2 = cell.get_Shape();
					CTextFrame textFrame = shape2.get_TextFrame();
					CTextRange textRange = textFrame.get_TextRange();
					CString txt = textRange.get_Text();
					return txt.GetString();
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return "";
}

CTable0 CMyPPT::InsertTablePPT(int inIndex, int inRow, int inColumn, float inLeft, float inTop, float inWidth /*= 150.0*/, float inHeight /*= 15.0*/)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			CTable0 table = Shapes.AddTable(inRow, inColumn, inLeft, inTop, inWidth, inHeight);
			return table;
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return NULL;
}

bool CMyPPT::ChangeCellColor(int inIndex, string inTableName, int inRow, int inColumn, string inRGBY)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape1 = Shapes.Item(COleVariant(i));
				CString name = shape1.get_Name();
				if (name.Compare(CString(inTableName.c_str())) == 0)
				{
					CTable0 table = shape1.get_Table();
					CCell cell = table.Cell(inRow, inColumn);
					CShape shape2 = cell.get_Shape();
					CFillFormat fillformat = shape2.get_Fill();
					CColorFormat color = fillformat.get_ForeColor();
					long rgbID;
					if (inRGBY == "R" || inRGBY == "r")
					{
						rgbID = long(65536 * 0 + 256 * 0 + 255);//red
					}
					else if (inRGBY == "G" || inRGBY == "g")
					{
						rgbID = long(65536 * 0 + 256 * 255 + 0);//green
					}
					else if (inRGBY == "B" || inRGBY == "b")
					{
						rgbID = long(65536 * 255 + 256 * 0 + 0);//blue
					}
					else if (inRGBY == "Y" || inRGBY == "y")
					{
						rgbID = long(65536 * 0 + 256 * 255 + 255);//yellow
					}
					color.put_RGB(rgbID);
					return true;
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

bool CMyPPT::ChangeCellTextColor(int inIndex, string inTableName, int inRow, int inColumn, string inRGBY)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape1 = Shapes.Item(COleVariant(i));
				CString name = shape1.get_Name();
				if (name.Compare(CString(inTableName.c_str())) == 0)
				{
					CTable0 table = shape1.get_Table();
					CCell cell = table.Cell(inRow, inColumn);
					CShape shape2 = cell.get_Shape();
					CTextFrame textFrame = shape2.get_TextFrame();
					CTextRange textRange = textFrame.get_TextRange();
					CFont0 font = textRange.get_Font();
					CColorFormat color = font.get_Color();
					long rgbID;
					if (inRGBY == "R" || inRGBY == "r")
					{
						rgbID = long(65536 * 0 + 256 * 0 + 255);//red
					}
					else if (inRGBY == "G" || inRGBY == "g")
					{
						rgbID = long(65536 * 0 + 256 * 255 + 0);//green
					}
					else if (inRGBY == "B" || inRGBY == "b")
					{
						rgbID = long(65536 * 255 + 256 * 0 + 0);//blue
					}
					else if (inRGBY == "Y" || inRGBY == "y")
					{
						rgbID = long(65536 * 0 + 256 * 255 + 255);//yellow
					}
					color.put_RGB(rgbID);
					return true;
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

bool CMyPPT::WriteStringToTable(int inIndex, string inTableName, int inRow, int inColumn, string inString)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape = Shapes.Item(COleVariant(i));
				CString name = shape.get_Name();
				if (name.Compare(CString(inTableName.c_str())) == 0)
				{
					CTable0 table = shape.get_Table();
					CCell cell = table.Cell(inRow, inColumn);
					CShape shape2 = cell.get_Shape();
					CTextFrame textFrame = shape2.get_TextFrame();
					CTextRange textRange = textFrame.get_TextRange();
					textRange.put_Text(inString.c_str());
					return true;
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

bool CMyPPT::AddRowToTable(int inIndex, string inTableName, int inRow /*= -1*/)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape = Shapes.Item(COleVariant(i));
				CString name = shape.get_Name();
				if (name.Compare(CString(inTableName.c_str())) == 0)
				{
					CTable0 table = shape.get_Table();
					CRows rows = table.get_Rows();
					if (inRow <= rows.get_Count())
					{
						rows.Add(inRow);
						return true;
					}
					else
					{
						MessageBoxA(NULL, "ָ�����кų����˱�������к�", "��ʾ", MB_ICONEXCLAMATION);
						return false;
					}
					
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

bool CMyPPT::AddColumnToTable(int inIndex, string inTableName, int inColumn /*= -1*/)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape = Shapes.Item(COleVariant(i));
				CString name = shape.get_Name();
				if (name.Compare(CString(inTableName.c_str())) == 0)
				{
					CTable0 table = shape.get_Table();
					CColumns0 colunms = table.get_Columns();
					if (inColumn <= colunms.get_Count())
					{
						colunms.Add(inColumn);
						return true;
					}
					else
					{
						MessageBoxA(NULL, "ָ�����кų����˱�������к�", "��ʾ", MB_ICONEXCLAMATION);
						return false;
					}

				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

CShape CMyPPT::InsertPicture(int inIndex, string inPicturePath, float inLeft, float inTop, float inWidth /*= 150.0*/, float inHeight /*= 20.0*/)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			CShape picture = Shapes.AddPicture2(inPicturePath.c_str(), true, true, inLeft, inTop, inWidth, inHeight, false);
			return picture;
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return NULL;
}

CShape CMyPPT::ReplacePicture(int inIndex, string inPictureName, string inNewPicturePath)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape1 = Shapes.Item(COleVariant(i));
				CString name = shape1.get_Name();
				if (name.Compare(CString(inPictureName.c_str())) == 0)
				{
					CShape picture = Shapes.AddPicture2(inNewPicturePath.c_str(), true, true, shape1.get_Left(), shape1.get_Top(), shape1.get_Width(), shape1.get_Height(), false);
					shape1.Delete();
					return picture;
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return NULL;
}

CShape CMyPPT::ReplacePicture(int inIndex, CShape inShape, string inNewPicturePath)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			CShape picture = Shapes.AddPicture2(inNewPicturePath.c_str(), true, true, inShape.get_Left(), inShape.get_Top(), inShape.get_Width(), inShape.get_Height(), false);
			inShape.Delete();
			return picture;
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return NULL;
}

bool CMyPPT::DeleteShape(int inIndex, string inShapeName)
{
	if (m_Slides != NULL)
	{
		if (inIndex > 0 && inIndex < m_slidesnum + 2)
		{
			m_curSlide = m_Slides.Item(COleVariant((long)inIndex));
			CShapes Shapes = m_curSlide.get_Shapes();
			for (long i = 1; i <= Shapes.get_Count(); ++i)
			{
				CShape shape1 = Shapes.Item(COleVariant(i));
				CString name = shape1.get_Name();
				if (name.Compare(CString(inShapeName.c_str())) == 0)
				{
					shape1.Delete();
					return true;
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "�õ�Ƭ����ֵ�����ķ�Χ!", "��ʾ", MB_ICONEXCLAMATION);
		}
	}
	return false;
}

bool CMyPPT::SavePPT()
{
	try
	{
		m_Presentaion.Save();
		return true;
	}
	catch (exception)
	{
		MessageBoxA(NULL, "����PPTʧ��!", "��ʾ", MB_ICONEXCLAMATION);
		return false;
	}

}

bool CMyPPT::SaveAsPPT(string inFullName)
{
	try
	{
		m_Presentaion.SaveAs(inFullName.c_str(), 11, false);//https://docs.microsoft.com/zh-cn/office/vba/api/PowerPoint.PpSaveAsFileType
		return true;
	}
	catch (exception)
	{
		MessageBoxA(NULL, "���PPTʧ��!", "��ʾ", MB_ICONEXCLAMATION);
		return false;
	}
}

bool CMyPPT::ClosePPT()
{
	try
	{
		m_Presentaion.Close();
		m_PPTApp.Quit();
		m_PPTApp = NULL;
		m_Slides = NULL;
		m_curSlide = NULL;
		m_Presentaion = NULL;
		m_Presentaions = NULL;
		m_slideshow = NULL;
		m_filename = "";
		m_isvisible = false;
		return true;
	}
	catch (exception)
	{
		MessageBoxA(NULL, "�ر�PPTʧ��!", "��ʾ", MB_ICONEXCLAMATION);
		m_PPTApp = NULL;
		m_Slides = NULL;
		m_curSlide = NULL;
		m_Presentaion = NULL;
		m_Presentaions = NULL;
		m_slideshow = NULL;
		m_filename = "";
		m_isvisible = false;
		return false;
	}
}

bool CMyPPT::KillPPT()
{
	try
	{
		m_Presentaion.Close();
		m_PPTApp.Quit();
		m_PPTApp = NULL;
		m_Slides = NULL;
		m_curSlide = NULL;
		m_Presentaion = NULL;
		m_Presentaions = NULL;
		m_slideshow = NULL;
		m_filename = "";
		m_isvisible = false;
		return true;
	}
	catch (exception)
	{
		MessageBoxA(NULL, "�ر�PPTʧ��!", "��ʾ", MB_ICONEXCLAMATION);
		m_PPTApp = NULL;
		m_Slides = NULL;
		m_curSlide = NULL;
		m_Presentaion = NULL;
		m_Presentaions = NULL;
		m_slideshow = NULL;
		m_filename = "";
		m_isvisible = false;
		return false;
	}
}


