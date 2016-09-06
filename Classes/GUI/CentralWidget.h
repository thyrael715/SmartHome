#pragma once

// ***** Includes *****

#include <QtWidgets/QWidget>
#include <QPainter>


// ***** CentralWidget class *****

class CentralWidget : public QWidget
{
public:

	static CentralWidget* create();
	static CentralWidget* create(QWidget* parent);
	
	~CentralWidget();

protected:

	virtual void paintEvent(QPaintEvent *event) override;

private:
	
	explicit CentralWidget();
	CentralWidget(QWidget* parent);
	CentralWidget(const CentralWidget&) = delete;
	CentralWidget& operator=(const CentralWidget&) = delete;

	void init();
};