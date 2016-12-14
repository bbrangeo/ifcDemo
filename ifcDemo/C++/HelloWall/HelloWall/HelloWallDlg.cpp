////////////////////////////////////////////////////////////////////////
//	Author:		Peter Bonsma
//	Date:		20 February 2015
//	Project:	IFC Engine Series (example using DLL)
//
//	This code may be used and edited freely,
//	also for commercial projects in open and closed source software
//
//	In case of use of the DLL:
//	be aware of license fee for use of this DLL when used commercially
//	more info for commercial use:	contact@rdf.bg
//
//	more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//									peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "ifccreation/propertiesIfc.h"
#include "ifccreation/brepIfc.h"
#include "HelloWall.h"
#include "HelloWallDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define		COORDINATIONVIEW	0
#define		PRESENTATIONVIEW	1

#ifdef UNICODE
extern	wchar_t	* ifcFileName, * ifcSchemaNameIFC2x3, * ifcSchemaNameIFC4;
#else
extern	char	* ifcFileName, * ifcSchemaNameIFC2x3, * ifcSchemaNameIFC4;
#endif
bool	saveIfcXML = false;
__int32	view;

// CAboutDlg dialog used for App About

class	CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void	CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHelloWallDlg dialog




CHelloWallDlg::CHelloWallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelloWallDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void	CHelloWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_METERS, m_ResultsAsMeters);
	DDX_Control(pDX, IDC_CHECK_QUANTITIES, m_Quantities);
	DDX_Control(pDX, IDC_EDIT_OPENING_Y_OFFSET, m_OpeningZOffset);
	DDX_Control(pDX, IDC_EDIT_WINDOW_THICKNESS, m_WindowThickness);
	DDX_Control(pDX, IDC_EDIT_WINDOW_HEIGHT, m_WindowYOffset);
	DDX_Control(pDX, IDC_EDIT_OPENING_X_OFFSET, m_OpeningXOffset);
	DDX_Control(pDX, IDC_EDIT_OPENING_WIDTH, m_OpeningWidth);
	DDX_Control(pDX, IDC_EDIT_OPENING_HEIGHT, m_OpeningHeight);
	DDX_Control(pDX, IDC_CHECK_WINDOW_BASICREPR, m_WindowBasicRepr);
	DDX_Control(pDX, IDC_CHECK_OPENING_BASICREPR, m_OpeningBasicRepr);
	DDX_Control(pDX, IDC_CHECK_WALL_BASICREPR, m_WallBasicRepr);
	DDX_Control(pDX, IDC_CHECK_WALL, m_Wall);
	DDX_Control(pDX, IDC_CHECK_WINDOW, m_Window);
	DDX_Control(pDX, IDC_CHECK_OPENING, m_Opening);
	DDX_Control(pDX, IDC_EDIT_0_NAME, m_Wall_Name);
	DDX_Control(pDX, IDC_STATIC_0_NAME, m_Static_0_Name);
	DDX_Control(pDX, IDC_STATIC_0_0, m_Static_0_0);
	DDX_Control(pDX, IDC_STATIC_0_1, m_Static_0_1);
	DDX_Control(pDX, IDC_EDIT_1_NAME, m_Opening_Name);
	DDX_Control(pDX, IDC_STATIC_1_NAME, m_Static_1_Name);
	DDX_Control(pDX, IDC_STATIC_1_0, m_Static_1_0);
	DDX_Control(pDX, IDC_STATIC_1_1, m_Static_1_1);
	DDX_Control(pDX, IDC_EDIT_2_NAME, m_Window_Name);
	DDX_Control(pDX, IDC_STATIC_2_NAME, m_Static_2_Name);
	DDX_Control(pDX, IDC_STATIC_2_0, m_Static_2_0);
	DDX_Control(pDX, IDC_STATIC_2_1, m_Static_2_1);
	DDX_Control(pDX, IDC_STATIC_00, m_Static00);
	DDX_Control(pDX, IDC_STATIC_10, m_Static10);
	DDX_Control(pDX, IDC_STATIC_20, m_Static20);
	DDX_Control(pDX, IDC_STATIC_30, m_Static30);
	DDX_Control(pDX, IDC_STATIC_40, m_Static40);
	DDX_Control(pDX, IDC_STATIC_50, m_Static50);
	DDX_Control(pDX, IDC_STATIC_60, m_Static60);
	DDX_Control(pDX, IDC_STATIC_70, m_Static70);
	DDX_Control(pDX, IDC_STATIC_80, m_Static80);
	DDX_Control(pDX, IDC_STATIC_01, m_Static01);
	DDX_Control(pDX, IDC_STATIC_11, m_Static11);
	DDX_Control(pDX, IDC_STATIC_21, m_Static21);
	DDX_Control(pDX, IDC_STATIC_31, m_Static31);
	DDX_Control(pDX, IDC_STATIC_41, m_Static41);
	DDX_Control(pDX, IDC_STATIC_51, m_Static51);
	DDX_Control(pDX, IDC_STATIC_61, m_Static61);
	DDX_Control(pDX, IDC_STATIC_71, m_Static71);
	DDX_Control(pDX, IDC_STATIC_81, m_Static81);
	DDX_Control(pDX, IDC_EDIT_WALL_WIDTH, m_WallWidth);
	DDX_Control(pDX, IDC_EDIT_WALL_THICKNESS, m_WallThickness);
	DDX_Control(pDX, IDC_EDIT_WALL_HEIGHT, m_WallHeight);
	DDX_Control(pDX, IDC_EDIT_SCHEMA_NAME, m_SchemaName);
	DDX_Control(pDX, IDC_EDIT_FILE_NAME, m_FileName);
}

