#ifndef QSUDO_H
#define QSUDO_H

#include "ui_qsudo.h"

#include <QProcess>

class Qsudo : public QDialog, private Ui::Qsudo
{
	Q_OBJECT
public:
	explicit Qsudo(int &argc, char **argv, QWidget *parent = 0);

protected:
	void writePassword();

private slots:
	void parseOutput();
	void sudoFinished(int code, QProcess::ExitStatus status);

	void on_showPass_clicked();
	void on_buttonBox_rejected();
	void on_buttonBox_accepted();

private:
	QProcess *sudo = nullptr;
	bool awaitForPassword = false;
};

#endif // QSUDO_H
