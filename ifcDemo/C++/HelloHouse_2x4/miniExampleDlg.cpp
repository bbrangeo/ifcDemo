////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  Date:    31 July 2010
//  Project: IFC Engine Series (example using DLL)
//
//  This code may be used and edited freely,
//  also for commercial projects in open and closed source software
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:	peter.bonsma@tno.nl
//
//  more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//									pim.vandenhelm@tno.nl
//								    peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////




#include "stdafx.h"
#include "propertiesIfc.h"
#include "BRepIfc.h"
#include "miniExample.h"
#include "miniExampleDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define     COORDINATIONVIEW    0
#define     PRESENTATIONVIEW    1
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

extern  char    * ifcSchemaName, * ifcFileName;
bool    saveIfx = false;
int     view;

CBitmap imgLevelIRooms, imgLevelIIRooms, imgLevelIWalls, imgLevelIIWalls,
		imgLevelISpaceBoundaries, imgLevelIISpaceBoundaries, imgLevelISpaceBoundaryNos, imgLevelIISpaceBoundaryNos;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiniExampleDlg dialog

CMiniExampleDlg::CMiniExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiniExampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiniExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiniExampleDlg)
	DDX_Control(pDX, IDC_STATIC_IMG_II, m_ImageII);
	DDX_Control(pDX, IDC_STATIC_IMG_I, m_ImageI);
	DDX_Control(pDX, IDC_EDIT_OUTER_HEIGHT, m_Height);
	DDX_Control(pDX, IDC_EDIT_INNER_DELTA, m_Delta);
	DDX_Control(pDX, IDC_EDIT_OUTER_WALL_THICKNESS, m_OuterWallThickness);
	DDX_Control(pDX, IDC_EDIT_WINDOW_ZOFFSET, m_WindowZOffset);
	DDX_Control(pDX, IDC_EDIT_WINDOW_WIDTH, m_WindowWidth);
	DDX_Control(pDX, IDC_EDIT_WINDOW_HEIGHT_, m_WindowHeight);
	DDX_Control(pDX, IDC_EDIT_INNER_WALL_THICKNESS, m_InnerWallThickness);
	DDX_Control(pDX, IDC_EDIT_DOOR_WIDTH, m_DoorWidth);
	DDX_Control(pDX, IDC_EDIT_ROOM_II_WIDTH, m_RoomIIWidth);
	DDX_Control(pDX, IDC_EDIT_ROOM_II_DEPTH, m_RoomIIDepth);
	DDX_Control(pDX, IDC_EDIT_ROOM_I_WIDTH, m_RoomIWidth);
	DDX_Control(pDX, IDC_EDIT_ROOM_I_DEPTH, m_RoomIDepth);
	DDX_Control(pDX, IDC_EDIT_DOOR_HEIGHT, m_DoorHeight);
	DDX_Control(pDX, IDC_CHECK_METERS, m_ResultsAsMeters);
	DDX_Control(pDX, IDC_CHECK_QUANTITIES, m_Quantities);
	DDX_Control(pDX, IDC_STATIC_0_NAME, m_Static_0_Name);
	DDX_Control(pDX, IDC_EDIT_SCHEMA_NAME, m_SchemaName);
	DDX_Control(pDX, IDC_EDIT_FILE_NAME, m_FileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMiniExampleDlg, CDialog)
	//{{AFX_MSG_MAP(CMiniExampleDlg)
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
	ON_BN_CLICKED(IDC_ShowWalls, OnShowWalls)
	ON_BN_CLICKED(IDC_ShowRooms, OnShowRooms)
	ON_BN_CLICKED(IDC_ShowSBs, OnShowSBs)
	ON_BN_CLICKED(IDC_ShowSBs2, OnShowSBs2)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_DOOR_WIDTH, &CMiniExampleDlg::OnEnChangeEditDoorWidth)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiniExampleDlg message handlers

BOOL CMiniExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
		
    m_FileName.SetWindowText(ifcFileName);
    m_SchemaName.SetWindowText(ifcSchemaName);

//    m_Wall_Name.SetWindowText("Wall xyz");
//    m_Opening_Name.SetWindowText("Opening Element xyz");
//    m_Window_Name.SetWindowText("Window xyz");

/*    m_WallThickness.SetWindowText("300");
    m_WallWidth.SetWindowText("5000");
    m_WallHeight.SetWindowText("2300");
    m_OpeningHeight.SetWindowText("1400");
    m_OpeningWidth.SetWindowText("750");
    m_OpeningXOffset.SetWindowText("900");
    m_OpeningZOffset.SetWindowText("250");
    m_WindowThickness.SetWindowText("190");
    m_WindowYOffset.SetWindowText("12");
*/
	m_RoomIWidth.SetWindowText("3500");
	m_RoomIDepth.SetWindowText("4500");
	m_RoomIIWidth.SetWindowText("3000");
	m_RoomIIDepth.SetWindowText("2200");

	m_DoorWidth.SetWindowText("930");
	m_DoorHeight.SetWindowText("2100");

	m_WindowWidth.SetWindowText("600");
	m_WindowHeight.SetWindowText("1400");
	m_WindowZOffset.SetWindowText("700");

	m_InnerWallThickness.SetWindowText("80");
	m_OuterWallThickness.SetWindowText("300");
	m_Delta.SetWindowText("1150");
	m_Height.SetWindowText("2800");

    OnRadio_View_0();

    OnRadio_0_2();
    OnRadio_1_2();
    OnRadio_2_2();

/*    m_Wall.SetCheck(1);
    m_WallBasicRepr.SetCheck(1);
    m_Opening.SetCheck(1);
    m_OpeningBasicRepr.SetCheck(1);
    m_Window.SetCheck(1);
    m_WindowBasicRepr.SetCheck(1);
*/
    OnCheckWindow();
    OnCheckOpening();
    OnCheckWall();

    m_Quantities.SetCheck(true);
	
	imgLevelIRooms.LoadBitmap(IDB_BITMAP1);
	imgLevelIIRooms.LoadBitmap(IDB_BITMAP2);
	imgLevelIWalls.LoadBitmap(IDB_BITMAP3);
	imgLevelIIWalls.LoadBitmap(IDB_BITMAP4);
	imgLevelISpaceBoundaries.LoadBitmap(IDB_BITMAP5);
	imgLevelIISpaceBoundaries.LoadBitmap(IDB_BITMAP6);
	imgLevelISpaceBoundaryNos.LoadBitmap(IDB_BITMAP7);
	imgLevelIISpaceBoundaryNos.LoadBitmap(IDB_BITMAP8);

	return  true;
}

void CMiniExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMiniExampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMiniExampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//void   localCreatePolygonStructureForSquare

point2DStruct  * create2DPoint(point2DStruct ** pPoint, double x, double y)
{
    (* pPoint) = new point2DStruct();
    (* pPoint)->x = x;
    (* pPoint)->y = y;

    return  (* pPoint);
}

point3DStruct  * create3DPoint(point3DStruct ** pPoint, double x, double y, double z)
{
    (* pPoint) = new point3DStruct();
    (* pPoint)->x = x;
    (* pPoint)->y = y;
    (* pPoint)->z = z;
    (* pPoint)->ifcCartesianPointInstance = 0;

    return  (* pPoint);
}

polygon2DStruct * localCreatePolygonStructureFor_(int left, int right, double length, double thickness)
{
    polygon2DStruct * pPolygon;

    pPolygon = new polygon2DStruct();
	pPolygon->pVector = new vector2DStruct();
    pPolygon->pVector->pPoint = new point2DStruct();
	pPolygon->pVector->pPoint->x = -left * thickness * 0.5;
	pPolygon->pVector->pPoint->y = -thickness * 0.5;
    pPolygon->pVector->next = new vector2DStruct();
    pPolygon->pVector->next->pPoint = new point2DStruct();
    pPolygon->pVector->next->pPoint->x = left * thickness * 0.5;
    pPolygon->pVector->next->pPoint->y = thickness * 0.5;
    pPolygon->pVector->next->next = new vector2DStruct();
    pPolygon->pVector->next->next->pPoint = new point2DStruct();
    pPolygon->pVector->next->next->pPoint->x = length + right * thickness * 0.5;
    pPolygon->pVector->next->next->pPoint->y = thickness * 0.5;
    pPolygon->pVector->next->next->next = new vector2DStruct();
    pPolygon->pVector->next->next->next->pPoint = new point2DStruct();
    pPolygon->pVector->next->next->next->pPoint->x = length - right * thickness * 0.5;
    pPolygon->pVector->next->next->next->pPoint->y = -thickness * 0.5;
    pPolygon->pVector->next->next->next->next = 0;

    return  pPolygon;
}

polygon2DStruct * localCreatePolygonStructureForSquare(double min_x, double min_y, double max_x, double max_y)
{
    polygon2DStruct * pPolygon;

    pPolygon = new polygon2DStruct();
    pPolygon->pVector = new vector2DStruct();
    pPolygon->pVector->pPoint = new point2DStruct();
    pPolygon->pVector->pPoint->x = min_x;
    pPolygon->pVector->pPoint->y = min_y;
    pPolygon->pVector->next = new vector2DStruct();
    pPolygon->pVector->next->pPoint = new point2DStruct();
    pPolygon->pVector->next->pPoint->x = min_x;
    pPolygon->pVector->next->pPoint->y = max_y;
    pPolygon->pVector->next->next = new vector2DStruct();
    pPolygon->pVector->next->next->pPoint = new point2DStruct();
    pPolygon->pVector->next->next->pPoint->x = max_x;
    pPolygon->pVector->next->next->pPoint->y = max_y;
    pPolygon->pVector->next->next->next = new vector2DStruct();
    pPolygon->pVector->next->next->next->pPoint = new point2DStruct();
    pPolygon->pVector->next->next->next->pPoint->x = max_x;
    pPolygon->pVector->next->next->next->pPoint->y = min_y;
    pPolygon->pVector->next->next->next->next = 0;

    return  pPolygon;
}

