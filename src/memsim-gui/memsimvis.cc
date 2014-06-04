/*!
 * MemSimVis class
 * \author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "memsimvis.h"


MemSimVis::MemSimVis(QWidget *parent) : QWidget(parent), values(NULL)
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
	
	double max = 0.0;
	double max_coef = 1.0;

	for (int ys = 0; ys < assoc; ys++) {
		painter.save();
		painter.translate(0, ys*30);
		if (values) {
			double accsum = 0;
			for (int i = 0; i < sets; i++) {
				accsum += values[i * assoc + ys];
			}
			accsum /= assoc;
			if (accsum > 255 && accsum > max) {
				max = accsum;
				max_coef = max / 255;
			}
			accsum /= max_coef;
			brush.setColor(QColor(255,0,0,static_cast<int>(accsum)));
			painter.setBrush(brush);
		}
		painter.drawRect(rect);
		painter.restore();
	}

	painter.setRenderHint(QPainter::Antialiasing, false);
	painter.setPen(palette().dark().color());
	painter.setBrush(Qt::NoBrush);
	painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
