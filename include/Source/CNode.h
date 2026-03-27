/*
CNode

Author: Zhen Yi
Created Date: May 07, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_NODE_
#define _FW_NODE_


#include"CBase.h"
#include<vector>



namespace FW
{
	class CNode
	{
	public:
		CNode():m_pParent(0) { m_vtSubNodes.clear(); }
		//CNode(const char* pszName):CBase(pszName), m_pParent(0) { m_vtSubNodes.clear(); }

		virtual ~CNode()
		{
			m_pParent = 0;

			for (std::vector<CNode*>::iterator iter = m_vtSubNodes.begin(); iter != m_vtSubNodes.end(); ++iter)
			{
				if (*iter != 0)
				{
					delete* iter;
				}
			}

			m_vtSubNodes.clear();
		}

		bool isNoneParent() { return (m_pParent == 0); }
		bool isEmptySubnodes() { return m_vtSubNodes.empty(); }

		void SetParent(CNode* pParentNode) { m_pParent = pParentNode; }
		void AttachChild(CNode* pChild) { m_vtSubNodes.push_back(pChild); }

	//attribute
	public:
		CNode* parent() { return m_pParent; }
		int countSubNodes() { return m_vtSubNodes.size(); }
		CNode* subNode(int index) 
		{ if ((index < 0) || (index >= m_vtSubNodes.size())) { return 0; }  return m_vtSubNodes[index]; }


	protected:
		CNode* m_pParent;
		std::vector<CNode*> m_vtSubNodes;
	};
}

#endif // !_FW_NODE_