polygon3DStruct * create3DPolygonWith4Vectors(polygon3DStruct ** pPolygon, point3DStruct * pPointI, point3DStruct * pPointII, point3DStruct * pPointIII, point3DStruct * pPointIV)
{
    vector3DStruct  * pVector;

    pVector = new vector3DStruct();
    pVector->pPoint = pPointI;
    pVector->next = new vector3DStruct();
    pVector->next->pPoint = pPointII;
    pVector->next->next = new vector3DStruct();
    pVector->next->next->pPoint = pPointIII;
    pVector->next->next->next = new vector3DStruct();
    pVector->next->next->next->pPoint = pPointIV;
    pVector->next->next->next->next = NULL;

    (* pPolygon) = new polygon3DStruct();
    (* pPolygon)->pVector = pVector;
    (* pPolygon)->pOpeningVector = NULL;
    (* pPolygon)->next = NULL;

    return  (* pPolygon);
}

void    add3DPolygonOpeningWith4Vectors(polygon3DStruct * polygon, point3DStruct * pPointI, point3DStruct * pPointII, point3DStruct * pPointIII, point3DStruct * pPointIV)
{
    vector3DStruct  * pVector;

    pVector = new vector3DStruct();
    pVector->pPoint = pPointI;
    pVector->next = new vector3DStruct();
    pVector->next->pPoint = pPointII;
    pVector->next->next = new vector3DStruct();
    pVector->next->next->pPoint = pPointIII;
    pVector->next->next->next = new vector3DStruct();
    pVector->next->next->next->pPoint = pPointIV;
    pVector->next->next->next->next = NULL;

    polygon->pOpeningVector = pVector;
}

polygon2DStruct * create2DPolygonWith6Vectors(polygon2DStruct ** pPolygon, point2DStruct * pPointI, point2DStruct * pPointII, point2DStruct * pPointIII, point2DStruct * pPointIV, point2DStruct * pPointV, point2DStruct * pPointVI)
{
    vector2DStruct  * pVector;

    pVector = new vector2DStruct();
    pVector->pPoint = pPointI;
    pVector->next = new vector2DStruct();
    pVector->next->pPoint = pPointII;
    pVector->next->next = new vector2DStruct();
    pVector->next->next->pPoint = pPointIII;
    pVector->next->next->next = new vector2DStruct();
    pVector->next->next->next->pPoint = pPointIV;
    pVector->next->next->next->next = new vector2DStruct();
    pVector->next->next->next->next->pPoint = pPointV;
    pVector->next->next->next->next->next = new vector2DStruct();
    pVector->next->next->next->next->next->pPoint = pPointVI;
    pVector->next->next->next->next->next->next = NULL;

    (* pPolygon) = new polygon2DStruct();
    (* pPolygon)->pVector = pVector;
    //(* pPolygon)->pOpeningVector = NULL;
    (* pPolygon)->next = NULL;

    return  (* pPolygon);
}

polygon2DStruct * create2DPolygonWith8Vectors(polygon2DStruct ** pPolygon, point2DStruct * pPointI, point2DStruct * pPointII, point2DStruct * pPointIII, point2DStruct * pPointIV, point2DStruct * pPointV, point2DStruct * pPointVI, point2DStruct * pPointVII, point2DStruct * pPointVIII)
{
    vector2DStruct  * pVector;

    pVector = new vector2DStruct();
    pVector->pPoint = pPointI;
    pVector->next = new vector2DStruct();
    pVector->next->pPoint = pPointII;
    pVector->next->next = new vector2DStruct();
    pVector->next->next->pPoint = pPointIII;
    pVector->next->next->next = new vector2DStruct();
    pVector->next->next->next->pPoint = pPointIV;
    pVector->next->next->next->next = new vector2DStruct();
    pVector->next->next->next->next->pPoint = pPointV;
    pVector->next->next->next->next->next = new vector2DStruct();
    pVector->next->next->next->next->next->pPoint = pPointVI;
    pVector->next->next->next->next->next->next = new vector2DStruct();
    pVector->next->next->next->next->next->next->pPoint = pPointVII;
    pVector->next->next->next->next->next->next->next = new vector2DStruct();
    pVector->next->next->next->next->next->next->next->pPoint = pPointVIII;
    pVector->next->next->next->next->next->next->next->next = NULL;

    (* pPolygon) = new polygon2DStruct();
    (* pPolygon)->pVector = pVector;
    //(* pPolygon)->pOpeningVector = NULL;
    (* pPolygon)->next = NULL;

    return  (* pPolygon);
}

shellStruct * localCreateShellStructureForCuboid(double min_x, double min_y, double min_z, double max_x, double max_y, double max_z)
{
    point3DStruct   * pPoints[8];
    polygon3DStruct * pPolygons[6];
    shellStruct     * pShell;

    create3DPoint(&pPoints[0], min_x, min_y, min_z);
    create3DPoint(&pPoints[1], max_x, min_y, min_z);
    create3DPoint(&pPoints[2], min_x, max_y, min_z);
    create3DPoint(&pPoints[3], max_x, max_y, min_z);
    create3DPoint(&pPoints[4], min_x, min_y, max_z);
    create3DPoint(&pPoints[5], max_x, min_y, max_z);
    create3DPoint(&pPoints[6], min_x, max_y, max_z);
    create3DPoint(&pPoints[7], max_x, max_y, max_z);

    pShell = new shellStruct();
    pShell->pPolygon = create3DPolygonWith4Vectors(&pPolygons[0], pPoints[0], pPoints[2], pPoints[3], pPoints[1]);
    pShell->next = NULL;

    pPolygons[0]->next = create3DPolygonWith4Vectors(&pPolygons[1], pPoints[4], pPoints[5], pPoints[7], pPoints[6]);
    pPolygons[1]->next = create3DPolygonWith4Vectors(&pPolygons[2], pPoints[0], pPoints[4], pPoints[6], pPoints[2]);
    pPolygons[2]->next = create3DPolygonWith4Vectors(&pPolygons[3], pPoints[2], pPoints[6], pPoints[7], pPoints[3]);
    pPolygons[3]->next = create3DPolygonWith4Vectors(&pPolygons[4], pPoints[3], pPoints[7], pPoints[5], pPoints[1]);
    pPolygons[4]->next = create3DPolygonWith4Vectors(&pPolygons[5], pPoints[1], pPoints[5], pPoints[4], pPoints[0]);

    return  pShell;
}

shellStruct * localCreateShellStructureForCuboidWithOpening(double min_x, double min_y, double min_z, double max_x, double max_y, double max_z, double min_x_opening, double min_z_opening, double max_x_opening, double max_z_opening)
{
    point3DStruct   * pPoints[16];
    polygon3DStruct * pPolygons[10];
    shellStruct     * pShell;

    create3DPoint(&pPoints[0], min_x, min_y, min_z);
    create3DPoint(&pPoints[1], max_x, min_y, min_z);
    create3DPoint(&pPoints[2], min_x, max_y, min_z);
    create3DPoint(&pPoints[3], max_x, max_y, min_z);
    create3DPoint(&pPoints[4], min_x, min_y, max_z);
    create3DPoint(&pPoints[5], max_x, min_y, max_z);
    create3DPoint(&pPoints[6], min_x, max_y, max_z);
    create3DPoint(&pPoints[7], max_x, max_y, max_z);
    create3DPoint(&pPoints[8], min_x_opening, min_y, min_z_opening);
    create3DPoint(&pPoints[9], max_x_opening, min_y, min_z_opening);
    create3DPoint(&pPoints[10], min_x_opening, max_y, min_z_opening);
    create3DPoint(&pPoints[11], max_x_opening, max_y, min_z_opening);
    create3DPoint(&pPoints[12], min_x_opening, min_y, max_z_opening);
    create3DPoint(&pPoints[13], max_x_opening, min_y, max_z_opening);
    create3DPoint(&pPoints[14], min_x_opening, max_y, max_z_opening);
    create3DPoint(&pPoints[15], max_x_opening, max_y, max_z_opening);

    pShell = new shellStruct();
    pShell->pPolygon = create3DPolygonWith4Vectors(&pPolygons[0], pPoints[0], pPoints[2], pPoints[3], pPoints[1]);
    pShell->next = NULL;
    pPolygons[0]->next = create3DPolygonWith4Vectors(&pPolygons[1], pPoints[4], pPoints[5], pPoints[7], pPoints[6]);
    pPolygons[1]->next = create3DPolygonWith4Vectors(&pPolygons[2], pPoints[0], pPoints[4], pPoints[6], pPoints[2]);
    pPolygons[2]->next = create3DPolygonWith4Vectors(&pPolygons[3], pPoints[2], pPoints[6], pPoints[7], pPoints[3]);
    pPolygons[3]->next = create3DPolygonWith4Vectors(&pPolygons[4], pPoints[3], pPoints[7], pPoints[5], pPoints[1]);
    pPolygons[4]->next = create3DPolygonWith4Vectors(&pPolygons[5], pPoints[1], pPoints[5], pPoints[4], pPoints[0]);

    pPolygons[5]->next = create3DPolygonWith4Vectors(&pPolygons[6], pPoints[0+8], pPoints[1+8], pPoints[3+8], pPoints[2+8]);
    pPolygons[6]->next = create3DPolygonWith4Vectors(&pPolygons[7], pPoints[4+8], pPoints[6+8], pPoints[7+8], pPoints[5+8]);
    pPolygons[7]->next = create3DPolygonWith4Vectors(&pPolygons[8], pPoints[0+8], pPoints[2+8], pPoints[6+8], pPoints[4+8]);
    pPolygons[8]->next = create3DPolygonWith4Vectors(&pPolygons[9], pPoints[3+8], pPoints[1+8], pPoints[5+8], pPoints[7+8]);

    add3DPolygonOpeningWith4Vectors(pPolygons[3], pPoints[2+8], pPoints[3+8], pPoints[7+8], pPoints[6+8]);
    add3DPolygonOpeningWith4Vectors(pPolygons[5], pPoints[1+8], pPoints[0+8], pPoints[4+8], pPoints[5+8]);

    return  pShell;
}

