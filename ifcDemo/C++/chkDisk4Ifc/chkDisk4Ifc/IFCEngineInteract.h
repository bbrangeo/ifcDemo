////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  Project: IFC Engine Series (example using DLL)
//
//  This code may be used and edited freely,
//  also for commercial projects in open and closed source software
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:	peter.bonsma@rdf.bg
//
//  more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//								    peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include	<stdint.h>

#if defined(WIN64) || defined(__LP64__)
	#define int __int64
#else
	#define int __int32
#endif


typedef struct CUSTOMVERTEX {
	double	x;
	double	y;
	double	z;
}	customvertex;

#define		ITEM_UNCHECKED			0
#define		ITEM_PARTLY_CHECKED		1
#define		ITEM_CHECKED			2

typedef struct STRUCT_INSTANCES {
	int					id;
	char				* globalId;
	char				* entityName;
	STRUCT_INSTANCES	* next;

	int					startVertex;
	int					startIndex;
	int					primitiveCount;
}	struct_type;


static int flagbit0  = 1;          // 2^^0    0000.0000..0000.0001
static int flagbit1  = 2;          // 2^^1    0000.0000..0000.0010
static int flagbit2  = 4;          // 2^^2    0000.0000..0000.0100
static int flagbit3  = 8;          // 2^^3    0000.0000..0000.1000

static int flagbit4  = 16;         // 2^^4    0000.0000..0001.0000
static int flagbit5  = 32;         // 2^^5    0000.0000..0010.0000
static int flagbit6  = 64;         // 2^^6    0000.0000..0100.0000
static int flagbit7  = 128;        // 2^^7    0000.0000..1000.0000

static int flagbit8  = 256;        // 2^^8    0000.0001..0000.0000
static int flagbit9  = 512;        // 2^^9    0000.0010..0000.0000
static int flagbit10 = 1024;       // 2^^10   0000.0100..0000.0000
static int flagbit11 = 2048;       // 2^^11   0000.1000..0000.0000

static int flagbit12 = 4096;       // 2^^12   0001.0000..0000.0000
static int flagbit13 = 8192;       // 2^^13   0010.0000..0000.0000
static int flagbit14 = 16384;      // 2^^14   0100.0000..0000.0000
static int flagbit15 = 32768;      // 2^^15   1000.0000..0000.0000


__int32	length(char * txt);
void	InitIFCEngineInteract();
void    AddObject(int id, char * name);
void	RetrieveObjects(char * ObjectSPFFName, char * ObjectGroupName);
int		StartLoadingIfcFile(char * fileName, char * name, CStatic * status, CStatic * totalFiles, CStatic * totalObjects, CStatic * totalTriangles);
void	ReadObjectVisualization(FILE * file, CStatic * status, CStatic * totalTriangles);

#undef int 
