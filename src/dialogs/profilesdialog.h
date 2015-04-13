/***************************************************************************
 *   Copyright (C) 2008 by Jean-Baptiste Mardelle (jb@kdenlive.org)        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef PROFILESDIALOG_H
#define PROFILESDIALOG_H


#include "definitions.h"
#include "ui_profiledialog_ui.h"

class ProfilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfilesDialog(QWidget * parent = 0);
    /** @brief Using this constructor, the dialog only allows editing one profile. */
    explicit ProfilesDialog(QString profilePath, QWidget * parent = 0);

    void fillList(const QString &selectedProfile = QString());
    static QMap< QString, QString > getSettingsFromFile(const QString& path);
    static MltVideoProfile getVideoProfile(const QString &name);
    static QMap <QString, QString> getProfilesInfo();
    static void saveProfile(MltVideoProfile &profile, QString profilePath = QString());
    static QString existingProfile(const MltVideoProfile &profile);
    static bool existingProfileDescription(const QString &desc);

    /** @brief Check if a given profile matches passed properties:
     *  @param width The profile frame width
     *  @param height The profile frame height
     *  @param fps The profile fps
     *  @param par The sample aspect ratio
     *  @param isImage If true, compare width with profile's display width ( = dar * height)
     *  @param profile The profile to match
     *  @return true if properties match profile */
    static bool matchProfile(int width, int height, double fps, double par, bool isImage, const MltVideoProfile &profile);

    /** @brief Find profiles that match parameter properties:
     *  @param width The profile frame width
     *  @param height The profile frame height
     *  @param fps The profile fps
     *  @param par The sample aspect ratio
     *  @param useDisplayWidth If true, compare width with profile's display width ( = dar * height)
     *  @return A string list of the matching profiles description */
    static QMap <QString, QString> getProfilesFromProperties(int width, int height, double fps, double par, bool useDisplayWidth = false);

    /** @brief Get the descriptive text for given colorspace code (defined by MLT)
     *  @param colorspace An int as defined in mlt_profile.h
     *  @return The string description */
    static QString getColorspaceDescription(int colorspace);

    /** @brief Get the colorspace code (defined by MLT) from a descriptive text
     *  @param desctiption A string description as defined in getColorspaceDescription(int colorspace)
     *  @return The int code */
    static int getColorspaceFromDescription(const QString &description);

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void slotUpdateDisplay(QString currentProfile = QString());
    void slotCreateProfile();
    bool slotSaveProfile();
    void slotDeleteProfile();
    void slotSetDefaultProfile();
    void slotProfileEdited();
    virtual void accept();

private:
    Ui::ProfilesDialog_UI m_view;
    int m_selectedProfileIndex;
    bool m_profileIsModified;
    bool m_isCustomProfile;
    /** @brief If we are in single profile editing, should contain the path for this profile. */
    QString m_customProfilePath;
    void saveProfile(QString path);
    bool askForSave();
};


#endif