void CMiniExampleDlg::OnOK() 
{
/*    polygon2DStruct * pPolygon;
    shellStruct     * pShell;
    int     ifcWallInstance, ifcOpeningElementInstance, ifcWindowInstance;
    double  wallHeight, wallWidth, wallThickness,
            openingHeight, openingWidth, openingXOffset, openingZOffset,
            windowThickness, windowYOffset,
            linearConversionFactor;
    char    ifcFileName[512], ifcSchemaName[512], buffer[512], * lengthUnitConversion = NULL,
            wallName[512], openingName[512], windowName[512];
    bool    objectsWillBeAdded;
    
    m_FileName.GetWindowText(ifcFileName, 512);
    m_SchemaName.GetWindowText(ifcSchemaName, 512);

//    m_Wall_Name.GetWindowText(wallName, 512);
//    m_Opening_Name.GetWindowText(openingName, 512);
//    m_Window_Name.GetWindowText(windowName, 512);

    if  (m_ResultsAsMeters.GetCheck()) {
        linearConversionFactor = 1;
    } else {
        linearConversionFactor = 1000;
        lengthUnitConversion = _T("MILLI");
    }

/*    m_WallHeight.GetWindowText(buffer, 512);
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

    if  ( ( (m_Wall.IsWindowEnabled())  &&
            (m_Wall.GetCheck()) ) ||
          ( (m_Window.IsWindowEnabled())  &&
            (m_Window.GetCheck()) ) ) {
        objectsWillBeAdded = true;
    } else {
        objectsWillBeAdded = false;
    }

    if  (createEmptyIfcFile(ifcSchemaName, objectsWillBeAdded, lengthUnitConversion)) {
        if  ( (m_Wall.IsWindowEnabled())  &&
              (m_Wall.GetCheck()) ) {

            switch  (GetCheckedRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_2)) {
                case  IDC_RADIO_0_1:
                    ifcWallInstance = createIfcWallStandardCase(wallName, 0, 0, 0);
                    buildRelDefinesByProperties(ifcWallInstance, buildPset_WallCommon());
                    if  (m_Quantities.GetCheck()) {
                        buildRelDefinesByProperties(ifcWallInstance, buildBaseQuantities_WallStandardCase(wallThickness, wallWidth, wallHeight, (openingWidth / linearConversionFactor) * (openingHeight / linearConversionFactor), linearConversionFactor));
                    }

                    buildRelAssociatesMaterial(ifcWallInstance, wallThickness);
                    createIfcPolylineShape(0, wallThickness/2, wallWidth, wallThickness/2);

                    pPolygon = localCreatePolygonStructureForSquare(0, 0, wallWidth, wallThickness);
                    createIfcExtrudedPolygonShape(pPolygon, wallHeight);
                    break;
                case  IDC_RADIO_0_2:
                    ifcWallInstance = createIfcWall(wallName, 0, 0, 0);
                    buildRelDefinesByProperties(ifcWallInstance, buildPset_WallCommon());
                    if  (m_Quantities.GetCheck()) {
                        buildRelDefinesByProperties(ifcWallInstance, buildBaseQuantities_Wall(wallThickness, wallWidth, wallHeight, (openingWidth / linearConversionFactor) * (openingHeight / linearConversionFactor), linearConversionFactor));
                    }

                    if  ( (view == PRESENTATIONVIEW)  &&  (m_Opening.IsWindowEnabled()) ) {
                        pShell = localCreateShellStructureForCuboidWithOpening(0, 0, 0, wallWidth, wallThickness, wallHeight, openingXOffset, openingZOffset, openingXOffset + openingWidth, openingZOffset + openingHeight);
                    } else {
                        pShell = localCreateShellStructureForCuboid(0, 0, 0, wallWidth, wallThickness, wallHeight);
                    }
                    createIfcBRepShape(pShell);
                    break;
                default:
                    MessageBox("Unknown selected type");
                    break;
            }

            if  (m_WallBasicRepr.GetCheck()) {
                createIfcBoundingBoxShape(wallWidth, wallThickness, wallHeight, "Box");
            }
        }

        if  ( (m_Opening.IsWindowEnabled())  &&
              (m_Opening.GetCheck()) ) {
            if  (view == COORDINATIONVIEW) {
                ifcOpeningElementInstance = createIfcOpeningElement(openingName, openingXOffset, 0, openingZOffset, true);
            } else {
                ASSERT(view == PRESENTATIONVIEW);
                ifcOpeningElementInstance = createIfcOpeningElement(openingName, openingXOffset, 0, openingZOffset, false);
            }

            if  (m_Quantities.GetCheck()) {
                buildRelDefinesByProperties(ifcOpeningElementInstance, buildBaseQuantities_Opening(wallThickness, openingHeight, openingWidth));
            }

            //
            //      Build relation between Wall and Opening
            //
            buildRelVoidsElementInstance(ifcWallInstance, ifcOpeningElementInstance);

            if  (view == COORDINATIONVIEW) {
                switch  (GetCheckedRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_2)) {
                    case  IDC_RADIO_1_1:
                        pPolygon = localCreatePolygonStructureForSquare(0, 0, openingWidth, wallThickness);
                        createIfcExtrudedPolygonShape(pPolygon, openingHeight);
                        break;
                    case  IDC_RADIO_1_2:
                        pShell = localCreateShellStructureForCuboid(0, 0, 0, openingWidth, wallThickness, openingHeight);
                        createIfcBRepShape(pShell);
                        break;
                    default:
                        MessageBox("Unknown selected type");
                        break;
                }

                if  (m_OpeningBasicRepr.GetCheck()) {
                    createIfcBoundingBoxShape(openingWidth, wallThickness, openingHeight, "Box");
                }
            } else {
                ASSERT(view == PRESENTATIONVIEW);
            }
        }

        if  ( (m_Window.IsWindowEnabled())  &&
              (m_Window.GetCheck()) ) {
            if  ( (m_Opening.IsWindowEnabled())  &&
                  (m_Opening.GetCheck()) ) {
                ifcWindowInstance = createIfcWindow(windowName, 0, windowYOffset, 0, true, openingHeight, openingWidth);

                //
                //      Build relation between Opening and Window
                //
                buildRelFillsElementInstance(ifcOpeningElementInstance, ifcWindowInstance);
            } else {
                ifcWindowInstance = createIfcWindow(windowName, 0, 0, 0, false, openingHeight, openingWidth);
            }

            buildRelDefinesByProperties(ifcWindowInstance, buildPset_WindowCommon());
            if  (m_Quantities.GetCheck()) {
                buildRelDefinesByProperties(ifcWindowInstance, buildBaseQuantities_Window(openingHeight, openingWidth));
            }

            switch  (GetCheckedRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_2)) {
                case  IDC_RADIO_2_1:
                    pPolygon = localCreatePolygonStructureForSquare(0, 0, openingWidth, windowThickness);
                    createIfcExtrudedPolygonShape(pPolygon, openingHeight);
                    break;
                case  IDC_RADIO_2_2:
                    pShell = localCreateShellStructureForCuboid(0, 0, 0, openingWidth, windowThickness, openingHeight);
                    createIfcBRepShape(pShell);
                    break;
                default:
                    MessageBox("Unknown selected type");
                    break;
            }

            if  (m_WindowBasicRepr.GetCheck()) {
                createIfcBoundingBoxShape(openingWidth, windowThickness, openingHeight, "Box");
            }
        }

        //
        //  Update header
        //

        char    description[512], timeStamp[512];
        time_t  t;
        struct tm   * tInfo;

        time ( &t );
        tInfo = localtime ( &t );

        if  (view == COORDINATIONVIEW) {
            if  (m_Quantities.GetCheck()) {
                memcpy(description, "ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]", sizeof("ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]"));
            } else {
                memcpy(description, "ViewDefinition [CoordinationView]", sizeof("ViewDefinition [CoordinationView]"));
            }
        } else {
            ASSERT(view == PRESENTATIONVIEW);
            if  (m_Quantities.GetCheck()) {
                memcpy(description, "ViewDefinition [PresentationView, QuantityTakeOffAddOnView]", sizeof("ViewDefinition [PresentationView, QuantityTakeOffAddOnView]"));
            } else {
                memcpy(description, "ViewDefinition [PresentationView]", sizeof("ViewDefinition [PresentationView]"));
            }
        }

        int i = 0, j = 0;
        while  (ifcFileName[i]) {
            if  (ifcFileName[i++] == '\\') {
                j = i;
            }
        }

        itoa(1900 + tInfo->tm_year, &timeStamp[0], 10);
        itoa(100 + 1 + tInfo->tm_mon, &timeStamp[4], 10);
        itoa(100 + tInfo->tm_mday, &timeStamp[7], 10);
        timeStamp[4] = '-';
        timeStamp[7] = '-';
        itoa(100 + tInfo->tm_hour, &timeStamp[10], 10);
        itoa(100 + tInfo->tm_min, &timeStamp[13], 10);
        itoa(100 + tInfo->tm_sec, &timeStamp[16], 10);
        timeStamp[10] = 'T';
        timeStamp[13] = ':';
        timeStamp[16] = ':';
        timeStamp[19] = 0;

        SetSPFFHeader(
                description,                        //  description
                "2;1",                              //  implementationLevel
                &ifcFileName[j],                    //  name
                &timeStamp[0],                      //  timeStamp
                "Architect",                        //  author
                "Building Designer Office",         //  organization
                "IFC Engine DLL version 1.03 beta", //  preprocessorVersion
                "IFC Engine DLL version 1.03 beta", //  originatingSystem
                "The authorising person",           //  authorization
                "IFC4"                              //  fileSchema
            );

        if  (saveIfx) {
            saveIfcFileAsXml(ifcFileName);
        } else {
            saveIfcFile(ifcFileName);
        }
    } else {
        MessageBox("Model could not be instantiated, probably it cannot find the schema file.");
    }
*/	
	CDialog::OnOK();
}

void CMiniExampleDlg::EnableProperties()
{
/*    if  ( (m_Wall.IsWindowEnabled())  &&
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

    if  ( (m_Opening.IsWindowEnabled())  &&
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

    if  ( (m_Window.IsWindowEnabled())  &&
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
    }*/
}

