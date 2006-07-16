/***************************************************************************
                          projectlistview.cpp  -  description
                             -------------------
    begin                : Sun Jun 30 2002
    copyright            : (C) 2002 by Jason Wood
    email                : jasonwood@blueyonder.co.uk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "projectlistview.h"

#include "avlistviewitem.h"
#include "docclipavfile.h"
#include "clipdrag.h"
#include "documentbasenode.h"

#include <kdebug.h>
#include <klocale.h>

ProjectListView::ProjectListView(QWidget * parent, const char *name):
KListView(parent, name)
{
    m_doc = 0;
    m_popuptext = "";

    addColumn(i18n("Thumbnail"));
    addColumn(i18n("Filename"));
    //addColumn( i18n( "Type" ) );
    //addColumn( i18n( "Duration" ) );
    //addColumn( i18n( "Usage Count" ) );
    //addColumn( i18n( "Size" ) );
    addColumn(i18n("Description"));

    setDragEnabled(true);
    setAcceptDrops(true);
    setItemsMovable(true);
    setDropVisualizer(true);
    setFullWidth(true);
    setShadeSortColumn(false);
    setDefaultRenameAction(Accept);
    setAllColumnsShowFocus(true);
    setRootIsDecorated(true);
    setSorting(1);
    QToolTip::remove(this);
    new ListViewToolTip(this);

    connect(this, SIGNAL(dropped(QDropEvent *, QListViewItem *,
		QListViewItem *)), this, SLOT(dragDropped(QDropEvent *,
		QListViewItem *, QListViewItem *)));

}

ProjectListView::~ProjectListView()
{
}

QString ProjectListView::parentName()
{
	QString parentNode;
	if (!currentItem()) parentNode = m_doc->clipHierarch()->name();
	else if (!static_cast<AVListViewItem *>(currentItem())->clip()) {
	    currentItem()->setOpen(true);
	    parentNode = currentItem()->text(1);
	}
	else if (currentItem()->parent()) {
	    currentItem()->parent()->setOpen(true);
	    parentNode = currentItem()->parent()->text(1);
	}
	else parentNode = m_doc->clipHierarch()->name();
	return parentNode;
}

QString ProjectListView::popupText()
{
	return m_popuptext;
}

void ProjectListView::setPopupText(QString txt)
{
	m_popuptext = txt;
}

/** returns a drag object which is used for drag operations. */
QDragObject *ProjectListView::dragObject()
{
    AVListViewItem *item = (AVListViewItem *) selectedItem();

    if (!item->clip())
	return false;

    emit dragStarted(item);

    if (m_doc == 0) {
	kdError() << "m_doc undefined" << endl;
	return 0;
    }
    return new ClipDrag(item->clip(), parentWidget(), "drag object");
}

bool ProjectListView::acceptDrag(QDropEvent * event) const
{
    return ClipDrag::canDecode(event);
}

/** This slot function should be called whenever a drag has been dropped
	onto the class. The cliplist produced will delete the clips within it
 	unless the signal is caught and told otherwise. Note that problems
  	will arise is multiple documents attempt to catch this signal and have
	different ideas about what to do with the clip list.*/
void ProjectListView::dragDropped(QDropEvent * e, QListViewItem * parent,
    QListViewItem * after)
{
    if (after) emit dragDropOccured(e, after);
    else emit dragDropOccured(e, parent);
}

/** Sets the document to the one specified */
void ProjectListView::setDocument(KdenliveDoc * doc)
{
    m_doc = doc;
}
