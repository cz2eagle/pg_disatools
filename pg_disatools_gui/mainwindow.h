/*
 *  Copyright (C) 2016  ProgSys
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QItemSelection>
#include "treemodel.h"
#include "treesort.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnDelete_clicked();

private slots:
    void on_treeView_activated(const QModelIndex &index);

private slots:
    void on_btnSave_clicked();

private slots:
    void on_btnInsert_clicked();

private slots:
    void on_btnExtract_clicked();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private slots:
    void on_checkBox_TX2_clicked(bool checked);

private slots:
    void on_checkBox_PHD_clicked(bool checked);

private slots:
    void on_checkBox_PNG_clicked(bool checked);

private slots:
    void on_checkBox_PBD_clicked(bool checked);

private slots:
    void on_checkBox_OGG_clicked(bool checked);

private slots:
    void on_checkBox_FFM_clicked(bool checked);

private slots:
    void on_checkBox_FAD_clicked(bool checked);

private slots:
    void on_checkBox_DAT_clicked(bool checked);

private slots:
    void on_checkBox_MPD_clicked(bool checked);

private slots:
    void on_checkBox_ARC_clicked(bool checked);

private slots:
    void on_checkBox_MMP_clicked(bool checked);

private slots:
    void on_btnAbout_clicked();

    void on_btnOpen_clicked();
public slots:
    void treeSelectionChanged (const QItemSelection & sel,const  QItemSelection & desel);

signals:
	bool saveFile();
	bool saveFileAs(const QString& filepath);

private slots:
    void on_btnSaveAs_clicked();

private:
    Ui::MainWindow *ui;

    TreeModel* m_treeModel;
    TreeSort* m_treeSort;
    QGraphicsScene* scene;
    QItemSelectionModel* selectionModel;
};

#endif // MAINWINDOW_H