void CMiniExampleDlg::OnCheckWall() 
{
/*    if  (m_Wall.GetCheck()) {
        m_Wall_Name.EnableWindow(true);
        m_Static_0_Name.EnableWindow(true);
        m_Static_0_0.EnableWindow(true);
        if  (view == COORDINATIONVIEW) {
            GetDlgItem(IDC_RADIO_0_1)->EnableWindow(true);     
            GetDlgItem(IDC_RADIO_0_2)->EnableWindow(true);
        } else {
            ASSERT(view == PRESENTATIONVIEW);
            GetDlgItem(IDC_RADIO_0_1)->EnableWindow(false);     
            GetDlgItem(IDC_RADIO_0_2)->EnableWindow(true);
            OnRadio_0_2();
        }

        if  (!GetCheckedRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_1)) {
            m_Static_0_1.EnableWindow(true);
            m_WallBasicRepr.EnableWindow(true);
        }

        m_Opening.EnableWindow(true);
        OnCheckOpening();
    } else {
        /*m_Wall_Name.EnableWindow(false);
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
        
        m_Window.EnableWindow(true);* /
        OnCheckWindow();
    }

    EnableProperties();*/
}

void CMiniExampleDlg::OnCheckOpening() 
{
/*    if  (m_Opening.GetCheck()) {
        m_Opening_Name.EnableWindow(true);
        m_Static_1_Name.EnableWindow(true);
        if  (view == COORDINATIONVIEW) {
            m_Static_1_0.EnableWindow(true);

            GetDlgItem(IDC_RADIO_1_1)->EnableWindow(true);     
            GetDlgItem(IDC_RADIO_1_2)->EnableWindow(true);  
            
            if  (!GetCheckedRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_1)) {
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
/*        m_Opening_Name.EnableWindow(false);
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
        m_WindowBasicRepr.EnableWindow(false);* /
    }

    EnableProperties();*/
}

void CMiniExampleDlg::OnCheckWindow() 
{
/*    if  (m_Window.GetCheck()) {
        m_Window_Name.EnableWindow(true);
        m_Static_2_Name.EnableWindow(true);
        m_Static_2_0.EnableWindow(true);
        if  (view == COORDINATIONVIEW) {
            GetDlgItem(IDC_RADIO_2_1)->EnableWindow(true);     
            GetDlgItem(IDC_RADIO_2_2)->EnableWindow(true);     
        } else {
            ASSERT(view == PRESENTATIONVIEW);
            GetDlgItem(IDC_RADIO_2_1)->EnableWindow(false);     
            GetDlgItem(IDC_RADIO_2_2)->EnableWindow(true);
            OnRadio_2_2();
        }

        if  (!GetCheckedRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_1)) {
            m_Static_2_1.EnableWindow(true);
            m_WindowBasicRepr.EnableWindow(true);
        }
    } else {
       /* m_Window_Name.EnableWindow(false);
        m_Static_2_Name.EnableWindow(false);
        m_Static_2_0.EnableWindow(false);
        GetDlgItem(IDC_RADIO_2_1)->EnableWindow(false);     
        GetDlgItem(IDC_RADIO_2_2)->EnableWindow(false);     
        
        m_Static_2_1.EnableWindow(false);
        m_WindowBasicRepr.EnableWindow(false);* /
    }

    EnableProperties();*/
}

void CMiniExampleDlg::OnRadio_View_0() 
{
    view = COORDINATIONVIEW;
    CheckRadioButton(IDC_RADIO_VIEW_0, IDC_RADIO_VIEW_1, IDC_RADIO_VIEW_0);

    OnCheckWall();
    OnCheckOpening();
    OnCheckWindow();
}

void CMiniExampleDlg::OnRadio_View_1() 
{
    view = PRESENTATIONVIEW;
    CheckRadioButton(IDC_RADIO_VIEW_0, IDC_RADIO_VIEW_1, IDC_RADIO_VIEW_1);

    OnCheckWall();
    OnCheckOpening();
    OnCheckWindow();
}

void CMiniExampleDlg::OnRadio_0_1() 
{
/*    CheckRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_2, IDC_RADIO_0_1);
    m_Static_0_1.EnableWindow(true);
    m_WallBasicRepr.EnableWindow(true);*/
}

void CMiniExampleDlg::OnRadio_0_2() 
{
/*    CheckRadioButton(IDC_RADIO_0_1, IDC_RADIO_0_2, IDC_RADIO_0_2);
    m_Static_0_1.EnableWindow(true);
    m_WallBasicRepr.EnableWindow(true);*/
}

void CMiniExampleDlg::OnRadio_1_1() 
{
/*    CheckRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_2, IDC_RADIO_1_1);
    m_Static_1_1.EnableWindow(true);
    m_OpeningBasicRepr.EnableWindow(true);*/
}

void CMiniExampleDlg::OnRadio_1_2() 
{
/*    CheckRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_2, IDC_RADIO_1_2);
    m_Static_1_1.EnableWindow(true);
    m_OpeningBasicRepr.EnableWindow(true);*/
}

void CMiniExampleDlg::OnRadio_2_1() 
{
/*    CheckRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_2, IDC_RADIO_2_1);
    m_Static_2_1.EnableWindow(true);
    m_WindowBasicRepr.EnableWindow(true);*/
}

void CMiniExampleDlg::OnRadio_2_2() 
{
/*    CheckRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_2, IDC_RADIO_2_2);
    m_Static_2_1.EnableWindow(true);
    m_WindowBasicRepr.EnableWindow(true);*/
}

bool CMiniExampleDlg::CheckWallAndWindowMeasuresNotSupported() 
{
    int     wallHeight, wallWidth,
            openingHeight, openingWidth, openingXOffset, openingZOffset;
    char    buffer[512];
    
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

    if  ( (openingXOffset <= 0)  ||
          (openingXOffset + openingWidth >= wallWidth)  ||
          (openingZOffset <= 0)  ||
          (openingZOffset + openingHeight >= wallHeight) ) {
        MessageBox("The opening is not placed totaly within the wall, this variant is not supported by this software in Presentation View. Please change values.", "Program incompatibility error", IDOK);
        return  true;
    }

    return  false;
}


int CreateWall(char * name, double rotation, int left, int right,
			   double xOffset, double yOffset, double zOffset,
			   double width, double height, double thickness,
			   double openingWidth, double openingHeight, double openingZOffset,
			   int Pset_WallCommon, int materialLayerSetUsage)
{
    polygon2DStruct * pPolygon;
	transformationMatrixStruct  matrix;

	identityMatrix(&matrix);
	matrix._11 = cos(rotation);
	matrix._12 = -sin(rotation);
	matrix._21 = sin(rotation);
	matrix._22 = cos(rotation);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

    int	ifcWallInstance = createIfcWall(name, matrix);
    buildRelDefinesByProperties(ifcWallInstance, Pset_WallCommon);
    /////TEMP REMOVE/////if  (m_Quantities.GetCheck()) {
        /////TEMP REMOVE/////buildRelDefinesByProperties(ifcWallInstance, buildBaseQuantities_WallStandardCase(thickness, width, height, (openingWidth / linearConversionFactor) * (openingHeight / linearConversionFactor), linearConversionFactor));
    /////TEMP REMOVE/////}

    buildRelAssociatesMaterial(ifcWallInstance, materialLayerSetUsage);
    //createIfcPolylineShape(0, wallThickness/2, wallWidth, wallThickness/2);
    pPolygon = localCreatePolygonStructureFor_(left, right, width, thickness);
	createIfcExtrudedPolygonShape(pPolygon, height);

	if	(openingWidth) {
		polygon2DStruct * pPolygonOpening;
		int				ifcOpeningElementInstance;

		ifcOpeningElementInstance = createIfcOpeningElement("Opening in Outer Wall x", (width - openingWidth)/2, -thickness/2, openingZOffset, true);
/////////////if  (m_Quantities.GetCheck()) {
/////TEMP REMOVED////////    buildRelDefinesByProperties(ifcOpeningElementInstance, buildBaseQuantities_Opening(wallThickness, openingHeight, openingWidth));
/////////////}
//
//      Build relation between Wall and Opening
//
		buildRelVoidsElementInstance(ifcWallInstance, ifcOpeningElementInstance);
		pPolygonOpening = localCreatePolygonStructureForSquare(0, 0, openingWidth, thickness);
		createIfcExtrudedPolygonShape(pPolygonOpening, openingHeight);

		if	(openingZOffset) {
			polygon2DStruct * pPolygonWindow;
			int				ifcWindowInstance;
			//
			//	Window
			//
            ifcWindowInstance = createIfcWindow("Window", 0, 0, 0, true, openingHeight, openingWidth);

            //
            //      Build relation between Opening and Window
            //
            buildRelFillsElementInstance(ifcOpeningElementInstance, ifcWindowInstance);

            buildRelDefinesByProperties(ifcWindowInstance, buildPset_WindowCommon());
//            if  (m_Quantities.GetCheck()) {
//                buildRelDefinesByProperties(ifcWindowInstance, buildBaseQuantities_Window(openingHeight, openingWidth));
//            }

			pPolygonWindow = localCreatePolygonStructureForSquare(0, 0, openingWidth, thickness/2);
			createIfcExtrudedPolygonShape(pPolygonWindow, openingHeight);
		} else {
			polygon2DStruct * pPolygonDoor;
			int				ifcDoorInstance;
			//
			//	Door
			//
            ifcDoorInstance = createIfcDoor("Door", 0, 0, 0, true, openingHeight, openingWidth);

            //
            //      Build relation between Opening and Door
            //
            buildRelFillsElementInstance(ifcOpeningElementInstance, ifcDoorInstance);

            buildRelDefinesByProperties(ifcDoorInstance, buildPset_DoorCommon());
//            if  (m_Quantities.GetCheck()) {
//                buildRelDefinesByProperties(ifcWindowInstance, buildBaseQuantities_Window(openingHeight, openingWidth));
//            }

			pPolygonDoor = localCreatePolygonStructureForSquare(0, 0, openingWidth, thickness/2);
			createIfcExtrudedPolygonShape(pPolygonDoor, openingHeight);
		}
	}

	return	ifcWallInstance;
}

int CreateWall(char * name, double rotation, int left, int right,
			   double xOffset, double yOffset, double zOffset,
			   double width, double height, double thickness,
			   int Pset_WallCommon, int materialLayerSetUsage)
{
	return	CreateWall(name, rotation, left, right,
			   xOffset, yOffset, zOffset,
			   width, height, thickness,
			   0, 0, 0,
			   Pset_WallCommon, materialLayerSetUsage);
}

