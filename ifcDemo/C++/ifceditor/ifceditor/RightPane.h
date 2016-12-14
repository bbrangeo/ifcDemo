#pragma once


struct	STRUCT_INSTANCE
{
#ifdef WIN64
	__int64			ifcEntity;
	__int64			ifcInstance;
#else
	__int32			ifcEntity;
	__int32			ifcInstance;
#endif
	HTREEITEM		hItem;

	wchar_t			* attributeName;
#ifdef WIN64
	__int64			attributeType;
#else
	__int32			attributeType;
#endif

	bool			expanded;
};

// CRightPane form view

class CRightPane : public CTreeView
{
	DECLARE_DYNCREATE(CRightPane)

protected:
	CRightPane();           // protected constructor used by dynamic creation
	virtual ~CRightPane();

public:
	enum { IDD = IDD_RIGHTPANE };

protected:
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void	OnInitialUpdate();
#ifdef WIN64
	virtual void	InsertItemInstanceEntity(__int64 ifcEntity, HTREEITEM hParent);
	virtual void	InsertItemInstanceAttribute(__int64 ifcInstance, wchar_t * attributeName, __int64 attributeType, HTREEITEM hParent);
	virtual __int64	InsertItemAttributes(__int64 ifcEntity, __int64 ifcInstance, HTREEITEM hParent);
	virtual void	InsertItemReferences(__int64 ifcInstance, wchar_t * attributeName, __int64 attributeType, HTREEITEM hParent);
	virtual void	InsertItemInstance(__int64 ifcInstance, HTREEITEM hParent);
	virtual void	SelectedEntity(__int64 ifcEntity);
#else
	virtual void	InsertItemInstanceEntity(__int32 ifcEntity, HTREEITEM hParent);
	virtual void	InsertItemInstanceAttribute(__int32 ifcInstance, wchar_t * attributeName, __int32 attributeType, HTREEITEM hParent);
	virtual __int32	InsertItemAttributes(__int32 ifcEntity, __int32 ifcInstance, HTREEITEM hParent);
	virtual void	InsertItemReferences(__int32 ifcInstance, wchar_t * attributeName, __int32 attributeType, HTREEITEM hParent);
	virtual void	InsertItemInstance(__int32 ifcInstance, HTREEITEM hParent);
	virtual void	SelectedEntity(__int32 ifcEntity);
#endif

#ifdef WIN64
	virtual void	GetAttributeReferencesADB(__int64 ADB, HTREEITEM hParent);
	virtual void	GetAttributeReferencesAGGR(__int64 * aggregate, __int64 elementIndex, HTREEITEM hParent);
	virtual void	GetAttributeReferences(__int64 ifcInstance, wchar_t * attributeName, __int64 attributeType, HTREEITEM hParent);
#else
	virtual void	GetAttributeReferencesADB(__int32 ADB, HTREEITEM hParent);
	virtual void	GetAttributeReferencesAGGR(__int32 * aggregate, __int32 elementIndex, HTREEITEM hParent);
	virtual void	GetAttributeReferences(__int32 ifcInstance, wchar_t * attributeName, __int32 attributeType, HTREEITEM hParent);
#endif

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
};


