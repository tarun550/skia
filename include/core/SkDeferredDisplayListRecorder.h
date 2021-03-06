/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkDeferredDisplayListMaker_DEFINED
#define SkDeferredDisplayListMaker_DEFINED

#include "SkRefCnt.h"

#include "../private/SkDeferredDisplayList.h"
#include "../private/SkSurfaceCharacterization.h"

class SkCanvas;
class SkSurface; // TODO: remove

/*
 * This class is intended to be used as:
 *   Get an SkSurfaceCharacterization representing the intended gpu-backed destination SkSurface
 *   Create one of these (an SkDDLMaker) on the stack
 *   Get the canvas and render into it
 *   Snap off and hold on to an SkDeferredDisplayList
 *   Once your app actually needs the pixels, call SkSurface::draw(SkDeferredDisplayList*)
 *
 * This class never accesses the GPU but performs all the cpu work it can. It
 * is thread-safe (i.e., one can break a scene into tiles and perform their cpu-side
 * work in parallel ahead of time).
 */
class SkDeferredDisplayListRecorder {
public:
    SkDeferredDisplayListRecorder(const SkSurfaceCharacterization&);

    const SkSurfaceCharacterization& characterization() const {
        return fCharacterization;
    }

    // The backing canvas will become invalid (and this entry point will return
    // null) once 'detach' is called.
    // Note: ownership of the SkCanvas is not transfered via this call.
    SkCanvas* getCanvas();

    std::unique_ptr<SkDeferredDisplayList> detach();

private:
    const SkSurfaceCharacterization fCharacterization;

    sk_sp<SkSurface> fSurface; // temporary until we have a real implementation
};

#endif
