/*!
 * MemSimVis class
 * \author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "memsimvis.h"


MemSimVis::MemSimVis(QWidget *parent) : QWidget(parent)
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
}

QSize MemSimVis::sizeHint() const
{
	return QSize(200, 200);
}

QSize MemSimVis::minimumSizeHint() const
{
	return QSize(200, 100);
}

void MemSimVis::paintEvent(QPaintEvent * event)
{
	QRect rect(25,50,150,30);

	QPainter painter(this);
	QPen pen(Qt::SolidLine);
	QBrush brush(QColor("white"), Qt::SolidPattern);
	painter.setPen(pen);
	painter.setBrush(brush);
	
	for (int ys = 0; ys < 30*assoc; ys += 30) {
		painter.save();
		painter.translate(0, ys);
		brush.setColor(QColor(255,0,0,ys));
		painter.setBrush(brush);
		painter.drawRect(rect);
		painter.restore();
	}

	painter.setRenderHint(QPainter::Antialiasing, false);
	painter.setPen(palette().dark().color());
	painter.setBrush(Qt::NoBrush);
	painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
