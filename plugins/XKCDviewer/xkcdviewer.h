//Copyright (C) 2018  Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3) with the exception that
//linking the OpenSSL library is allowed.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef XKCDVIEWER_H
#define XKCDVIEWER_H

#include <QObject>
#include <QtNetwork>
#include <QDesktopServices>

#include <cstdlib>
#include <ctime>

class XKCDviewer: public QObject {
	Q_OBJECT

	int currentComic = -1;
	int latestComic = -1;

	QString cacheDir;
	QJsonDocument comicData;
	QString imgPath;

	// Networking
	QNetworkAccessManager *netmgr;
	QNetworkReply *netreply;
	QByteArray *dataBuffer;

	/**
	 * Obtains the JSON data for the currently selected comic
	 */
	void updateJSON();

	/**
	 * Indicate that network data is ready to be read
	 */
	void dataReady();

	/**
	 * Indicate that comic data is done being read
	 */
	void dataFinished();

	/**
	 * Indicate that image data is done being read
	 */
	void imageFinished();

	/**
	 * Clean up resources used during network interaction
	 */
	void networkCleanup();

public:
	/**
	 * Initialize the viewer
	 */
	XKCDviewer();

	Q_PROPERTY(QString imgPath MEMBER imgPath);
	Q_PROPERTY(QJsonObject comicData READ getComicData)

	/**
	 * Obtains comic data for the current comic
	 * @return QJsonObject containing data about the currently selected comic
	 */
	QJsonObject getComicData();

	/**
	 * Downloads the JSON data for the currently selected comic
	 * from the server
	 */
	Q_INVOKABLE void downloadJSON();

	/**
	 * Show the latest comic
	 */
	Q_INVOKABLE void jumpToLatest();

	/**
	 * Show the previous comic
	 */
	Q_INVOKABLE void prevComic();

	/**
	 * Show the next comic
	 */
	Q_INVOKABLE void nextComic();

	/**
	 * Show a random comic
	 */
	Q_INVOKABLE void randomComic();

	/**
	 * Go to the explainxkcd page for the current comic
	 */
	Q_INVOKABLE void explainComic();

signals:
	void doRefreshView();
	void isLoading();
	void imageReady();
};

#endif
