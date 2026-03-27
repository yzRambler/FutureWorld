/*

CCommandAspect

Author:   Zhen  Yi

Created Date: Jun. 7, 2026

Version: 0.2.0 Alpha

*/


#ifndef _FW_COMMAND_ASPECT_
#define _FW_COMMAND_ASPECT_

#include"CAspect.h"
#include"MathLibrary.h"


namespace FW
{
	class CCommandAspect : public CAspect
	{
	public:
		CCommandAspect(CAspect* pHost = nullptr);
		CCommandAspect(const char* pszName, CAspect* pHost = nullptr);
		virtual ~CCommandAspect();

		bool Create(const char* pszCommandName, const char* pszValue);

		virtual CCommandAspect* Clone()
		{
			CCommandAspect* pCmdApt = new CCommandAspect;
			pCmdApt->Create(name(), m_strValue.Get());
			return pCmdApt;
		}

		//attribute
	public:
		const char* value() { return m_strValue.Get(); }


	private:
		CString m_strValue;

	};


	class CCommandAspectBlend : public CCommandAspect
	{
		//Inherite from CCommandAspect
	public:
		//virtual bool Clone(CCommandAspect* pCmdApt)
		//{
		//	if (nullptr != pCmdApt) 
		//	{
		//		m_strSrc = ((CCommandAspectBlend*)pCmdApt)->m_strSrc; m_strTag = ((CCommandAspectBlend*)pCmdApt)->m_strTag; return true;
		//	}

		//	return false;
		//}

		virtual CCommandAspect* Clone()
		{
			CCommandAspectBlend* pCmdApt = new CCommandAspectBlend;
			pCmdApt->Create(name(), m_strSrc.Get(), m_strTag.Get());
			return pCmdApt;
		}


	public:
		CCommandAspectBlend(CAspect* pHost = nullptr) : CCommandAspect(pHost) {}
		CCommandAspectBlend(const char* pszName, CAspect* pHost = nullptr) : CCommandAspect(pszName, pHost){}
		virtual ~CCommandAspectBlend() {}

		bool Create(const char* pszCommandName, const char* pszSrc, const char* pszTag);


		//attribute
	public:
		const char* valueSrc() { return m_strSrc.Get(); }
		const char* valueTag() { return m_strTag.Get(); }

	private:
		CString m_strSrc;
		CString m_strTag;
	};


	class CCommandAspectClearColor : public CCommandAspect
	{
	public:
		CCommandAspectClearColor(CAspect* pHost = nullptr) : CCommandAspect(pHost) {}
		CCommandAspectClearColor(const char* pszName, CAspect* pHost = nullptr) : CCommandAspect(pszName, pHost) {}
		virtual ~CCommandAspectClearColor() {}

		bool Create(float r, float g, float b, float a) 
		{
			m_v4Color.x = r; m_v4Color.y = g; m_v4Color.z = b; m_v4Color.w = a; return true;
		}

		virtual CCommandAspect* Clone()
		{
			CCommandAspectClearColor* pCmdApt = new CCommandAspectClearColor();
			pCmdApt->Create(m_v4Color.x, m_v4Color.y, m_v4Color.z, m_v4Color.w);
			pCmdApt->ResetName(name());


			return pCmdApt;
		}

		//Attribute
	public:
		Vector4& color() { return m_v4Color; }


	private:
		Vector4 m_v4Color;

	};


	class CCommandAspectViewPort : public CCommandAspect
	{
	public:
		CCommandAspectViewPort(CAspect* pHost = nullptr) : CCommandAspect(pHost) {}
		CCommandAspectViewPort(const char* pszName, CAspect* pHost = nullptr) : CCommandAspect(pszName, pHost) {}
		virtual ~CCommandAspectViewPort() {}

		bool Create(float x, float y, float w, float h) 
		{
			m_v4VP.x = x; m_v4VP.y = y; m_v4VP.z = w; m_v4VP.w = h; return true;
		}


		virtual CCommandAspect* Clone()
		{
			CCommandAspectViewPort* pCmdapt = new CCommandAspectViewPort();
			pCmdapt->Create(m_v4VP.x, m_v4VP.y, m_v4VP.z, m_v4VP.w);
			pCmdapt->ResetName(name());

			return pCmdapt;
		}


		//Attribute
	public:
		Vector4& viewPort() { return m_v4VP; }

	private:
		Vector4 m_v4VP;
	};

}






#endif // !_FW_COMMAND_ASPECT_
