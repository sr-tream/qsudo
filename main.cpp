#include "gsudo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Gsudo w(argc, argv);

	return a.exec();
}
