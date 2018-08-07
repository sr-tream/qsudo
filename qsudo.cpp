#include "qsudo.h"
#include <iostream>

Qsudo::Qsudo(QStringList arguments, QWidget *parent) :
	QDialog(parent)
{
	arguments.pop_front();
	setupUi(this);
	sudo = new QProcess();

	connect(sudo, &QProcess::readyReadStandardOutput, this, &Qsudo::parseOutput);
	connect(sudo, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Qsudo::sudoFinished);

	QStringList args;
	args << "-S"; // Write the prompt to the standard error and read the password from the standard input instead of using the terminal device.
	args << "-p"; // Use a custom password prompt with optional escape sequences.
	args << "qsudogetpass"; // prompt
	for (auto &argument : arguments){
		if (argument.front() != '-' && windowTitle() == "Qsudo")
			setWindowTitle(argument);
		args << argument;
	}

	sudo->setArguments(args);
	sudo->setEnvironment(QProcess::systemEnvironment());
	sudo->setProcessChannelMode(QProcess::ProcessChannelMode::MergedChannels);
	sudo->setProgram("sudo");
	sudo->start();
}

void Qsudo::writePassword()
{
	sudo->write(pass->text().toLocal8Bit() + "\n");
	pass->clear();
}

void Qsudo::parseOutput()
{
	QString stdout = sudo->readAllStandardOutput().toStdString().c_str();

	if (stdout.indexOf("qsudogetpass") == 0){
		if (!pass->text().isEmpty())
			writePassword();
		else {
			awaitForPassword = true;
			if (isHidden())
				show();
		}
	} else
		std::cout << stdout.toStdString();
}

void Qsudo::sudoFinished(int code, QProcess::ExitStatus)
{
	QApplication::exit(code);
}

void Qsudo::on_showPass_clicked()
{
	if (pass->echoMode() == QLineEdit::Password){
                showPass->setIcon(QIcon(":/passShow.png"));
		pass->setEchoMode(QLineEdit::Normal);
	} else {
                showPass->setIcon(QIcon(":/passHide.png"));
		pass->setEchoMode(QLineEdit::Password);
	}
}

void Qsudo::on_buttonBox_rejected()
{
	if (sudo)
		sudo->kill();
	close();
}

void Qsudo::on_buttonBox_accepted()
{
	if (!pass->text().isEmpty()){
		if (awaitForPassword)
			writePassword();
		hide();
	}
}
