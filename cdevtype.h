#ifndef CDEVTYPE_H
#define CDEVTYPE_H

#include <QWidget>
#include "ui_cdevtype.h"

#define DeviceFactoryType	"CDevType"

class CDevType : public QWidget
{
	Q_OBJECT

public:
	CDevType(QWidget *parent = 0);
	~CDevType();

private:
	Ui::CDevType ui;

	QList<QPushButton*> m_listFactory;
	QList<QPushButton*> m_listType;

private:
	void Init();
	void InitUi();
	void InitSlot();
	void Start();
	void ShowFactory();
	void ShowType(QString path);
	void HmiVisible(bool visible);

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotImportClicked();
	void SlotFactoryClick();
	void SlotTypeClick();
	void SlotAffirmClicked();
	void SlotCancelClicked();
	void SlotSelectClicked();

};

#endif // CDEVTYPE_H
