// LeftPane.cpp : implementation file
//

#include "stdafx.h"
#include "ifceditor.h"
#include "LeftPane.h"

#include "ifcengine\include\ifcengine.h"


#ifdef WIN64
__int64	model = 0;
#else
__int32	model = 0;
#endif


// CLeftPane

IMPLEMENT_DYNCREATE(CLeftPane, CTreeView)

CLeftPane::CLeftPane()
	: CTreeView()
{

}

CLeftPane::~CLeftPane()
{
}

void CLeftPane::DoDataExchange(CDataExchange* pDX)
{
	CTreeView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLeftPane, CTreeView)
	ON_NOTIFY_REFLECT(NM_CLICK, &CLeftPane::OnNMClick)
END_MESSAGE_MAP()



// CLeftPane message handlers


#ifdef WIN64
STRUCT_ENTITY	* new_STRUCT_ENTITY(__int64 ifcEntity)
#else
STRUCT_ENTITY	* new_STRUCT_ENTITY(__int32 ifcEntity)
#endif
{
	STRUCT_ENTITY	* entity = new STRUCT_ENTITY;

	entity->ifcEntity = ifcEntity;
	entity->hTreeItem = 0;
	entity->hTreeItemSubTypes = 0;
	entity->hTreeItemAttributes = 0;

	entity->attributeCnt = 0;
	entity->instanceCnt = 0;

	entity->parent = 0;
	entity->child = 0;
	entity->next = 0;

	return	entity;
}

#ifdef WIN64
__int64	NestedInstanceCnt(STRUCT_ENTITY * entity)
#else
__int32	NestedInstanceCnt(STRUCT_ENTITY * entity)
#endif
{
#ifdef WIN64
	__int64			instanceCnt = entity->instanceCnt;
#else
	__int32			instanceCnt = entity->instanceCnt;
#endif
	STRUCT_ENTITY	* child = entity->child;
	while  (child) {
		instanceCnt += NestedInstanceCnt(child);
		child = child->next;
	}
	return	instanceCnt;
}

void	CreateEntityName(STRUCT_ENTITY * entity, wchar_t * buffer)
{
	wchar_t	* entityName = 0;
	engiGetEntityName(entity->ifcEntity, sdaiUNICODE, (char**) &entityName);

	size_t	index = wcslen(entityName);
	memcpy(&buffer[0], entityName, wcslen(entityName) * sizeof(wchar_t));

#ifdef WIN64
	__int64	instanceCnt = NestedInstanceCnt(entity);
#else
	__int32	instanceCnt = NestedInstanceCnt(entity);
#endif
	if	(instanceCnt) {
		buffer[index++] = ' ';
		buffer[index++] = ' ';
#ifdef WIN64
		_i64tow_s(entity->instanceCnt, &buffer[index], 33, 10);
#else
		_itow_s(entity->instanceCnt, &buffer[index], 33, 10);
#endif
		index += wcslen(&buffer[index]);
		if	(entity->child) {
			buffer[index++] = ' ';
			buffer[index++] = '/';
			buffer[index++] = ' ';
#ifdef WIN64
			_i64tow_s(instanceCnt, &buffer[index], 33, 10);
#else
			_itow_s(instanceCnt, &buffer[index], 33, 10);
#endif
			index += wcslen(&buffer[index]);
		}
	}
	buffer[index] = 0;
}

#ifdef WIN64
void CLeftPane::InsertItemAttribute(STRUCT_ENTITY * entity, __int64 index)
#else
void CLeftPane::InsertItemAttribute(STRUCT_ENTITY * entity, __int32 index)
#endif
{
	wchar_t	* argumentName = 0;
	engiGetEntityArgumentName(entity->ifcEntity, index, sdaiUNICODE, (char**) &argumentName);

	TV_INSERTSTRUCT		tvstruct;
	tvstruct.hParent = entity->hTreeItemAttributes;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
	tvstruct.item.cChildren = 0;
	tvstruct.item.pszText = argumentName;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.lParam = (LPARAM) 0;

	GetTreeCtrl().InsertItem(&tvstruct);
}

void CLeftPane::InsertItemAttributes(STRUCT_ENTITY * entity)
{
	TV_INSERTSTRUCT		tvstruct;
	tvstruct.hParent = entity->hTreeItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
	tvstruct.item.cChildren = 1;
	tvstruct.item.pszText = L"attributes";
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.lParam = (LPARAM) 0;

	entity->hTreeItemAttributes = GetTreeCtrl().InsertItem(&tvstruct);

#ifdef WIN64
	__int64	noArguments, i = 0;
#else
	__int32	noArguments, i = 0;
#endif
	noArguments = engiGetEntityNoArguments(entity->ifcEntity);
	if	(entity->parent) {
		i = entity->parent->attributeCnt;
	}
	while  (i < noArguments) {
		InsertItemAttribute(entity, i);
		i++;
	}
}

