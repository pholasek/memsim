/*!
 * Power spinbox class
 * \author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "powerspinbox.h"

void PowerSpinBox::stepBy(int steps)
{
  if(steps == 1)
      setValue(value()*2);
  else if(steps == -1)
      setValue(value()/2);
  else
      QSpinBox::stepBy(steps);
}
