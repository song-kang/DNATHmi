#ifndef CDEVLIST_H
#define CDEVLIST_H

#include <QWidget>
#include "ui_cdevlist.h"

#define DeviceList	"CDevList"

class CDevList : public QWidget
{
	Q_OBJECT

public:
	CDevList(QWidget *parent = 0);
	~CDevList();

private:
	Ui::CDevList ui;

	QList<QToolButton *> m_pToolBtns;

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotBrowseClicked();
	void SlotImportClicked();
	void SlotExportClicked();
	void SlotStateClicked();
	void SlotCheckImportClicked();
	void SlotCheckExportClicked();

};

#endif // CDEVLIST_H
