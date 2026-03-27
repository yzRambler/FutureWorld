/*

CMessage.


Author: Zhen Yi.    взеђ

Created Date: Feb. 3, 2024

Version: 0.2.0 Alpha

*/

#ifndef _FW_MESSAGE_
#define _FW_MESSAGE_

#include"BaseData.h"
#include"EngineCoreCommon.h"
#include"CommonUI.h"



namespace FW
{
	class CMsgBase
	{
	public:
		CMsgBase(EMSGTYPE msgType = EMSGTYPE::MSG_UNKNOWN):type(msgType), idTarget(0), idSource(0) {}
		virtual ~CMsgBase() {}

		//idTarget is the receiver's id. If idTarget equal zero then this is the broadcast message. 
		void Create(FDWORD idSrc, FDWORD idTag = 0 ) { idTarget = idTag;  idSource = idSrc; }

	//attribute
	//public:
	//	EMSGTYPE type() { return m_type; }
	//	FDWORD idTarget() { return m_idTarget; }
	//	FDWORD idSource() { return m_idSource; }

	//protected:
	public:
		EMSGTYPE type;
		FDWORD idTarget;
		FDWORD idSource;
	};


	class CMsgTime : public CMsgBase
	{
	public:
		CMsgTime() : CMsgBase(EMSGTYPE::MSG_TIME), m_time(0), m_dltTime(0){}
		virtual ~CMsgTime(){}

		void Create(FDWORD time, FDWORD dTime)
		{
			m_time = time;
			m_dltTime = dTime;
		}

	public:
		FDWORD time() { return m_time; }
		FDWORD dltTime() { return m_dltTime; }

	private:
		FDWORD m_time;
		FDWORD m_dltTime;
	};


	class CMsgMSMove : public CMsgBase
	{
	public:
		CMsgMSMove() : CMsgBase(EMSGTYPE::MSG_MMOVE), m_scrX(0), m_scrY(0), m_scrDx(0), m_scrDy(0) {}
		virtual ~CMsgMSMove() {}

		void Create(int sx, int sy, int dsx, int dsy, FDWORD idSrc = 0, FDWORD idTag = 0)
		{
			CMsgBase::Create(idSrc, idTag);
			m_scrX = sx;
			m_scrY = sy;
			m_scrDx = dsx;
			m_scrDy = dsy;
		}

	//attribute
	public:
		int scrX() { return m_scrX; }
		int scrY() { return m_scrY; }
		int scrDx() { return m_scrDx; }
		int scrDy() { return m_scrDy; }

		float x() { return m_x; }
		void setX(float x) { m_x = x; }

		float y() { return m_y; }
		void setY(float y) { m_y = y; }

		float z() { return m_z; }
		void setZ(float z) { m_z = z; }

		float dx() { return m_dx; }
		void setDx(float dx) { m_dx = dx; }

		float dy() { return m_dy; }
		void setDy(float dy) { m_dy = dy; }

		float dz() { return m_dz; }
		void setDz(float dz) { m_dz = dz; }


	private:
		int m_scrX;
		int m_scrY;
		int m_scrDx;
		int m_scrDy;

		float m_x;
		float m_y;
		float m_z;
		float m_dx;
		float m_dy;
		float m_dz;
	};


	class CMsgLBDown : public CMsgBase
	{
	public:
		CMsgLBDown() : CMsgBase(EMSGTYPE::MSG_MLBDOWN) {}
		virtual ~CMsgLBDown() {}
	};



	class CMsgLBUp : public CMsgBase
	{
	public:
		CMsgLBUp() : CMsgBase(EMSGTYPE::MSG_MLBUP) {}
		virtual ~CMsgLBUp() {}
	};




	//------------------------------------------------------------------


	class CMsgUI : public CMsgBase
	{
	public:
		CMsgUI(EMSGTYPE msgType, EUITYPE uiSrcType) : CMsgBase(msgType),uiType(uiSrcType),
			command(EUICOMD::UIC_UNKNOW) {}
		virtual ~CMsgUI() {}

		void Create(FDWORD idSource, FDWORD idTarget, EUICOMD commandSrc)
		{
			CMsgBase::Create(idSource, idTarget);
			command = commandSrc;
		}

	//atrribute
	//public:
	//	EUITYPE typeSrcUI() { return m_srcUIType; }
	//	EUICOMD command() { return m_command; }

	//private:
	public:
		EUITYPE uiType;
		EUICOMD command;
	};

}



#endif // !_FW_MESSAGE_
