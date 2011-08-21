/*

Copyright (C) 2009, Etienne Moutot <e.moutot@gmail.com>

This file is part of colorPickerWidget.

    colorPickerWidget is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    colorPickerWidget is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "colorpickerwidget.h"

ColorPickerWidget::ColorPickerWidget(QWidget *parent)
    : QWidget(parent)
{
    ecran=0;
    colorTriangle = new QtColorTriangle(this);

    connect(colorTriangle, SIGNAL(colorChanged(QColor)), this, SLOT(colorChgd()));

    colorView = new ColorViewer(this);
    colorView->setColor(colorTriangle->color());
        connect(colorTriangle, SIGNAL(colorChanged(QColor)), colorView, SLOT(changeColor(QColor)));

    pickColor = new QPushButton(tr("Pick a color"), this);
        connect(pickColor, SIGNAL(released()), this, SLOT(pickMode()));

    layout = new QGridLayout;
    layout->addWidget(  colorTriangle,  0, 0, 1, 2);
	layout->addWidget(  colorView,      1, 0, 1, 1);
    layout->addWidget(  pickColor,      1, 1, 1, 1);

	layout->setSpacing(4);
	layout->setMargin(0);

    setLayout(layout);
}

ColorPickerWidget::~ColorPickerWidget()
{
}

void ColorPickerWidget::pickMode()
{
    if(ecran!=0)
        delete ecran;
    ecran = new screen;
        connect( ecran, SIGNAL(colorSelected(QColor)), colorTriangle, SLOT(setColor(QColor)) );
}

void ColorPickerWidget::setColor(const QColor &col)
{
    colorView->setColor(col);
    colorTriangle->setColor(col);
}


void ColorPickerWidget::colorChgd()
{
    emit colorChanged(colorView->color());
}
