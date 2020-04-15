#ifndef MY_WINDOWS_SERVER_H
#define MY_WINDOWS_SERVER_H

#include <QtWidgets/QWidget>
#include "ui_my_windows_server.h"
#include<QTimer>
class My_windows_server : public QWidget
{
	Q_OBJECT

public:
	My_windows_server(QWidget *parent = 0);
	~My_windows_server();
private slots:
	void on_btn_start_clicked(void);
	void on_btn_new_file_clicked(void);
	void open_obs(void);
private:
	Ui::My_windows_serverClass ui;
	QTimer *Guard_time;
	
};

#endif // MY_WINDOWS_SERVER_H
