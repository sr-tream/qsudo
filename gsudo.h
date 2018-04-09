#ifndef GSUDO_H
#define GSUDO_H

#include "ui_gsudo.h"

#include <QProcess>

class Gsudo : public QDialog, private Ui::Gsudo
{
	Q_OBJECT
public:
	explicit Gsudo(int &argc, char **argv, QWidget *parent = 0);

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

#endif // GSUDO_H
