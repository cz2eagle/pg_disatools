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
#include <FileManager/FileManager.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QImage>
#include <QtQml>
#include <QFile>

#include <fileManager/FileDefModel.h>


inline void aboutFileManager(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("About");
    //msgBox.setWindowIcon(QMessageBox::Information);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(
    			"This gui application allows you to view and edit Disgaea archives.<br>"\

				"You can find the source code here: <a href='https://github.com/ProgSys/pg_disatools/'>https://github.com/ProgSys/pg_disatools</a><br>"

				"<br><b>GNU Lesser General Public License (LGPL):</b> <br>"
				"<br>Copyright (C) 2016  ProgSys"\
                "<br><br>This program is free software: you can redistribute it and/or modify"\
                "<br>it under the terms of the GNU Lesser General Public License as published by"\
                "<br>the Free Software Foundation, version 3 of the License."\

                "<br><br>This program is distributed in the hope that it will be useful,"\
                "<br>but WITHOUT ANY WARRANTY; without even the implied warranty of"\
                "<br>MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"\
                "<br>GNU Lesser General Public License for more details."\

                "<br><br>You should have received a copy of the GNU Lesser General Public License"\
                "<br>along with this program.  If not, see <a href='http://doc.qt.io/qt-5/lgpl.html'> http://doc.qt.io/qt-5/lgpl.html</a>"\
				"<br>or <a href='http://www.gnu.org/licenses/'> http://www.gnu.org/licenses/ </a>."\
                );

    msgBox.exec();
}

FileManager::FileManager(QWidget *parent):
	QMainWindow(parent){
	setupUi(this);

	setWindowIcon(QIcon(":/disa_tools_icon.ico"));
	setWindowTitle(FileManagerTITLE);


	//About
	connect(actionAbout, &QAction::triggered, this, [this]{
		aboutFileManager();
	});
	connect(actionAbout_Qt, &QAction::triggered, this, [this]{
		 QMessageBox::aboutQt(this);
	} );


	connect(actionOpen, SIGNAL( triggered() ),  this, SLOT( open() ));
	connect(pushButton_open, SIGNAL( clicked() ),  this, SLOT( open() ));

	connect(pushButton_save, SIGNAL( clicked() ),  this, SLOT( save() ));
	connect(pushButton_saveAs, SIGNAL( clicked() ),  this, SLOT( saveAs() ));


	QFile qfile("D:/Users/ProgSys/pg_disatools/dependencies/pg_disatools_gui/debug/mingw/bin/resources/archiveFiles/TEST.DEF");
	if(!qfile.open(QIODevice::ReadOnly)) return;
	QTextStream st(&qfile);
	QList<token> tokens;
	tokenize(st,tokens, false);

	for(const token& t: tokens)
		qDebug() << t.lexeme<<" = "<<toString(t.type);

	qDebug()<<"===================";
	Programm* p = parse(tokens);

	QVariant out;
	QList<variable> variables;
	p->run(out, variables);
	for(const variable& t: variables)
		qDebug() << t.name<<" = "<<t.value;
}

FileManager::~FileManager() {
}


void FileManager::open(){
    QFileDialog openDialog(this);
    openDialog.setNameFilter(tr("Archive (*.dat)"));

    QStringList fileNames;
	if (openDialog.exec()){
		fileNames = openDialog.selectedFiles();
		if(fileNames.size() > 0){
			open(fileNames[0]);
		}
	}
}

void FileManager::open(const QString& filepath){
	if(filepath.isEmpty()) return;

}


void FileManager::save(){
	save(m_currentOpendFile);
}

void FileManager::saveAs(){
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save image"),
				QFileInfo(m_currentOpendFile).baseName(),
			   tr("Archive (*.dat)"));
	save(fileName);
}
void FileManager::save(const QString& filepath){
	if(filepath.isEmpty()) return;

}


void FileManager::setTitel(){
	setWindowTitle(FileManagerTITLE);
}

void FileManager::setTitel(const QString& filename){
	 if(filename.isEmpty()){
		 setTitel();
		 return;
	 }
	 QString title(FileManagerTITLE);
	 title.append(" - ");
	 title.append(filename);
	 setWindowTitle(title);
}


