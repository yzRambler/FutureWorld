#include "CFWEditor.h"
#include <QWindow>

////#include<vld.h>

using namespace FW;

CFWEditor::CFWEditor(QWidget* parent)
	: QMainWindow(parent), m_pFWEngineWdg(0)
{
    ui.setupUi(this);

}

CFWEditor::~CFWEditor()
{
	if (nullptr != m_pFWEngineWdg)
	{
		delete m_pFWEngineWdg;
		m_pFWEngineWdg = nullptr;
	}

}




bool CFWEditor::Create()
{

	m_pFWEngineWdg = new CFWEngineWidget(ui.SceneView);
	m_pFWEngineWdg->InitialFWEngine(ui);

	
	QWindow* pNavWnd = QWindow::fromWinId((WId)m_pFWEngineWdg->GetWndHandle());
	QWidget* pMatchWndWgt = QWidget::createWindowContainer(pNavWnd, ui.SceneView);


	ui.SceneView->layout()->addWidget(pMatchWndWgt);

	


    return true;
}
