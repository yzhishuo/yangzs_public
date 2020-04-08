
#include <QtWidgets/QApplication>
#include"my_file_monitor.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	My_File_Monitor my_monitor;
	my_monitor.init();

	return a.exec();
}
