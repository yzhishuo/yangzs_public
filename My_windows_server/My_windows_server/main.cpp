//#include "my_windows_server.h"
#include <QtWidgets/QApplication>
//#include"my_windows_server.h"
#include"my_obs_guard.h"
#include<QDir>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	My_obs_Guard obs_guard;
	//obs_guard.init();

	return a.exec();

}
