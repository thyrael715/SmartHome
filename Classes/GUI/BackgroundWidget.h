#pragma once


// ***** Includes *****

#include <QtWidgets/QWidget>
#include <QGridLayout>
#include <QPainter>


// ***** BackgroundWidget class *****

class BackgroundWidget : public QWidget
{
public:
	
	static BackgroundWidget* BackgroundWidget::create();
	static BackgroundWidget* BackgroundWidget::create(QWidget* parent);
	~BackgroundWidget();

	QGridLayout* getMainLayout();
	
protected:

	virtual void paintEvent(QPaintEvent *event) override;

private:

	QGridLayout* m_mainLayout;

	explicit BackgroundWidget();
	BackgroundWidget(QWidget *parent);
	BackgroundWidget(const BackgroundWidget&) = delete;
	BackgroundWidget& operator=(const BackgroundWidget&) = delete;
	
	void init();

	void drawHexagonGrid();
	void drawCentralPanel();	
};

