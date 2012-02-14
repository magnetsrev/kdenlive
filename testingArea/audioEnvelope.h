/***************************************************************************
 *   Copyright (C) 2012 by Simon Andreas Eugster (simon.eu@gmail.com)      *
 *   This file is part of kdenlive. See www.kdenlive.org.                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef AUDIOENVELOPE_H
#define AUDIOENVELOPE_H

#include "audioInfo.h"
#include <mlt++/Mlt.h>

class QImage;
class AudioEnvelope
{
public:
    AudioEnvelope(Mlt::Producer *producer);
    ~AudioEnvelope();

    /// Returns the envelope, calculates it if necessary.
    int64_t const* envelope();
    int envelopeSize() const;

    void loadEnvelope();
    int64_t loadStdDev();
    void normalizeEnvelope(bool clampTo0 = false);

    QImage drawEnvelope();

    void dumpInfo() const;

private:
    int64_t *m_envelope;
    Mlt::Producer *m_producer;
    AudioInfo *m_info;

    int m_envelopeSize;
    int64_t m_envelopeMax;
    int64_t m_envelopeMean;
    int64_t m_envelopeStdDev;

    bool m_envelopeStdDevCalculated;
    bool m_envelopeIsNormalized;
};

#endif // AUDIOENVELOPE_H
