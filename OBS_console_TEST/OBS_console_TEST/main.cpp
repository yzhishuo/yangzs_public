#include "obs_console_test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OBS_console_TEST w;
	w.show();
	return a.exec();
}
