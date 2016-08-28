#pragma once

#include <QtWidgets/QWidget>
#include <QPainter>
#include <iostream>
#include <QtCore/qmath.h>



class BackgroundWidget : public QWidget
{
public:
		
	BackgroundWidget(QWidget *parent);
	~BackgroundWidget();

	bool init();

protected:

	virtual void paintEvent(QPaintEvent *event) override;

private:
	
};