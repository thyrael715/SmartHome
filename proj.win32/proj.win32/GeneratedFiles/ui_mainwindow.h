/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_CLASS_H
#define UI_MAINWINDOW_CLASS_H

// ***** Includes *****

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDesktopWidget>

#include "BackgroundWidget.h"
#include "CentralWidget.h"


// ***** Namespace *****

QT_BEGIN_NAMESPACE


// ***** Macros *****

#define WINDOW_SCALE_X 0.5		// used to determine the width of program window from screen resolution
#define WINDOW_SCALE_Y 0.5		// used to determine the height of program window from screen resolution

#define ASPECT_RATIO_16_9 16/9; // 16:9


// ***** MainWindow class *****


class MainWindowClass
{
private:

	BackgroundWidget* backgroundWidget;
	CentralWidget* centralWidget;

public:

	void setupUI(QMainWindow *MainWindowClass)
	{
		if (MainWindowClass->objectName().isEmpty())
			MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));

		// Create Window

		MainWindowClass->resize(1280, 720);
		//MainWindowClass->showFullScreen();

		// Create widgets

		backgroundWidget = BackgroundWidget::create(MainWindowClass);
		centralWidget = CentralWidget::create();

		backgroundWidget->getMainLayout()->addWidget(centralWidget);
		
		// Init main window

		MainWindowClass->setCentralWidget(backgroundWidget);
		MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "SmartHome", 0));

		QMetaObject::connectSlotsByName(MainWindowClass);
	} // setupUi


	QSize generateResolution()
	{
		QDesktopWidget widget;
		QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());

		unsigned int h = mainScreenSize.height() * WINDOW_SCALE_Y;
		unsigned int w = h * ASPECT_RATIO_16_9;

		return QSize(w, h);
	} // generateResolution

};



QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
