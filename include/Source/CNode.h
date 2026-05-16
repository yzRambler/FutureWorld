/*
CNode

Author: Zhen Yi (взеђ)

Date: May 07, 2021

Version 0.2.1 Alpha

*/

#ifndef _FW_NODE_
#define _FW_NODE_


#include<vector>
#include"CBase.h"
#include"FWEngineBaseExport.h"



namespace FW
{
	class DLLBSAPI CNode
	{
	public:
		CNode();
		virtual ~CNode();

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
