/*!
 * MemSimVis class
 * \author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "memsimvis.h"


MemSimVis::MemSimVis(QWidget *parent) : QWidget(parent), assoc(0), sets(0), values(NULL)
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
	
	long bigsum = 0;

	if (values) {
		for (int j = 0; j < assoc; j++) {
			for (int i = 0; i < sets; i++)
				bigsum += values[i * assoc + j];
		}
	}
	for (int ys = 0; ys < assoc; ys++) {
		painter.save();
		painter.translate(0, ys*30);
		double alpha = 0;
		if (values) {
			double accsum = 0;
			for (int i = 0; i < sets; i++) {
				accsum += values[i * assoc + ys];
			}
			alpha = accsum ? 255*accsum/bigsum : 0;
			brush.setColor(QColor(255,0,0,static_cast<int>(alpha)));
			painter.setBrush(brush);
		}
		painter.drawRect(rect);
		QFont font = painter.font();
		font.setPointSize(12);
		painter.setFont(font);
		painter.drawText(QPoint(200, 70), QString("%1\%").arg(alpha/255*100, 0, 'f', 3));
		painter.restore();
	}

	painter.setRenderHint(QPainter::Antialiasing, false);
	painter.setPen(palette().dark().color());
	painter.setBrush(Qt::NoBrush);
	painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
