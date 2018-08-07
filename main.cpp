#include "qsudo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
		Qsudo w(a.arguments());

	return a.exec();
}