int CreateSlab(char * name,
			   double xOffset, double yOffset, double zOffset,
			   double x0, double y0, 
			   double x1, double y1, 
			   double x2, double y2, 
			   double x3, double y3, 
			   double x4, double y4, 
			   double x5, double y5,
			   double x6, double y6,
			   double x7, double y7,
			   double height)
{
    point2DStruct   * pPoints[8];
    //polygon3DStruct * pPolygons;
    //shellStruct     * pShell;

    create2DPoint(&pPoints[0], x0, y0);
    create2DPoint(&pPoints[1], x1, y1);
    create2DPoint(&pPoints[2], x2, y2);
    create2DPoint(&pPoints[3], x3, y3);
    create2DPoint(&pPoints[4], x4, y4);
    create2DPoint(&pPoints[5], x5, y5);
    create2DPoint(&pPoints[6], x6, y6);
    create2DPoint(&pPoints[7], x7, y7);

    polygon2DStruct * pPolygon;
	transformationMatrixStruct  matrix;

	identityMatrix(&matrix);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

    int	ifcSlabInstance = createIfcSlab(name, matrix);

    //pPolygon = localCreatePolygonStructureForSquare(0, 0, width, depth);//localCreatePolygonStructureFor_(0, 0, width, depth);
	pPolygon = create2DPolygonWith8Vectors(&pPolygon, pPoints[0], pPoints[1], pPoints[2], pPoints[3], pPoints[4], pPoints[5], pPoints[6], pPoints[7]);
	createIfcExtrudedPolygonShape(pPolygon, height);

	return	ifcSlabInstance;
}

int CreateRoof(char * name,
			   double xOffset, double yOffset, double zOffset,
			   double x0, double y0, 
			   double x1, double y1, 
			   double x2, double y2, 
			   double x3, double y3, 
			   double x4, double y4, 
			   double x5, double y5,
			   double x6, double y6,
			   double x7, double y7,
			   double height)
{
    point2DStruct   * pPoints[8];
    //polygon3DStruct * pPolygons;
    //shellStruct     * pShell;

    create2DPoint(&pPoints[0], x0, y0);
    create2DPoint(&pPoints[1], x1, y1);
    create2DPoint(&pPoints[2], x2, y2);
    create2DPoint(&pPoints[3], x3, y3);
    create2DPoint(&pPoints[4], x4, y4);
    create2DPoint(&pPoints[5], x5, y5);
    create2DPoint(&pPoints[6], x6, y6);
    create2DPoint(&pPoints[7], x7, y7);

    polygon2DStruct * pPolygon;
	transformationMatrixStruct  matrix;

	identityMatrix(&matrix);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

    int	ifcRoofInstance = createIfcRoof(name, matrix);

    //pPolygon = localCreatePolygonStructureForSquare(0, 0, width, depth);//localCreatePolygonStructureFor_(0, 0, width, depth);
	pPolygon = create2DPolygonWith8Vectors(&pPolygon, pPoints[0], pPoints[1], pPoints[2], pPoints[3], pPoints[4], pPoints[5], pPoints[6], pPoints[7]);
	createIfcExtrudedPolygonShape(pPolygon, height);

	return	ifcRoofInstance;
}

int CreateSpace(char * name,
			   double xOffset, double yOffset, double zOffset,
			   double x0, double y0, 
			   double x1, double y1, 
			   double x2, double y2, 
			   double x3, double y3, 
			   double x4, double y4, 
			   double x5, double y5, 
			   double height)
{
    point2DStruct   * pPoints[6];
    //polygon3DStruct * pPolygons;
    //shellStruct     * pShell;

    create2DPoint(&pPoints[0], x0, y0);
    create2DPoint(&pPoints[1], x1, y1);
    create2DPoint(&pPoints[2], x2, y2);
    create2DPoint(&pPoints[3], x3, y3);
    create2DPoint(&pPoints[4], x4, y4);
    create2DPoint(&pPoints[5], x5, y5);

    polygon2DStruct * pPolygon;
	transformationMatrixStruct  matrix;

	identityMatrix(&matrix);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

    int	ifcSpaceInstance = createIfcSpace(name, matrix);

    //pPolygon = localCreatePolygonStructureForSquare(0, 0, width, depth);//localCreatePolygonStructureFor_(0, 0, width, depth);
	pPolygon = create2DPolygonWith6Vectors(&pPolygon, pPoints[0], pPoints[1], pPoints[2], pPoints[3], pPoints[4], pPoints[5]);
	createIfcExtrudedPolygonShape(pPolygon, height);

	return	ifcSpaceInstance;
}

int CreateSpace(char * name,
			   double xOffset, double yOffset, double zOffset,
			   double width, double height, double depth)
{
    polygon2DStruct * pPolygon;
	transformationMatrixStruct  matrix;

	identityMatrix(&matrix);
//	matrix._11 = cos(rotation);
//	matrix._12 = -sin(rotation);
//	matrix._21 = sin(rotation);
//	matrix._22 = cos(rotation);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

    int	ifcSpaceInstance = createIfcSpace(name, matrix);
//    buildRelDefinesByProperties(ifcWallInstance, Pset_WallCommon);
    /////TEMP REMOVE/////if  (m_Quantities.GetCheck()) {
        /////TEMP REMOVE/////buildRelDefinesByProperties(ifcWallInstance, buildBaseQuantities_WallStandardCase(thickness, width, height, (openingWidth / linearConversionFactor) * (openingHeight / linearConversionFactor), linearConversionFactor));
    /////TEMP REMOVE/////}

//    buildRelAssociatesMaterial(ifcWallInstance, materialLayerSetUsage);
    //createIfcPolylineShape(0, wallThickness/2, wallWidth, wallThickness/2);
    pPolygon = localCreatePolygonStructureForSquare(0, 0, width, depth);//localCreatePolygonStructureFor_(0, 0, width, depth);
	createIfcExtrudedPolygonShape(pPolygon, height);

	/*if	(openingWidth) {
		polygon2DStruct * pPolygonOpening;
		int				ifcOpeningElementInstance;

		ifcOpeningElementInstance = createIfcOpeningElement("Opening in Outer Wall x", (width - openingWidth)/2, -thickness/2, openingZOffset, true);
/////////////if  (m_Quantities.GetCheck()) {
/////TEMP REMOVED////////    buildRelDefinesByProperties(ifcOpeningElementInstance, buildBaseQuantities_Opening(wallThickness, openingHeight, openingWidth));
/////////////}
//
//      Build relation between Wall and Opening
//
		buildRelVoidsElementInstance(ifcWallInstance, ifcOpeningElementInstance);
		pPolygonOpening = localCreatePolygonStructureForSquare(0, 0, openingWidth, thickness);
		createIfcExtrudedPolygonShape(pPolygonOpening, openingHeight);

		.if	(openingZOffset) {
			polygon2DStruct * pPolygonWindow;
			int				ifcWindowInstance;
			//
			//	Window
			//
            ifcWindowInstance = createIfcWindow("Window", 0, 0, 0, true, openingHeight, openingWidth);

            //
            //      Build relation between Opening and Window
            //
            buildRelFillsElementInstance(ifcOpeningElementInstance, ifcWindowInstance);

            buildRelDefinesByProperties(ifcWindowInstance, buildPset_WindowCommon());
//            if  (m_Quantities.GetCheck()) {
//                buildRelDefinesByProperties(ifcWindowInstance, buildBaseQuantities_Window(openingHeight, openingWidth));
//            }

			pPolygonWindow = localCreatePolygonStructureForSquare(0, 0, openingWidth, thickness/2);
			createIfcExtrudedPolygonShape(pPolygonWindow, openingHeight);
		} else {
			polygon2DStruct * pPolygonDoor;
			int				ifcDoorInstance;
			//
			//	Door
			//
            ifcDoorInstance = createIfcDoor("Door", 0, 0, 0, true, openingHeight, openingWidth);

            //
            //      Build relation between Opening and Door
            //
            buildRelFillsElementInstance(ifcOpeningElementInstance, ifcDoorInstance);

            buildRelDefinesByProperties(ifcDoorInstance, buildPset_DoorCommon());
//            if  (m_Quantities.GetCheck()) {
//                buildRelDefinesByProperties(ifcWindowInstance, buildBaseQuantities_Window(openingHeight, openingWidth));
//            }

			pPolygonDoor = localCreatePolygonStructureForSquare(0, 0, openingWidth, thickness/2);
			createIfcExtrudedPolygonShape(pPolygonDoor, openingHeight);
		}
	}*/

	return	ifcSpaceInstance;
}

POINT2DLISTSTRUCT	* build2DPointsFromSquare(double x, double y)
{
	POINT2DLISTSTRUCT	* p2DPoint = new POINT2DLISTSTRUCT;

	p2DPoint->x = 0;
	p2DPoint->y = 0;
	p2DPoint->next = new POINT2DLISTSTRUCT;
	p2DPoint->next->x = x;
	p2DPoint->next->y = 0;
	p2DPoint->next->next = new POINT2DLISTSTRUCT;
	p2DPoint->next->next->x = x;
	p2DPoint->next->next->y = y;
	p2DPoint->next->next->next = new POINT2DLISTSTRUCT;
	p2DPoint->next->next->next->x = 0;
	p2DPoint->next->next->next->y = y;
	p2DPoint->next->next->next->next = NULL;

	return	p2DPoint;
}