BEGIN_MESSAGE_MAP(CHelloWallDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_WALL, OnCheckWall)
	ON_BN_CLICKED(IDC_CHECK_OPENING, OnCheckOpening)
	ON_BN_CLICKED(IDC_CHECK_WINDOW, OnCheckWindow)
	ON_BN_CLICKED(IDC_RADIO_VIEW_0, OnRadio_View_0)
	ON_BN_CLICKED(IDC_RADIO_VIEW_1, OnRadio_View_1)
	ON_BN_CLICKED(IDC_RADIO_0_1, OnRadio_0_1)
	ON_BN_CLICKED(IDC_RADIO_0_2, OnRadio_0_2)
	ON_BN_CLICKED(IDC_RADIO_1_1, OnRadio_1_1)
	ON_BN_CLICKED(IDC_RADIO_1_2, OnRadio_1_2)
	ON_BN_CLICKED(IDC_RADIO_2_1, OnRadio_2_1)
	ON_BN_CLICKED(IDC_RADIO_2_2, OnRadio_2_2)
	ON_BN_CLICKED(IDC_IFC, OnIfc)
	ON_BN_CLICKED(IDC_IFX, OnIfx)
END_MESSAGE_MAP()


// CHelloWallDlg message handlers

BOOL	CHelloWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

#ifdef UNICODE
	m_FileName.SetWindowTextW(ifcFileName);
	m_SchemaName.SetWindowTextW(ifcSchemaNameIFC2x3);
#else
	m_FileName.SetWindowText(ifcFileName);
	m_SchemaName.SetWindowText(ifcSchemaNameIFC2x3);
#endif

#ifdef UNICODE
	m_Wall_Name.SetWindowTextW(L"Wall xyz");
	m_Opening_Name.SetWindowTextW(L"Opening Element xyz");
	m_Window_Name.SetWindowTextW(L"Window xyz");
#else
	m_Wall_Name.SetWindowText("Wall xyz");
	m_Opening_Name.SetWindowText("Opening Element xyz");
	m_Window_Name.SetWindowText("Window xyz");
#endif

#ifdef UNICODE
	m_WallThickness.SetWindowTextW(L"300");
	m_WallWidth.SetWindowTextW(L"5000");
	m_WallHeight.SetWindowTextW(L"2300");
	m_OpeningHeight.SetWindowTextW(L"1400");
	m_OpeningWidth.SetWindowTextW(L"750");
	m_OpeningXOffset.SetWindowTextW(L"900");
	m_OpeningZOffset.SetWindowTextW(L"250");
	m_WindowThickness.SetWindowTextW(L"190");
	m_WindowYOffset.SetWindowTextW(L"12");
#else
	m_WallThickness.SetWindowText("300");
	m_WallWidth.SetWindowText("5000");
	m_WallHeight.SetWindowText("2300");
	m_OpeningHeight.SetWindowText("1400");
	m_OpeningWidth.SetWindowText("750");
	m_OpeningXOffset.SetWindowText("900");
	m_OpeningZOffset.SetWindowText("250");
	m_WindowThickness.SetWindowText("190");
	m_WindowYOffset.SetWindowText("12");