void CLeftPane::InsertItemSubTypes(STRUCT_ENTITY * entity)
{
	TV_INSERTSTRUCT		tvstruct;
	tvstruct.hParent = entity->hTreeItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
	tvstruct.item.cChildren = 1;
	tvstruct.item.pszText = L"sub types";
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.lParam = (LPARAM) 0;

	entity->hTreeItemSubTypes = GetTreeCtrl().InsertItem(&tvstruct);

	STRUCT_ENTITY	* childEntity = entity->child;
	while  (childEntity) {
		InsertItemEntity(childEntity);
		childEntity = childEntity->next;
	}
}

void CLeftPane::InsertItemEntity(STRUCT_ENTITY * entity)
{
	wchar_t	buffer[512];
	CreateEntityName(entity, buffer);

	TV_INSERTSTRUCT		tvstruct;
	if	(entity->parent) {
		tvstruct.hParent = entity->parent->hTreeItemSubTypes;
	} else {
		tvstruct.hParent = 0;
	}
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
	if	(entity->child  ||  (entity->attributeCnt  &&  (entity->parent == 0  ||  entity->parent->attributeCnt < entity->attributeCnt))) {
		tvstruct.item.cChildren = 1;
	} else {
		tvstruct.item.cChildren = 0;
	}
	tvstruct.item.pszText = buffer;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.lParam = (LPARAM) entity;

	entity->hTreeItem = GetTreeCtrl().InsertItem(&tvstruct);

	if	(entity->child) {
		InsertItemSubTypes(entity);
	}

	if	(entity->attributeCnt  &&  (entity->parent == 0  ||  entity->parent->attributeCnt < entity->attributeCnt)) {
		InsertItemAttributes(entity);
	}
}

void CLeftPane::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CImageList* pImageList = new CImageList();
	pImageList->Create(16, 16, ILC_COLOR4, 0, 0);//6, 6);

	CBitmap bitmap;

/*	bitmap.LoadBitmap(IDB_SELECTED_ALL);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	bitmap.LoadBitmap(IDB_SELECTED_PART);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	bitmap.LoadBitmap(IDB_SELECTED_NONE);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	bitmap.LoadBitmap(IDB_PROPERTY_SET);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	bitmap.LoadBitmap(IDB_PROPERTY);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	bitmap.LoadBitmap(IDB_NONE);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();
//	*/

	CTreeCtrl *tst = &GetTreeCtrl();

	::SetWindowLong(*tst, GWL_STYLE, TVS_EDITLABELS|TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|TVS_INFOTIP|::GetWindowLong(*tst, GWL_STYLE));

	GetTreeCtrl().SetImageList(pImageList, TVSIL_NORMAL);
	GetTreeCtrl().DeleteAllItems();

	if	(model) {
#ifdef WIN64
		__int64	cnt, i = 0;
#else
		__int32	cnt, i = 0;
#endif
		cnt = engiGetEntityCount(model);
		STRUCT_ENTITY	** entities = (STRUCT_ENTITY **) new size_t[cnt];

		while  (i < cnt) {
			entities[i] = new_STRUCT_ENTITY(engiGetEntityElement(model, i));
			entities[i]->attributeCnt = engiGetEntityNoArguments(entities[i]->ifcEntity);
			entities[i]->instanceCnt = sdaiGetMemberCount(sdaiGetEntityExtent(model, entities[i]->ifcEntity));
			i++;
		}

		while  (i) {
			i--;
#ifdef	WIN64
			__int64	ifcParentEntity;
#else
			__int32	ifcParentEntity;
#endif
			ifcParentEntity = engiGetEntityParent(entities[i]->ifcEntity);
			if	(ifcParentEntity) {
				int	j = 0;
				while  (j < cnt) {
					if	(ifcParentEntity == entities[j]->ifcEntity) {
						if	(entities[j]->child) {
							entities[i]->next = entities[j]->child;
						}
						entities[j]->child = entities[i];
						entities[i]->parent = entities[j];
					}
					j++;
				}
			}
		}

		while  (i < cnt) {
			if	(entities[i]->parent == 0) {
				InsertItemEntity(entities[i]);
			}
			i++;
		}
	}
}


void CLeftPane::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	DWORD		pos = GetMessagePos();
	CPoint		pt(LOWORD(pos), HIWORD(pos));
	GetTreeCtrl().ScreenToClient(&pt);

	HTREEITEM	hItem = GetTreeCtrl().GetFirstVisibleItem();

	while  (hItem) {
		CRect r;
		GetTreeCtrl().GetItemRect(hItem, &r, true);

		if	(r.PtInRect(pt)) {
			STRUCT_ENTITY	* entity = (STRUCT_ENTITY *) GetTreeCtrl().GetItemData(hItem);
			if	(entity) {
				this->GetWindow(GW_HWNDNEXT)->SendMessage(ID_UPDATE_RIGHT_VIEW, 0, (LPARAM) entity->ifcEntity);
			}
		}
		hItem = GetTreeCtrl().GetNextVisibleItem(hItem);
	}

	*pResult = 0;
}
