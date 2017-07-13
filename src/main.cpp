#include "atm.h"
#include "workerATM.h"
#include "controller.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ATM *v = new ATM();
	workerATM *w = new workerATM();
	Controller cntrl(v, w);

	v->show();
	return a.exec();
}
