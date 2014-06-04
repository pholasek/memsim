#ifndef MEMSIMVIS_H
#define MEMSIMVIS_H
//! Class implementing cache visualization
/*!
 * Header file of cache visualization class
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>

class MemSimVis : public QWidget
{
	Q_OBJECT
public:
	MemSimVis(QWidget *parent);
	QSize sizeHint() const;
	QSize minimumSizeHint() const;
	void set_assoc(long val) { assoc = val; }
	void set_values(quint64 *p) { values = p; }
	void set_sets(long val) { sets = val; }
protected slots:
	void paintEvent(QPaintEvent * event);
private:
	long assoc;
	long sets;
	quint64 * values;
};

#endif