#endif

	OnRadio_View_0();

	OnRadio_0_2();
	OnRadio_1_2();
	OnRadio_2_2();

	m_Wall.SetCheck(1);
	m_WallBasicRepr.SetCheck(1);
	m_Opening.SetCheck(1);
	m_OpeningBasicRepr.SetCheck(1);
	m_Window.SetCheck(1);
	m_WindowBasicRepr.SetCheck(1);

	OnCheckWindow();
	OnCheckOpening();
	OnCheckWall();

	m_Quantities.SetCheck(true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void	CHelloWallDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void	CHelloWallDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		__int32	cxIcon = GetSystemMetrics(SM_CXICON),
				cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		__int32	x = (rect.Width() - cxIcon + 1) / 2,
				y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR	CHelloWallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

POINT3D	* create3DPoint(POINT3D ** pPoint, double x, double y, double z)
{
	(*pPoint) = new POINT3D;
	(*pPoint)->x = x;
	(*pPoint)->y = y;
	(*pPoint)->z = z;
	(*pPoint)->ifcCartesianPointInstance = 0;

	return	(*pPoint);
}

POLYGON2D	* localCreatePolygonStructureForSquare(double min_x, double min_y, double max_x, double max_y)
{
	POLYGON2D	* polygon = new POLYGON2D;
	polygon->point = new POINT2D;
	polygon->point->x = min_x;
	polygon->point->y = min_y;
	polygon->next = new POLYGON2D;
	polygon->next->point = new POINT2D;
	polygon->next->point->x = min_x;
	polygon->next->point->y = max_y;
	polygon->next->next = new POLYGON2D;
	polygon->next->next->point = new POINT2D;
	polygon->next->next->point->x = max_x;
	polygon->next->next->point->y = max_y;
	polygon->next->next->next = new POLYGON2D;
	polygon->next->next->next->point = new POINT2D;
	polygon->next->next->next->point->x = max_x;
	polygon->next->next->next->point->y = min_y;
	polygon->next->next->next->next = 0;

	return	polygon;
}

POLYGON3D	* create3DPolygonWith4Vectors(POLYGON3D ** pPolygon, POINT3D * pointI, POINT3D * pointII, POINT3D * pointIII, POINT3D * pointIV)
{
	VECTOR3D	* vector = new VECTOR3D;
	vector->point = pointI;
	vector->next = new VECTOR3D;
	vector->next->point = pointII;
	vector->next->next = new VECTOR3D;
	vector->next->next->point = pointIII;
	vector->next->next->next = new VECTOR3D;
	vector->next->next->next->point = pointIV;
	vector->next->next->next->next = 0;

	(*pPolygon) = new POLYGON3D;
	(*pPolygon)->vector = vector;
	(*pPolygon)->openingVector = 0;
	(*pPolygon)->next = 0;

	return	(*pPolygon);
}

void	add3DPolygonOpeningWith4Vectors(POLYGON3D * polygon, POINT3D * pointI, POINT3D * pointII, POINT3D * pointIII, POINT3D * pointIV)
{
	VECTOR3D	* vector = new VECTOR3D;
	vector->point = pointI;
	vector->next = new VECTOR3D;
	vector->next->point = pointII;
	vector->next->next = new VECTOR3D;
	vector->next->next->point = pointIII;
	vector->next->next->next = new VECTOR3D;
	vector->next->next->next->point = pointIV;
	vector->next->next->next->next = 0;

	polygon->openingVector = vector;
}

SHELL	* localCreateShellStructureForCuboid(double min_x, double min_y, double min_z, double max_x, double max_y, double max_z)
{
	POINT3D		* points[8];
	POLYGON3D	* polygons[6];
	SHELL		* shell;

	create3DPoint(&points[0], min_x, min_y, min_z);
	create3DPoint(&points[1], max_x, min_y, min_z);
	create3DPoint(&points[2], min_x, max_y, min_z);
	create3DPoint(&points[3], max_x, max_y, min_z);
	create3DPoint(&points[4], min_x, min_y, max_z);
	create3DPoint(&points[5], max_x, min_y, max_z);
	create3DPoint(&points[6], min_x, max_y, max_z);
	create3DPoint(&points[7], max_x, max_y, max_z);

	shell = new SHELL;
	shell->polygon = create3DPolygonWith4Vectors(&polygons[0], points[0], points[2], points[3], points[1]);
	shell->next = 0;

	polygons[0]->next = create3DPolygonWith4Vectors(&polygons[1], points[4], points[5], points[7], points[6]);
	polygons[1]->next = create3DPolygonWith4Vectors(&polygons[2], points[0], points[4], points[6], points[2]);
	polygons[2]->next = create3DPolygonWith4Vectors(&polygons[3], points[2], points[6], points[7], points[3]);
	polygons[3]->next = create3DPolygonWith4Vectors(&polygons[4], points[3], points[7], points[5], points[1]);
	polygons[4]->next = create3DPolygonWith4Vectors(&polygons[5], points[1], points[5], points[4], points[0]);

	return	shell;
}

SHELL	* localCreateShellStructureForCuboidWithOpening(double min_x, double min_y, double min_z, double max_x, double max_y, double max_z, double min_x_opening, double min_z_opening, double max_x_opening, double max_z_opening)
{
	POINT3D		* points[16];
	POLYGON3D	* polygons[10];
	SHELL		* shell;

	create3DPoint(&points[0], min_x, min_y, min_z);
	create3DPoint(&points[1], max_x, min_y, min_z);
	create3DPoint(&points[2], min_x, max_y, min_z);
	create3DPoint(&points[3], max_x, max_y, min_z);
	create3DPoint(&points[4], min_x, min_y, max_z);
	create3DPoint(&points[5], max_x, min_y, max_z);
	create3DPoint(&points[6], min_x, max_y, max_z);
	create3DPoint(&points[7], max_x, max_y, max_z);
	create3DPoint(&points[8], min_x_opening, min_y, min_z_opening);
	create3DPoint(&points[9], max_x_opening, min_y, min_z_opening);
	create3DPoint(&points[10], min_x_opening, max_y, min_z_opening);
	create3DPoint(&points[11], max_x_opening, max_y, min_z_opening);
	create3DPoint(&points[12], min_x_opening, min_y, max_z_opening);
	create3DPoint(&points[13], max_x_opening, min_y, max_z_opening);
	create3DPoint(&points[14], min_x_opening, max_y, max_z_opening);
	create3DPoint(&points[15], max_x_opening, max_y, max_z_opening);

	shell = new SHELL;
	shell->polygon = create3DPolygonWith4Vectors(&polygons[0], points[0], points[2], points[3], points[1]);
	shell->next = 0;

	polygons[0]->next = create3DPolygonWith4Vectors(&polygons[1], points[4], points[5], points[7], points[6]);
	polygons[1]->next = create3DPolygonWith4Vectors(&polygons[2], points[0], points[4], points[6], points[2]);
	polygons[2]->next = create3DPolygonWith4Vectors(&polygons[3], points[2], points[6], points[7], points[3]);
	polygons[3]->next = create3DPolygonWith4Vectors(&polygons[4], points[3], points[7], points[5], points[1]);
	polygons[4]->next = create3DPolygonWith4Vectors(&polygons[5], points[1], points[5], points[4], points[0]);

	polygons[5]->next = create3DPolygonWith4Vectors(&polygons[6], points[0+8], points[1+8], points[3+8], points[2+8]);
	polygons[6]->next = create3DPolygonWith4Vectors(&polygons[7], points[4+8], points[6+8], points[7+8], points[5+8]);
	polygons[7]->next = create3DPolygonWith4Vectors(&polygons[8], points[0+8], points[2+8], points[6+8], points[4+8]);
	polygons[8]->next = create3DPolygonWith4Vectors(&polygons[9], points[3+8], points[1+8], points[5+8], points[7+8]);

	add3DPolygonOpeningWith4Vectors(polygons[3], points[2+8], points[3+8], points[7+8], points[6+8]);
	add3DPolygonOpeningWith4Vectors(polygons[5], points[1+8], points[0+8], points[4+8], points[5+8]);

	return	shell;
}

void	CHelloWallDlg::OnOK() 
{
	POLYGON2D	* polygon;
	SHELL		* shell;
#ifdef WIN64
	__int64	ifcWallInstance, ifcOpeningElementInstance, ifcWindowInstance;
#else
	__int32	ifcWallInstance, ifcOpeningElementInstance, ifcWindowInstance;
#endif
	double	wallHeight, wallWidth, wallThickness,
			openingHeight, openingWidth, openingXOffset, openingZOffset,
			windowThickness, windowYOffset,
			linearConversionFactor;
#ifdef UNICODE
	wchar_t	ifcFileName[512], ifcSchemaName[512], buffer[512], * lengthUnitConversion = NULL,
			wallName[512], openingName[512], windowName[512];
#else
	char	ifcFileName[512], ifcSchemaName[512], buffer[512], * lengthUnitConversion = NULL,
			wallName[512], openingName[512], windowName[512];
#endif
	bool	objectsWillBeAdded;

#ifdef UNICODE
	m_FileName.GetWindowTextW(ifcFileName, 512);
	m_SchemaName.GetWindowTextW(ifcSchemaName, 512);

	m_Wall_Name.GetWindowTextW(wallName, 512);
	m_Opening_Name.GetWindowTextW(openingName, 512);
	m_Window_Name.GetWindowTextW(windowName, 512);
#else
	m_FileName.GetWindowText(ifcFileName, 512);
	m_SchemaName.GetWindowText(ifcSchemaName, 512);

	m_Wall_Name.GetWindowText(wallName, 512);
	m_Opening_Name.GetWindowText(openingName, 512);
	m_Window_Name.GetWindowText(windowName, 512);
#endif

	if	(m_ResultsAsMeters.GetCheck()) {
		linearConversionFactor = 1;
	} else {
		linearConversionFactor = 1000;
		lengthUnitConversion = _T("MILLI");
	}

#ifdef UNICODE
	m_WallHeight.GetWindowTextW(buffer, 512);
	wallHeight = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_WallWidth.GetWindowTextW(buffer, 512);
	wallWidth = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_WallThickness.GetWindowTextW(buffer, 512);
	wallThickness = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningHeight.GetWindowTextW(buffer, 512);
	openingHeight = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningWidth.GetWindowTextW(buffer, 512);
	openingWidth = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningXOffset.GetWindowTextW(buffer, 512);
	openingXOffset = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningZOffset.GetWindowTextW(buffer, 512);
	openingZOffset = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_WindowThickness.GetWindowTextW(buffer, 512);
	windowThickness = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
	m_WindowYOffset.GetWindowTextW(buffer, 512);
	windowYOffset = (double) _wtoi(buffer) * 0.001 * linearConversionFactor;
#else
	m_WallHeight.GetWindowText(buffer, 512);
	wallHeight = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_WallWidth.GetWindowText(buffer, 512);
	wallWidth = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_WallThickness.GetWindowText(buffer, 512);
	wallThickness = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningHeight.GetWindowText(buffer, 512);
	openingHeight = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningWidth.GetWindowText(buffer, 512);
	openingWidth = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningXOffset.GetWindowText(buffer, 512);
	openingXOffset = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_OpeningZOffset.GetWindowText(buffer, 512);
	openingZOffset = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_WindowThickness.GetWindowText(buffer, 512);
	windowThickness = (double) atoi(buffer) * 0.001 * linearConversionFactor;
	m_WindowYOffset.GetWindowText(buffer, 512);
	windowYOffset = (double) atoi(buffer) * 0.001 * linearConversionFactor;
#endif

	if	( ( (m_Wall.IsWindowEnabled())  &&
			(m_Wall.GetCheck()) ) ||
		  ( (m_Window.IsWindowEnabled())  &&
			(m_Window.GetCheck()) ) ) {
		objectsWillBeAdded = true; 
	} else {
		objectsWillBeAdded = false;
	}

#ifdef WIN64
	__int64	ifcModel;
#else
	__int32	ifcModel;
#endif

#ifdef UNICODE
	setStringUnicode(true);
#endif

	ifcModel = createEmptyIfcFile(ifcSchemaName, objectsWillBeAdded, lengthUnitConversion);
	if	(ifcModel) {
		if	( (m_Wall.IsWindowEnabled())  &&
			  (m_Wall.GetCheck()) ) {

			switch  (GetCheckedRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_2)) {
				case  IDC_RADIO_0_1:
					ifcWallInstance = createIfcWallStandardCase(wallName, 0, 0, 0);
					buildRelDefinesByProperties(ifcWallInstance, buildPset_WallCommon());
					if	(m_Quantities.GetCheck()) {
						buildRelDefinesByProperties(ifcWallInstance, buildBaseQuantities_WallStandardCase(wallThickness, wallWidth, wallHeight, (openingWidth / linearConversionFactor) * (openingHeight / linearConversionFactor), linearConversionFactor));
					}

					buildRelAssociatesMaterial(ifcWallInstance, wallThickness);
					createIfcPolylineShape(0, wallThickness/2, wallWidth, wallThickness/2);

					polygon = localCreatePolygonStructureForSquare(0, 0, wallWidth, wallThickness);
					createIfcExtrudedPolygonShape(polygon, wallHeight);
					break;
				case  IDC_RADIO_0_2:
					ifcWallInstance = createIfcWall(wallName, 0, 0, 0);
					buildRelDefinesByProperties(ifcWallInstance, buildPset_WallCommon());
					if  (m_Quantities.GetCheck()) {
						buildRelDefinesByProperties(ifcWallInstance, buildBaseQuantities_Wall(wallThickness, wallWidth, wallHeight, (openingWidth / linearConversionFactor) * (openingHeight / linearConversionFactor), linearConversionFactor));
					}

					if	( (view == PRESENTATIONVIEW)  &&  (m_Opening.IsWindowEnabled()) ) {
						shell = localCreateShellStructureForCuboidWithOpening(0, 0, 0, wallWidth, wallThickness, wallHeight, openingXOffset, openingZOffset, openingXOffset + openingWidth, openingZOffset + openingHeight);
					} else {
						shell = localCreateShellStructureForCuboid(0, 0, 0, wallWidth, wallThickness, wallHeight);
					}
					createIfcBRepShape(shell, 0, wallThickness/2, wallWidth, wallThickness/2);
					break;
				default:
#ifdef UNICODE
					MessageBoxW(L"Unknown selected type");
#else
					MessageBox("Unknown selected type");
#endif
					break;
			}

			if	(m_WallBasicRepr.GetCheck()) {
#ifdef UNICODE
				createIfcBoundingBoxShape(wallWidth, wallThickness, wallHeight, L"Box");
#else
				createIfcBoundingBoxShape(wallWidth, wallThickness, wallHeight, "Box");
#endif
			}
		}

		if	( (m_Opening.IsWindowEnabled())  &&
				(m_Opening.GetCheck()) ) {
			if	(view == COORDINATIONVIEW) {
				ifcOpeningElementInstance = createIfcOpeningElement(openingName, openingXOffset, 0, openingZOffset, true);
			} else {
				ASSERT(view == PRESENTATIONVIEW);
				ifcOpeningElementInstance = createIfcOpeningElement(openingName, openingXOffset, 0, openingZOffset, false);
			}

			if	(m_Quantities.GetCheck()) {
				buildRelDefinesByProperties(ifcOpeningElementInstance, buildBaseQuantities_Opening(wallThickness, openingHeight, openingWidth));
			}

			//
			//		Build relation between Wall and Opening
			//
			buildRelVoidsElementInstance(ifcWallInstance, ifcOpeningElementInstance);

			if	(view == COORDINATIONVIEW) {
				switch  (GetCheckedRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_2)) {
					case  IDC_RADIO_1_1:
						polygon = localCreatePolygonStructureForSquare(0, 0, openingWidth, wallThickness);
						createIfcExtrudedPolygonShape(polygon, openingHeight);
						buildRelAssociatesMaterial(ifcOpeningElementInstance);
						break;
					case  IDC_RADIO_1_2:
						shell = localCreateShellStructureForCuboid(0, 0, 0, openingWidth, wallThickness, openingHeight);
						createIfcBRepShape(shell);
						break;
					default:
#ifdef UNICODE
						MessageBoxW(L"Unknown selected type");
#else
						MessageBox("Unknown selected type");
#endif
						break;
				}

				if	(m_OpeningBasicRepr.GetCheck()) {
#ifdef UNICODE
					createIfcBoundingBoxShape(openingWidth, wallThickness, openingHeight, L"Box");
#else
					createIfcBoundingBoxShape(openingWidth, wallThickness, openingHeight, "Box");
#endif
				}
			} else {
				ASSERT(view == PRESENTATIONVIEW);
			}
		}

		if	( (m_Window.IsWindowEnabled())  &&
				(m_Window.GetCheck()) ) {
			if	( (m_Opening.IsWindowEnabled())  &&
					(m_Opening.GetCheck()) ) {
				ifcWindowInstance = createIfcWindow(windowName, 0, windowYOffset, 0, true, openingHeight, openingWidth);

				//
				//		Build relation between Opening and Window
				//
				buildRelFillsElementInstance(ifcOpeningElementInstance, ifcWindowInstance);
			} else {
				ifcWindowInstance = createIfcWindow(windowName, 0, 0, 0, false, openingHeight, openingWidth);
			}

			buildRelDefinesByProperties(ifcWindowInstance, buildPset_WindowCommon());
			if	(m_Quantities.GetCheck()) {
				buildRelDefinesByProperties(ifcWindowInstance, buildBaseQuantities_Window(openingHeight, openingWidth));
			}

			switch  (GetCheckedRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_2)) {
				case  IDC_RADIO_2_1:
					polygon = localCreatePolygonStructureForSquare(0, 0, openingWidth, windowThickness);
					createIfcExtrudedPolygonShape(polygon, openingHeight);
					break;
				case  IDC_RADIO_2_2:
					shell = localCreateShellStructureForCuboid(0, 0, 0, openingWidth, windowThickness, openingHeight);
					createIfcBRepShape(shell);
					break;
				default:
#ifdef UNICODE
					MessageBoxW(L"Unknown selected type");
#else
					MessageBox("Unknown selected type");
#endif
					break;
			}

			if	(m_WindowBasicRepr.GetCheck()) {
#ifdef UNICODE
				createIfcBoundingBoxShape(openingWidth, windowThickness, openingHeight, L"Box");
#else
				createIfcBoundingBoxShape(openingWidth, windowThickness, openingHeight, "Box");
#endif
			}
		}

		//
		//	Update header
		//

