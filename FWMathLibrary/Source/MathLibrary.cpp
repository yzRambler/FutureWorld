#include<memory>
#include "MathLibrary.h"


using namespace FW;


Vector3 Vector3::Cross(Vector3 v3)
{
	Vector3 v3Tmp;

	v3Tmp.x = y*v3.z - z*v3.y;
	v3Tmp.y = z*v3.x - x*v3.z;
	v3Tmp.z = x*v3.y - y*v3.x;

	return v3Tmp;
}

Vector4 Vector4::operator*(const Matrix4x4& mat)
{
	Vector4 v4;
	v4.x = x*mat[0][0] + y*mat[1][0] + z*mat[2][0] + w*mat[3][0];
	v4.y = x*mat[0][1] + y*mat[1][1] + z*mat[2][1] + w*mat[3][1];
	v4.z = x*mat[0][2] + y*mat[1][2] + z*mat[2][2] + w*mat[3][2];
	v4.w = x*mat[0][3] + y*mat[1][3] + z*mat[2][3] + w*mat[3][3];

	return v4;
}



const Matrix3x3& Matrix3x3::Transpose()
{
	Matrix3x3 mat = (*this);
	SetCol(0, mat.GetRow(0));
	SetCol(1, mat.GetRow(1));
	SetCol(2, mat.GetRow(2));

	return (*this);
}

float Matrix3x3::Det()
{
	return (e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1]) - e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0]) 
		+ e[0][2]*(e[1][0]*e[2][1]-e[1][1]*e[2][0]));
}

float Matrix3x3::Cofacter(int row, int col)
{
#ifdef _WND_OPENGL_PLATFORM_
   assert((0 <= row)&&(row<=2)&&(0<=col)&&(col<=2));
#endif
	

	float a[4];

	int count = 0;
	for (int r = 0; r < 3; r++)
	{
		if (r == row)
		{
			continue;
		}

		for (int c = 0; c < 3; c++)
		{
			
			if (c == col)
			{
				continue;
			}

			a[count++] = e[r][c];
		}
	}

	return (a[0] * a[3] - a[1] * a[2]);
}

void Matrix3x3::Adjoint(Matrix3x3& matAdj)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			matAdj.e[c][r] = ((r+c)%2==0?1.0f:-1.0f)*Cofacter(r, c);
		}
	}
}


Matrix4x4& Matrix4x4::Transpose()
{
	Matrix4x4 mat = (*this);
	SetCol(0, mat.GetRow(0));
	SetCol(1, mat.GetRow(1));
	SetCol(2, mat.GetRow(2));
	SetCol(3, mat.GetRow(3));

	return (*this);
}


float Matrix4x4::Det()
{
	return -e[0][3] * Cofacter(0, 3) + e[1][3] * Cofacter(1, 3) - e[2][3] * Cofacter(2, 3) + e[3][3] * Cofacter(3, 3);
}

float Matrix4x4::Cofacter(int row, int col)
{
#ifdef _WND_OPENGL_PLATFORM_
   assert((0 <= row) && (row <= 3) && (0 <= col) && (col <= 3));
#endif
	

	Matrix3x3 mat33;

	int count = 0;
	for (int r = 0; r < 4; r++)
	{
		if (r == row)
		{
			continue;
		}

		for (int c = 0; c < 4; c++)
		{

			if (c == col)
			{
				continue;
			}

			mat33[count / 3][count % 3] = e[r][c];
			count++;
		}
	}

	return mat33.Det();
}

void Matrix4x4::Adjoint(Matrix4x4& matAdj)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			matAdj.e[c][r] = ((r + c) % 2 == 0 ? 1.0f : -1.0f)*Cofacter(r, c);
		}
	}
}

