/*

CPrimatterDescribe


Author:  Zhen Yi

Date:  Feb. 14, 2023

*/

#ifndef _FW_PRIMATTER_DESCRIBE_
#define _FW_PRIMATTER_DESCRIBE_

#include<string>
#include"CommonPrimatter.h"
#include"CAspect.h"


namespace FW
{

	class CFileDescribe : public CBase
	{
	public:
		CFileDescribe() :m_typeFile(EFILETYPE::FI_UNKNOWN), m_pNamePathFile(0){};
		virtual ~CFileDescribe() {}

		
		void Initialize(const char* pszNamePathFile, EFILETYPE typeFile)
		{
			m_pNamePathFile = pszNamePathFile;
			m_typeFile = typeFile;
		}
		


	//attribute
	public:
		EFILETYPE typeFile() { return m_typeFile; }
		const char* namePathFile() { return m_pNamePathFile; }

	protected:
		EFILETYPE m_typeFile;
		const char* m_pNamePathFile;
	};


	class CPrimatterAspectDescribe : public CFileDescribe
	{
	public:
		CPrimatterAspectDescribe() {}//:m_pNamePrimatterApt(0) {}
		virtual ~CPrimatterAspectDescribe() {}

		bool Initialize(const char* pNamePrimatterApt, const char* pNamePathFile);
			/*
		{
			if ((0 == pNamePrimatterApt) || (0 == pNamePathFile))
			{
				return false;
			}

			//m_pNamePrimatterApt = pNamePrimatterApt;
			//m_pszName = pNamePrimatterApt;
			ResetName(pNamePrimatterApt);
			m_pNamePathFile = pNamePathFile;

			std::string strNameFile = pNamePathFile;
			std::string::size_type rs = strNameFile.find(".sce", 0);
			if (rs != std::string::npos)
			{
				m_typeFile = EFILETYPE::FI_SCENECFG;
				return true;
			}

			rs = strNameFile.find(".mat", 0);
			if (rs != std::string::npos)
			{
				m_typeFile = EFILETYPE::FI_MATERIAL;
				return true;
			}

			return false;
		}
		*/

	//public:
		//const char* namePrimatterApt() { return m_pNamePrimatterApt; }

	//private:
		//const char* m_pNamePrimatterApt;
	};


	//class CPrimatterDescribe : public CBase
	class CPrimatterDescribe : public CFileDescribe
	{
	public:
		CPrimatterDescribe() :m_typePmt(EPMTTYPE::PR_UNKNOWN) {}//, m_pNamePrimatter(0){}
		virtual ~CPrimatterDescribe() {}

		bool Initialize(const char* pNamePrimatter, const char* pNamePathFile, EPMTTYPE typePmt);
			/*
		{
			if ((0 == pNamePrimatter) || (0 == pNamePathFile))
			{
				return false;
			}

			//m_pNamePrimatter = pNamePrimatter;
			//m_pszName = pNamePrimatter;
			ResetName(pNamePrimatter);
			m_pNamePathFile = pNamePathFile;

			m_typePmt = typePmt;

			switch (m_typePmt)
			{
			case EPMTTYPE::COMESH:
			case EPMTTYPE::MESH:
			{
				std::string strNameFile = pNamePathFile;
				std::string::size_type rs = strNameFile.find(".fwd", 0);
				if (rs != std::string::npos)
				{
					m_typeFile = EFILETYPE::FI_FWD;
					return true;
				}


				rs = strNameFile.find(".fbx", 0);
				if (rs != std::string::npos)
				{
					m_typeFile = EFILETYPE::FI_FBX;
					return true;
				}

				rs = strNameFile.find(".obj", 0);
				if (rs != std::string::npos)
				{
					m_typeFile = EFILETYPE::FI_OBJ;
					return true;
				}

			}
			break;

			case EPMTTYPE::SKELETON:
			case EPMTTYPE::DEFORMER:
			case EPMTTYPE::ANIMATION:
			{
				m_typeFile = EFILETYPE::FI_FBX;
				return true;
			}
			break;

			case EPMTTYPE::TEXTURE:
			{
				m_typeFile = EFILETYPE::FI_PNG;
				return true;
			}
			break;

			case EPMTTYPE::SHADER:
			{
				m_typeFile = EFILETYPE::FI_SHADER;
				return true;
			}
			break;

			
			case EPMTTYPE::PROGRAM:
			case EPMTTYPE::MATERIAL:
			{
				m_typeFile = EFILETYPE::FI_MATERIAL;
				return true;
			}
			break;

			default:
				break;
			}

			m_typeFile = EFILETYPE::FI_UNKNOWN;

			return false;
		}
		*/


	//attribute
	public:
		EPMTTYPE typePrimatter() { return m_typePmt; }


	private:
		EPMTTYPE m_typePmt;

	};

}


#endif // !_FW_PRIMATTER_DESCRIBE_