#ifdef UNICODE
		wchar_t		description[512], timeStamp[512];
#else
		char		description[512], timeStamp[512];
#endif
		time_t		t;
		struct tm	tInfo;

		time(&t);
		localtime_s(&tInfo, &t);

		if	(view == COORDINATIONVIEW) {
			if	(m_Quantities.GetCheck()) {
#ifdef UNICODE
				memcpy(description, L"ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]", (wcslen(L"ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]") + 1) * sizeof(wchar_t));
#else
				memcpy(description, "ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]", (strlen("ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]") + 1) * sizeof(char));
#endif
			} else {
#ifdef UNICODE
				memcpy(description, L"ViewDefinition [CoordinationView]", (wcslen(L"ViewDefinition [CoordinationView]") + 1) * sizeof(wchar_t));
#else
				memcpy(description, "ViewDefinition [CoordinationView]", (strlen("ViewDefinition [CoordinationView]") + 1) * sizeof(char));
#endif
			}
		} else {
			ASSERT(view == PRESENTATIONVIEW);
			if	(m_Quantities.GetCheck()) {
#ifdef UNICODE
				memcpy(description, L"ViewDefinition [PresentationView, QuantityTakeOffAddOnView]", (wcslen(L"ViewDefinition [PresentationView, QuantityTakeOffAddOnView]") + 1) * sizeof(wchar_t));
#else
				memcpy(description, "ViewDefinition [PresentationView, QuantityTakeOffAddOnView]", (strlen("ViewDefinition [PresentationView, QuantityTakeOffAddOnView]") + 1) * sizeof(char));
#endif
			} else {
#ifdef UNICODE
				memcpy(description, L"ViewDefinition [PresentationView]", (wcslen(L"ViewDefinition [PresentationView]") + 1) * sizeof(wchar_t));
#else
				memcpy(description, "ViewDefinition [PresentationView]", (strlen("ViewDefinition [PresentationView]") + 1) * sizeof(char));
#endif
			}
		}

		__int32	i = 0, j = 0;
		while  (ifcFileName[i]) {
			if	(ifcFileName[i++] == '\\') {
				j = i;
			}
		}

