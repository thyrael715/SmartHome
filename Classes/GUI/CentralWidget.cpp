// ############## Source(.cpp) file of CentralWidget ############## 

// ***** Includes *****

#include "CentralWidget.h"
#include <iostream>

// ***** Defines *****

#define CW_CIRCLE_RADIUS_SCALE 0.5


// ***** Function definitions *****

CentralWidget::CentralWidget()
{
	init();
}

CentralWidget::CentralWidget(QWidget* parent)
	: QWidget(parent)
{
	init();
}

CentralWidget::~CentralWidget()
{

}

CentralWidget* CentralWidget::create()
{
	static CentralWidget* cs = new CentralWidget();
	return cs;
}

CentralWidget* CentralWidget::create(QWidget* parent)
{
	static CentralWidget* cs = new CentralWidget(parent);
	return cs;
}


void CentralWidget::init()
{
	setAttribute(Qt::WA_TranslucentBackground);
	int ten = 10;
	for (int i = 0; i < ten-1; i++)
	{
		std::cout << i << std::endl;
	}
}


void CentralWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	

	QPen pen(QColor(10,100,200), 8);
	painter.setPen(pen); 

	unsigned int d = height() * CW_CIRCLE_RADIUS_SCALE;
	unsigned int x = width() / 2 - d / 2;
	unsigned int y = height() / 2 - d / 2;

	painter.drawArc(x, y, d, d, 0, 16 * 360);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);

	painter.drawArc(x - d/2, y - d/2 , d * 2, d * 2, 16*225, 8*360);
}
