#ifndef CDEVTYPEEDIT_H
#define CDEVTYPEEDIT_H

#include <QDialog>
#include "ui_cdevtypeedit.h"

enum eNewClass
{
	CLASS_FACTORY = 0,
	CLASS_TYPE
};

class CdevTypeEdit : public QDialog
{
	Q_OBJECT

public:
	CdevTypeEdit(QWidget *parent = 0);
	~CdevTypeEdit();

	void SetClass(eNewClass c) { m_eClass = c; }
	void SetFactoryName(QString name) { m_sFactoryName = name; }
	void Start();

private:
	Ui::CdevTypeEdit ui;

	eNewClass m_eClass;
	QString m_sFactoryName;
	QString m_sPicName;

private:
	void Init();
	void InitUi();
	void InitSlot();

private slots:
	void SlotPicture();
	void SlotAffirm();
	void SlotCancel();

};

#endif // CDEVTYPEEDIT_H
