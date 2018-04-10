#include "qsudo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
        Qsudo w(argc, argv);

	return a.exec();
}
