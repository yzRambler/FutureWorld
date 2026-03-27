/*

BaseData.h


Author: Zhen Yi

Created Date: Nov. 9, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_BASE_DATA_
#define _FW_BASE_DATA_

namespace FW
{
	typedef unsigned char FBYTE;
	typedef unsigned int FDWORD;
	typedef unsigned short FWORD;

	//typedef union URect
	//{
	//	struct
	//	{
	//		int x;
	//		int y;
	//		int w;
	//		int h;
	//	};
	//	struct
	//	{
	//		float fx;
	//		float fy;
	//		float fw;
	//		float fh;
	//	};
	//	
	//}SRECT;

	typedef struct URect
	{
		union
		{
			struct
			{
				int x;
				int y;
				int w;
				int h;
			};
			struct
			{
				float fx;
				float fy;
				float fw;
				float fh;
			};
		};
		

	}SRECT;

}


#endif // !_FW_BASE_DATA_

