#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FWEditor.h"
#include "CFWEngineWidget.h"



namespace FW
{
    class CFWEditor : public QMainWindow
    {
        Q_OBJECT

    public:
        CFWEditor(QWidget* parent = nullptr);
        virtual ~CFWEditor();

        bool Create();

    private:
        //Ui::FWEditor ui;
        Ui_FWEditor ui;

        CFWEngineWidget* m_pFWEngineWdg;

        //IEngine* m_pEngine;
    };
}


