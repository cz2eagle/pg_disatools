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
#include <util/AbstractTreeListModel.h>
#include <QFile>
#include <QTextStream>


AbstractTreeListModel::AbstractTreeListModel(QObject *parent): QAbstractListModel(parent) {
	// TODO Auto-generated constructor stub

}

AbstractTreeListModel::~AbstractTreeListModel() {
	if(m_root) delete m_root;
}

bool AbstractTreeListModel::open(const QString& filepath){return false;}
bool AbstractTreeListModel::save(const QString& filepath){return false;}


int AbstractTreeListModel::getColumnWidth(int index) const{
	return 150;
}

bool AbstractTreeListModel::exportCSV(const QString& filepath) const{
	if(!m_root || filepath.isEmpty()) return false;

	QFile qfile(filepath);
    if (!qfile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&qfile);

	for(const QVariant& var: m_root->getData())
		out<< var.toString()<<", ";
	out<<"\n";

	for(const TreeItem* child: m_root->getChilderen()){
		for(const QVariant& var: child->getData())
			out<< var.toString()<<", ";
		out<<"\n";

	}

    qfile.close();

	return true;
}

bool AbstractTreeListModel::insertFront(){
	beginInsertRows(QModelIndex(),0,0);
	if(m_root->childCount()){
		m_root->insertFront(new TreeItem(m_root->child(0)->getData(), m_root));
	}else{
		QList<QVariant> data;
		for(unsigned int i = 0; i < m_root->columnCount(); i++) data << "0";
		m_root->insertFront(new TreeItem(data, m_root));
	}
	endInsertRows();
	return true;
}
bool AbstractTreeListModel::insertBack(){
	beginInsertRows(QModelIndex(),m_root->childCount(),m_root->childCount());
	if(m_root->childCount()){
		m_root->insertBack(new TreeItem(m_root->child(m_root->childCount()-1)->getData(), m_root));
	}else{
		QList<QVariant> data;
		for(unsigned int i = 0; i < m_root->columnCount(); i++) data << "0";
		m_root->insertBack(new TreeItem(data, m_root));
	}
	endInsertRows();
	return true;
}
bool AbstractTreeListModel::insertAt(int index){
	if(index < 0 || index > m_root->childCount()) return false;
	beginInsertRows(QModelIndex(),index,index);
	if(m_root->childCount()){
		m_root->insertAt(index, new TreeItem(m_root->child(index)->getData(), m_root));
	}else{
		QList<QVariant> data;
		for(unsigned int i = 0; i < m_root->columnCount(); i++) data << "0";
		m_root->insertAt(index, new TreeItem(data, m_root));
	}
	endInsertRows();
	return true;
}

bool AbstractTreeListModel::removeAt(int index){
	beginRemoveRows(QModelIndex(),index,index);
	if(!m_root->childCount()) return false;
	m_root->removeAt(index);
	endRemoveRows();
	return true;
}

QVariant AbstractTreeListModel::data(const QModelIndex &index, int role) const{
    if (!m_root || !index.isValid())
        return QVariant();

    if(role == Qt::EditRole || role == Qt::DisplayRole){
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(index.column());
    }else
    	return QVariant();


}

Qt::ItemFlags AbstractTreeListModel::flags(const QModelIndex &index) const{
    if (!m_root || !index.isValid())
        return 0;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant AbstractTreeListModel::headerData(int section, Qt::Orientation orientation,
                    int role) const{

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_root->data(section);

    return QVariant();

}

QModelIndex AbstractTreeListModel::index(int row, int column,
                  const QModelIndex &parent) const{

    if (!m_root || !hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex AbstractTreeListModel::parent(const QModelIndex &index) const{
    if (!m_root || !index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);

}

int AbstractTreeListModel::rowCount(const QModelIndex &parent) const{
    TreeItem *parentItem;
    if (!m_root || parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int AbstractTreeListModel::columnCount(const QModelIndex &parent) const{
	if(!m_root) return 0;
	if (parent.isValid())
		return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
	else
		return m_root->columnCount();
}
