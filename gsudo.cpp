#include "gsudo.h"

Gsudo::Gsudo(int &argc, char **argv, QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);
	sudo = new QProcess();

	connect(sudo, &QProcess::readyReadStandardOutput, this, &Gsudo::parseOutput);
	connect(sudo, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Gsudo::sudoFinished);

	QStringList args;
	args << "-S"; // Write the prompt to the standard error and read the password from the standard input instead of using the terminal device.
	args << "-p"; // Use a custom password prompt with optional escape sequences.
	args << "gsudogetpass"; // prompt
	for (int i = 1; i < argc; ++i)
		args << argv[i];

	sudo->setArguments(args);
	sudo->setEnvironment(QProcess::systemEnvironment());
	sudo->setProcessChannelMode(QProcess::ProcessChannelMode::MergedChannels);
	sudo->setProgram("sudo");
	sudo->start();
}

void Gsudo::writePassword()
{
	sudo->write(pass->text().toLocal8Bit() + "\n");
	pass->clear();
}

void Gsudo::parseOutput()
{
	QString stdout = sudo->readAllStandardOutput().toStdString().c_str();

	if (stdout.indexOf("gsudogetpass") == 0){
		if (!pass->text().isEmpty())
			writePassword();
		else {
			awaitForPassword = true;
			if (isHidden())
				show();
		}
	}
}

void Gsudo::sudoFinished(int code, QProcess::ExitStatus)
{
	QApplication::exit(code);
}

void Gsudo::on_showPass_clicked()
{
	if (pass->echoMode() == QLineEdit::Password){
		showPass->setIcon(QIcon(":/eye.png"));
		pass->setEchoMode(QLineEdit::Normal);
	} else {
		showPass->setIcon(QIcon(":/closed.png"));
		pass->setEchoMode(QLineEdit::Password);
	}
}

void Gsudo::on_buttonBox_rejected()
{
	if (sudo)
		sudo->kill();
	close();
}

void Gsudo::on_buttonBox_accepted()
{
	if (!pass->text().isEmpty()){
		if (awaitForPassword)
			writePassword();
		hide();
	}
}