#ifdef UNICODE
		_itow_s(1900 + tInfo.tm_year, &timeStamp[0], 512, 10);
		_itow_s(100 + 1 + tInfo.tm_mon, &timeStamp[4], 512-4, 10);
		_itow_s(100 + tInfo.tm_mday, &timeStamp[7], 512-7, 10);
#else
		_itoa_s(1900 + tInfo.tm_year, &timeStamp[0], 512, 10);
		_itoa_s(100 + 1 + tInfo.tm_mon, &timeStamp[4], 512-4, 10);
		_itoa_s(100 + tInfo.tm_mday, &timeStamp[7], 512-7, 10);
#endif
		timeStamp[4] = '-';
		timeStamp[7] = '-';
#ifdef UNICODE
		_itow_s(100 + tInfo.tm_hour, &timeStamp[10], 512-10, 10);
		_itow_s(100 + tInfo.tm_min, &timeStamp[13], 512-13, 10);
		_itow_s(100 + tInfo.tm_sec, &timeStamp[16], 512-16, 10);
#else
		_itoa_s(100 + tInfo.tm_hour, &timeStamp[10], 512-10, 10);
		_itoa_s(100 + tInfo.tm_min, &timeStamp[13], 512-13, 10);
		_itoa_s(100 + tInfo.tm_sec, &timeStamp[16], 512-16, 10);
