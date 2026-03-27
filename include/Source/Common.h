#ifndef _FW_COMMON_
#define _FW_COMMON_


#include<vector>
#include<string>
//#include"CSkin.h"
#include"MathLibrary.h"
#include"BaseData.h"

#define ID_VALID(x) (((x) & 0x0000ffff) != 0)



namespace FW
{

	typedef struct FMATRIX
	{
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
		};
	}FMATRIX;

	typedef	union ID
	{
		FDWORD  v;  //id value
		struct
		{
			FWORD  u : 16;  //use index  for v low 16 bits.
			FWORD  r: 16;   //rest index for v high 16 bits.
		};
	}UID;


	//For .obj file+
	typedef struct {}Data;

	typedef struct Vertex : public Data
	{
		union
		{
			float c[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};

	}Vertex, Normal;

	typedef struct UV : public Data
	{
		union
		{
			float c[2];
			struct
			{
				float u;
				float v;
			};

		};

	}UV;


	/*
	//Note:
	  0. This struct Surface is not a triangle surface, it just is a point of this triangle while reading the surface
	     data from the file.

	  1. The parameter _a, _b and _c are the indices of vertex, uv, and normal separately in turn in .obj file 
	     and .fbx file.   The least index value is one in .obj file, but zero in .fbx file. 

	  2. In .obj file, the index is counted from one not zero.
	*/

	typedef struct Surface : Data
	{
		union
		{
			unsigned int c[3];
			struct
			{
				unsigned int _a;   // The index of the vertex in .obj file.  _a - 1 map the index in program.
				                   // The index of the vertex in .fbx file.  _a map the index in program.

				unsigned int _b;   // The index of the uv in .obj file.  _b - 1 map the index in program.
				                   // The index of the uv in .fbx file.  _b map the index in program.

				unsigned int _c;   // The index of the normal in .obj file. _c - 1 map the index in program.
				                   // The index of the normal in .fbx file. _c map the index in program.
			};
		};

	}Surface;



	typedef std::vector<Vertex*> VTVT;
	typedef std::vector<Normal*> VTNL;
	typedef std::vector<UV*> VTUV;
	typedef std::vector<Surface*> VTSF;

	typedef VTVT::iterator VTVT_ITER;
	typedef VTNL::iterator VTNL_ITER;
	typedef VTUV::iterator VTUV_ITER;
	typedef VTSF::iterator VTSF_ITER;




	/* NOTE:

	1. For .fbx file the offsetVertex = offsetvertex = offsetUV = 0, but not for .obj file.
	
	2. The index of normals vector is matched the order of vertex index (of vertices vector).
	   The index of the normal is equal the index of the vertex in most cases for .obj file. ( Refer to .obj file )
	   The index of the normal is equal the index of the vertex for .fbx file.

	3. The struct surface members are different for .obj file and .fbx file. (Refer to the struct Surface definition)

	*/
	class CSkin;
	typedef struct OBJECT
	{
		//name
		std::string name;

		//the index offset of vertices in .obj file
		int offsetVertex;  

		//the index offset of normals in .obj file
		int offsetNormal;  

		//the index offset of uvs in .obj file
		int offsetUV;  

		//vertex pos array
		VTVT vertices;

		//vertex normal array
		VTNL normals;        
		                     
		//vertex tangent array
		VTVT tangents;

		//vertex uv array
		VTUV uvs;

		//surface index array
		VTSF surfaces;

		//just for skeleton animation??
		Matrix4x4* pMatGeometry;

		Matrix4x4* pMatLocalTransform;

		CSkin* pSkin;

		unsigned int sizeVertices;

		unsigned int sizeNormals;

		unsigned int sizeTangents;

		unsigned int sizeUVs;

		unsigned int sizePolygens;

		unsigned int sizeSkinData;

		//the size of this OBJECT block self.
		unsigned int sizeOBJ;

		unsigned int sizeFWDMeshBlock;

	}OBJECT;


	class CIter
	{
	public:
		CIter() {}
		virtual ~CIter() {}

		virtual void SetBegin() = 0;
		virtual Data* GetCurrent() = 0;
		virtual void MoveToNext() = 0;
		virtual bool IsEnd() = 0;
	};


	class CVertexIter : public CIter
	{
	public:
		CVertexIter(VTVT_ITER begin, VTVT_ITER end) :m_iterBegin(begin), m_iterWork(begin), m_iterEnd(end) {}
		virtual ~CVertexIter() {}

		void Init(VTVT_ITER begin, VTVT_ITER end) { m_iterBegin = begin; m_iterWork = begin; m_iterEnd = end; }

		virtual void SetBegin() { m_iterWork = m_iterBegin; }
		virtual Data* GetCurrent() { return *m_iterWork; }
		virtual void MoveToNext() { if (!IsEnd()) { m_iterWork++; } }
		virtual bool IsEnd() { return m_iterWork == m_iterEnd; }

	public:
		VTVT_ITER m_iterBegin;
		VTVT_ITER m_iterEnd;
		VTVT_ITER m_iterWork;
	};

	class CNormalIter : public CIter
	{
	public:
		CNormalIter(VTNL_ITER begin, VTNL_ITER end) :m_iterBegin(begin), m_iterWork(begin), m_iterEnd(end) {}
		virtual ~CNormalIter() {}

		void Init(VTNL_ITER begin, VTNL_ITER end) { m_iterBegin = begin; m_iterWork = begin; m_iterEnd = end; }

		virtual void SetBegin() { m_iterWork = m_iterBegin; }
		virtual Data* GetCurrent() { return *m_iterWork; }
		virtual void MoveToNext() { if (!IsEnd()) { m_iterWork++; } }
		virtual bool IsEnd() { return m_iterWork == m_iterEnd; }

	public:
		VTNL_ITER m_iterBegin;
		VTNL_ITER m_iterEnd;
		VTNL_ITER m_iterWork;
	};

	class CUVIter : public CIter
	{
	public:
		CUVIter(VTUV_ITER begin, VTUV_ITER end) :m_iterBegin(begin), m_iterWork(begin), m_iterEnd(end) {}
		virtual ~CUVIter() {}

		void Init(VTUV_ITER begin, VTUV_ITER end) { m_iterBegin = begin; m_iterWork = begin; m_iterEnd = end; }

		virtual void SetBegin() { m_iterWork = m_iterBegin; }
		virtual Data* GetCurrent() { return *m_iterWork; }
		virtual void MoveToNext() { if (!IsEnd()) { m_iterWork++; } }
		virtual bool IsEnd() { return m_iterWork == m_iterEnd; }

	public:
		VTUV_ITER m_iterBegin;
		VTUV_ITER m_iterEnd;
		VTUV_ITER m_iterWork;
	};

	class CSurfaceIter : public CIter
	{
	public:
		CSurfaceIter(VTSF_ITER begin, VTSF_ITER end) :m_iterBegin(begin), m_iterWork(begin), m_iterEnd(end) {}
		virtual ~CSurfaceIter() {}

		void Init(VTSF_ITER begin, VTSF_ITER end) { m_iterBegin = begin; m_iterWork = begin; m_iterEnd = end; }

		virtual void SetBegin() { m_iterWork = m_iterBegin; }
		virtual Data* GetCurrent() { return *m_iterWork; }
		virtual void MoveToNext() { if (!IsEnd()) { m_iterWork++; } }
		virtual bool IsEnd() { return m_iterWork == m_iterEnd; }

	public:
		VTSF_ITER m_iterBegin;
		VTSF_ITER m_iterEnd;
		VTSF_ITER m_iterWork;
	};



	


	//For mesh
	typedef struct SRelation
	{
		bool inited;
		unsigned int index;   // the location in  m_vtSVertex
		unsigned int uvIndex;
		SRelation* next;
	}SRelation;

	/*
	typedef struct SVertex
	{
		union
		{
			float m[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};
	}SVertex;


	typedef struct SNormal
	{
		union
		{
			float m[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};
	}SNormal;


	typedef struct STangent
	{
		union
		{
			float m[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};
	};



	typedef struct SUV
	{
		union
		{
			float m[2];
			struct
			{
				float x;
				float y;
			};
		};
	};
	*/


	typedef struct SSurface
	{
		union
		{
			unsigned int arIndex[3];
			struct
			{
				unsigned int _v0;      //the index of the first vertex
				unsigned int _v1;      //the index of the second vertex
				unsigned int _v2;      //the index of the third vertex
			};

		};
	}SSurface;




	typedef struct SVertexOld
	{
		union
		{
			float m[11];
			struct 
			{
				float x;     //pos x
				float y;     //pos y
				float z;     //pos z
				float nx;    //normal x
				float ny;    //normal y
				float nz;    //normal z
				float tx;    //tangent x
				float ty;    //tangent y 
				float tz;    //tangent z
				float u;
				float v;
			};
			
		};
		
	}SVertexOld;

	/*
	typedef struct SVertex
	{
		union
		{
			//float arVertices[11];
			//struct
			//{
			//	bool completed;
			//	unsigned int meshIndex;
			//	float x;     //pos x
			//	float y;     //pos y
			//	float z;     //pos z
			//	float nx;    //normal x
			//	float ny;    //normal y
			//	float nz;    //normal z
			//	float tx;    //tangent x
			//	float ty;    //tangent y
			//	float tz;    //tangent z
			//	float u;     //UV coordinate u
			//	float v;     //UV coordinate v
			//};

			//float arVertices[11];
			//struct
			//{
			//	float x;     //pos x
			//	float y;     //pos y
			//	float z;     //pos z
			//	float nx;    //normal x
			//	float ny;    //normal y
			//	float nz;    //normal z
			//	float tx;    //tangent x
			//	float ty;    //tangent y
			//	float tz;    //tangent z
			//	float u;     //UV coordinate u
			//	float v;     //UV coordinate v
			//};


			//float arVertices[8];
			//struct
			//{
			//	float x;
			//	float y;
			//	float z;
			//	float nx;
			//	float ny;
			//	float nz;
			//	float u;
			//	float v;
			//};

		};

	}SVertex;
	*/

	//typedef struct SSurface
	typedef struct SSurfaceOld
	{
		union
		{
			unsigned int arIndex[9];
			struct
			{
				unsigned int _v0;      //the index of the first vertex
				unsigned int _v1;      //the index of the second vertex
				unsigned int _v2;      //the index of the third vertex
				unsigned int _n0;	   //the normal index of the first vertex
				unsigned int _n1;      //the normal index of the second vertex
				unsigned int _n2;      //the normal index of the third vertex
				unsigned int _uv0;     //the UV index of the first vertex
				unsigned int _uv1;     //the UV index of the second vertex
				unsigned int _uv2;     //the UV index of the third vertex
			};

		};
	}SSurfaceOld;



	typedef struct SBorder
	{
		Vector3 start;
		Vector3 end;
	}SBorder;



	//for CFBXFile and CFWDFile
	class CBAT;
	typedef std::vector<CBAT*> VTBNTK;
	typedef VTBNTK::iterator VTBNTK_ITER;




	//For primatter center
	class COBJFile;
	class CPngFile;
	class CShaderFile;
	typedef std::vector<COBJFile*> VTOBJFILE;
	typedef std::vector<CPngFile*> VTPNGFILE;
	typedef std::vector<CShaderFile*> VTSHADERFILE;
}





#endif // !_FW_COMMON_
