/*
 * Copyright (C) 2016  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KSL_CHARTVIEW_H
#define KSL_CHARTVIEW_H

#include <Ksl/chart.h>
#include <QWidget>

class KSL_EXPORT KslChartView
    : public QWidget
    , public KslObject
{
    Q_OBJECT

public:

    KslChartView(QWidget *parent);

    KslChartView(const QString &title="Ksl", int with=500,
                 int height=350, QWidget *parent=0);

    KslChart* chart() const;

protected:

    virtual void paintEvent(QPaintEvent *event);

    KslChartView(KslObjectPrivate *priv, QWidget *parent)
        : QWidget(parent)
        , KslObject(priv)
    { }
};

#endif // KSL_CHARTVIEW_H