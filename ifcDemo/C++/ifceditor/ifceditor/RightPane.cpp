// RightPane.cpp : implementation file
//

#include "stdafx.h"
#include "ifceditor.h"
#include "RightPane.h"

#include "ifcengine\include\engine.h"
#include "ifcengine\include\ifcengine.h"


#ifdef WIN64
extern	__int64	model;
#else
extern	__int32	model;
#endif


// CRightPane

IMPLEMENT_DYNCREATE(CRightPane, CTreeView)

CRightPane::CRightPane()
	: CTreeView()
{

}

CRightPane::~CRightPane()
{
}

void CRightPane::DoDataExchange(CDataExchange* pDX)
{
	CTreeView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRightPane, CTreeView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, &CRightPane::OnTvnItemexpanding)
	ON_NOTIFY_REFLECT(NM_CLICK, &CRightPane::OnNMClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CRightPane::OnNMRClick)
END_MESSAGE_MAP()



// CRightPane message handlers


void	_ecvt(double value, wchar_t * buffer)
{
	int			dec = 0, sign = 0, i = 0, j = 0;
//	const char	*p = _ecvt_s(value, 7, &dec, &sign);
	char	p[512];
	_ecvt_s(p, 512, value, 7, &dec, &sign);
	if	(sign) {
		buffer[j++] = '-';
	}
	if	(dec == 0) {
		buffer[j++] = '0';
	}
	bool	dot = false;
	if	(dec > -4  &&  dec < 0) {
		buffer[j++] = '0';
		buffer[j++] = '.';
		dot = true;
		while  (dec) {
			buffer[j++] = '0';
			dec++;
		}
		dec--;
	}
	while  (p[i]) {
		if	(dec == i) {
			buffer[j++] = '.';
			dot = true;
		}
		buffer[j++] = p[i++];
	}
	if	(dot == false) {
		j = 0;
		buffer[j++] = p[0];
		buffer[j++] = '.';
		while  (p[j-1]) {
			buffer[j] = p[j-1];
			j++;
		}
		buffer[j++] = 'e';
		_itow_s(dec, &buffer[j], 33, 10);
	}
	buffer[j] = 0;
}

#ifdef WIN64
STRUCT_INSTANCE	* new_STRUCT_INSTANCE(__int64 ifcInstance)
#else
STRUCT_INSTANCE	* new_STRUCT_INSTANCE(__int32 ifcInstance)
#endif
{
	STRUCT_INSTANCE	* instance = new STRUCT_INSTANCE;

	instance->ifcInstance = ifcInstance;
	instance->hItem = 0;
	instance->expanded = false;

	instance->attributeName = 0;
	instance->attributeType = 0;

	return	instance;
}

#ifdef WIN64
void	CreateInstanceName(__int64 instance, wchar_t * buffer)
#else
void	CreateInstanceName(__int32 instance, wchar_t * buffer)
#endif
{
	size_t	index = 0;
	buffer[index++] = '#';
#ifdef WIN64
	_i64tow_s(internalGetP21Line(instance), &buffer[index], 33, 10);
#else
	_itow_s(internalGetP21Line(instance), &buffer[index], 33, 10);
#endif
	index += wcslen(&buffer[index]);
	buffer[index++] = ' ';
	buffer[index++] = '=';
	buffer[index++] = ' ';
	wchar_t	* className = 0;
	engiGetEntityName(sdaiGetInstanceType(instance), sdaiUNICODE, (char**) &className);
	memcpy(&buffer[index], className, wcslen(className) * sizeof(wchar_t));
	index += wcslen(className);
	buffer[index++] = '(';
	buffer[index++] = ')';
	buffer[index] = 0;
}

#ifdef WIN64
void CRightPane::InsertItemInstanceEntity(__int64 ifcEntity, HTREEITEM hParent)
#else
void CRightPane::InsertItemInstanceEntity(__int32 ifcEntity, HTREEITEM hParent)
#endif
{
	wchar_t	* className = 0;
	engiGetEntityName(ifcEntity, sdaiUNICODE, (char**) &className);

	TV_INSERTSTRUCT		tvstruct;
	tvstruct.hParent = hParent;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
	tvstruct.item.cChildren = 0;
	tvstruct.item.pszText = className;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.lParam = (LPARAM) 0;

	GetTreeCtrl().InsertItem(&tvstruct);
}

