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

#pragma once

typedef struct VECTOR3
{
	double	x, y, z;
}	VECTOR3;

typedef struct MATRIX
{
	double	_11, _12, _13,
			_21, _22, _23,
			_31, _32, _33,
			_41, _42, _43;
}	MATRIX;



void	MatrixIdentity(MATRIX *pInOut);
void	Vector3Identity(VECTOR3 *pInOut);
void	Vector3Transform(VECTOR3 *pOut, const VECTOR3 *pV, const MATRIX *pM);

