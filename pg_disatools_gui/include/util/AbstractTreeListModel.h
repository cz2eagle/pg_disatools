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

#ifndef INCLUDE_FILES_AbstractTreeListModel_H_
#define INCLUDE_FILES_AbstractTreeListModel_H_

#include <QAbstractListModel>
#include <QString>
#include <util/TreeItem.h>

class AbstractTreeListModel : public QAbstractListModel {
	Q_OBJECT
public:
	AbstractTreeListModel(QObject *parent = 0);
	virtual ~AbstractTreeListModel();
	virtual int getColumnWidth(int index) const;

	virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
	virtual  QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	virtual QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	virtual QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

public slots:
	virtual bool open(const QString& filepath);
	virtual bool save(const QString& filepath);

	virtual bool exportCSV(const QString& filepath) const;

	virtual bool insertFront();
	virtual bool insertBack();
	virtual bool insertAt(int index);
	virtual bool removeAt(int index);
protected:

	TreeItem* m_root = nullptr;
};

#endif /* INCLUDE_FILES_AbstractTreeListModel_H_ */
