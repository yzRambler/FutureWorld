#include"CFileDescribe.h"
#include"CListener.h"

using namespace FW;




bool CFileDescribe::Initialize(const char* pszNamePathFile)//, CListener* pLsn /* = nullptr */)
{
	if (nullptr == pszNamePathFile)
	{
		return false;
	}

	ResetName(pszNamePathFile);
	m_strNamePathFile.Set(pszNamePathFile);

	//m_pLsn = pLsn;

	return true;
}




///////////////////////////////////////////////////////////




bool CAspectDescribe::Initialize(const char* pNamePrimatterApt, const char* pNamePathFile)
{
	if ((nullptr == pNamePrimatterApt) || (nullptr == pNamePathFile))
	{
		return false;
	}


	if (!CFileDescribe::Initialize(pNamePathFile))
	{
		return false;
	}

	ResetName(pNamePrimatterApt);

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


	rs = strNameFile.find(".fui", 0);
	if (rs != std::string::npos)
	{
		m_typeFile = EFILETYPE::FI_UI;
		return true;
	}



	return false;
}






////////////////////////////////////////////////////////////




bool CPrimatterDescribe::Initialize(const char* pNamePrimatter, const char* pNamePathFile, EPMTTYPE typePmt)
{
	if ((nullptr == pNamePrimatter) || (nullptr == pNamePathFile))
	{
		return false;
	}


	if (!CFileDescribe::Initialize(pNamePathFile))
	{
		return false;
	}


	ResetName(pNamePrimatter);


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
