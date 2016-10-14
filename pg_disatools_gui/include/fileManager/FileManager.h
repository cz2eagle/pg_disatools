/*
 *  GNU Lesser General Public License (LGPL):
 *
 *	Copyright (C) 2016  ProgSys
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, version 3 of the License.
 *
 *	This program is distributed in the hope that it will be useful,
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with this program.  If not, see http://doc.qt.io/qt-5/lgpl.html
 *	or http://www.gnu.org/licenses/
 */

#include <QString>
#include <QMainWindow>
#include <ui_fileManager.h>

#ifndef INCLUDE_FILEMANAGER_H_
#define INCLUDE_FILEMANAGER_H_

class FileManager: public QMainWindow, public Ui::FileManagerUI {
	Q_OBJECT
public:
	FileManager(QWidget *parent = 0);
	virtual ~FileManager();
public slots:
	void open();
	void open(const QString& filepath);

	void save();
	void saveAs();
	void save(const QString& filepath);

private:
	void setTitel();
	void setTitel(const QString& filename);

	QString m_currentOpendFile;

};

#endif /* INCLUDE_FILEMANAGER_H_ */