#ifdef WIN64
void	CreateAttributeTextADB(wchar_t * buffer, bool * children, __int64 ADB)
#else
void	CreateAttributeTextADB(wchar_t * buffer, bool * children, __int32 ADB)
#endif
{
	size_t	index = 0;
	switch  (sdaiGetADBType((void*) ADB)) {
		case  sdaiADB:
			{
#ifdef WIN64
				__int64	ADBsub = 0;
#else
				__int32	ADBsub = 0;
#endif
				sdaiGetADBValue((void*) ADB, sdaiADB, &ADBsub);
				if	(ADBsub) {
					wchar_t	* path = (wchar_t*) sdaiGetADBTypePath((void*) ADBsub, sdaiUNICODE);
					memcpy(&buffer[index], path, wcslen(path) * sizeof(wchar_t));
					index += wcslen(path);
					buffer[index++] = '(';

					CreateAttributeTextADB(&buffer[index], children, ADBsub);
					index += wcslen(&buffer[index]);

					buffer[index++] = ')';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiAGGR:
			{
#ifdef WIN64
				__int64	* value = 0, cnt, i;
#else
				__int32	* value = 0, cnt, i;
#endif
				sdaiGetADBValue((void*) ADB, sdaiAGGR, &value);
				if	(value) {
					buffer[index++] = '(';
					i = 0;
					cnt = sdaiGetMemberCount(value);
					while  (i < cnt) {
						if	(i) {
							buffer[index++] = ',';
							buffer[index++] = ' ';
						}
						buffer[index++] = '?';
						buffer[index++] = '?';
						buffer[index++] = '?';
						i++;
					}
					buffer[index++] = ')';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiBOOLEAN:
		case  sdaiENUM:
		case  sdaiLOGICAL:
			{
				wchar_t	* value = 0;
				sdaiGetADBValue((void*) ADB, sdaiUNICODE, (char**) &value);
				if	(value) {
					memcpy(&buffer[index], value, wcslen(value) * sizeof(wchar_t));
					index += wcslen(value);
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiINSTANCE:
			{
#ifdef WIN64
				__int64	localIfcInstance = 0, value;
#else
				__int32	localIfcInstance = 0, value;
#endif
				sdaiGetADBValue((void*) ADB, sdaiINSTANCE, &localIfcInstance);
				if	(localIfcInstance) {
					buffer[index++] = '#';
					value = internalGetP21Line(localIfcInstance);
#ifdef WIN64
					_i64tow_s(value, &buffer[index], 33, 10);
#else
					_itow_s(value, &buffer[index], 33, 10);
#endif
					index += wcslen(&buffer[index]);
					(*children) = true;
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiINTEGER:
			{
#ifdef WIN64
				__int64	value = 0;
#else
				__int32	value = 0;
#endif
				sdaiGetADBValue((void*) ADB, sdaiINTEGER, &value);
#ifdef WIN64
				_i64tow_s(value, &buffer[index], 33, 10);
#else
				_itow_s(value, &buffer[index], 33, 10);
#endif
				index += wcslen(&buffer[index]);
			}
			break;
		case  sdaiSTRING:
			{
				wchar_t	* value = 0;
				sdaiGetADBValue((void*) ADB, sdaiUNICODE, (char**) &value);
				if	(value) {
					buffer[index++] = '\'';
					memcpy(&buffer[index], value, wcslen(value) * sizeof(wchar_t));
					index += wcslen(value);
					buffer[index++] = '\'';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiREAL:
			{
				double	value = 0;
				sdaiGetADBValue((void*) ADB, sdaiREAL, &value);
				_ecvt(value, &buffer[index]);
				index += wcslen(&buffer[index]);
			}
			break;
		default:
			ASSERT(false);
			break;
	}
	buffer[index] = 0;
}

#ifdef WIN64
void	CreateAttributeTextAGGR(wchar_t * buffer, bool * children, __int64 * aggregate, __int64 elementIndex)
#else
void	CreateAttributeTextAGGR(wchar_t * buffer, bool * children, __int32 * aggregate, __int32 elementIndex)
#endif
{
	size_t	index = 0;
#ifdef WIN64
	__int64	aggregateType = 0;
#else
	__int32	aggregateType = 0;
#endif
	engiGetAggrType(aggregate, &aggregateType);
	switch  (aggregateType) {
		case  sdaiADB:
			{
#ifdef WIN64
				__int64	ADB = 0;
#else
				__int32	ADB = 0;
#endif
				engiGetAggrElement(aggregate, elementIndex, sdaiADB, &ADB);
				if	(ADB) {
					wchar_t	* path = (wchar_t*) sdaiGetADBTypePath((void*) ADB, sdaiUNICODE);
					memcpy(&buffer[index], path, wcslen(path) * sizeof(wchar_t));
					index += wcslen(path);
					buffer[index++] = '(';

					CreateAttributeTextADB(&buffer[index], children, ADB);
					index += wcslen(&buffer[index]);

					buffer[index++] = ')';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiAGGR:
			{
#ifdef WIN64
				__int64	* value = 0, cnt, i;
#else
				__int32	* value = 0, cnt, i;
#endif
				engiGetAggrElement(aggregate, elementIndex, sdaiAGGR, &value);
				if	(value) {
					buffer[index++] = '(';
					i = 0;
					cnt = sdaiGetMemberCount(value);
					while  (i < cnt  &&  i < 8) {
						if	(i) {
							buffer[index++] = ',';
							buffer[index++] = ' ';
						}

						CreateAttributeTextAGGR(&buffer[index], children, value, i);
						index += wcslen(&buffer[index]);

						i++;
					}

					if	(i < cnt) {
						buffer[index++] = ',';
						buffer[index++] = ' ';
						buffer[index++] = '.';
						buffer[index++] = '.';
						buffer[index++] = '.';
					}

					buffer[index++] = ')';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiBOOLEAN:
		case  sdaiENUM:
		case  sdaiLOGICAL:
			{
				wchar_t	* value = 0;
				engiGetAggrElement(aggregate, elementIndex, sdaiUNICODE, (char**) &value);
				if	(value) {
					memcpy(&buffer[index], value, wcslen(value) * sizeof(wchar_t));
					index += wcslen(value);
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiINSTANCE:
			{
#ifdef WIN64
				__int64	localIfcInstance = 0, value;
#else
				__int32	localIfcInstance = 0, value;
#endif
				engiGetAggrElement(aggregate, elementIndex, sdaiINSTANCE, &localIfcInstance);
				if	(localIfcInstance) {
					buffer[index++] = '#';
					value = internalGetP21Line(localIfcInstance);
#ifdef WIN64
					_i64tow_s(value, &buffer[index], 33, 10);
#else
					_itow_s(value, &buffer[index], 33, 10);
#endif
					index += wcslen(&buffer[index]);
					(*children) = true;
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiINTEGER:
			{
#ifdef WIN64
				__int64	value = 0;
#else
				__int32	value = 0;
#endif
				engiGetAggrElement(aggregate, elementIndex, sdaiINTEGER, &value);
#ifdef WIN64
				_i64tow_s(value, &buffer[index], 33, 10);
#else
				_itow_s(value, &buffer[index], 33, 10);
#endif
				index += wcslen(&buffer[index]);
			}
			break;
		case  sdaiSTRING:
			{
				wchar_t	* value = 0;
				engiGetAggrElement(aggregate, elementIndex, sdaiUNICODE, (char**) &value);
				if	(value) {
					buffer[index++] = '\'';
					memcpy(&buffer[index], value, wcslen(value) * sizeof(wchar_t));
					index += wcslen(value);
					buffer[index++] = '\'';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiREAL:
			{
				double	value = 0;
				engiGetAggrElement(aggregate, elementIndex, sdaiREAL, &value);
				_ecvt(value, &buffer[index]);
				index += wcslen(&buffer[index]);
			}
			break;
		default:
			ASSERT(false);
			break;
	}
	buffer[index] = 0;
}

#ifdef WIN64
void	CreateAttributeText(wchar_t * buffer, bool * children, __int64 ifcInstance, wchar_t * attributeName, __int64 attributeType)
#else
void	CreateAttributeText(wchar_t * buffer, bool * children, __int32 ifcInstance, wchar_t * attributeName, __int32 attributeType)
#endif
{
	size_t	index = 0;
	switch  (attributeType) {
		case  sdaiADB:
			{
#ifdef WIN64
				__int64	ADB = 0;
#else
				__int32	ADB = 0;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiADB, &ADB);
				if	(ADB) {
					wchar_t	* path = (wchar_t*) sdaiGetADBTypePath((void*) ADB, sdaiUNICODE);
					memcpy(&buffer[index], path, wcslen(path) * sizeof(wchar_t));
					index += wcslen(path);
					buffer[index++] = '(';

					CreateAttributeTextADB(&buffer[index], children, ADB);
					index += wcslen(&buffer[index]);

					buffer[index++] = ')';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiAGGR:
			{
#ifdef WIN64
				__int64	* value = 0, cnt, i;
#else
				__int32	* value = 0, cnt, i;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiAGGR, &value);
				if	(value) {
					buffer[index++] = '(';
					i = 0;
					cnt = sdaiGetMemberCount(value);
					while  (i < cnt  &&  i < 8) {
						if	(i) {
							buffer[index++] = ',';
							buffer[index++] = ' ';
						}

						CreateAttributeTextAGGR(&buffer[index], children, value, i);
						index += wcslen(&buffer[index]);

						i++;
					}

					if	(i < cnt) {
						buffer[index++] = ',';
						buffer[index++] = ' ';
						buffer[index++] = '.';
						buffer[index++] = '.';
						buffer[index++] = '.';
					}
					buffer[index++] = ')';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiBOOLEAN:
		case  sdaiENUM:
		case  sdaiLOGICAL:
			{
				wchar_t	* value = 0;
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiUNICODE, (char**) &value);
				if	(value) {
					memcpy(&buffer[index], value, wcslen(value) * sizeof(wchar_t));
					index += wcslen(value);
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiINSTANCE:
			{
#ifdef WIN64
				__int64	localIfcInstance = 0, value;
#else
				__int32	localIfcInstance = 0, value;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiINSTANCE, &localIfcInstance);
				if	(localIfcInstance) {
					buffer[index++] = '#';
					value = internalGetP21Line(localIfcInstance);
#ifdef WIN64
					_i64tow_s(value, &buffer[index], 33, 10);
#else
					_itow_s(value, &buffer[index], 33, 10);
#endif
					index += wcslen(&buffer[index]);
					(*children) = true;
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiINTEGER:
			{
#ifdef WIN64
				__int64	value = 0;
#else
				__int32	value = 0;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiINTEGER, &value);
#ifdef WIN64
				_i64tow_s(value, &buffer[index], 33, 10);
#else
				_itow_s(value, &buffer[index], 33, 10);
#endif
				index += wcslen(&buffer[index]);
			}
			break;
		case  sdaiSTRING:
			{
				wchar_t	* value = 0;
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiUNICODE, (char**) &value);
				if	(value) {
					buffer[index++] = '\'';
					memcpy(&buffer[index], value, wcslen(value) * sizeof(wchar_t));
					index += wcslen(value);
					buffer[index++] = '\'';
				} else {
					buffer[index++] = L'Ø';
				}
			}
			break;
		case  sdaiREAL:
			{
				double	value = 0;
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiREAL, &value);
				_ecvt(value, &buffer[index]);
				index += wcslen(&buffer[index]);
			}
			break;
		default:
			ASSERT(false);
			break;
	}
	buffer[index] = 0;
}

#ifdef WIN64
void CRightPane::GetAttributeReferencesADB(__int64 ADB, HTREEITEM hParent)
#else
void CRightPane::GetAttributeReferencesADB(__int32 ADB, HTREEITEM hParent)
#endif
{
	switch  (sdaiGetADBType((void*) ADB)) {
		case  sdaiADB:
			{
#ifdef WIN64
				__int64	ADBsub = 0;
#else
				__int32	ADBsub = 0;
#endif
				sdaiGetADBValue((void*) ADB, sdaiADB, &ADBsub);
				if	(ADBsub) {
					GetAttributeReferencesADB(ADBsub, hParent);
				}
			}
			break;
		case  sdaiAGGR:
			{
#ifdef WIN64
				__int64	* value = 0, cnt, i;
#else
				__int32	* value = 0, cnt, i;
#endif
				sdaiGetADBValue((void*) ADB, sdaiAGGR, &value);
				if	(value) {
					i = 0;
					cnt = sdaiGetMemberCount(value);
					while  (i < cnt) {
						GetAttributeReferencesAGGR(value, i, hParent);
						i++;
					}
				}
			}
			break;
		case  sdaiBOOLEAN:
		case  sdaiENUM:
		case  sdaiLOGICAL:
			break;
		case  sdaiINSTANCE:
			{
#ifdef WIN64
				__int64	localIfcInstance = 0;
#else
				__int32	localIfcInstance = 0;
#endif
				sdaiGetADBValue((void*) ADB, sdaiINSTANCE, &localIfcInstance);
				if	(localIfcInstance) {
					InsertItemInstance(localIfcInstance, hParent);
				}
			}
			break;
		case  sdaiINTEGER:
			break;
		case  sdaiSTRING:
			break;
		case  sdaiREAL:
			break;
		default:
			ASSERT(false);
			break;
	}
}

#ifdef WIN64
void CRightPane::GetAttributeReferencesAGGR(__int64 * aggregate, __int64 elementIndex, HTREEITEM hParent)
#else
void CRightPane::GetAttributeReferencesAGGR(__int32 * aggregate, __int32 elementIndex, HTREEITEM hParent)
#endif
{
#ifdef WIN64
	__int64	aggregateType = 0;
#else
	__int32	aggregateType = 0;
#endif
	engiGetAggrType(aggregate, &aggregateType);
	switch  (aggregateType) {
		case  sdaiADB:
			{
#ifdef WIN64
				__int64	ADB = 0;
#else
				__int32	ADB = 0;
#endif
				engiGetAggrElement(aggregate, elementIndex, sdaiADB, &ADB);
				if	(ADB) {
					GetAttributeReferencesADB(ADB, hParent);
				}
			}
			break;
		case  sdaiAGGR:
			{
#ifdef WIN64
				__int64	* value = 0, cnt, i;
#else
				__int32	* value = 0, cnt, i;
#endif
				engiGetAggrElement(aggregate, elementIndex, sdaiAGGR, &value);
				if	(value) {
					i = 0;
					cnt = sdaiGetMemberCount(value);
					while  (i < cnt) {
						GetAttributeReferencesAGGR(value, i, hParent);
						i++;
					}
				}
			}
			break;
		case  sdaiBOOLEAN:
		case  sdaiENUM:
		case  sdaiLOGICAL:
			break;
		case  sdaiINSTANCE:
			{
#ifdef WIN64
				__int64	localIfcInstance = 0;
#else
				__int32	localIfcInstance = 0;
#endif
				engiGetAggrElement(aggregate, elementIndex, sdaiINSTANCE, &localIfcInstance);
				if	(localIfcInstance) {
					InsertItemInstance(localIfcInstance, hParent);
				}
			}
			break;
		case  sdaiINTEGER:
			break;
		case  sdaiSTRING:
			break;
		case  sdaiREAL:
			break;
		default:
			ASSERT(false);
			break;
	}
}

#ifdef WIN64
void CRightPane::GetAttributeReferences(__int64 ifcInstance, wchar_t * attributeName, __int64 attributeType, HTREEITEM hParent)
#else
void CRightPane::GetAttributeReferences(__int32 ifcInstance, wchar_t * attributeName, __int32 attributeType, HTREEITEM hParent)
#endif
{
	switch  (attributeType) {
		case  sdaiADB:
			{
#ifdef WIN64
				__int64	ADB = 0;
#else
				__int32	ADB = 0;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiADB, &ADB);
				if	(ADB) {
					GetAttributeReferencesADB(ADB, hParent);
				}
			}
			break;
		case  sdaiAGGR:
			{
#ifdef WIN64
				__int64	* value = 0, cnt, i;
#else
				__int32	* value = 0, cnt, i;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiAGGR, &value);
				if	(value) {
					i = 0;
					cnt = sdaiGetMemberCount(value);
					while  (i < cnt) {
						GetAttributeReferencesAGGR(value, i, hParent);
						i++;
					}
				}
			}
			break;
		case  sdaiBOOLEAN:
		case  sdaiENUM:
		case  sdaiLOGICAL:
			break;
		case  sdaiINSTANCE:
			{
#ifdef WIN64
				__int64	localIfcInstance = 0;
#else
				__int32	localIfcInstance = 0;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiINSTANCE, &localIfcInstance);
				if	(localIfcInstance) {
					InsertItemInstance(localIfcInstance, hParent);
				}
			}
			break;
		case  sdaiINTEGER:
			break;
		case  sdaiSTRING:
			break;
		case  sdaiREAL:
			break;
		default:
			ASSERT(false);
			break;
	}
}

#ifdef WIN64
void CRightPane::InsertItemInstanceAttribute(__int64 ifcInstance, wchar_t * attributeName, __int64 attributeType, HTREEITEM hParent)
#else
void CRightPane::InsertItemInstanceAttribute(__int32 ifcInstance, wchar_t * attributeName, __int32 attributeType, HTREEITEM hParent)
#endif
{
	wchar_t	buffer[512];
	size_t	index = 0;
	buffer[index++] = ' ';
	buffer[index++] = ' ';
	memcpy(&buffer[index], attributeName, wcslen(attributeName) * sizeof(wchar_t));
	index += wcslen(attributeName);

	buffer[index++] = ' ';
	buffer[index++] = '=';
	buffer[index++] = ' ';

	bool	children = false;
	CreateAttributeText(&buffer[index], &children, ifcInstance, attributeName, attributeType);

	STRUCT_INSTANCE	* instance = new_STRUCT_INSTANCE(ifcInstance);
	instance->attributeName = attributeName;
	instance->attributeType = attributeType;

	TV_INSERTSTRUCT		tvstruct;
	tvstruct.hParent = hParent;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
	if	(children) {
		tvstruct.item.cChildren = 1;
	} else {
		tvstruct.item.cChildren = 0;
	}
	tvstruct.item.pszText = buffer;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.lParam = (LPARAM) instance;

	instance->hItem = GetTreeCtrl().InsertItem(&tvstruct);
}

#ifdef WIN64
__int64 CRightPane::InsertItemAttributes(__int64 ifcEntity, __int64 ifcInstance, HTREEITEM hParent)
#else
__int32 CRightPane::InsertItemAttributes(__int32 ifcEntity, __int32 ifcInstance, HTREEITEM hParent)
#endif
{
	if	(ifcEntity) {
		//
		//	Walk over the parents
		//
#ifdef WIN64
		__int64	attributeCnt = InsertItemAttributes(engiGetEntityParent(ifcEntity), ifcInstance, hParent), attributeType;
#else
		__int32	attributeCnt = InsertItemAttributes(engiGetEntityParent(ifcEntity), ifcInstance, hParent), attributeType;
#endif

		//
		//	Start with Entity name
		//
		InsertItemInstanceEntity(ifcEntity, hParent);

		//
		//	Walk over attributes
		//
		while  (attributeCnt < engiGetEntityNoArguments(ifcEntity)) {
			wchar_t	* attributeName = 0;
//			char	* attributeName = 0;
			attributeType = 0;
			engiGetEntityArgumentName(ifcEntity, attributeCnt, sdaiUNICODE, (char**) &attributeName);
//			engiGetEntityArgumentName(ifcEntity, attributeCnt, sdaiSTRING, &attributeName);
			attributeType = engiGetAttrTypeBN(ifcInstance, (char*) attributeName);
			if	(attributeType & 128) {
				attributeType = sdaiAGGR;
			}
			if	(attributeType == sdaiADB) {
#ifdef WIN64
				__int64	ADB = 0;
#else
				__int32	ADB = 0;
#endif
				sdaiGetAttrBN(ifcInstance, (char*) attributeName, sdaiADB, &ADB);
				if	(ADB == 0) {
					ASSERT(false);
					attributeType = sdaiINSTANCE;
				}
			}
//			engiGetEntityArgumentType(ifcEntity, attributeCnt, &attributeType);
			InsertItemInstanceAttribute(ifcInstance, attributeName, attributeType, hParent);

			attributeCnt++;
		}

		return	attributeCnt;
	}

	return	0;
}

#ifdef WIN64
void CRightPane::InsertItemReferences(__int64 ifcInstance, wchar_t * attributeName, __int64 attributeType, HTREEITEM hParent)
#else
void CRightPane::InsertItemReferences(__int32 ifcInstance, wchar_t * attributeName, __int32 attributeType, HTREEITEM hParent)
#endif
{
	GetAttributeReferences(ifcInstance, attributeName, attributeType, hParent);
}

#ifdef WIN64
void CRightPane::InsertItemInstance(__int64 ifcInstance, HTREEITEM hParent)
#else
void CRightPane::InsertItemInstance(__int32 ifcInstance, HTREEITEM hParent)
#endif
{
	if	(ifcInstance) {
		wchar_t	buffer[512];
		CreateInstanceName(ifcInstance, buffer);

		STRUCT_INSTANCE	* instance = new_STRUCT_INSTANCE(ifcInstance);

		TV_INSERTSTRUCT		tvstruct;
		tvstruct.hParent = hParent;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
		tvstruct.item.cChildren = 1;
		tvstruct.item.pszText = buffer;
		tvstruct.item.iImage = 0;
		tvstruct.item.iSelectedImage = 0;
		tvstruct.item.lParam = (LPARAM) instance;

		instance->hItem = GetTreeCtrl().InsertItem(&tvstruct);
	}
}

void CRightPane::OnInitialUpdate()
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

//	InsertItemInstance(0);
}

#ifdef WIN64
void CRightPane::SelectedEntity(__int64 ifcEntity)
#else
void CRightPane::SelectedEntity(__int32 ifcEntity)
#endif
{
	GetTreeCtrl().DeleteAllItems();

#ifdef WIN64
	__int64	* ifcObjects, ifcObjectsCnt, ifcObject, i = 0;
#else
	__int32	* ifcObjects, ifcObjectsCnt, ifcObject, i = 0;
#endif
	ifcObjects = sdaiGetEntityExtent(model, ifcEntity);
	ifcObjectsCnt = sdaiGetMemberCount(ifcObjects);

	while  (i < ifcObjectsCnt) {
		ifcObject = 0;
		engiGetAggrElement(ifcObjects, i++, sdaiINSTANCE, &ifcObject);

		InsertItemInstance(ifcObject, 0);
	}
}

LRESULT CRightPane::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if	(message == ID_UPDATE_RIGHT_VIEW) {
		SelectedEntity(lParam);
	}

	return CTreeView::WindowProc(message, wParam, lParam);
}


void CRightPane::OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTREEVIEW* pnmtv = (NMTREEVIEW*) pNMHDR;
	HTREEITEM hItem = pnmtv->itemNew.hItem;

	STRUCT_INSTANCE	* instance = (STRUCT_INSTANCE *) GetTreeCtrl().GetItemData(hItem);
	if	(instance  &&  instance->expanded == false) {
		if	(instance->attributeName) {
			InsertItemReferences(instance->ifcInstance, instance->attributeName, instance->attributeType, instance->hItem);
		} else {
			InsertItemAttributes(sdaiGetInstanceType(instance->ifcInstance), instance->ifcInstance, instance->hItem);
		}
		instance->expanded = true;
	}

	*pResult = 0;
}

void CRightPane::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	//...

	*pResult = 0;
}


void CRightPane::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	DWORD		pos = GetMessagePos();
	CPoint		pt(LOWORD(pos), HIWORD(pos));
	GetTreeCtrl().ScreenToClient(&pt);
//	this->GetParent()->



	HTREEITEM	hItem = GetTreeCtrl().GetFirstVisibleItem();

	while  (hItem) {
		CRect r;
		GetTreeCtrl().GetItemRect(hItem, &r, true);

		if	(r.PtInRect(pt)) {
			STRUCT_INSTANCE	* instance = (STRUCT_INSTANCE *) GetTreeCtrl().GetItemData(hItem);
			if	(instance) {
				if	(instance->attributeName == 0  &&  instance->attributeType == 0) {
					HMENU	hMenu = ::CreatePopupMenu();
					
					int64_t	owlInstance = 0;
					createGeometryConversion(instance->ifcInstance, &owlInstance);

if	(owlInstance) {
__int64	vertexBufferSize = 0, indexBufferSize = 0;
CalculateInstance(owlInstance, &vertexBufferSize, &indexBufferSize, 0);
float	* vertexBuffer = new float[6 * vertexBufferSize];
__int32	* indexBuffer = new __int32[indexBufferSize];
UpdateInstanceVertexBuffer(owlInstance, vertexBuffer);
UpdateInstanceIndexBuffer(owlInstance, indexBuffer);

int	u = 0;
}

					if	(owlInstance) {
						::AppendMenu(hMenu, 0, 1, L"export geometry as *.rdf");
					} else {
						::AppendMenu(hMenu, MF_DISABLED, 1, L"no geometry attached to this instance");
					}
DWORD	posa = GetMessagePos();
CPoint	pta(LOWORD(posa), HIWORD(posa));
					int sel = ::TrackPopupMenuEx(hMenu, 
						TPM_CENTERALIGN | TPM_RETURNCMD,
						pta.x,// + r.right,
						pta.y,// + r.top,
						GetTreeCtrl(),
						NULL);
					::DestroyMenu(hMenu);
					if	(sel > 0) {
						int	express_id = internalGetP21Line(instance->ifcInstance);

						char strFilter[] = { "Text Files (*.rdf)|*.rdf|" }, buff[512];
						CFileDialog FileDlg(false, CString(".rdf"), CString("item #") + CString(itoa(express_id, buff, 10)) + CString(".rdf"), 0, CString(strFilter)); 

						if	(FileDlg.DoModal() == IDOK)
						{
							CString	fileName = FileDlg.GetFolderPath() + "\\" + FileDlg.GetFileName();

							char	fileNameChar[512];// = (char *) fileName.GetBuffer();
							int		i = 0;
							while  (fileName[i]) {
								fileNameChar[i] = fileName[i];
								i++;
							}
							fileNameChar[i] = 0;
							SaveModel(model, fileNameChar);
//							agendaName = FileDlg.GetFileName(); //filename
//							agendaPath = FileDlg.GetFolderPath(); //filepath (folders)
							int u = 0;
//							if(model->agendaExists(CSToString(agendaPath+TEXT("\\")+agendaName))) // there is another file called the same way
//							{
//								if(MessageBox(TEXT("A file with the specified name already exists. Overwrite?"), TEXT("File exists"), MB_YESNO) != 6) // user clicked NO (do not overwrite file)
//								{
//									continue;
//								}

//							}

//							model->sendToFile(CSToString(agendaPath+TEXT("\\")+agendaName));  // the file is unique so the agenda named agendaName found at path agendaPath is saved
//							return;
						}
//						__int64	noVertices = 0, noIndices = 0;
//						CalculateInstance((__int64)instance->ifcInstance, &noVertices, &noIndices, 0);
//						int	u = 0~~;
					}

					cleanMemory(model, 1);
				}
			}
		}
		hItem = GetTreeCtrl().GetNextVisibleItem(hItem);
	}

	*pResult = 0;
}
