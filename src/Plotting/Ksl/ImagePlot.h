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

#ifndef KSL_IMAGEPLOT_H
#define KSL_IMAGEPLOT_H

#include <Ksl/Array.h>
#include <Ksl/FigureItem.h>

namespace Ksl {

class KSL_EXPORT ImagePlot:
    public FigureItem
{
    Q_OBJECT

public:


    enum ColorMode {
        GrayScale
    };


    ImagePlot(const ArrayView<quint32> &data,
              ColorMode colorMode=GrayScale,
              const QString &name="imagePlot",
              QObject *parent=0);

    ImagePlot(const ArrayView<quint32> &x,
              const ArrayView<quint32> &y,
              ColorMode colorMode=GrayScale,
              const QString &name="imagePlot",
              QObject *parent=0);

};

} // namespace Ksl

#endif // KSL_IMAGEPLOT_H
