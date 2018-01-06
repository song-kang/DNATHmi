#ifndef CDEV_H
#define CDEV_H

#include <QWidget>
#include "ui_cdev.h"

#define Device	"CDevice"

class CDev : public QWidget
{
	Q_OBJECT

public:
	CDev(QWidget *parent = 0);
	~CDev();

private:
	Ui::CDev ui;

	QList<QToolButton *> m_pToolBtns;

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotBrowseClicked();
	void SlotOperateClicked();
	void SlotConfigClicked();
	void SlotStatisticsClicked();
	void SlotLogClicked();
	void SlotAdvancedClicked();
};

#endif // CDEV_H
