#include"CNode.h"

using namespace FW;

CNode::CNode() : m_pParent(nullptr) 
{
	m_vtSubNodes.clear(); 
}


CNode::~CNode()
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