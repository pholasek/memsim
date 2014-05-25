#ifndef POWERSPINBOX_H
#define POWERSPINBOX_H
//! Power spinbox class
/*!
 * powerspinbox header file
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include <QSpinBox>
#include <QLineEdit>

class PowerSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    PowerSpinBox(QWidget* parent = 0) : QSpinBox(parent) { findChild<QLineEdit*>()->setReadOnly(true); }
public slots:
    void stepBy(int steps);
};


#endif
