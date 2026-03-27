/*

FOColorOperation


Author:  Zhen Yi

Created Date:  Oct. 26, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_FOCOLOR_OPERATION_
#define _FW_FOCOLOR_OPERATION_

#include <GL/glew.h>
#include "CCommand.h"
#include"FWEngineCoreExport.h"

namespace FW
{

// For the camera and the material.
	class DLLCOAPI CEnable : public CCommand
	{
	private:
		typedef void(CEnable::*PFUNC)();

	public:
		CEnable():m_pWorkFun(0){}
		virtual ~CEnable() {}

		virtual bool Initialize( const char* pParam );
		virtual void Execute() { (this->*m_pWorkFun)(); }

	private:
		//for camera
		void funEnableStencilTest() { glEnable(GL_STENCIL_TEST); }
		void funEnableDepthTest() { glEnable(GL_DEPTH_TEST); }
		void funEnableBlend() { glEnable(GL_BLEND); }

		//for material
		void funEnableCullFace() { glEnable(GL_CULL_FACE); }


	private:
		PFUNC m_pWorkFun;
	};


	class DLLCOAPI CDisable : public CCommand
	{
	private:
		typedef void (CDisable::*PFUNC)();

	public:
		CDisable():m_pWorkFun(0) {}
		virtual ~CDisable() {}

		virtual bool Initialize(const char* pParam);
		virtual void Execute() { (this->*m_pWorkFun)() ; }

	private:
		//for camera
		void funDisableStencilTest() { glDisable(GL_STENCIL_TEST); }
		void funDisableDepthTest() { glDisable(GL_DEPTH_TEST); }
		void funDisableBlend() { glDisable(GL_BLEND); }

		//for material
		void funDisableCullFace() { glDisable(GL_CULL_FACE); }

	private:
		PFUNC m_pWorkFun;
	};


	class DLLCOAPI CColorClear : public CCommand
	{
	public:
		CColorClear(float r, float g, float b, float a) : m_valR(r), m_valG(g), m_valB(b), m_valA(a) {}
		virtual ~CColorClear() {}

		virtual void Execute() { glClearColor(m_valR, m_valG, m_valB, m_valA); }

	private:
		GLclampf m_valR;
		GLclampf m_valG;
		GLclampf m_valB;
		GLclampf m_valA;
	};


	class DLLCOAPI CViewPortSet : public CCommand
	{
	public:
		CViewPortSet(float x, float y, float w, float h) :m_x(x), m_y(y), m_fWidth(w), m_fHeight(h) {}
		virtual ~CViewPortSet() {}

		virtual void Execute() { glViewport(m_x, m_y, m_fWidth, m_fHeight); }


	private:
		float m_x;
		float m_y;
		float m_fWidth;
		float m_fHeight;
	};



//=================================================================================

// Just for the material.
	
	class DLLCOAPI CCullFace : public CCommand
	{
	private:
		typedef void(CCullFace::*PFUNC)();

	public:
		CCullFace():m_pWorkFun(0){}
		virtual ~CCullFace() {}

		virtual bool Initialize(const char* pParam);
		virtual void Execute() { (this->*m_pWorkFun)(); }

	private:
		void funCullFaceFront() { glCullFace(GL_FRONT); }
		void funCullFaceBack() { glCullFace(GL_BACK); }
		void funCullFaceFB() { glCullFace(GL_FRONT_AND_BACK); }

	private:
		PFUNC m_pWorkFun;
	};


	class DLLCOAPI CFrontFace : public CCommand
	{
	private:
		typedef void(CFrontFace::*PFUNC)();

	public:
		CFrontFace() :m_pWorkFun(0) {}
		virtual ~CFrontFace() {}

		virtual bool Initialize(const char* pParam);
		virtual void Execute() { (this->*m_pWorkFun)(); }

	private:
		void funFrontFaceCW() { glFrontFace(GL_CW); }
		void funFrontFaceCCW() { glFrontFace(GL_CCW); }

	private:
		PFUNC m_pWorkFun;
	};


	class DLLCOAPI CClear : public CCommand
	{
	private:
		typedef void (CClear::*PFUNC)();

	public:
		CClear():m_pWorkFun(0){}
		virtual ~CClear() {}

		virtual bool Initialize(const char* pParam);
		virtual void Execute() { (this->*m_pWorkFun)(); }

	private:
		void funClearStencilBB() { glClear(GL_STENCIL_BUFFER_BIT); }
		void funClearDepthBB() { glClear(GL_DEPTH_BUFFER_BIT); }
		void funclearColorBB() { glClear(GL_COLOR_BUFFER_BIT); }

	private:
		PFUNC m_pWorkFun;
	};



	class DLLCOAPI CStencilClear : public CCommand
	{
	public:
		CStencilClear(int val) :m_val(val) {}
		virtual ~CStencilClear() {}

		virtual void Execute() { glClearStencil(m_val); }

	private:
		GLint m_val;
	};

	class DLLCOAPI CStencilMask : public CCommand
	{
	public:
		CStencilMask(int val) :m_val(val) {}
		virtual ~CStencilMask() {}

		virtual void Execute() { glStencilMask(m_val); }

	private:
		GLint m_val;
	};


	class DLLCOAPI CDepthClear : public CCommand
	{
	public:
		CDepthClear(float val) :m_val(val) {}
		virtual ~CDepthClear() {}

		virtual void Execute() { glClear(m_val); }

	private:
		GLclampf m_val;
	};


	class DLLCOAPI CDepthMask : public CCommand
	{
	public:
		CDepthMask(bool b) :m_val(b) {}
		virtual ~CDepthMask() {}

		virtual void Execute() { glDepthMask(m_val); }

	private:
		GLboolean m_val;
	};


	class DLLCOAPI CDepthFunc : public CCommand
	{
	private:
		typedef void (CDepthFunc::*PFUN)();

	public:
		CDepthFunc() :m_pWorkFun(0) { }
		virtual ~CDepthFunc() {}

		bool Initialize(const char* pParam);

		virtual void Execute() { (this->*m_pWorkFun)(); }

	private:
		void funLess() { glDepthFunc(GL_LESS); }
		void funGreater() { glDepthFunc(GL_GREATER); }
		void funLEqual() { glDepthFunc(GL_LEQUAL); }
		void funGEqual() { glDepthFunc(GL_GEQUAL); }
		void funEqual() { glDepthFunc(GL_EQUAL); }
		void funNotEqual() { glDepthFunc(GL_NOTEQUAL); }
		void funAlways() { glDepthFunc(GL_ALWAYS); }
		void funNever() { glDepthFunc(GL_NEVER); }

	private:
		PFUN m_pWorkFun;
	};




	class DLLCOAPI CColorMask : public CCommand
	{
	public:
		CColorMask(bool bR, bool bG, bool bB, bool bA):m_valR(bR), m_valG(bG), m_valB(bB), m_valA(bA) {}
		virtual ~CColorMask(){}

		virtual void Execute() { glColorMask(m_valR, m_valG, m_valB, m_valA); }

	private:
		GLboolean m_valR;
		GLboolean m_valG;
		GLboolean m_valB;
		GLboolean m_valA;
	};




	class DLLCOAPI CBlendFunc : public CCommand
	{
	public:
		bool Initialize(const char* pszSF, const char* pszDF);
		virtual void Execute() { glBlendFunc(m_eSourceFactor, m_eDestinationFactor); }

	private:
		GLenum m_eSourceFactor;
		GLenum m_eDestinationFactor;
	};



	class DLLCOAPI CBlendOp : public CCommand
	{
	private:
		typedef void (CBlendOp::*PFUN)();

	public:
		bool Initialize(const char* pszParam);
		virtual void Execute() { (this->*m_pWorkFun)(); }

	private:
		void funAdd() { glBlendEquation(GL_FUNC_ADD); }
		void funSub() { glBlendEquation(GL_FUNC_SUBTRACT); }
		void funRevSub() { glBlendEquation(GL_FUNC_REVERSE_SUBTRACT); }

	private:
		PFUN m_pWorkFun;

	};



}

#endif // !_FW_FOCOLOR_OPERATION_
