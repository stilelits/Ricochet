/*
 * OptionBox.h
 *
 *  Created on: Nov 30, 2017
 *      Author: tr_dawson
 */

#ifndef OPTIONBOX_H_
#define OPTIONBOX_H_

#include "TextBox.h"

class OptionBox: public TextBox {
public:
 OptionBox(const std::string& promptNew, const std::vector<std::pair<std::string, unsigned> >& optionsNew);
 virtual ~OptionBox(){};
 unsigned selected;
 std::string prompt;
 std::vector<std::pair<std::string, unsigned> > options;
 void refresh();
 void selectUp();
 void selectDown();
 virtual void finish();
};

#endif /* OPTIONBOX_H_ */
