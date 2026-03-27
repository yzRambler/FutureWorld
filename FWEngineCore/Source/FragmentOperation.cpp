#include<string.h>
#include"FragmentOperation.h"

using namespace FW;


bool CEnable::Initialize(const char* pParam)
{
	if (0 == pParam)
	{
		return false;
	}

	if (strcmp(pParam, "Stencil") == 0)
	{
		m_pWorkFun = &CEnable::funEnableStencilTest;
	}
	else if (strcmp(pParam, "Depth") == 0)
	{
		m_pWorkFun = &CEnable::funEnableDepthTest;
	}
	else if (strcmp(pParam, "Blend") == 0)
	{
		m_pWorkFun = &CEnable::funEnableBlend;
	}
	else if (strcmp(pParam, "CullFace") == 0)
	{
		m_pWorkFun = &CEnable::funEnableCullFace;
	}
	else
	{
		return false;
	}


	return true;
}



bool CDisable::Initialize(const char* pParam)
{
	if (0 == pParam)
	{
		return false;
	}

	if (strcmp(pParam, "Stencil") == 0)
	{
		m_pWorkFun = &CDisable::funDisableStencilTest;
	}
	else if (strcmp(pParam, "Depth") == 0)
	{
		m_pWorkFun = &CDisable::funDisableDepthTest;
	}
	else if (strcmp(pParam, "Blend") == 0)
	{
		m_pWorkFun = &CDisable::funDisableBlend;
	}
	else if (strcmp(pParam, "CullFace") == 0)
	{
		m_pWorkFun = &CDisable::funDisableCullFace;
	}
	else
	{
		return false;
	}


	return true;
}




bool CClear::Initialize(const char* pParam)
{
	if (0 == pParam)
	{
		return false;
	}

	if (strcmp(pParam, "Stencil") == 0)
	{
		m_pWorkFun = &CClear::funClearStencilBB;
	}
	else if (strcmp(pParam, "Depth") == 0)
	{
		m_pWorkFun = &CClear::funClearDepthBB;
	}
	else if (strcmp(pParam, "Color") == 0)
	{
		m_pWorkFun = &CClear::funclearColorBB;
	}
	else
	{
		return false;
	}

	return true;
}




//==================================================================



bool CCullFace::Initialize(const char* pParam)
{
	if (0 == pParam)
	{
		return false;
	}

	if (strcmp(pParam, "Front") == 0)
	{
		m_pWorkFun = &CCullFace::funCullFaceFront;
	}
	else if (strcmp(pParam, "Back") == 0)
	{
		m_pWorkFun = &CCullFace::funCullFaceBack;
	}
	else if (strcmp(pParam, "FrontAndBack") == 0)
	{
		m_pWorkFun = &CCullFace::funCullFaceFB;
	}
	else
	{
		return false;
	}

	return true;
}




bool CFrontFace::Initialize(const char* pParam)
{
	if (0 == pParam)
	{
		return false;
	}

	if (strcmp(pParam, "CW") == 0)
	{
		m_pWorkFun = &CFrontFace::funFrontFaceCW;
	}
	else if (strcmp(pParam, "CCW") == 0)
	{
		m_pWorkFun = &CFrontFace::funFrontFaceCCW;
	}
	else
	{
		return false;
	}

	return true;
}






bool CDepthFunc::Initialize(const char* pParam)
{
	if (0 == pParam)
	{
		return false;
	}
	//////Never
	if (strcmp(pParam, "Less") == 0)
	{
		m_pWorkFun = &CDepthFunc::funLess;
	}
	else if (strcmp(pParam, "Greater") == 0)
	{
		m_pWorkFun = &CDepthFunc::funGreater;
	}
	else if (strcmp(pParam, "LEqual") == 0)
	{
		m_pWorkFun = &CDepthFunc::funLEqual;
	}
	else if (strcmp(pParam, "GEqual") == 0)
	{
		m_pWorkFun = &CDepthFunc::funGEqual;
	}
	else if (strcmp(pParam, "Equal") == 0)
	{
		m_pWorkFun = &CDepthFunc::funEqual;
	}
	else if (strcmp(pParam, "Notequal") == 0)
	{
		m_pWorkFun = &CDepthFunc::funNotEqual;
	}
	else if (strcmp(pParam, "Always") == 0)
	{
		m_pWorkFun = &CDepthFunc::funAlways;
	}
	else if (strcmp(pParam, "Never") == 0)
	{
		m_pWorkFun = &CDepthFunc::funNever;
	}
	else
	{
		return false;
	}

	return true;
}




