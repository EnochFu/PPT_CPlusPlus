// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

//#import "D:\\Office2013\\Office15\\MSPPT.OLB" no_namespace
// CCell ��װ����

class CCell : public COleDispatchDriver
{
public:
	CCell(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CCell(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCell(const CCell& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// Cell ����
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x7d1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x7d2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Shape()
	{
		LPDISPATCH result;
		InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Borders()
	{
		LPDISPATCH result;
		InvokeHelper(0x7d4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Merge(LPDISPATCH MergeTo)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x7d5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MergeTo);
	}
	void Split(long NumRows, long NumColumns)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x7d6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NumRows, NumColumns);
	}
	void Select()
	{
		InvokeHelper(0x7d7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_Selected()
	{
		BOOL result;
		InvokeHelper(0x7d8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}

	// Cell ����
public:

};
