//
//  Author:  Peter Bonsma
//  $Date: 1999-12-31 23:59:59 +0000 (Wed, 31 Jan 1999) $
//  $Revision: 3999 $
//  Project: Geometry Kernel
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:  peter.bonsma@rdf.bg
//

#include	"stdafx.h"

#include	"matrixVectorOperations.h"

#include	<math.h>
//#include	<stdint.h>

#if defined(WIN64) || defined(__LP64__)
	#define int __int64
#else
	#define int __int32
#endif


void	MatrixIdentity(MATRIX * pInOut)
{
	pInOut->_12 = pInOut->_13 = 
	pInOut->_21 = pInOut->_23 = 
	pInOut->_31 = pInOut->_32 = 
	pInOut->_41 = pInOut->_42 = pInOut->_43 = 0;

	pInOut->_11 = pInOut->_22 = pInOut->_33 = 1;
}

void	Vector3Identity(VECTOR3 * pInOut)
{
	pInOut->x = pInOut->y = pInOut->z = 0;
}

void	Vector3Transform(VECTOR3 *pOut, const VECTOR3 *pV, const MATRIX *pM)
{
	VECTOR3	pTmp;
	pTmp.x = pV->x * pM->_11 + pV->y * pM->_21 + pV->z * pM->_31 + pM->_41;
	pTmp.y = pV->x * pM->_12 + pV->y * pM->_22 + pV->z * pM->_32 + pM->_42;
	pTmp.z = pV->x * pM->_13 + pV->y * pM->_23 + pV->z * pM->_33 + pM->_43;

	pOut->x = pTmp.x;
	pOut->y = pTmp.y;
	pOut->z = pTmp.z;
}

#undef int 
