#include "cdevtypeedit.h"
#include "iconhelper.h"
#include "msgbox.h"
#include "dnathmi.h"

#define topIcoWidth		18
#define topTitleSize	18
#define topBtnWidth		45
#define charSize		20
#define iconSize		30
#define iconWidth		40
#define iconHeight		40
#define btnHeight		40

CdevTypeEdit::CdevTypeEdit(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
}

CdevTypeEdit::~CdevTypeEdit()
{

}

void CdevTypeEdit::Init()
{
	ui.label_title->setFixedHeight(20);
	ui.lineEdit_name->setFixedHeight(30);
	ui.btnPicture->setFixedHeight(250);
	ui.btnPicture->setText(tr("Click select picture."));

	QPixmap iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00c, iconSize, iconWidth, iconHeight);
	ui.btnAffirm->setText(tr("  Affirm"));
	ui.btnAffirm->setFixedHeight(btnHeight);
	ui.btnAffirm->setIcon(QIcon(iconNormal));
	ui.btnAffirm->setStyleSheet(QString("QPushButton#btnAffirm{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00d, iconSize, iconWidth, iconHeight);
	ui.btnCancel->setText(tr("  Cancel"));
	ui.btnCancel->setFixedHeight(btnHeight);
	ui.btnCancel->setIcon(QIcon(iconNormal));
	ui.btnCancel->setStyleSheet(QString("QPushButton#btnCancel{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #b3424a,stop:1 #b3424a);font:%1px;}").arg(charSize));

	ui.widget_top->setStyleSheet(QString("QWidget#widget_top"
		"{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}").arg("#00688B").arg("#093746"));

	QStringList qss;
	qss.append(QString("*{outline:0px;}"));
	qss.append(QString("QWidget#widget_main{background-color:#f2eada;border:1px solid #242424;}"));
	qss.append(QString("QLabel#label_title{font:%1px;color:#FEFEFE;}").arg(topTitleSize));
	qss.append(QString("QLabel#label_name{font:%1px;color:#383838;}").arg(charSize));
	qss.append(QString("QLineEdit#lineEdit_name{font:%1px;border:1px solid #181d4b;border-radius:3px;}").arg(charSize));
	qss.append(QString("QPushButton#btnPicture{background:transparent;font:%1px;border:1px solid #181d4b}").arg(charSize));
	this->setStyleSheet(qss.join(""));
}

void CdevTypeEdit::InitUi()
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	this->setFixedSize(500, 400);
	ui.widget_top->setFixedHeight(40);

	QRect rect = QApplication::desktop()->availableGeometry(QApplication::desktop()->primaryScreen());
	move((rect.width() - width())/2,(rect.height() - height())/2);
}

void CdevTypeEdit::InitSlot()
{
	connect(ui.btnPicture, SIGNAL(clicked()), this, SLOT(SlotPicture()));
	connect(ui.btnAffirm, SIGNAL(clicked()), this, SLOT(SlotAffirm()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(SlotCancel()));
}

void CdevTypeEdit::Start()
{
	if (m_eClass == CLASS_FACTORY)
	{
		ui.label_title->setText(tr("New Factory"));
		ui.label_name->setText(tr("Input Factory:"));
	}
	else if (m_eClass == CLASS_TYPE)
	{
		ui.label_title->setText(tr("New Device Type"));
		ui.label_name->setText(tr("Input Type:"));
	}
}

void CdevTypeEdit::SlotPicture()
{
	m_sPicName = QFileDialog::getOpenFileName(this, tr("Import Picture File"),QString::null,tr("Png File (*.png)"));
	if (!m_sPicName.isEmpty())
	{
		QPixmap pix;
		pix.load(m_sPicName);
		ui.btnPicture->setIcon(QIcon(pix));
		ui.btnPicture->setIconSize(QSize(350,300));
		ui.btnPicture->setText(QString::null);
	}
}

void CdevTypeEdit::SlotAffirm()
{
	bool ret;
	if (ui.lineEdit_name->text().isEmpty())
	{
		MsgBox::Instance()->warning(tr("Please input name"));
		return;
	}
	
	if (m_eClass == CLASS_FACTORY)
	{
		if (Common::FolderExists(Common::GetCurrentAppPath()+"devices/"+ui.lineEdit_name->text()))
		{
			MsgBox::Instance()->warning(tr("Factory already exist."));
			return;
		}

		ret = Common::CreateFolder(Common::GetCurrentAppPath()+"devices/"+ui.lineEdit_name->text());
		if (ret && !m_sPicName.isEmpty())
			ret = QFile::copy(m_sPicName,Common::GetCurrentAppPath()+"devices/"+ui.lineEdit_name->text()+"/logo.png");
	}
	else if (m_eClass == CLASS_TYPE)
	{
		if (Common::FolderExists(Common::GetCurrentAppPath()+"devices/"+m_sFactoryName+"/"+ui.lineEdit_name->text()))
		{
			MsgBox::Instance()->warning(tr("Device type already exist."));
			return;
		}

		ret = Common::CreateFolder(Common::GetCurrentAppPath()+"devices/"+m_sFactoryName+"/"+ui.lineEdit_name->text());
		if (ret && !m_sPicName.isEmpty())
			QFile::copy(m_sPicName,Common::GetCurrentAppPath()+"devices/"+m_sFactoryName+"/"+ui.lineEdit_name->text()+"/logo.png");
	}

	if (ret)
	{
		MsgBox::Instance()->information(tr("New Success."));
		accept();
	}
	else
		MsgBox::Instance()->critical(tr("New Failed."));

	SlotCancel();
}

void CdevTypeEdit::SlotCancel()
{
	close();
}
