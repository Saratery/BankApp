#include "controller.h"

Controller::Controller(ATM *v, workerATM *w, QObject *parent)
{
	view = v;
	worker = w;
	currentPage = view->page;
	connect(view, &ATM::checkIfWithDrawalSumIsAvailabale, w, &workerATM::checkAvailableMoney);
	connect(view, &ATM::checkAvailableSpaceInMachine, w, &workerATM::checkFreeAmountForNewNotes);
	connect(view, &ATM::sendNew50NotesToMachine, w, &workerATM::setNewValueOf50Notes);
	connect(view, &ATM::sendNew100NotesToMachine, w, &workerATM::setNewValueOf100Notes);
	connect(view, &ATM::sendNew500NotesToMachine, w, &workerATM::setNewValueOf500Notes);
	connect(view, &ATM::sendNew1000NotesToMachine, w, &workerATM::setNewValueOf1000Notes);
	connect(view, &ATM::sendNew5000NotesToMachine, w, &workerATM::setNewValueOf5000Notes);
	connect(view, &ATM::signalToPerformOperation, w, &workerATM::setNewValues);
	connect(view, &ATM::signalRequestCurrentMachineState, w, &workerATM::checkCurrentMachineState);
	connect(w, &workerATM::enoughAmountForNewNotes, v, &ATM::setDepositionPage);
	connect(w, &workerATM::notEnoughAmountForNewNotes, v, &ATM::setDepositionIsCanceledPage);
	connect(w, &workerATM::enoughMoneyToWithdraw, v, &ATM::setWithdrawalChoicePage);
	connect(w, &workerATM::notEnoughMoneyToWithdraw, v, &ATM::withdrawalSumIsNotCorrect);
	connect(w, &workerATM::sentNotesState, v, &ATM::showCurrentMachineState);
	connect(w, &workerATM::requestedNote50NumberIsNotAvailable, v, &ATM::showNote50IsNotAvailable);
	connect(w, &workerATM::requestedNote100NumberIsNotAvailable, v, &ATM::showNote100IsNotAvailable);
	connect(w, &workerATM::requestedNote500NumberIsNotAvailable, v, &ATM::showNote500IsNotAvailable);
	connect(w, &workerATM::requestedNote1000NumberIsNotAvailable, v, &ATM::showNote1000IsNotAvailable);
	connect(w, &workerATM::requestedNote5000NumberIsNotAvailable, v, &ATM::showNote5000IsNotAvailable);
}

Controller::~Controller()
{
	delete view;
	delete worker;
}