void CMiniExampleDlg::CreateFloor()
{
    shellStruct     * pShell;

    int     ifcWallInstance_OuterWall_I, ifcWallInstance_OuterWall_II, ifcWallInstance_OuterWall_III, ifcWallInstance_OuterWall_IV, ifcWallInstance_OuterWall_V,
			ifcWallInstance_OuterWall_VI, ifcWallInstance_OuterWall_VII, ifcWallInstance_OuterWall_VIII, ifcWallInstance_OuterWall_IX, ifcWallInstance_OuterWall_X, 
			ifcWallInstance_OuterWall_XI, ifcWallInstance_OuterWall_XII, ifcWallInstance_OuterWall_XIII, ifcWallInstance_OuterWall_XIV, ifcWallInstance_OuterWall_XV,
			ifcWallInstance_OuterWall_XVI,
			ifcWallInstance_InnerWall_I, ifcWallInstance_InnerWall_II,
			ifcSlabInstance_Floor_I, ifcSlabInstance_Floor_II,
			ifcRoofInstance_Roof_I,
			ifcSpaceInstance_Room_I, ifcSpaceInstance_Room_II, ifcSpaceInstance_Room_III, ifcSpaceInstance_Room_IV,
			ifcOpeningElementInstance, ifcWindowInstance;
    double  openingHeight, openingWidth, openingXOffset, openingZOffset,
            windowThickness, windowYOffset,
            linearConversionFactor;
    char    ifcFileName[512], ifcSchemaName[512], buffer[512], * lengthUnitConversion = NULL,
            wallName[512], openingName[512], windowName[512];
    bool    objectsWillBeAdded = true;
    
    m_FileName.GetWindowText(ifcFileName, 512);
    m_SchemaName.GetWindowText(ifcSchemaName, 512);

    if  (m_ResultsAsMeters.GetCheck()) {
        linearConversionFactor = 1;
    } else {
        linearConversionFactor = 1000;
        lengthUnitConversion = _T("MILLI");
    }

	double	innerWallThickness, outerWallThickness,
			roomIwidth, roomIdepth, roomIIwidth, roomIIdepth,
			doorWidth, doorHeight,
			windowWidth, windowHeight, windowZOffset,
			delta, wallHeight;

    m_RoomIWidth.GetWindowText(buffer, 512);
    roomIwidth = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_RoomIDepth.GetWindowText(buffer, 512);
    roomIdepth = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_RoomIIWidth.GetWindowText(buffer, 512);
    roomIIwidth = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_RoomIIDepth.GetWindowText(buffer, 512);
    roomIIdepth = (double) atoi(buffer) * 0.001 * linearConversionFactor;

    m_DoorWidth.GetWindowText(buffer, 512);
    doorWidth = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_DoorHeight.GetWindowText(buffer, 512);
    doorHeight = (double) atoi(buffer) * 0.001 * linearConversionFactor;

    m_WindowWidth.GetWindowText(buffer, 512);
    windowWidth = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_WindowHeight.GetWindowText(buffer, 512);
    windowHeight = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_WindowZOffset.GetWindowText(buffer, 512);
    windowZOffset = (double) atoi(buffer) * 0.001 * linearConversionFactor;

    m_InnerWallThickness.GetWindowText(buffer, 512);
    innerWallThickness = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_OuterWallThickness.GetWindowText(buffer, 512);
    outerWallThickness = (double) atoi(buffer) * 0.001 * linearConversionFactor;

    m_Delta.GetWindowText(buffer, 512);
    delta = (double) atoi(buffer) * 0.001 * linearConversionFactor;
    m_Height.GetWindowText(buffer, 512);
    wallHeight = (double) atoi(buffer) * 0.001 * linearConversionFactor;

	int	model = createEmptyIfcFile(ifcSchemaName, objectsWillBeAdded, lengthUnitConversion);
    if  (model) {
		double	Pi = 3.14159265359;
		int	Pset_WallCommon = buildPset_WallCommon(),
		materialLayerSetUsage = buildMaterialLayerSetUsage(outerWallThickness);
		
		ifcWallInstance_OuterWall_I = CreateWall("Outer Wall I",
					Pi, 1, -1,
					roomIwidth + 1.5 * outerWallThickness, roomIIdepth - delta + roomIdepth + 1.5 * outerWallThickness, 0,
					roomIwidth + outerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_II = CreateWall("Outer Wall II",
					0.5 * Pi, 1, -1,
					0.5 * outerWallThickness, roomIIdepth - delta + roomIdepth + 1.5 * outerWallThickness, 0,
					(roomIdepth + outerWallThickness), wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_III = CreateWall("Outer Wall III",
					0, 1, 1,
					0.5 * outerWallThickness, roomIIdepth - delta + 0.5 * outerWallThickness, 0,
					roomIwidth + innerWallThickness, wallHeight, outerWallThickness,
					doorWidth, doorHeight, 0,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_IV = CreateWall("Outer Wall IV",
					0.5 * Pi, -1, -1,
					roomIwidth + innerWallThickness + 0.5 * outerWallThickness, roomIIdepth - delta + 0.5 * outerWallThickness, 0,
					roomIIdepth - delta, wallHeight, outerWallThickness,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_V = CreateWall("Outer Wall V",
					0, 1, -1,
					roomIwidth + innerWallThickness + 0.5 * outerWallThickness, 0.5 * outerWallThickness, 0,
					roomIIwidth + outerWallThickness, wallHeight, outerWallThickness,
					doorWidth, doorHeight, 0,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_VI = CreateWall("Outer Wall VI",
					1.5 * Pi, 1, -1,
					roomIwidth + innerWallThickness + roomIIwidth + 1.5 * outerWallThickness, 0.5 * outerWallThickness, 0,
					roomIIdepth + outerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_VII = CreateWall("Outer Wall VII",
					Pi, 1, 1,
					roomIwidth + innerWallThickness + roomIIwidth + 1.5 * outerWallThickness, roomIIdepth + 1.5 * outerWallThickness, 0,
					roomIIwidth + innerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_VIII = CreateWall("Outer Wall VIII",
					1.5 * Pi, -1, -1,
					roomIwidth + 1.5 * outerWallThickness, roomIIdepth + 1.5 * outerWallThickness, 0,
					roomIdepth - delta, wallHeight, outerWallThickness,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_InnerWall_I = CreateWall("Inner Wall I",
					0.5 * Pi, 0, 0,
					roomIwidth + outerWallThickness + 0.5 * innerWallThickness, roomIIdepth + outerWallThickness, 0,
					delta, wallHeight, innerWallThickness,
					doorWidth, doorHeight, 0,
					Pset_WallCommon, materialLayerSetUsage);

		double	floorHeight = 300;

		ifcSlabInstance_Floor_I = CreateSlab("Floor I",
					0, 0, -floorHeight,
					0, roomIIdepth - delta,
					0, roomIIdepth - delta + roomIdepth  + 2 * outerWallThickness,
					roomIwidth + 2 * outerWallThickness, roomIIdepth - delta + roomIdepth + 2 * outerWallThickness,
					roomIwidth + 2 * outerWallThickness, roomIIdepth + 2 * outerWallThickness,
					roomIwidth + roomIIwidth + 2 * outerWallThickness + innerWallThickness, roomIIdepth + 2 * outerWallThickness,
					roomIwidth + roomIIwidth + 2 * outerWallThickness + innerWallThickness, 0,
					roomIwidth + innerWallThickness, 0,
					roomIwidth + innerWallThickness, roomIIdepth - delta,
					floorHeight);

		ifcSlabInstance_Floor_II = CreateSlab("Floor II",
					0, 0, wallHeight,
					0, roomIIdepth - delta,
					0, roomIIdepth - delta + roomIdepth  + 2 * outerWallThickness,
					roomIwidth + 2 * outerWallThickness, roomIIdepth - delta + roomIdepth + 2 * outerWallThickness,
					roomIwidth + 2 * outerWallThickness, roomIIdepth + 2 * outerWallThickness,
					roomIwidth + roomIIwidth + 2 * outerWallThickness + innerWallThickness, roomIIdepth + 2 * outerWallThickness,
					roomIwidth + roomIIwidth + 2 * outerWallThickness + innerWallThickness, 0,
					roomIwidth + innerWallThickness, 0,
					roomIwidth + innerWallThickness, roomIIdepth - delta,
					floorHeight);

		ifcRoofInstance_Roof_I = CreateRoof("Roof I",
					0, 0, 2 * wallHeight + floorHeight,
					0, roomIIdepth - delta,
					0, roomIIdepth - delta + roomIdepth  + 2 * outerWallThickness,
					roomIwidth + 2 * outerWallThickness, roomIIdepth - delta + roomIdepth + 2 * outerWallThickness,
					roomIwidth + 2 * outerWallThickness, roomIIdepth + 2 * outerWallThickness,
					roomIwidth + roomIIwidth + 2 * outerWallThickness + innerWallThickness, roomIIdepth + 2 * outerWallThickness,
					roomIwidth + roomIIwidth + 2 * outerWallThickness + innerWallThickness, 0,
					roomIwidth + innerWallThickness, 0,
					roomIwidth + innerWallThickness, roomIIdepth - delta,
					floorHeight);

		ifcSpaceInstance_Room_I = CreateSpace("Room I",
					outerWallThickness, roomIIdepth - delta + outerWallThickness, 0,
					roomIwidth, wallHeight, roomIdepth);
		 
		ifcSpaceInstance_Room_II = CreateSpace("Room II",
					outerWallThickness + roomIwidth + innerWallThickness, outerWallThickness, 0,
					roomIIwidth, wallHeight, roomIIdepth);

		double zOffset = wallHeight + floorHeight;

		ifcSpaceInstance_Room_III = CreateSpace("Room III",
					outerWallThickness, outerWallThickness + roomIIdepth + innerWallThickness, zOffset,
					roomIwidth, wallHeight, roomIdepth - delta - innerWallThickness);

		ifcSpaceInstance_Room_IV = CreateSpace("Room IV",
					outerWallThickness, outerWallThickness, zOffset,
					0, 0 + roomIIdepth - delta,
					0, 0 + roomIIdepth,
					0 + roomIwidth + innerWallThickness + roomIIwidth, 0 + roomIIdepth,
					0 + roomIwidth + innerWallThickness + roomIIwidth, 0,
					0 + roomIwidth + innerWallThickness, 0,
					0 + roomIwidth + innerWallThickness, 0 + roomIIdepth - delta,
					/*0, 0, zOffset,
					outerWallThickness, outerWallThickness + roomIIdepth - delta,
					outerWallThickness, outerWallThickness + roomIIdepth,
					outerWallThickness + roomIwidth + innerWallThickness + roomIIwidth, outerWallThickness + roomIIdepth,
					outerWallThickness + roomIwidth + innerWallThickness + roomIIwidth, outerWallThickness,
					outerWallThickness + roomIwidth + innerWallThickness, outerWallThickness,
					outerWallThickness + roomIwidth + innerWallThickness, outerWallThickness + roomIIdepth - delta,*/
					wallHeight);


		ifcWallInstance_OuterWall_IX = CreateWall("Outer Wall IX",
					Pi, 1, -1,
					roomIwidth + 1.5 * outerWallThickness, roomIIdepth - delta + roomIdepth + 1.5 * outerWallThickness, zOffset,
					roomIwidth + outerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_X = CreateWall("Outer Wall X",
					0.5 * Pi, 1, -1,
					0.5 * outerWallThickness, roomIIdepth - delta + roomIdepth + 1.5 * outerWallThickness, zOffset,
					(roomIdepth + outerWallThickness), wallHeight, outerWallThickness,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_XI = CreateWall("Outer Wall XI",
					0, 1, 1,
					0.5 * outerWallThickness, roomIIdepth - delta + 0.5 * outerWallThickness, zOffset,
					roomIwidth + innerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_XII = CreateWall("Outer Wall XII",
					0.5 * Pi, -1, -1,
					roomIwidth + innerWallThickness + 0.5 * outerWallThickness, roomIIdepth - delta + 0.5 * outerWallThickness, zOffset,
					roomIIdepth - delta, wallHeight, outerWallThickness,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_XIII = CreateWall("Outer Wall XIII",
					0, 1, -1,
					roomIwidth + innerWallThickness + 0.5 * outerWallThickness, 0.5 * outerWallThickness, zOffset,
					roomIIwidth + outerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_XIV = CreateWall("Outer Wall XIV",
					1.5 * Pi, 1, -1,
					roomIwidth + innerWallThickness + roomIIwidth + 1.5 * outerWallThickness, 0.5 * outerWallThickness, zOffset,
					roomIIdepth + outerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_XV = CreateWall("Outer Wall XV",
					Pi, 1, 1,
					roomIwidth + innerWallThickness + roomIIwidth + 1.5 * outerWallThickness, roomIIdepth + 1.5 * outerWallThickness, zOffset,
					roomIIwidth + innerWallThickness, wallHeight, outerWallThickness,
					windowWidth, windowHeight, windowZOffset,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_OuterWall_XVI = CreateWall("Outer Wall XVI",
					1.5 * Pi, -1, -1,
					roomIwidth + 1.5 * outerWallThickness, roomIIdepth + 1.5 * outerWallThickness, zOffset,
					roomIdepth - delta, wallHeight, outerWallThickness,
					Pset_WallCommon, materialLayerSetUsage);
		ifcWallInstance_InnerWall_II = CreateWall("Inner Wall II",
					Pi, 0, 0,
					roomIwidth + outerWallThickness, roomIIdepth + outerWallThickness + 0.5 * innerWallThickness, zOffset,
					roomIwidth, wallHeight, innerWallThickness,
					doorWidth, doorHeight, 0,
					Pset_WallCommon, materialLayerSetUsage);


		//
		//		Creation of the space boundaries
		//

		TRANSFORMATIONMATRIXSTRUCT	* pMatrix = new TRANSFORMATIONMATRIXSTRUCT;
		POINT2DLISTSTRUCT			* pPoints = new POINT2DLISTSTRUCT;

		double	roomIIIwidth = roomIwidth,
				roomIIIdepth = roomIdepth - delta - innerWallThickness,
				roomIVwidth = roomIwidth + innerWallThickness + roomIIwidth,
				roomIVdepth = roomIIdepth;

		char	* spaceBoundaryName = "2ndLevel";

		pPoints->x = 0;
		pPoints->y = roomIIdepth - delta;
		pPoints->next = new POINT2DLISTSTRUCT;
		pPoints->next->x = roomIwidth + innerWallThickness;
		pPoints->next->y = roomIIdepth - delta;
		pPoints->next->next = new POINT2DLISTSTRUCT;
		pPoints->next->next->x = roomIwidth + innerWallThickness;
		pPoints->next->next->y = 0;
		pPoints->next->next->next = new POINT2DLISTSTRUCT;
		pPoints->next->next->next->x = roomIVwidth;
		pPoints->next->next->next->y = 0;
		pPoints->next->next->next->next = new POINT2DLISTSTRUCT;
		pPoints->next->next->next->next->x = roomIVwidth;
		pPoints->next->next->next->next->y = roomIVdepth;
		pPoints->next->next->next->next->next = new POINT2DLISTSTRUCT;
		pPoints->next->next->next->next->next->x = 0;
		pPoints->next->next->next->next->next->y = roomIVdepth;
		pPoints->next->next->next->next->next->next = NULL;
		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 1;
		pMatrix->_23 = 0;
		pMatrix->_31 = 0;
		pMatrix->_32 = 0;
		pMatrix->_33 = 1;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;

		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_I, ifcSlabInstance_Floor_I, spaceBoundaryName, _T("Space Boundary I"), pMatrix, build2DPointsFromSquare(roomIwidth, roomIdepth), 0, 0);
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_II, ifcSlabInstance_Floor_I, spaceBoundaryName, _T("Space Boundary II"), pMatrix, build2DPointsFromSquare(roomIIwidth, roomIIdepth), 0, 0);



		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = roomIdepth;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_I, ifcWallInstance_OuterWall_I, spaceBoundaryName, _T("Space Boundary III"), pMatrix, build2DPointsFromSquare(roomIwidth, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_I, ifcWallInstance_OuterWall_II, spaceBoundaryName, _T("Space Boundary IV"), pMatrix, build2DPointsFromSquare(roomIdepth, wallHeight), 0, 0);

		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_I, ifcWallInstance_OuterWall_III, spaceBoundaryName, _T("Space Boundary V"), pMatrix, build2DPointsFromSquare(roomIwidth, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = roomIwidth;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_I, ifcWallInstance_OuterWall_VIII, spaceBoundaryName, _T("Space Boundary VI"), pMatrix, build2DPointsFromSquare(roomIdepth, wallHeight), 0, 0);


		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = roomIIdepth;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_II, ifcWallInstance_OuterWall_VII, spaceBoundaryName, _T("Space Boundary X"), pMatrix, build2DPointsFromSquare(roomIIwidth, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_II, ifcWallInstance_OuterWall_IV, spaceBoundaryName, _T("Space Boundary VII"), pMatrix, build2DPointsFromSquare(roomIIdepth, wallHeight), 0, 0);

		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_II, ifcWallInstance_OuterWall_V, spaceBoundaryName, _T("Space Boundary VIII"), pMatrix, build2DPointsFromSquare(roomIIwidth, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = roomIIwidth;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_II, ifcWallInstance_OuterWall_VI, spaceBoundaryName, _T("Space Boundary IX"), pMatrix, build2DPointsFromSquare(roomIIdepth, wallHeight), 0, 0);


		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 1;
		pMatrix->_23 = 0;
		pMatrix->_31 = 0;
		pMatrix->_32 = 0;
		pMatrix->_33 = 1;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;

		pMatrix->_43 = wallHeight;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_I, ifcSlabInstance_Floor_II, spaceBoundaryName, _T("Space Boundary XIX"), pMatrix, build2DPointsFromSquare(roomIwidth, roomIdepth), 0, 0);
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_II, ifcSlabInstance_Floor_II, spaceBoundaryName, _T("Space Boundary XX"), pMatrix, build2DPointsFromSquare(roomIIwidth, roomIIdepth), 0, 0);
		pMatrix->_43 = 0;

		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_III, ifcSlabInstance_Floor_II, spaceBoundaryName, _T("Space Boundary XXI"), pMatrix, build2DPointsFromSquare(roomIIIwidth, roomIIIdepth), 0, 0);
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcSlabInstance_Floor_II, spaceBoundaryName, _T("Space Boundary XXII"), pMatrix, pPoints, 0, 0);





		pMatrix->_43 = wallHeight;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_III, ifcRoofInstance_Roof_I, spaceBoundaryName, _T("Space Boundary XXXIX"), pMatrix, build2DPointsFromSquare(roomIIIwidth, roomIIIdepth), 0, 0);
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcRoofInstance_Roof_I, spaceBoundaryName, _T("Space Boundary XL"), pMatrix, pPoints, 0, 0);


		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = roomIIIdepth;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_III, ifcWallInstance_OuterWall_IX, spaceBoundaryName, _T("Space Boundary XXIII"), pMatrix, build2DPointsFromSquare(roomIIIwidth, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_III, ifcWallInstance_OuterWall_X, spaceBoundaryName, _T("Space Boundary XXIV"), pMatrix, build2DPointsFromSquare(roomIIIdepth, wallHeight), 0, 0);

		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_III, ifcWallInstance_InnerWall_II, spaceBoundaryName, _T("Space Boundary XXV"), pMatrix, build2DPointsFromSquare(roomIIIwidth, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = roomIIIwidth;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_III, ifcWallInstance_OuterWall_XVI, spaceBoundaryName, _T("Space Boundary XXVI"), pMatrix, build2DPointsFromSquare(roomIIIdepth, wallHeight), 0, 0);

		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = roomIVdepth;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcWallInstance_OuterWall_XV, spaceBoundaryName, _T("Space Boundary XXXII"), pMatrix, build2DPointsFromSquare(roomIVwidth, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = roomIVdepth-delta;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcWallInstance_OuterWall_X, spaceBoundaryName, _T("Space Boundary XXVII"), pMatrix, build2DPointsFromSquare(delta, wallHeight), 0, 0);

		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = 0;
		pMatrix->_42 = roomIVdepth-delta;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcWallInstance_OuterWall_XI, spaceBoundaryName, _T("Space Boundary XXVIII"), pMatrix, build2DPointsFromSquare(roomIIIwidth + innerWallThickness, wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = roomIIIwidth + innerWallThickness;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcWallInstance_OuterWall_XII, spaceBoundaryName, _T("Space Boundary XXIX"), pMatrix, build2DPointsFromSquare(roomIVdepth-delta, wallHeight), 0, 0);

		pMatrix->_11 = 1;
		pMatrix->_12 = 0;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 0;
		pMatrix->_32 = -1;
		pMatrix->_33 = 0;
		pMatrix->_41 = roomIIIwidth + innerWallThickness;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcWallInstance_OuterWall_XIII, spaceBoundaryName, _T("Space Boundary XXX"), pMatrix, build2DPointsFromSquare(roomIVwidth - (roomIIIwidth + innerWallThickness), wallHeight), 0, 0);

		pMatrix->_11 = 0;
		pMatrix->_12 = 1;
		pMatrix->_13 = 0;
		pMatrix->_21 = 0;
		pMatrix->_22 = 0;
		pMatrix->_23 = 1;
		pMatrix->_31 = 1;
		pMatrix->_32 = 0;
		pMatrix->_33 = 0;
		pMatrix->_41 = roomIVwidth;
		pMatrix->_42 = 0;
		pMatrix->_43 = 0;
		buildRelSpaceBoundary2ndLevelInstance(ifcSpaceInstance_Room_IV, ifcWallInstance_OuterWall_XIV, spaceBoundaryName, _T("Space Boundary XXXI"), pMatrix, build2DPointsFromSquare(roomIVdepth, wallHeight), 0, 0);



		/*        ifcWallInstance = createIfcWall(wallName, matrix);
        buildRelDefinesByProperties(ifcWallInstance, Pset_WallCommon);
        if  (m_Quantities.GetCheck()) {
            buildRelDefinesByProperties(ifcWallInstance, buildBaseQuantities_WallStandardCase(wallThickness, wallWidth, wallHeight, (openingWidth / linearConversionFactor) * (openingHeight / linearConversionFactor), linearConversionFactor));
        }

        buildRelAssociatesMaterial(ifcWallInstance, materialLayerSetUsage);
        //createIfcPolylineShape(0, wallThickness/2, wallWidth, wallThickness/2);
        pPolygon = localCreatePolygonStructureFor_(1, -1, wallWidth, wallThickness);
		createIfcExtrudedPolygonShape(pPolygon, wallHeight);

        //pPolygon = localCreatePolygonStructureForSquare(0, 0, wallWidth, wallThickness);
        //createIfcExtrudedPolygonShape(pPolygon, wallHeight);
*/



/*if  ( (m_Opening.IsWindowEnabled())  &&
              (m_Opening.GetCheck()) ) {
            if  (view == COORDINATIONVIEW) {
                ifcOpeningElementInstance = createIfcOpeningElement(openingName, openingXOffset, 0, openingZOffset, true);
            } else {
                ASSERT(view == PRESENTATIONVIEW);
                ifcOpeningElementInstance = createIfcOpeningElement(openingName, openingXOffset, 0, openingZOffset, false);
            }

            if  (m_Quantities.GetCheck()) {
                buildRelDefinesByProperties(ifcOpeningElementInstance, buildBaseQuantities_Opening(wallThickness, openingHeight, openingWidth));
            }

            //
            //      Build relation between Wall and Opening
            //
            buildRelVoidsElementInstance(ifcWallInstance, ifcOpeningElementInstance);

            if  (view == COORDINATIONVIEW) {
                switch  (GetCheckedRadioButton(IDC_RADIO_1_1, IDC_RADIO_1_2)) {
                    case  IDC_RADIO_1_1:
                        pPolygon = localCreatePolygonStructureForSquare(0, 0, openingWidth, wallThickness);
                        createIfcExtrudedPolygonShape(pPolygon, openingHeight);
                        break;
                    case  IDC_RADIO_1_2:
                        pShell = localCreateShellStructureForCuboid(0, 0, 0, openingWidth, wallThickness, openingHeight);
                        createIfcBRepShape(pShell);
                        break;
                    default:
                        MessageBox("Unknown selected type");
                        break;
                }

                if  (m_OpeningBasicRepr.GetCheck()) {
                    createIfcBoundingBoxShape(openingWidth, wallThickness, openingHeight, "Box");
                }
            } else {
                ASSERT(view == PRESENTATIONVIEW);
            }
        }

        if  ( (m_Window.IsWindowEnabled())  &&
              (m_Window.GetCheck()) ) {
            if  ( (m_Opening.IsWindowEnabled())  &&
                  (m_Opening.GetCheck()) ) {
                ifcWindowInstance = createIfcWindow(windowName, 0, windowYOffset, 0, true, openingHeight, openingWidth);

                //
                //      Build relation between Opening and Window
                //
                buildRelFillsElementInstance(ifcOpeningElementInstance, ifcWindowInstance);
            } else {
                ifcWindowInstance = createIfcWindow(windowName, 0, 0, 0, false, openingHeight, openingWidth);
            }

            buildRelDefinesByProperties(ifcWindowInstance, buildPset_WindowCommon());
            if  (m_Quantities.GetCheck()) {
                buildRelDefinesByProperties(ifcWindowInstance, buildBaseQuantities_Window(openingHeight, openingWidth));
            }

            switch  (GetCheckedRadioButton(IDC_RADIO_2_1, IDC_RADIO_2_2)) {
                case  IDC_RADIO_2_1:
                    pPolygon = localCreatePolygonStructureForSquare(0, 0, openingWidth, windowThickness);
                    createIfcExtrudedPolygonShape(pPolygon, openingHeight);
                    break;
                case  IDC_RADIO_2_2:
                    pShell = localCreateShellStructureForCuboid(0, 0, 0, openingWidth, windowThickness, openingHeight);
                    createIfcBRepShape(pShell);
                    break;
                default:
                    MessageBox("Unknown selected type");
                    break;
            }

            if  (m_WindowBasicRepr.GetCheck()) {
                createIfcBoundingBoxShape(openingWidth, windowThickness, openingHeight, "Box");
            }
        }*/









        //
        //  Update header
        //

        char    description[512], timeStamp[512];
        time_t  t;
        struct tm   * tInfo;

        time ( &t );
        tInfo = localtime ( &t );

        if  (view == COORDINATIONVIEW) {
            if  (m_Quantities.GetCheck()) {
                memcpy(description, "ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]", sizeof("ViewDefinition [CoordinationView, QuantityTakeOffAddOnView]"));
            } else {
                memcpy(description, "ViewDefinition [CoordinationView]", sizeof("ViewDefinition [CoordinationView]"));
            }
        } else {
            ASSERT(view == PRESENTATIONVIEW);
            if  (m_Quantities.GetCheck()) {
                memcpy(description, "ViewDefinition [PresentationView, QuantityTakeOffAddOnView]", sizeof("ViewDefinition [PresentationView, QuantityTakeOffAddOnView]"));
            } else {
                memcpy(description, "ViewDefinition [PresentationView]", sizeof("ViewDefinition [PresentationView]"));
            }
        }

        int i = 0, j = 0;
        while  (ifcFileName[i]) {
            if  (ifcFileName[i++] == '\\') {
                j = i;
            }
        }

        itoa(1900 + tInfo->tm_year, &timeStamp[0], 10);
        itoa(100 + 1 + tInfo->tm_mon, &timeStamp[4], 10);
        itoa(100 + tInfo->tm_mday, &timeStamp[7], 10);
        timeStamp[4] = '-';
        timeStamp[7] = '-';
        itoa(100 + tInfo->tm_hour, &timeStamp[10], 10);
        itoa(100 + tInfo->tm_min, &timeStamp[13], 10);
        itoa(100 + tInfo->tm_sec, &timeStamp[16], 10);
        timeStamp[10] = 'T';
        timeStamp[13] = ':';
        timeStamp[16] = ':';
        timeStamp[19] = 0;

        SetSPFFHeader(
				model,
                description,                        //  description
                "2;1",                              //  implementationLevel
                &ifcFileName[j],                    //  name
                &timeStamp[0],                      //  timeStamp
                "Architect",                        //  author
                "Building Designer Office",         //  organization
                "IFC Engine DLL version 1.03 beta", //  preprocessorVersion
                "IFC Engine DLL version 1.03 beta", //  originatingSystem
                "The authorising person",           //  authorization
                "IFC4"                              //  fileSchema
            );

        if  (saveIfx) {
            saveIfcFileAsXml(ifcFileName);
        } else {
            saveIfcFile(ifcFileName);
        }
	}
}

void CMiniExampleDlg::CreateHouse()
{
	CreateFloor();
}

void CMiniExampleDlg::OnIfc() 
{
    //saveIfx = true;

	CreateHouse();

	//return;

/*    if  ( (view == PRESENTATIONVIEW)  &&  (m_Opening.IsWindowEnabled()) ) {
        if  (CheckWallAndWindowMeasuresNotSupported()) {
            return;
        }
    }*/

    OnOK();
}

void CMiniExampleDlg::OnIfx() 
{
    //
    //  Check if the opening is easy enough for this program to generate in Presentation View
    //
/*    if  ( (view == PRESENTATIONVIEW)  &&  (m_Opening.IsWindowEnabled()) ) {
        if  (CheckWallAndWindowMeasuresNotSupported()) {
            return;
        }
    }*/

    saveIfx = true;

    m_FileName.GetWindowText(ifcFileName, 512);
    int i = strlen(ifcFileName);

    if  ( (ifcFileName[i-4] == '.')  &&
          (ifcFileName[i-3] == 'i'  ||  ifcFileName[i-3] == 'I')  &&
          (ifcFileName[i-2] == 'f'  ||  ifcFileName[i-2] == 'F')  &&
          (ifcFileName[i-1] == 'c'  ||  ifcFileName[i-1] == 'C') ) {
        ifcFileName[i] = ifcFileName[i-1] + 'x' - 'c';
        ifcFileName[i+1] = ifcFileName[i-1] + 'm' - 'c';
        ifcFileName[i+2] = ifcFileName[i-1] + 'l' - 'c';
        ifcFileName[i+3] = 0;
        m_FileName.SetWindowText(ifcFileName);
    }

	CreateHouse();

    OnOK();
}

void CMiniExampleDlg::OnShowRooms() 
{
	m_ImageI.SetBitmap(imgLevelIRooms);
	m_ImageII.SetBitmap(imgLevelIIRooms);
}

void CMiniExampleDlg::OnShowWalls() 
{
	m_ImageI.SetBitmap(imgLevelIWalls);
	m_ImageII.SetBitmap(imgLevelIIWalls);
}

void CMiniExampleDlg::OnShowSBs() 
{
	m_ImageI.SetBitmap(imgLevelISpaceBoundaries);
	m_ImageII.SetBitmap(imgLevelIISpaceBoundaries);
}

void CMiniExampleDlg::OnShowSBs2() 
{
	m_ImageI.SetBitmap(imgLevelISpaceBoundaryNos);
	m_ImageII.SetBitmap(imgLevelIISpaceBoundaryNos);
}


void CMiniExampleDlg::OnEnChangeEditDoorWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
