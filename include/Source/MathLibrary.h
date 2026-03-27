/*
MathLibrary



Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/




#ifndef _FW_MATH_LIBRARY_
#define _FW_MATH_LIBRARY_

#ifndef  _WND_OPENGL_PLATFORM_
//#include<emscripten/emscripten.h>
#include<emscripten/emscripten.h>
#else

#include<assert.h>

#endif


#include<math.h>

#define PI 3.1415926f

//#define abs(x) ((x)=((x)>0?(x):(-x)))
#define AngleToRadian(a) ((a)*PI/180.0f)
#define FZERO 0.0000001f
//#define EQUAL (x)(y) ((x>y?(x-y):(y-x)) > FZERO )

namespace FW
{

	//inline int abs(int x) { return  ((x) > 0 ? (x) : (-x)); }
	inline float abs(float x) { return ((x) > 0.0f ? (x) : (- x)); }

	class Matrix3x3;
	class Matrix4x4;

//#ifdef _WND_OPENGL_PLATFORM_
//	struct FWMATHLIBCL Vector2
//#else
	struct Vector2
//#endif // _WND_OPENGL_PLATFORM_
	{
		union 
		{
			float c[2];
			struct
			{
				float x;
				float y;
			};
		};
		

		Vector2():x(0.0),y(0.0){}
		Vector2(const Vector2& v) { x = v.x; y = v.y; }
		Vector2(float fx, float fy):x(fx),y(fy){}
		~Vector2(){}
		Vector2 operator-() { return Vector2(-x, -y); }
		Vector2& operator=(Vector2 vt) { x = vt.x; y = vt.y; return *this; }
		Vector2  operator+(Vector2 vt) { return Vector2(x+vt.x, y+vt.y); }

		Vector2 operator*(float f) { return Vector2(x*f, y*f); }
		void operator+=(Vector2 vt) { x += vt.x; y += vt.y; }
		void operator*=(float f) { x *= f; y *= f; }

		float Len() { return sqrtf(x * x + y * y);}
		float SquareLen() { return x * x + y * y; }
		void Normalize() { float len = sqrtf(x * x + y * y); x /= len; y /= len; }
		void Clean() { x = y = 0.0; }
		float Dot(const Vector2& v) { return x * v.x + y * v.y; }
	};


//#ifdef _WND_OPENGL_PLATFORM_
//	struct FWMATHLIBCL Vector3
//#else
	struct Vector3
//#endif // _WND_OPENGL_PLATFORM_
	{
		union 
		{
			Vector2 v2;
			float c[3];
			struct 
			{
				float x;
				float y;
				float z;
			};
		};

		Vector3():x(0.0), y(0.0), z(0.0){}
		Vector3(const Vector3& v):x(v.x),y(v.y),z(v.z){}
		Vector3(float fx, float fy, float fz):x(fx),y(fy),z(fz){}
		~Vector3() {}

		Vector3 operator=(const Vector3& vt) { x = vt.x; y = vt.y; z = vt.z; return *this; }
		Vector3 operator-() { return Vector3(-x, -y, -z); }
		Vector3 operator-(const Vector3& vt) { return Vector3(x-vt.x, y-vt.y, z-vt.z); }
		Vector3 operator+(const Vector3& vt) { return Vector3(x + vt.x, y + vt.y, z+vt.z); }

		Vector3 operator*(float f) { return Vector3(x*f, y*f, z*f); }


		void operator+=(const Vector3& vt) { x += vt.x; y += vt.y; z += vt.z; }
		void operator*=(float f) { x *= f; y *= f; z *= f; }
	
		float Len() { return sqrtf(x * x + y * y + z * z); }
		float SquareLen() { return  x * x + y * y + z * z;  }
		void Normalize() { float len = sqrtf(x * x + y * y + z * z); x /= len; y /= len; z /= len; }
		Vector3 Cross(Vector3 v3);
		void Clean() { x = y = z = 0.0; }
		float Dot(const Vector3& v) { return x * v.x + y * v.y + z * v.z; }
	};


//#ifdef _WND_OPENGL_PLATFORM_
//	struct FWMATHLIBCL Vector4
//#else
	struct Vector4
//#endif // _WND_OPENGL_PLATFORM_
	{
		union 
		{
			Vector3 v3;
			float c[4];
			struct 
			{
				float x;
				float y;
				float z;
				float w;
			};
		};
		

		Vector4():x(0.0),y(0.0),z(0.0),w(0.0){}
		Vector4(const Vector4& v):x(v.x),y(v.y),z(v.z),w(v.w){}
		Vector4(const Vector3& v, float fw):x(v.x),y(v.y),z(v.z),w(fw){}
		Vector4(float fx, float fy, float fz, float fw):x(fx),y(fy),z(fz),w(fw){}
		~Vector4(){}

		Vector4& operator=(const Vector4& vt) { x = vt.x; y = vt.y; z = vt.z; w = vt.w; return *this; }
		Vector4 operator+(const Vector4& vt) { return Vector4(x+vt.x, y+vt.y, z+vt.z, w+vt.w); }
		Vector4 operator-() { return Vector4(-x, -y, -z, -w); }
		Vector4 operator-(const Vector4& vt) { return Vector4(x-vt.x, y-vt.y, z-vt.z, w-vt.w); }
		Vector4 operator*(float f) { return Vector4(x*f, y*f, z*f, w*f); }
		Vector4 operator*(const Matrix4x4& mat);

		void operator+=(const Vector4& vt) { x += vt.x; y += vt.y; z += vt.z; w += vt.w;}
		void operator*=(float f) { x *= f; y *= f; z *= f; w *= f;}

		void Normalize() { float len = sqrtf(x * x + y * y + z * z + w * w); x /= len; y /= len; z /= len; w /= len; }
		void Clean() { x = y = z = w = 0.0; }
		void SetPos(const Vector3& v3) { x = v3.x; y = v3.y; z = v3.z; w = 1.0; }
		void SetVector(const Vector3& v3) { x = v3.x; y = v3.y; z = v3.z; w = 0.0; }
		float Dot(const Vector4& v) { return x * v.x + y * v.y + z * v.z + w * v.w; }
	};



//#ifdef _WND_OPENGL_PLATFORM_
//	class FWMATHLIBCL Matrix3x3
//#else
	//row major order
	class Matrix3x3
//#endif // _WND_OPENGL_PLATFORM_
	{
	protected:
		union 
		{
			float e[3][3];

			struct 
			{
				float _00, _01, _02;
				float _10, _11, _12;
				float _20, _21, _22;
			};

			Vector3 v[3];  //row vector3
			struct 
			{
				Vector3 _v0;  //row vector3
				Vector3 _v1;  //row vector3
				Vector3 _v2;  //row vector3
			};
		};

		friend Vector3;

	public:
		Matrix3x3(){ _00 = _01 = _02 = _10 = _11 = _12 = _20 = _21 = _22 = 0.0f; }
		Matrix3x3(Matrix3x3& mat) { _v0 = mat._v0; _v1 = mat._v1; _v2 = mat._v2; }
		~Matrix3x3() {}

		Matrix3x3& operator= (const Matrix3x3& mat) { _v0 = mat._v0; _v1 = mat._v1; _v2 = mat._v2; return *this; }
		void operator+= (const Matrix3x3& mat) { _v0 += mat._v0; _v1 += mat._v1; _v2 += mat._v2; }
		void operator*= (float f) { _v0 *= f; _v1 *= f; _v2 *= f; }
		Matrix3x3& operator*(float f) { _v0 *= f; _v1 *= f; _v2 *= f; return *this; }

		Matrix3x3& operator*(const Matrix3x3& mat)
		{
			Matrix3x3 matTmp = (*this);
			for (int r = 0; r < 3; r++)
			{
				for (int m = 0; m < 3; m++)
				{
					e[r][m] = matTmp.v[r].Dot(mat.GetCol(m));
				}
			}

			return *this;
		}

		void operator*=(const Matrix3x3& mat) { (*this)*mat; }
		float* operator[](int i)
		 {
#ifdef _WND_OPENGL_PLATFORM_
       assert((0 <= i) && (i <= 2)); 
#endif
		 	 
		 	 return ((float*)e[i]);
		 }

		float Det();
		float Cofacter(int row, int col);
		void Zero() { _00 = _01 = _02 = _10 = _11 = _12 = _20 = _21 = _22 = 0.0f; }
		void Identity() { _01 = _02 = _10 = _12 = _20 = _21 = 0.0f; _00 = _11 = _22 = 1.0f; }
		const Matrix3x3& Transpose();
		Matrix3x3& Inverse()
		{
			float det = Det();
#ifdef _WND_OPENGL_PLATFORM_
      //assert(det > FZERO);
#endif

			Matrix3x3 matAdj;
			Adjoint(matAdj);
			return *this = matAdj * (1.0f / det);
		}


		void SetElt(int r, int m, float v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= r) && (r <= 2) && (0 <= m) && (m <= 2));
#endif
			
			if ((0 <= r) && (r <= 2) && (0 <= m) && (m <= 2)) { e[r][m] = v; }
		}

		void SetRow(int ind, float x, float y, float z) 
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 2));
#endif
			
			if ((ind >= 0) && (ind <= 2)) { e[ind][0] = x; e[ind][1] = y; e[ind][2] = z; }
		}

		void SetRow(int ind, const Vector3& v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 2));
#endif
			if ((ind >= 0) && (ind <= 2)) { e[ind][0] = v.x; e[ind][1] = v.y; e[ind][2] = v.z; }
		}

		//set column
		void SetCol(int ind, float x, float y, float z)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 2));
#endif
			
			if ((ind >= 0) && (ind <= 2)) { e[0][ind] = x; e[1][ind] = y; e[2][ind] = z; }
		}

		//set column
		void SetCol(int ind, const Vector3& v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 2));
#endif

			if ((ind >= 0) && (ind <= 2)) { e[0][ind] = v.x; e[1][ind] = v.y; e[2][ind] = v.z; }
		}

		Vector3& GetRow(int ind)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 2));
#endif
			return (ind == 0) ? _v0 : ((ind == 1) ? _v1 : _v2);
		}

		//get column
		Vector3 GetCol(int ind) const
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 2));
#endif
			
			return Vector3(e[0][ind], e[1][ind], e[2][ind]);
		}

	private:
		void Adjoint(Matrix3x3& matAdj);
	    
	};


//#ifdef _WND_OPENGL_PLATFORM_
//	class FWMATHLIBCL Matrix4x4
//#else
	//row major order
	class Matrix4x4
//#endif // _WND_OPENGL_PLATFORM_
	{
	protected:
		union 
		{
			float e[4][4];
			struct 
			{
				float _00, _01, _02, _03;
				float _10, _11, _12, _13;
				float _20, _21, _22, _23;
				float _30, _31, _32, _33;
			};

			Vector4 v[4];    //row vector4
			struct 
			{
				Vector4 _v0;  //row vector4
				Vector4 _v1;  //row vector4
				Vector4 _v2;  //row vector4
				Vector4 _v3;  //row vector4
			};
		};

		

	public:
		Matrix4x4() { _00 = _01 = _02 = _03 = _10 = _11 = _12 = _13 = _20 = _21 = _22 = _23 = _30 = _31 = _32 = _33 = 0.0f; }
		Matrix4x4(const Matrix4x4& mat) { _v0 = mat._v0; _v1 = mat._v1; _v2 = mat._v2; _v3 = mat._v3; }
		~Matrix4x4(){}

		Matrix4x4& operator=(const Matrix4x4& mat) { _v0 = mat._v0; _v1 = mat._v1; _v2 = mat._v2; _v3 = mat._v3; return *this; }
		Matrix4x4& operator+(const Matrix4x4& mat) { _v0 += mat._v0; _v1 += mat._v1; _v2 += mat._v2; _v3 += mat._v3; return *this; }
		Matrix4x4& operator*(const Matrix4x4& mat) 
		{
			Matrix4x4 matTmp = (*this);
			for (int r = 0; r < 4; r++) 
			{ 
				for (int m = 0; m < 4; m++) 
				{
					e[r][m] = matTmp.v[r].Dot(mat.GetCol(m));
				} 
			}

			return (*this);
		}

		void operator*=(const Matrix4x4& mat){ (*this)*mat; }

		Matrix4x4& operator*(float f) { _v0 *= f; _v1 *= f; _v2 *= f; _v3 *= f; return *this; }
		void operator+=(const Matrix4x4& mat) { _v0 += mat._v0; _v1 += mat._v1; _v2 += mat._v2; _v3 += mat._v3; }
		void operator*=(float f) { _v0 *= f; _v1 *= f; _v2 *= f; _v3 *= f;}
		float* operator[](int i) const { 
#ifdef _WND_OPENGL_PLATFORM_
      assert((0<=i)&&(i<=3)); 
#endif
			
			return ((float*)e[i]); 
			}

		float Det();
		float Cofacter(int row, int col);
		void Zero() { _00 = _01 = _02 = _03 = _10 = _11 = _12 = _13 = _20 = _21 = _22 = _23 = _30 = _31 = _32 = _33 = 0.0f; }
		void Identity() { _01 = _02 = _03 = _10 = _12 = _13 = _20 = _21 = _23 = _30 = _31 = _32 = 0.0f; _00 = _11 = _22 = _33 = 1.0f; }

		Matrix4x4& Transpose();
		Matrix4x4& Inverse()
		{
			float det = Det();
#ifdef _WND_OPENGL_PLATFORM_
      //assert(det > FZERO);
#endif
			

			Matrix4x4 matAdj;
			Adjoint(matAdj);
			return *this = matAdj * (1.0f / det);
		}

		void SetElt(int r, int m, float v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= r) && (r <= 3)&& (0 <= m) && (m <= 3));
#endif
			
			if ((0 <= r) && (r <= 3) && (0 <= m) && (m <= 3)) { e[r][m] = v; }
		}

		void SetRow(int ind, float x, float y, float z, float w)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			if ((ind >= 0) && (ind <= 3)) { e[ind][0] = x; e[ind][1] = y; e[ind][2] = z; e[ind][3] = w; }
		}

		void SetRow(int ind, const Vector4& v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			if ((ind >= 0) && (ind <= 3)) { e[ind][0] = v.x; e[ind][1] = v.y; e[ind][2] = v.z; e[ind][3] = v.w; }
		}

		//Set row with vector3 align left.
		void SetRowV3AL(int ind, const Vector3& v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			if ((ind >= 0) && (ind <= 3)) { e[ind][0] = v.x; e[ind][1] = v.y; e[ind][2] = v.z;}
		}

		//set column
		void SetCol(int ind, float x, float y, float z, float w=1.0)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			if ((ind >= 0) && (ind <= 3)) { e[0][ind] = x; e[1][ind] = y; e[2][ind] = z; e[3][ind] = w; }
		}

		//set column
		void SetCol(int ind, const Vector4& v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			if ((ind >= 0) && (ind <= 3)) { e[0][ind] = v.x; e[1][ind] = v.y; e[2][ind] = v.z; e[3][ind] = v.w; }
		}

		//Set column with vector3 align top, zero appending.
		void SetColV3AT(int ind, const Vector3& v)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			if ((ind >= 0) && (ind <= 3)) { e[0][ind] = v.x; e[1][ind] = v.y; e[2][ind] = v.z; }
		}

		Vector4& GetRow(int ind)
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			return (ind == 0) ? _v0 : ((ind == 1) ? _v1 : (ind == 2)?_v2:_v3);
		}

		//get column
		Vector4 GetCol(int ind) const
		{
#ifdef _WND_OPENGL_PLATFORM_
      assert((0 <= ind) && (ind <= 3));
#endif
			
			return Vector4(e[0][ind], e[1][ind], e[2][ind], e[3][ind]);
		}

	private:
		void Adjoint(Matrix4x4& matAdj);

		friend class AMatrix4x4;
	};



//#ifdef _WND_OPENGL_PLATFORM_
//	class FWMATHLIBCL Quaternion
//#else
	class Quaternion
//#endif // _WND_OPENGL_PLATFORM_
	{
	public:
		union
		{
			struct
			{
				Vector3 v;
				//float w;
			};

			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};

	public:
		Quaternion() { x = y = z = w = 0.0f; }
		Quaternion(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }
		Quaternion(const Vector3& sv, float sw) { v = sv; w = sw; }
		Quaternion(const Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; }
		virtual ~Quaternion(){}

		Quaternion operator+(Quaternion q) { return Quaternion(v + q.v, w + q.w); }
		Quaternion operator-(Quaternion& q) { return Quaternion(v - q.v, w - q.w); }
		Quaternion operator*(Quaternion q) 
		{ return Quaternion(v.Cross(q.v) + q.v * w + v * q.w, w * q.w - v.Dot(q.v));}

		Quaternion operator*(float f) { return Quaternion(x*f , y*f, z*f, w*f); }

		Quaternion& operator=(const Quaternion& q) { v = q.v; w = q.w; return(*this); }
		void operator*=(float f) { x *= f; y *= f; z *= f; w *= f; }
		void operator+=(Quaternion& q) { v += q.v; w += q.w; }
		
		Quaternion Conjugate() { return Quaternion(-v,w); }
		float Normalize() { return sqrt(x*x + y * y + z * z + w * w); }
		float DotProduct(Quaternion& q) { return v.Dot(q.v) + w * q.w; }
		void Zero() { x = y = z = w = 0.0f; }
	};




//#ifdef _WND_OPENGL_PLATFORM_
//	class FWMATHLIBCL DualQuaternion
//#else
	class DualQuaternion
//#endif // _WND_OPENGL_PLATFORM_
	{
	private:
		Quaternion a;      //first quaternion
		Quaternion b;      //second quaternion ( epsilon part )

	public:
		DualQuaternion() {}
		DualQuaternion(Quaternion q, Vector4 t) { a = q; b = (Quaternion(t.v3, 0.0f) * a) * 0.5f; }
		virtual ~DualQuaternion(){}

		DualQuaternion& operator*(float f) { a *= f; b *= f;  return *this; }
		void operator +=(DualQuaternion& dq) { a += dq.a; b += dq.b; }
		void operator -=(DualQuaternion& dq) { a = a-dq.a; b = b-dq.b;  }
		Quaternion& GetFirstQuaternion() { return a; }

		//Assumes that the rotation is expressed first, followed by translation.
		Vector4 Deform(Vector4& v4)
		{
			//get translation
			Quaternion qt = b * a.Conjugate() * 2.0f;
			
			//compute the rotation result 
			Quaternion qr = a * Quaternion(v4.v3, 0.0f) * a.Conjugate();

			return Vector4((qt + qr).v, 1.0f);
		}

		void Normalize() 
		{ 
			float na = a.Normalize();  
			b = (a*b.Conjugate() + b * a.Conjugate());
			b *= 1.0f / (2.0f * na);

			a.Zero();
			a.w = na;
		}

		void Zero() { a.Zero(); b.Zero(); }
	};




//#ifdef _WND_OPENGL_PLATFORM_
//	class FWMATHLIBCL AMatrix4x4 : public Matrix4x4
//#else
	//the affine matrix4x4, row major order too.
	class AMatrix4x4 : public Matrix4x4
//#endif // _WND_OPENGL_PLATFORM_
	{
	public:
		AMatrix4x4() {}
		virtual ~AMatrix4x4() {}

		AMatrix4x4& operator=(const Matrix4x4& mat) { _v0 = mat._v0; _v1 = mat._v1; _v2 = mat._v2; _v3 = mat._v3; return *this; }

		void SetT(Vector3& v3){ SetRow(3, v3.x, v3.y, v3.z, 1.0f); }


		Quaternion getQ()
		{
			float qw = sqrt(_00 + _11 + _22 + 1.0f) * 0.5f;
			float f = 1.0f / (4.0f * qw);
			return Quaternion((_21 - _12)*f, (_02 - _20)*f, (_10 - _01)*f, qw);
		}

		Vector4 getT() { return GetRow(3); }

	private:
		//CFrame m_jBaseFrame;
	};


//#ifdef _WND_OPENGL_PLATFORM_
//
//	FWMATHLIBFU float Dot(const Vector3& v1, const Vector3& v2);
//	FWMATHLIBFU Vector3 Mul3(const Vector3& v, Matrix3x3& mat);
//	FWMATHLIBFU Vector4 Mul4(const Vector4& v, AMatrix4x4& mat);
//
//#else

	extern "C" inline float Dot(const Vector3& v1, const Vector3& v2)
	{
		return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
	}


	//Equation: row vector x matrix
	extern "C" inline Vector3 Mul3(const Vector3& v, Matrix3x3& mat)
	{
		return Vector3(v.x*mat[0][0] + v.y*mat[1][0] + v.z*mat[2][0],
			v.x*mat[0][1] + v.y*mat[1][1] + v.z*mat[2][1],
			v.x*mat[0][2] + v.y*mat[1][2] + v.z*mat[2][2]);
	}


	//Equation: row vector x matrix
	extern "C" inline Vector4 Mul4(const Vector4& v, Matrix4x4& mat)
	{
		return Vector4(v.x*mat[0][0] + v.y*mat[1][0] + v.z*mat[2][0] + v.w*mat[3][0],
			v.x*mat[0][1] + v.y*mat[1][1] + v.z*mat[2][1] + v.w*mat[3][1],
			v.x*mat[0][2] + v.y*mat[1][2] + v.z*mat[2][2] + v.w*mat[3][2],
			v.x*mat[0][3] + v.y*mat[1][3] + v.z*mat[2][3] + v.w*mat[3][3]);
	}

//#endif // _WND_OPENGL_PLATFORM_


	
}

#endif // !_FW_MATH_LIBRARY_
