/*

CFWEngineWidget


Author:  Zhen Yi.

Date: Feb. 1, 2025


*/




#ifndef _CFWEngine_Widget_
#define _CFWEngine_Widget_

#include <qwidget.h>
#include <qopenglwidget.h>
#include <qboxlayout.h>
#include<QTimer.h>
#include "ui_FWEditor.h"

#include "IEngine.h"
#include "IInputDevice.h"
#include "IUIManager.h"

using namespace FW;

class CFWEngineWidget : public QWidget
{
public:
	CFWEngineWidget();
	CFWEngineWidget(QWidget* parent);
	virtual~CFWEngineWidget();

	bool InitialFWEngine(Ui_FWEditor& ui);
	void* GetWndHandle() { return (m_pEngine == nullptr)?nullptr:m_pEngine->getWindowHandle(); }


public slots:
	void OnTime();
	void OnNew();
	void OnOpen();
	void OnTransform();
     	
	

private:
	IEngine* m_pEngine;
	QTimer m_timer;

};




#endif // !_CFWEngine_Widget_


