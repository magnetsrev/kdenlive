/*
Copyright (C) 2012  Till Theato <root@ttill.de>
This file is part of kdenlive. See www.kdenlive.org.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/

#ifndef IMAGEPROJECTCLIP_H
#define IMAGEPROJECTCLIP_H

#include "core/project/abstractprojectclip.h"
#include <QPixmap>

class ImageClipPlugin;
class ImageTimelineClip;

namespace Mlt
{
    class Properties;
}

class ImageProjectClip : public AbstractProjectClip
{
    Q_OBJECT

public:
    ImageProjectClip(const KUrl& url, const QString &id, ProjectFolder* parent, ImageClipPlugin const *plugin);
    ImageProjectClip(const QString& service, Mlt::Properties props, const QString &id, ProjectFolder* parent, ImageClipPlugin const *plugin);
    ImageProjectClip(ProducerWrapper* producer, ProjectFolder* parent, ImageClipPlugin const *plugin);
    ImageProjectClip(const QDomElement &description, ProjectFolder *parent, ImageClipPlugin const *plugin);
    ~ImageProjectClip();

    AbstractTimelineClip *createInstance(TimelineTrack *parent, ProducerWrapper *producer = 0);
    void initProducer();
    void initProducer(const QString &service, Mlt::Properties props);
    void hash();

public slots:
    QPixmap thumbnail();

private:
    void init(int duration = 0);

    QList<ImageTimelineClip *> m_instances;
};

#endif