#endif
		timeStamp[10] = 'T';
		timeStamp[13] = ':';
		timeStamp[16] = ':';
		timeStamp[19] = 0;

#ifdef UNICODE
		//	set Description
		SetSPFFHeaderItem(ifcModel, 0, 0, sdaiUNICODE, (char*) description);
		SetSPFFHeaderItem(ifcModel, 0, 1, sdaiSTRING, 0);
		//	set Implementation Level
		SetSPFFHeaderItem(ifcModel, 1, 0, sdaiSTRING, "2;1");
		//	set Name
		SetSPFFHeaderItem(ifcModel, 2, 0, sdaiUNICODE, (char*) &ifcFileName[j]);
		//	set Time Stamp
		SetSPFFHeaderItem(ifcModel, 3, 0, sdaiUNICODE, (char*) &timeStamp[0]);
		//	set	Author
		SetSPFFHeaderItem(ifcModel, 4, 0, sdaiSTRING, "Architect");
		SetSPFFHeaderItem(ifcModel, 4, 1, sdaiSTRING, 0);
		//	set Organization
		SetSPFFHeaderItem(ifcModel, 5, 0, sdaiSTRING, "Building Designer Office");
		//	set Preprocessor Version
		SetSPFFHeaderItem(ifcModel, 6, 0, sdaiSTRING, "IFC Engine DLL 2015");
		//	set Originating System
		SetSPFFHeaderItem(ifcModel, 7, 0, sdaiSTRING, "Hello Wall example");
		//	set Authorization
		SetSPFFHeaderItem(ifcModel, 8, 0, sdaiSTRING, "The authorising person");
		//	set File Schema
//SetSPFFHeaderItem(ifcModel, 9, 0, sdaiSTRING, "IFC4");
		SetSPFFHeaderItem(ifcModel, 9, 0, sdaiSTRING, "IFC2X3"); 
		SetSPFFHeaderItem(ifcModel, 9, 1, sdaiSTRING, 0);
#else
		//	set Description
		SetSPFFHeaderItem(ifcModel, 0, 0, sdaiSTRING, description);
		SetSPFFHeaderItem(ifcModel, 0, 1, sdaiSTRING, 0);
		//	set Implementation Level
		SetSPFFHeaderItem(ifcModel, 1, 0, sdaiSTRING, "2;1");
		//	set Name
		SetSPFFHeaderItem(ifcModel, 2, 0, sdaiSTRING, &ifcFileName[j]);
		//	set Time Stamp
		SetSPFFHeaderItem(ifcModel, 3, 0, sdaiSTRING, &timeStamp[0]);
		//	set	Author
		SetSPFFHeaderItem(ifcModel, 4, 0, sdaiSTRING, "Architect");
		SetSPFFHeaderItem(ifcModel, 4, 1, sdaiSTRING, 0);
		//	set Organization
		SetSPFFHeaderItem(ifcModel, 5, 0, sdaiSTRING, "Building Designer Office");
		//	set Preprocessor Version
		SetSPFFHeaderItem(ifcModel, 6, 0, sdaiSTRING, "IFC Engine DLL 2015");
		//	set Originating System
		SetSPFFHeaderItem(ifcModel, 7, 0, sdaiSTRING, "Hello Wall example");
		//	set Authorization
		SetSPFFHeaderItem(ifcModel, 8, 0, sdaiSTRING, "The authorising person");
		//	set File Schema
//SetSPFFHeaderItem(ifcModel, 9, 0, sdaiSTRING, "IFC4");
		SetSPFFHeaderItem(ifcModel, 9, 0, sdaiSTRING, "IFC2X3");
		SetSPFFHeaderItem(ifcModel, 9, 1, sdaiSTRING, 0);
#endif

		if	(saveIfcXML) {
			saveIfcFileAsXml(ifcFileName);
		} else {
			saveIfcFile(ifcFileName);
		}
	} else {
#ifdef UNICODE
		MessageBoxW(L"Model could not be instantiated, probably it cannot find the schema file.");
#else
		MessageBox("Model could not be instantiated, probably it cannot find the schema file.");
#endif
	}
	
	CDialog::OnOK();
}

void	CHelloWallDlg::EnableProperties()
{
	if	( (m_Wall.IsWindowEnabled())  &&
		  (m_Wall.GetCheck()) ) {
		m_Static00.EnableWindow(true);
		m_Static10.EnableWindow(true);
		m_Static20.EnableWindow(true);

		m_WallWidth.EnableWindow(true);
		m_WallThickness.EnableWindow(true);
		m_WallHeight.EnableWindow(true);

		m_Static01.EnableWindow(true);
		m_Static11.EnableWindow(true);
		m_Static21.EnableWindow(true);
	} else {
		m_Static00.EnableWindow(false);
		m_Static10.EnableWindow(false);
		m_Static20.EnableWindow(false);

		m_WallWidth.EnableWindow(false);
		m_WallThickness.EnableWindow(false);
		m_WallHeight.EnableWindow(false);

		m_Static01.EnableWindow(false);
		m_Static11.EnableWindow(false);
		m_Static21.EnableWindow(false);
	}

	if	( (m_Opening.IsWindowEnabled())  &&
		  (m_Opening.GetCheck()) ) {
		m_Static30.EnableWindow(true);
		m_Static40.EnableWindow(true);
		m_Static50.EnableWindow(true);
		m_Static60.EnableWindow(true);

		m_OpeningWidth.EnableWindow(true);
		m_OpeningHeight.EnableWindow(true);
		m_OpeningXOffset.EnableWindow(true);
		m_OpeningZOffset.EnableWindow(true);

		m_Static31.EnableWindow(true);
		m_Static41.EnableWindow(true);
		m_Static51.EnableWindow(true);
		m_Static61.EnableWindow(true);
	} else {
		m_Static30.EnableWindow(false);
		m_Static40.EnableWindow(false);
		m_Static50.EnableWindow(false);
		m_Static60.EnableWindow(false);

		m_OpeningWidth.EnableWindow(false);
		m_OpeningHeight.EnableWindow(false);
		m_OpeningXOffset.EnableWindow(false);
		m_OpeningZOffset.EnableWindow(false);

		m_Static31.EnableWindow(false);
		m_Static41.EnableWindow(false);
		m_Static51.EnableWindow(false);
		m_Static61.EnableWindow(false);
	}

	if	( (m_Window.IsWindowEnabled())  &&
		  (m_Window.GetCheck()) ) {
		m_Static50.EnableWindow(true);
		m_Static60.EnableWindow(true);
		m_Static70.EnableWindow(true);
		m_Static80.EnableWindow(true);

		m_OpeningWidth.EnableWindow(true);
		m_WindowThickness.EnableWindow(true);
		m_OpeningHeight.EnableWindow(true);
		m_WindowYOffset.EnableWindow(true);

		m_Static51.EnableWindow(true);
		m_Static61.EnableWindow(true);
		m_Static71.EnableWindow(true);
		m_Static81.EnableWindow(true);
	} else {
		m_Static70.EnableWindow(false);
		m_Static80.EnableWindow(false);

		m_WindowThickness.EnableWindow(false);
		m_WindowYOffset.EnableWindow(false);

		m_Static71.EnableWindow(false);
		m_Static81.EnableWindow(false);
	}
}

