#include "my_file_watch_test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MY_File_watch_Test w;
	w.show();
	return a.exec();
}