bool CBlendFunc::Initialize(const char* pszSF, const char* pszDF)
{
	if (strcmp(pszSF, "0") == 0)
	{
		m_eSourceFactor = GL_ZERO;
	}
	else if (strcmp(pszSF, "1") == 0)
	{
		m_eSourceFactor = GL_ONE;
	}
	else if (strcmp(pszSF, "SC") == 0)
	{
		m_eSourceFactor = GL_SRC_COLOR;
	}
	else if (strcmp(pszSF, "1-SC") == 0)
	{
		m_eSourceFactor = GL_ONE_MINUS_SRC_COLOR;
	}
	else if (strcmp(pszSF, "SA") == 0)
	{
		m_eSourceFactor = GL_SRC_ALPHA;
	}
	else if (strcmp(pszSF, "1-SA") == 0)
	{
		m_eSourceFactor = GL_ONE_MINUS_SRC_ALPHA;
	}
	else if (strcmp(pszSF, "DC") == 0)
	{
		m_eSourceFactor = GL_DST_COLOR;
	}
	else if (strcmp(pszSF, "1-DC") == 0)
	{
		m_eSourceFactor = GL_ONE_MINUS_DST_COLOR;
	}
	else if (strcmp(pszSF, "DA") == 0)
	{
		m_eSourceFactor = GL_DST_ALPHA;
	}
	else if (strcmp(pszSF, "1-DA") == 0)
	{
		m_eSourceFactor = GL_ONE_MINUS_DST_ALPHA;
	}
	else
	{
		return false;
	}



	if (strcmp(pszDF, "0") == 0)
	{
		m_eDestinationFactor = GL_ZERO;
	}
	else if (strcmp(pszDF, "1") == 0)
	{
		m_eDestinationFactor = GL_ONE;
	}
	else if (strcmp(pszDF, "SC") == 0)
	{
		m_eDestinationFactor = GL_SRC_COLOR;
	}
	else if (strcmp(pszDF, "1-SC") == 0)
	{
		m_eDestinationFactor = GL_ONE_MINUS_SRC_COLOR;
	}
	else if (strcmp(pszDF, "SA") == 0)
	{
		m_eDestinationFactor = GL_SRC_ALPHA;
	}
	else if (strcmp(pszDF, "1-SA") == 0)
	{
		m_eDestinationFactor = GL_ONE_MINUS_SRC_ALPHA;
	}
	else if (strcmp(pszDF, "DC") == 0)
	{
		m_eDestinationFactor = GL_DST_COLOR;
	}
	else if (strcmp(pszDF, "1-DC") == 0)
	{
		m_eDestinationFactor = GL_ONE_MINUS_DST_COLOR;
	}
	else if (strcmp(pszDF, "DA") == 0)
	{
		m_eDestinationFactor = GL_DST_ALPHA;
	}
	else if (strcmp(pszDF, "1-DA") == 0)
	{
		m_eDestinationFactor = GL_ONE_MINUS_DST_ALPHA;
	}
	else
	{
		return false;
	}


	return true;
}




bool CBlendOp::Initialize(const char* pszParam)
{
	if (strcmp(pszParam, "+") == 0)
	{
		m_pWorkFun = &CBlendOp::funAdd;
	}
	else if (strcmp(pszParam, "-") == 0)
	{
		m_pWorkFun = &CBlendOp::funSub;
	}
	else if (strcmp(pszParam, "R-") == 0)
	{
		m_pWorkFun = &CBlendOp::funRevSub;
	}
	else
	{
		return false;
	}


	return true;
}