void	CHelloWallDlg::OnCheckWall() 
{
	if	(m_Wall.GetCheck()) {
		m_Wall_Name.EnableWindow(true);
		m_Static_0_Name.EnableWindow(true);
		m_Static_0_0.EnableWindow(true);
		if	(view == COORDINATIONVIEW) {
			GetDlgItem(IDC_RADIO_0_1)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_0_2)->EnableWindow(true);
		} else {
			ASSERT(view == PRESENTATIONVIEW);
			GetDlgItem(IDC_RADIO_0_1)->EnableWindow(false);
			GetDlgItem(IDC_RADIO_0_2)->EnableWindow(true);
			OnRadio_0_2();
		}

		if	(!GetCheckedRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_1)) {
			m_Static_0_1.EnableWindow(true);
			m_WallBasicRepr.EnableWindow(true);
		}

		m_Opening.EnableWindow(true);
		OnCheckOpening();
	} else {
		m_Wall_Name.EnableWindow(false);
		m_Static_0_Name.EnableWindow(false);
		m_Static_0_0.EnableWindow(false);
		GetDlgItem(IDC_RADIO_0_1)->EnableWindow(false);
		GetDlgItem(IDC_RADIO_0_2)->EnableWindow(false);

		m_Static_0_1.EnableWindow(false);
		m_WallBasicRepr.EnableWindow(false);

		m_Opening.EnableWindow(false);
		m_Opening_Name.EnableWindow(false);
		m_Static_1_Name.EnableWindow(false);
		m_Static_1_0.EnableWindow(false);
		GetDlgItem(IDC_RADIO_1_1)->EnableWindow(false);
		GetDlgItem(IDC_RADIO_1_2)->EnableWindow(false);

		m_Static_1_1.EnableWindow(false);
		m_OpeningBasicRepr.EnableWindow(false);

		m_Window.EnableWindow(true);
		OnCheckWindow();
	}

	EnableProperties();
}

void	CHelloWallDlg::OnCheckOpening() 
{
	if	(m_Opening.GetCheck()) {
		m_Opening_Name.EnableWindow(true);
		m_Static_1_Name.EnableWindow(true);
		if	(view == COORDINATIONVIEW) {
			m_Static_1_0.EnableWindow(true);

			GetDlgItem(IDC_RADIO_1_1)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_1_2)->EnableWindow(true);

			if	(!GetCheckedRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_1)) {
				m_Static_1_1.EnableWindow(true);
				m_OpeningBasicRepr.EnableWindow(true);
			}
		} else {
			ASSERT(view == PRESENTATIONVIEW);
			m_Static_1_0.EnableWindow(false);

			GetDlgItem(IDC_RADIO_1_1)->EnableWindow(false);
			GetDlgItem(IDC_RADIO_1_2)->EnableWindow(false);

			m_Static_1_1.EnableWindow(false);
			m_OpeningBasicRepr.EnableWindow(false);
		}

		m_Window.EnableWindow(true);
		OnCheckWindow();
	} else {
		m_Opening_Name.EnableWindow(false);
		m_Static_1_Name.EnableWindow(false);
		m_Static_1_0.EnableWindow(false);
		GetDlgItem(IDC_RADIO_1_1)->EnableWindow(false);
		GetDlgItem(IDC_RADIO_1_2)->EnableWindow(false);

		m_Static_1_1.EnableWindow(false);
		m_OpeningBasicRepr.EnableWindow(false);

		m_Window.EnableWindow(false);
		m_Window_Name.EnableWindow(false);
		m_Static_2_Name.EnableWindow(false);
		m_Static_2_0.EnableWindow(false);
		GetDlgItem(IDC_RADIO_2_1)->EnableWindow(false);
		GetDlgItem(IDC_RADIO_2_2)->EnableWindow(false);

		m_Static_2_1.EnableWindow(false);
		m_WindowBasicRepr.EnableWindow(false);
	}

	EnableProperties();
}

void	CHelloWallDlg::OnCheckWindow() 
{
	if	(m_Window.GetCheck()) {
		m_Window_Name.EnableWindow(true);
		m_Static_2_Name.EnableWindow(true);
		m_Static_2_0.EnableWindow(true);
		if	(view == COORDINATIONVIEW) {
			GetDlgItem(IDC_RADIO_2_1)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_2_2)->EnableWindow(true);
		} else {
			ASSERT(view == PRESENTATIONVIEW);
			GetDlgItem(IDC_RADIO_2_1)->EnableWindow(false);
			GetDlgItem(IDC_RADIO_2_2)->EnableWindow(true);
			OnRadio_2_2();
		}

		if	(!GetCheckedRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_1)) {
			m_Static_2_1.EnableWindow(true);
			m_WindowBasicRepr.EnableWindow(true);
		}
	} else {
		m_Window_Name.EnableWindow(false);
		m_Static_2_Name.EnableWindow(false);
		m_Static_2_0.EnableWindow(false);
		GetDlgItem(IDC_RADIO_2_1)->EnableWindow(false);
		GetDlgItem(IDC_RADIO_2_2)->EnableWindow(false);

		m_Static_2_1.EnableWindow(false);
		m_WindowBasicRepr.EnableWindow(false);
	}

	EnableProperties();
}

