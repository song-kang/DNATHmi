#ifndef CHOME_H
#define CHOME_H

#include <QWidget>
#include "ui_chome.h"

#define Home	"CHome"

class CHome : public QWidget
{
	Q_OBJECT

public:
	CHome(QWidget *parent = 0);
	~CHome();

private:
	Ui::CHome ui;

	QList<QToolButton *> m_pToolBtns;

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotLoginClicked();
	void SlotTypeManClicked();
	void SlotDevManClicked();

};

#endif // CHOME_H
