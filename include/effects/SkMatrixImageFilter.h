/*
 * Copyright 2014 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkMatrixImageFilter_DEFINED
#define SkMatrixImageFilter_DEFINED

#include "SkImageFilter.h"
#include "SkScalar.h"
#include "SkSize.h"
#include "SkPoint.h"
#include "SkPaint.h"

/*! \class SkMatrixImageFilter
    Matrix transformation image filter.  This filter draws its source
    input transformed by the given matrix.
 */

class SK_API SkMatrixImageFilter : public SkImageFilter {
public:
    /** Construct a 2D transformation image filter.
     *  @param transform    The matrix to apply when drawing the src bitmap
     *  @param filterLevel  The quality of filtering to apply when scaling.
     *  @param input        The input image filter.  If NULL, the src bitmap
     *                      passed to filterImage() is used instead.
     */

    static SkMatrixImageFilter* Create(const SkMatrix& transform,
                                       SkFilterQuality,
                                       SkImageFilter* input = NULL,
                                       uint32_t uniqueID = 0);
#ifdef SK_SUPPORT_LEGACY_FILTERLEVEL_ENUM
    static SkMatrixImageFilter* Create(const SkMatrix& transform,
                                       SkPaint::FilterLevel level,
                                       SkImageFilter* input = NULL,
                                       uint32_t uniqueID = 0) {
        return Create(transform, SkFilterQuality(level), input, uniqueID);
    }
#endif
    virtual ~SkMatrixImageFilter();

    void computeFastBounds(const SkRect&, SkRect*) const SK_OVERRIDE;

    SK_TO_STRING_OVERRIDE()
    SK_DECLARE_PUBLIC_FLATTENABLE_DESERIALIZATION_PROCS(SkMatrixImageFilter)

protected:
    SkMatrixImageFilter(const SkMatrix& transform,
                        SkFilterQuality,
                        SkImageFilter* input,
                        uint32_t uniqueID);
    void flatten(SkWriteBuffer&) const SK_OVERRIDE;

    virtual bool onFilterImage(Proxy*, const SkBitmap& src, const Context&,
                               SkBitmap* result, SkIPoint* loc) const SK_OVERRIDE;
    virtual bool onFilterBounds(const SkIRect& src, const SkMatrix&,
                                SkIRect* dst) const SK_OVERRIDE;

private:
    SkMatrix              fTransform;
    SkFilterQuality       fFilterQuality;
    typedef SkImageFilter INHERITED;
};

#endif
