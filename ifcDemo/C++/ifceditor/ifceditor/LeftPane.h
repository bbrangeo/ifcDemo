#pragma once


struct	STRUCT_ENTITY
{
#ifdef WIN64
	__int64				ifcEntity;
#else
	__int32				ifcEntity;
#endif
	HTREEITEM			hTreeItem;
	HTREEITEM			hTreeItemSubTypes;
	HTREEITEM			hTreeItemAttributes;

#ifdef WIN64
	__int64				attributeCnt;
	__int64				instanceCnt;
#else
	__int32				attributeCnt;
	__int32				instanceCnt;
#endif

	STRUCT_ENTITY		* parent;
	STRUCT_ENTITY		* child;
	STRUCT_ENTITY		* next;
};


// CLeftPane form view

class CLeftPane : public CTreeView
{
	DECLARE_DYNCREATE(CLeftPane)

protected:
	CLeftPane();           // protected constructor used by dynamic creation
	virtual ~CLeftPane();

public:
	enum { IDD = IDD_LEFTPANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void InsertItemSubTypes(STRUCT_ENTITY * entity);
#ifdef WIN64
	virtual void InsertItemAttribute(STRUCT_ENTITY * entity, __int64 index);
#else
	virtual void InsertItemAttribute(STRUCT_ENTITY * entity, __int32 index);
#endif
	virtual void InsertItemAttributes(STRUCT_ENTITY * entity);
	virtual void InsertItemEntity(STRUCT_ENTITY * entity);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