void	CHelloWallDlg::OnRadio_View_0() 
{
	view = COORDINATIONVIEW;
	CheckRadioButton(IDC_RADIO_VIEW_0, IDC_RADIO_VIEW_1, IDC_RADIO_VIEW_0);

	OnCheckWall();
	OnCheckOpening();
	OnCheckWindow();
}

void	CHelloWallDlg::OnRadio_View_1() 
{
	view = PRESENTATIONVIEW;
	CheckRadioButton(IDC_RADIO_VIEW_0, IDC_RADIO_VIEW_1, IDC_RADIO_VIEW_1);

	OnCheckWall();
	OnCheckOpening();
	OnCheckWindow();
}

void	CHelloWallDlg::OnRadio_0_1() 
{
	CheckRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_2, IDC_RADIO_0_1);
	m_Static_0_1.EnableWindow(true);
	m_WallBasicRepr.EnableWindow(true);
}

void	CHelloWallDlg::OnRadio_0_2() 
{
	CheckRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_2, IDC_RADIO_0_2);
	m_Static_0_1.EnableWindow(true);
	m_WallBasicRepr.EnableWindow(true);
}

void	CHelloWallDlg::OnRadio_1_1() 
{
	CheckRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_2, IDC_RADIO_1_1);
	m_Static_1_1.EnableWindow(true);
	m_OpeningBasicRepr.EnableWindow(true);
}

void	CHelloWallDlg::OnRadio_1_2() 
{
	CheckRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_2, IDC_RADIO_1_2);
	m_Static_1_1.EnableWindow(true);
	m_OpeningBasicRepr.EnableWindow(true);
}

void	CHelloWallDlg::OnRadio_2_1() 
{
	CheckRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_2, IDC_RADIO_2_1);
	m_Static_2_1.EnableWindow(true);
	m_WindowBasicRepr.EnableWindow(true);
}

void	CHelloWallDlg::OnRadio_2_2() 
{
	CheckRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_2, IDC_RADIO_2_2);
	m_Static_2_1.EnableWindow(true);
	m_WindowBasicRepr.EnableWindow(true);
}

bool	CHelloWallDlg::CheckWallAndWindowMeasuresNotSupported() 
{
	__int32	wallHeight, wallWidth,
			openingHeight, openingWidth, openingXOffset, openingZOffset;
#ifdef UNICODE
	wchar_t	buffer[512];

	m_WallHeight.GetWindowTextW(buffer, 512);
	wallHeight = _wtoi(buffer);
	m_WallWidth.GetWindowTextW(buffer, 512);
	wallWidth = _wtoi(buffer);
	m_OpeningHeight.GetWindowTextW(buffer, 512);
	openingHeight = _wtoi(buffer);
	m_OpeningWidth.GetWindowTextW(buffer, 512);
	openingWidth = _wtoi(buffer);
	m_OpeningXOffset.GetWindowTextW(buffer, 512);
	openingXOffset = _wtoi(buffer);
	m_OpeningZOffset.GetWindowTextW(buffer, 512);
	openingZOffset = _wtoi(buffer);
#else
	char	buffer[512];

	m_WallHeight.GetWindowText(buffer, 512);
	wallHeight = atoi(buffer);
	m_WallWidth.GetWindowText(buffer, 512);
	wallWidth = atoi(buffer);
	m_OpeningHeight.GetWindowText(buffer, 512);
	openingHeight = atoi(buffer);
	m_OpeningWidth.GetWindowText(buffer, 512);
	openingWidth = atoi(buffer);
	m_OpeningXOffset.GetWindowText(buffer, 512);
	openingXOffset = atoi(buffer);
	m_OpeningZOffset.GetWindowText(buffer, 512);
	openingZOffset = atoi(buffer);
#endif

	if	( (openingXOffset <= 0)  ||
			(openingXOffset + openingWidth >= wallWidth)  ||
			(openingZOffset <= 0)  ||
			(openingZOffset + openingHeight >= wallHeight) ) {
#ifdef UNICODE
		MessageBoxW(L"The opening is not placed totaly within the wall, this variant is not supported by this software in Presentation View. Please change values.", L"Program incompatibility error", IDOK);
#else
		MessageBox("The opening is not placed totaly within the wall, this variant is not supported by this software in Presentation View. Please change values.", "Program incompatibility error", IDOK);
#endif
		return	true;
	}

	return	false;
}

void	CHelloWallDlg::OnIfc() 
{
	if	( (view == PRESENTATIONVIEW)  &&  (m_Opening.IsWindowEnabled()) ) {
		if	(CheckWallAndWindowMeasuresNotSupported()) {
			return;
		}
	}

	OnOK();
}

void	CHelloWallDlg::OnIfx() 
{
	//
	//	Check if the opening is easy enough for this program to generate in Presentation View
	//
	if	( (view == PRESENTATIONVIEW)  &&  (m_Opening.IsWindowEnabled()) ) {
		if	(CheckWallAndWindowMeasuresNotSupported()) {
			return;
		}
	}

	saveIfcXML = true;

#ifdef UNICODE
	m_FileName.GetWindowTextW(ifcFileName, 512);
	size_t	i = wcslen(ifcFileName);
#else
	m_FileName.GetWindowText(ifcFileName, 512);
	size_t	i = strlen(ifcFileName);
#endif

	if	( (ifcFileName[i-4] == '.')  &&
			(ifcFileName[i-3] == 'i'  ||  ifcFileName[i-3] == 'I')  &&
			(ifcFileName[i-2] == 'f'  ||  ifcFileName[i-2] == 'F')  &&
			(ifcFileName[i-1] == 'c'  ||  ifcFileName[i-1] == 'C') ) {
		ifcFileName[i] = ifcFileName[i-1] + 'x' - 'c';
		ifcFileName[i+1] = ifcFileName[i-1] + 'm' - 'c';
		ifcFileName[i+2] = ifcFileName[i-1] + 'l' - 'c';
		ifcFileName[i+3] = 0;
		m_FileName.SetWindowText(ifcFileName);
	}

	OnOK();
}
