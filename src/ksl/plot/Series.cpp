/*
 * Copyright (C) 2017  Elvis Teixeira
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

#include <ksl/plot/Series_p.h>
#include <ksl/plot/FigureScale.h>
#include <ksl/plot/Util.h>
#include <QtGui>

namespace ksl {
namespace plot {

Series::Series(ksl::ObjectPrivate *priv, QObject *parent)
    : FigureItem(priv, parent)
{}

Series::Series(const QVector<double> &x, const QVector<double> &y,
               const char *style, QObject *parent)
    : Series(new SeriesPrivate(this), parent)
{
    setData(x, y);
    setStyle(style);
}

void Series::setData(const QVector<double> &x, const QVector<double> &y) {
    KSL_PUBLIC(Series);
    m->x = x;
    m->y = y;
    m->checkBounds();
}

QRect Series::figureRect() const {
    KSL_PUBLIC(const Series);
    return QRect(); // TODO
}

QRectF Series::dataRect() const {
    KSL_PUBLIC(const Series);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}

void Series::paint(QPainter *painter) {
    KSL_PUBLIC(Series);
    if (m->pointCount < 1L) {
        return;
    }
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
    switch (m->symbol) {
        case Line:
            m->paintLine(painter);
            break;
        case Circles:
            m->paintCircles(painter);
            break;
    }
}

void SeriesPrivate::paintLine(QPainter *painter) {
    QPainterPath path;
    QPoint p1 = scale->map(QPointF(x[0], y[0]));
    path.moveTo(p1);
    for (int64_t k=1; k<pointCount; ++k) {
        QPoint p2 = scale->map(QPointF(x[k], y[k]));
        // only draw segments at least 2 pixels long
        double dx = p2.x() - p1.x();
        double dy = p2.y() - p1.y();
        double d2 = dx*dx + dy*dy;
        if (d2 >= 4.0) {
            path.lineTo(p2);
            p1 = p2;
        }
    }
    painter->strokePath(path, linePen);
}

void SeriesPrivate::paintCircles(QPainter *painter) {
    double symbolDiameter = 2.0 * symbolRadius;
    painter->setPen(symbolPen);
    painter->setBrush(symbolBrush);
    for (int64_t k=0; k<pointCount; ++k) {
        QPoint p = scale->map(QPointF(x[k], y[k]));
        painter->drawEllipse(
            p.x() - symbolRadius,
            p.y() - symbolRadius,
            symbolDiameter,
            symbolDiameter
        );
    }
}

void SeriesPrivate::checkBounds() {
    pointCount = qMin(x.size(), y.size());
    if (pointCount < 1L) {
        return;
    }
    xMin = xMax = x[0];
    yMin = yMax = y[0];
    for (int64_t k=1; k<pointCount; ++k) {
        if (x[k] < xMin) xMin = x[k];
        if (x[k] > xMax) xMax = x[k];
        if (y[k] < yMin) yMin = y[k];
        if (y[k] > yMax) yMax = y[k];
    }
}

inline Series::Symbol parseSymbol(char c) {
    switch (c) {
        case '-': return Series::Line;
        case 'o': return Series::Circles;
    }
    return Series::Line;
}

void Series::setStyle(const char *style) {
    KSL_PUBLIC(Series);
    QPen linePen(Qt::blue);
    QPen symbolPen(Qt::red);
    QBrush symbolBrush(Qt::green);
    Symbol symbol = Line;
    int k = 0;

    // get all colors, later we specialize symbol
    if (style!=nullptr && style[k]!='\0') {
        linePen.setColor(Util::parseColor(style[k++]));
        symbolPen.setColor(linePen.color());
        symbolBrush.setColor(linePen.color());
    }
    // get the symbol
    if (style!=nullptr && style[k]!='\0') {
        symbol = parseSymbol(style[k++]);
    }
    // get specialize symbol filling color
    if (style!=nullptr && style[k]!='\0') {
        symbolBrush.setColor(Util::parseColor(style[k++]));
    }

    // widths bigger than 1 are prettier
    linePen.setWidthF(1.05);

    m->linePen = linePen;
    m->symbolPen = symbolPen;
    m->symbolBrush = symbolBrush;
    m->symbol = symbol;
}
}}
