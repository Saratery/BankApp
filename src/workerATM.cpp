#include "workerATM.h"
#define MIN(a,b) ((a) < (b) ? (a) : (b))

workerATM::workerATM(uint16 n50, uint16 n100, uint16 n500, uint16 n1000, uint16 n5000)
{
	machine = new ATM_Instance(n50, n100, n500, n1000, n5000);
	tempNotes.note50 = machine->getNote50Number();
	tempNotes.note100 = machine->getNote100Number();
	tempNotes.note500 = machine->getNote500Number();
	tempNotes.note1000 = machine->getNote1000Number();
	tempNotes.note5000 = machine->getNote5000Number();

	// need to add exception here
	if (machine->getLimit() >= machine->getCurrentNoteNumber()) {
		tempLimit = machine->getLimit() - machine->getCurrentNoteNumber();
	}
	else {
		tempLimit = 0;
	}
}

workerATM::~workerATM()
{
	delete machine;
}

uint16 workerATM::getFreeAmountForNewNotes()
{
	return tempLimit;
}

void workerATM::checkAvailableMoney(int sum)
{
	const char limitWithdraw_str[] = "limit of withdraw operation: ";
	QByteArray str;
	if (tempNotes.note5000 > 5)
		str.append("\n5000 Ruble\n");
	if (tempNotes.note1000 > 4)
		str.append("1000 Ruble\n");
	if (tempNotes.note500 > 4)
		str.append("500 Ruble\n");
	if (tempNotes.note100 > 4)
		str.append("100 Ruble\n");
	if (tempNotes.note50 > 4)
		str.append("50 Ruble\n");

	int overall_sum = tempNotes.note5000 * 5000 + tempNotes.note1000 * 1000 +
		tempNotes.note500 * 500 + tempNotes.note100 * 100 + tempNotes.note50 * 50;
	str.append(limitWithdraw_str);
	str.append(QByteArray::number(MIN(overall_sum, withdrawLimit)));

	if (sum > withdrawLimit) {
		emit notEnoughMoneyToWithdraw(str.data());
		return;
	}

	int tsum = sum, tnumber;

	tnumber = tsum / 5000;
	tsum -= MIN(tnumber, tempNotes.note5000) * 5000;
	tempNotes.note5000 -= MIN(tnumber, tempNotes.note5000);

	tnumber = tsum / 1000;
	tsum -= MIN(tnumber, tempNotes.note1000) * 1000;
	tempNotes.note1000 -= MIN(tnumber, tempNotes.note1000);
	
	tnumber = tsum / 500;
	tsum -= MIN(tnumber, tempNotes.note500) * 500;
	tempNotes.note500 -= MIN(tnumber, tempNotes.note500);
	
	tnumber = tsum / 100;
	tsum -= MIN(tnumber, tempNotes.note100) * 100;
	tempNotes.note100 -= MIN(tnumber, tempNotes.note100);
	
	tnumber = tsum / 50;
	tsum -= MIN(tnumber, tempNotes.note50) * 50;
	tempNotes.note50 -= MIN(tnumber, tempNotes.note50);

	if (tsum == 0) {
		emit enoughMoneyToWithdraw();
	}
	else {
		setRealNumbersOfNotes();		
		emit notEnoughMoneyToWithdraw(str.data());
	}
}

void workerATM::setNewValues() {
	setNewNumbersOfNotes();
}

void workerATM::setNewValueOf50Notes(int value)
{
	if ((getNote50Number() + value) < 0) {
		emit requestedNote50NumberIsNotAvailable();
	}
	else {
		tempNotes.note50 = getNote50Number() + value;
	}
}

void workerATM::setNewValueOf100Notes(int value)
{
	if ((getNote100Number() + value) < 0) {
		emit requestedNote100NumberIsNotAvailable();
	}
	else {
		tempNotes.note100 = getNote100Number() + value;
	}
}

void workerATM::setNewValueOf500Notes(int value)
{
	if ((getNote500Number() + value) < 0) {
		emit requestedNote500NumberIsNotAvailable();
	}
	else {
		tempNotes.note500 = getNote500Number() + value;
	}
}

void workerATM::setNewValueOf1000Notes(int value)
{
	if ((getNote1000Number() + value) < 0) {
		emit requestedNote1000NumberIsNotAvailable();
	}
	else {
		tempNotes.note1000 = getNote1000Number() + value;
	}
}

void workerATM::setNewValueOf5000Notes(int value)
{
	if ((getNote5000Number() + value) < 0) {
		emit requestedNote5000NumberIsNotAvailable();
	}
	else {
		tempNotes.note5000 = getNote5000Number() + value;
	}
}

uint16 workerATM::getNote50Number() const
{
	return machine->getNote50Number();
}

uint16 workerATM::getNote100Number() const
{
	return machine->getNote100Number();
}

uint16 workerATM::getNote500Number() const
{
	return machine->getNote500Number();
}

uint16 workerATM::getNote1000Number() const
{
	return machine->getNote1000Number();
}

uint16 workerATM::getNote5000Number() const
{
	return machine->getNote5000Number();
}

void workerATM::checkFreeAmountForNewNotes()
{
	int amount = getFreeAmountForNewNotes();
	if (amount > 0) {
		emit enoughAmountForNewNotes(amount);
	}
	else {
		emit notEnoughAmountForNewNotes();
	}
}

void workerATM::setRealNumbersOfNotes()
{
	tempNotes.note50 = machine->getNote50Number();
	tempNotes.note100 = machine->getNote100Number();
	tempNotes.note500 = machine->getNote500Number();
	tempNotes.note1000 = machine->getNote1000Number();
	tempNotes.note5000 = machine->getNote5000Number();
}

void workerATM::setNewNumbersOfNotes()
{
	machine->setNote50(tempNotes.note50);
	machine->setNote100(tempNotes.note100);
	machine->setNote500(tempNotes.note500);
	machine->setNote1000(tempNotes.note1000);
	machine->setNote5000(tempNotes.note5000);
}

void workerATM::checkCurrentMachineState()
{
	QByteArray str;
	str.append("\n");
	str.append(QByteArray::number(machine->getNote50Number()));
	str.append(": 50 Ruble notes\n");
	str.append(QByteArray::number(machine->getNote100Number()));
	str.append(": 100 Ruble notes\n");
	str.append(QByteArray::number(machine->getNote500Number()));
	str.append(": 500 Ruble notes\n");
	str.append(QByteArray::number(machine->getNote1000Number()));
	str.append(": 1000 Ruble notes\n");
	str.append(QByteArray::number(machine->getNote5000Number()));
	str.append(": 5000 Ruble notes");
	sentNotesState(str.data());
}