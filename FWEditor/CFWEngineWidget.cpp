////#include<vld.h>
#include"CFWEngineWidget.h"
//#include"CEngine.h"
//#include"CTest.h"



CFWEngineWidget::CFWEngineWidget() :m_pEngine(nullptr)
{
}


CFWEngineWidget::CFWEngineWidget(QWidget* parent) :QWidget(parent,
	Qt::WindowFlags(Qt::MSWindowsOwnDC)), m_pEngine(nullptr)
{
}


CFWEngineWidget::~CFWEngineWidget()
{
	if (nullptr != m_pEngine)
	{
		ReleaseEngine();
		m_pEngine = nullptr;
	}
}

/*
void CFWEngineWidget::initializeGL()
{
	InitialFWEngine();
}
*/


bool CFWEngineWidget::InitialFWEngine(Ui_FWEditor& ui)
{

	m_pEngine = CreateEngine();
	if (m_pEngine == 0)
	{
		return false;
	}


	if (!m_pEngine->Initalize(800, 600))
	{
		return false;
	}



	QTimer* timer = new QTimer();
	timer->setInterval(30);

	//QObject::connect(timer, &QTimer::timeout, this, &CFWEngineWidget::OnTime);
	connect(timer, &QTimer::timeout, this, &CFWEngineWidget::OnTime);

	timer->start();


	connect(ui.actionNew, &QAction::triggered, this, &CFWEngineWidget::OnNew);
	connect(ui.actionOpen, &QAction::triggered, this, &CFWEngineWidget::OnOpen);
	connect(ui.actionSave_As, &QAction::triggered, this, &CFWEngineWidget::OnTransform);

	return true;

}



void CFWEngineWidget::OnTransform()
{
	//m_pEngine->TransformFileFromFBX2FWD("./resources/David/DavidHead.fbx");
	m_pEngine->TransformFileFromFBX2FWD("./resources/Horse/horse.fbx");

}




static int i = 0;
void CFWEngineWidget::OnNew()
{

	if (i == 1)
	{
		m_pEngine->UnloadScene("./resources/Horse/Horse.sce");
	}
	else if(i == 2)
	{
		m_pEngine->UnloadScene("./resources/David/DavidHead.sce");
	}
}





void CFWEngineWidget::OnOpen()
{
	if ((i == 0)||(i==2))
	{
		m_pEngine->UnloadScene("./resources/Horse/Horse.sce");
	    m_pEngine->LoadScene("./resources/Horse/Horse.sce");
	    m_pEngine->SetCurrentScene("./resources/Horse/Horse.sce");

		i = 1;
	}
	else
	{
		m_pEngine->UnloadScene("./resources/David/DavidHead.sce");
		m_pEngine->LoadScene("./resources/David/DavidHead.sce");
		m_pEngine->SetCurrentScene("./resources/David/DavidHead.sce");

		i = 2;
	}
}





void CFWEngineWidget::OnTime()
{


	if (0 != m_pEngine)
	{
		m_pEngine->Run();

	}

}


/*
void CFWEngineWidget::paintGL()
{


}
*/

