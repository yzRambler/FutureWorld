/*


Author:  Zhen Yi

Created Date: Feb. 14, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_COMMON_PRIMATTER_
#define _FW_COMMON_PRIMATTER_

namespace FW
{
	//typedef enum eAspectGenerate { ORG = 0, CLONE, COPY } EAPTGEN;
	/*
	* GE_ORG_PM: generate by CPrimatterCenter
	* GE_ORG_FL: generate from file
	* GE_ORG_DT: generate directly.
	*/
	typedef enum eGenerate { GE_ORG_PM=0, GE_ORG_FL, GE_ORG_DT, GE_CLONE, GE_COPY, GE_UNKNOW } EGEN;

	typedef enum eConstructType {
		CST_PRIMATTER = 0, CST_BONE, CST_SCENENODE, CST_SCENE, CST_PRM_MAT, CST_UI_TREE, CST_TEXTUREUNIT, 
		CST_ESSETY, CST_SPACE, CST_TRACK, CST_COMPONENT, CST_RENDERUNIT,  CST_BOUND, CST_LISTERNER, 
		CST_COMMAND, CST_UNKNOWN }ECONSTRTYPE, EAPTTYPE;


	//Note: MESH, PROGRAM and DEFORMER(SKIN)  are just appendage, do not own the id of themself.
	
	typedef enum ePrimatterType {
		ANIMATION = 0, MATERIAL, COMESH, MESH, TEXTURE, PROGRAM, SHADER, SKELETON, DEFORMER, SCENE, 
		PR_UNKNOWN
	}EPMTTYPE;



	typedef enum eAnimationType {
		AN_VERTEX = 0, AN_SKELETON, AN_UNKNOWN
	}EANITYPE;


	typedef enum eDeformerType{
		DE_SKIN = 0, DE_UNKNOWN
	}EDEFORMTYPE;



	typedef enum ePrimatterState {
		READY = 0, PROCESSING, FAILED, UNKNOWN
	}EPMTSTATE;



	typedef enum eAspectState {
		APT_READY = 0, APT_INITING, APT_FAILED, APT_UNKNOWN
	}EAPTSTATE;



	typedef enum eTexture {
		TEXTURE_0 = 0, TEXTURE_1, TEXTURE_2, TEXTURE_3, TEXTURE_4, TEXTURE_5,
		TEXTURE_6, TEXTURE_7, TEXTURE_COUNT
	}ETXTU;


	typedef enum eShaderType {
		SH_UNKOWN = 0, VERTEX_SH, FRAGMENT_SH
	} ESHDTYPE;


	typedef enum eFileType {
		FI_UNKNOWN = 0, FI_OBJ, FI_MATERIAL, FI_SCENECFG, FI_UI, FI_SHADER, FI_FBX, FI_PNG, FI_FWD
	} EFILETYPE;



	typedef enum eComponentType {
		CO_SPACE = 0, CO_RENDER, CO_COLLISION, CO_SCRIPTE, CO_ANIMATIONGROUP, CO_CAMERA, CO_LIGHT, 
		CO_UI, CO_AUDIO, CO_PARTICALSYS, CO_UNKNOW
	} ECOMTYPE;


	typedef enum eApplicationPrimatterResult {
		INVAL_PARA = 0, APP_FAILED, APP_SUCCESS, APP_UNKNOWN
	}EAPPPRRES;


	typedef enum eRenderType {
		RT_OPACITY = 0, RT_TRANSPARENT, RT_FRAME, RT_UNKNOW
	}ERNDTYPE;


	typedef enum eLightType {
		LT_POINT = 0, LT_DIRECT, LT_SPOT, LT_UNKNOW 
	}ELITTYPE;


	typedef enum eOutputBufferType {
		OUB_RENDERBUF = 0, OUB_TEXTURE, OUB_UNKNOW
	}EOUTBFTYPE;


	typedef enum eShaderVariableType {
		SV_VTATTR = 0, SV_UNIFORM, SV_UNKNOW
	}ESVTYPE;


	typedef enum eVertexAttributeType {
		VA_POS = 0, VA_NORMAL, VA_TANGENT, VA_UV, VA_UNKNOW
	}EVATYPE;


	typedef enum eShaderUniformType {
		SU_CAMERA = 0, SU_LIGHT, SU_TEXTURE, SU_WORLDTF, SU_VECTOR, SU_COLOR, SU_NUMBER, SU_UNKNOW 
	}ESUTYPE;

	typedef enum eShaderDataType {
		SD_FLOAT = 0, SD_INT, SD_BOOL, SD_VEC2, SD_VEC3, SD_VEC4, SD_MAT2, SD_MAT3, SD_MAT4, SD_SAMP2, SD_UNKNOW
	}ESHDATATYPE;


	typedef enum eShaderCameraValueType{
		SCV_POS = 0, SCV_V, SCV_PROJ, SCV_MV, SCV_MVP, SCV_UNKNOW
	}ESHCAMVALTYPE;


	typedef enum eShaderLightValueType{
		SLV_POS = 0, SLV_DIRECT, SLV_INTENSITY, SLV_COLOR, SLV_UNKNOW
	}ESHLITVALTYPE;


	typedef enum eCameraType{
		CAM_PERSPECT = 0, CAM_ORTHOGRA, CAM_UNKNOW
	}ECAMERATYPE;



	typedef enum eICTargetType{
		ICT_MSGCENTER = 0, ICT_FILEMAG, ICT_UIMAG, ICT_UNKNOW
	}EICTAGTYPE;

}


#endif // !_FW_COMMON_PRIMATTER_
