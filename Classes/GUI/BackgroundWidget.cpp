// ############## Source(.cpp) file of BackgroundWidget ############## 

#include "BackgroundWidget.h"
#include <iostream>

#define BGW_COLOR_GRAY {40, 40, 40, 255} // Color of hexagonal grid


BackgroundWidget::BackgroundWidget()
{
	init();
}

BackgroundWidget::BackgroundWidget(QWidget *parent)
	: QWidget(parent)
{
	init();
}


BackgroundWidget::~BackgroundWidget()
{
	if (m_mainLayout)
		delete m_mainLayout;
}


BackgroundWidget* BackgroundWidget::create()
{
	static BackgroundWidget* bgw = new BackgroundWidget();
	return bgw;
}

BackgroundWidget* BackgroundWidget::create(QWidget* parent)
{
	static BackgroundWidget* bgw = new BackgroundWidget(parent);
	return bgw;
}

void BackgroundWidget::init()
{
	setObjectName(QStringLiteral("centralWidget"));
	setStyleSheet(QStringLiteral("background-color: black;"));

	m_mainLayout = new QGridLayout();
	setLayout(m_mainLayout);
}


void BackgroundWidget::paintEvent(QPaintEvent *event)
{
	drawHexagonGrid();
}


void BackgroundWidget::drawHexagonGrid()
{
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);

	unsigned int lineWidth = 1;							// thickness of hexagons line
	unsigned int r = 10;								// radius of hexagons
	unsigned int h = static_cast<int>(sqrt(3) / 2 * r); // cos30° * r
	unsigned int halfSide = static_cast<int>(0.5 * r);  // sin30° * r

	QPoint origin(-(r * 5 / 4), -r * 2);				// startpoint of hexagonal grid
	QColor color(BGW_COLOR_GRAY);						// color of hexagons
	
	QPen pen(color, lineWidth);
	painter.setPen(pen);

	unsigned int shiftX = (r * 3);						// tile shifting horizontal
	unsigned int shiftY = (h * 2);						// tile shifting vertical
	unsigned int countX = (width() / shiftX) + 1;		// num of horizontal hexagon
	unsigned int countY = (height() / shiftY) + 1;		// num of vertical hexagon

	for (unsigned int i = 0; i < countX; i++)
	{
		for (unsigned int j = 0; j < countY; j++)
		{
			for (unsigned int k = 0; k < 2; k++)
			{
				QPoint topLeftXY(i*shiftX + (k * (r + halfSide)), j*shiftY + (k * h));
				topLeftXY += origin;

				QPolygon poly;

				poly << QPoint(topLeftXY.x() + halfSide, topLeftXY.y()) << QPoint(topLeftXY.x() + halfSide + r, topLeftXY.y())
					<< QPoint(topLeftXY.x() + (2 * r), topLeftXY.y() + h) << QPoint(topLeftXY.x() + (halfSide + r), topLeftXY.y() + (2 * h))
					<< QPoint(topLeftXY.x() + halfSide, topLeftXY.y() + (2 * h)) << QPoint(topLeftXY.x(), topLeftXY.y() + h);

				painter.drawPolygon(poly);
			}
		}
	}
}


QGridLayout* BackgroundWidget::getMainLayout()
{
	return m_mainLayout;
}