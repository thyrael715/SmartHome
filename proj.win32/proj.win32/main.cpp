//#include "mainwindow.h"
//#include <QtWidgets/QApplication>
//
//int main(int argc, char *argv[])
//{
//	QApplication a(argc, argv);
//	MainWindow w;
//	w.show();
//	
//	return a.exec();
//}


#include <sapi.h>
#include <sphelper.h>
#include <iostream>
#include "Defaults.h"
#include "Speaker.h"

int main(int argc, char* argv[])
{
	Speaker* sp = Speaker::getInstance();
	sp->say(tx::main_program_start());
}