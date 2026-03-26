/*
CFinalSpaceTime


Author: Zhen Yi

Created Date: Nov. 14, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_FINAL_SPACETIME_
#define _FW_FINAL_SPACETIME_

#include<vector>

#include"CSpaceTime.h"
//#include"CPlaneMesh.h"
#include"CMaterial.h"
#include"CCamera.h"
//#include"CSpace.h"
#include"CSceneNode.h"

namespace FW
{
	const int CON_TEXUARY_SIZE = 2;

	class CPass;
	class CRectFinalImage;
	class CProgram;
	class CVertexShader;
	class CFragmentShader;
	class CTextureBuffer;
	class CFinalSpaceTime : public CSpaceTime
	{
	public:
		CFinalSpaceTime();
		virtual ~CFinalSpaceTime();

		bool CreateDefault();

		bool Create(float fw, float fh, CTextureBuffer* pTexBuf0, CTextureBuffer* pTexBuf1);

		void Update();


	private:
		CRectFinalImage* m_pRectFImg;

		CCamera* m_pCam;
		CSceneNode* m_pHostCam;
		VTLIT m_vtLight;

		GLenum m_ayTextureAptIDSET[ETXTU::TEXTURE_COUNT];

		CTexture* m_aryText[CON_TEXUARY_SIZE];

	};

}


#endif // !_FW_FINAL_SPACETIME_
