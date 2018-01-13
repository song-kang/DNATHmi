#include "cdevtype.h"
#include "iconhelper.h"
#include "dnathmi.h"

#define charSize		20
#define iconSize		30
#define iconWidth		40
#define iconHeight		40
#define btnHeight		60

CDevType::CDevType(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
	Start();
}

CDevType::~CDevType()
{

}

void CDevType::Init()
{
	ui.label_manufacture->setText(tr("Device Factory"));
	ui.label_manufacture->setStyleSheet(QString("QLabel#label_manufacture{font:%1px;color:#383838;}").arg(20));
	ui.label_type->setText(tr("Device Type"));
	ui.label_type->setStyleSheet(QString("QLabel#label_type{font:%1px;color:#383838;}").arg(20));

	QPixmap iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf03c, iconSize, iconWidth, iconHeight);
	ui.btnImport->setText(tr("  Import"));
	ui.btnImport->setFixedHeight(btnHeight);
	ui.btnImport->setFixedWidth(200);
	ui.btnImport->setIcon(QIcon(iconNormal));
	ui.btnImport->setStyleSheet(QString("QPushButton#btnImport{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf19c, iconSize, iconWidth, iconHeight);
	ui.btnNewManufacture->setText(tr("  New Factory"));
	ui.btnNewManufacture->setFixedHeight(btnHeight);
	ui.btnNewManufacture->setFixedWidth(200);
	ui.btnNewManufacture->setIcon(QIcon(iconNormal));
	ui.btnNewManufacture->setStyleSheet(QString("QPushButton#btnNewManufacture{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #594c6d,stop:1 #594c6d);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf0ca, iconSize, iconWidth, iconHeight);
	ui.btnNewType->setText(tr("  New Type"));
	ui.btnNewType->setFixedHeight(btnHeight);
	ui.btnNewType->setFixedWidth(200);
	ui.btnNewType->setIcon(QIcon(iconNormal));
	ui.btnNewType->setStyleSheet(QString("QPushButton#btnNewType{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #525f42,stop:1 #525f42);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00c, iconSize, iconWidth, iconHeight);
	ui.btnAffirm->setText(tr("  Affirm"));
	ui.btnAffirm->setFixedHeight(btnHeight);
	ui.btnAffirm->setFixedWidth(200);
	ui.btnAffirm->setIcon(QIcon(iconNormal));
	ui.btnAffirm->setStyleSheet(QString("QPushButton#btnAffirm{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00d, iconSize, iconWidth, iconHeight);
	ui.btnCancel->setText(tr("  Cancel"));
	ui.btnCancel->setFixedHeight(btnHeight);
	ui.btnCancel->setFixedWidth(200);
	ui.btnCancel->setIcon(QIcon(iconNormal));
	ui.btnCancel->setStyleSheet(QString("QPushButton#btnCancel{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #b3424a,stop:1 #b3424a);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf016, iconSize, iconWidth, iconHeight);
	ui.btnSelect->setText(tr("  Import File"));
	ui.btnSelect->setFixedHeight(btnHeight);
	ui.btnSelect->setFixedWidth(200);
	ui.btnSelect->setIcon(QIcon(iconNormal));
	ui.btnSelect->setStyleSheet(QString("QPushButton#btnSelect{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #009ad6,stop:1 #009ad6);font:%1px;}").arg(charSize));

	ui.lineEdit_select->setFixedHeight(btnHeight);
	ui.lineEdit_select->setStyleSheet(QString("QLineEdit#lineEdit_select{font:%1px;border:1px solid #181d4b;border-radius:5px;}").arg(charSize));
}

void CDevType::InitUi()
{
	QStringList qss;
	qss.append(QString("QScrollArea#scrollArea1{background:transparent;}"));
	qss.append(QString("QScrollArea#scrollArea2{background:transparent;}"));
	qss.append(QString("QWidget#scrollAreaManufacture{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QWidget#scrollAreaType{background-color:rgb(255,255,255,150);}"));
	this->setStyleSheet(qss.join(""));
}

void CDevType::InitSlot()
{
	connect(ui.btnImport, SIGNAL(clicked(bool)), this, SLOT(SlotImportClicked()));
	connect(ui.btnAffirm, SIGNAL(clicked(bool)), this, SLOT(SlotAffirmClicked()));
	connect(ui.btnCancel, SIGNAL(clicked(bool)), this, SLOT(SlotCancelClicked()));
	connect(ui.btnSelect, SIGNAL(clicked(bool)), this, SLOT(SlotSelectClicked()));
}

void CDevType::Start()
{
	HmiVisible(false);

	if (!Common::FolderExists(Common::GetCurrentAppPath()+"devices"))
		Common::CreateFolder(Common::GetCurrentAppPath()+"devices");

	ShowFactory();
}

void CDevType::SlotImportClicked()
{
	HmiVisible(true);
}

void CDevType::SlotAffirmClicked()
{
	HmiVisible(false);
}

void CDevType::SlotCancelClicked()
{
	HmiVisible(false);
}

void CDevType::SlotSelectClicked()
{

}

void CDevType::SlotFactoryClick()
{
	QString factoryName;
	QPushButton *btn = (QPushButton *)sender();
	for (int i = 0; i < m_listFactory.count(); i++)
	{
		if (m_listFactory.at(i) == btn)
		{
			QWidget *w = (QWidget*)m_listFactory.at(i)->parent();
			w->setStyleSheet(QString("QWidget#%1{border:3px solid #d71345;}").arg(w->objectName()));
			QLabel *name = w->findChild<QLabel *>(QString("factoryLabel%1").arg(i+1));
			factoryName = name->text();
		}
		else
		{
			QWidget *w = (QWidget*)m_listFactory.at(i)->parent();
			w->setStyleSheet(QString("QWidget#%1{border:0px solid #242424;}").arg(w->objectName()));
		}
	}

	ShowType(Common::GetCurrentAppPath()+"devices/"+factoryName);
}

void CDevType::SlotTypeClick()
{
	QString typeName;
	QPushButton *btn = (QPushButton *)sender();
	for (int i = 0; i < m_listType.count(); i++)
	{
		if (m_listType.at(i) == btn)
		{
			QWidget *w = (QWidget*)m_listType.at(i)->parent();
			w->setStyleSheet(QString("QWidget#%1{border:3px solid #d71345;}").arg(w->objectName()));
			QLabel *name = w->findChild<QLabel *>(QString("typeLabel%1").arg(i+1));
			typeName = name->text();
		}
		else
		{
			QWidget *w = (QWidget*)m_listType.at(i)->parent();
			w->setStyleSheet(QString("QWidget#%1{border:0px solid #242424;}").arg(w->objectName()));
		}
	}
}

void CDevType::ShowFactory()
{
	Common::ClearLayout(ui.gridLayout_manufacture);
	m_listFactory.clear();

	int pos = 1;
	QHBoxLayout *hLayout;
	QVBoxLayout *vLayout,*vLayout1,*vLayout2; 
	QWidget *factoryWidget;

	QDir dir(Common::GetCurrentAppPath()+"devices");
	dir.setFilter(QDir::Dirs);
	QFileInfoList list = dir.entryInfoList();
	vLayout = new QVBoxLayout();
	foreach (QFileInfo fileInfo,list)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		factoryWidget = new QWidget;
		factoryWidget->setObjectName(QString("factoryWidget%1").arg(pos));
		factoryWidget->setContentsMargins(0,0,0,0);
		if (pos % 2)
		{
			hLayout = new QHBoxLayout();
			vLayout1 = new QVBoxLayout(factoryWidget);
			QPushButton *logo = new QPushButton();
			logo->setFixedSize(200,100);
			logo->setStyleSheet("background:transparent;");
			QPixmap pix;
			if (Common::FileExists(fileInfo.absolutePath()+"/"+fileInfo.fileName()+"/logo.png"))
				pix.load(tr("%1/logo.png").arg(fileInfo.absolutePath()+"/"+fileInfo.fileName()));
			else
				pix.load(":/image/unLogo");
			logo->setIcon(QIcon(pix));
			logo->setIconSize(QSize(200,100));
			m_listFactory.append(logo);
			connect(logo, SIGNAL(clicked(bool)), this, SLOT(SlotFactoryClick()));

			QLabel *name = new QLabel(fileInfo.fileName());
			name->setObjectName(QString("factoryLabel%1").arg(pos));
			name->setStyleSheet(QString("font:%1px;color:#383838;").arg(15));
			name->setAlignment(Qt::AlignCenter);
			vLayout1->addWidget(logo,0,Qt::AlignHCenter);
			vLayout1->addWidget(name,0,Qt::AlignHCenter);
			hLayout->addWidget(factoryWidget);
		}
		else
		{
			vLayout2 = new QVBoxLayout(factoryWidget);
			QPushButton *logo = new QPushButton;
			logo->setFixedSize(200,100);
			logo->setStyleSheet("background:transparent;");
			QPixmap pix;
			if (Common::FileExists(fileInfo.absolutePath()+"/"+fileInfo.fileName()+"/logo.png"))
				pix.load(tr("%1/logo.png").arg(fileInfo.absolutePath()+"/"+fileInfo.fileName()));
			else
				pix.load(":/image/unLogo");
			logo->setIcon(QIcon(pix));
			logo->setIconSize(QSize(200,100));
			m_listFactory.append(logo);
			connect(logo, SIGNAL(clicked(bool)), this, SLOT(SlotFactoryClick()));

			QLabel *name = new QLabel(fileInfo.fileName());
			name->setObjectName(QString("factoryLabel%1").arg(pos));
			name->setStyleSheet(QString("font:%1px;color:#383838;").arg(15));
			name->setAlignment(Qt::AlignCenter);
			vLayout2->addWidget(logo,0,Qt::AlignHCenter);
			vLayout2->addWidget(name,0,Qt::AlignHCenter);
			hLayout->addWidget(factoryWidget);
		}

		vLayout->addLayout(hLayout);
		pos++;
	}

	vLayout->addStretch();
	ui.gridLayout_manufacture->addLayout(vLayout,0,0);
	if (m_listFactory.count() > 0)
		m_listFactory.at(0)->click();
}

void CDevType::ShowType(QString path)
{
	Common::ClearLayout(ui.gridLayout_type);
	m_listType.clear();

	int pos = 1;
	QHBoxLayout *hLayout;
	QVBoxLayout *vLayout,*vLayout1,*vLayout2; 
	QWidget *typeWidget;

	QDir dir(path);
	dir.setFilter(QDir::Dirs);
	QFileInfoList list = dir.entryInfoList();
	vLayout = new QVBoxLayout();
	foreach (QFileInfo fileInfo,list)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		typeWidget = new QWidget;
		typeWidget->setObjectName(QString("typeWidget%1").arg(pos));
		typeWidget->setContentsMargins(0,0,0,0);
		if (pos % 2)
		{
			hLayout = new QHBoxLayout();
			vLayout1 = new QVBoxLayout(typeWidget);
			QPushButton *type = new QPushButton();
			type->setFixedSize(200,100);
			type->setStyleSheet("background:transparent;");
			QPixmap pix;
			if (Common::FileExists(path+QString("/%1").arg(fileInfo.fileName())+"/logo.png"))
				pix.load(tr("%1/logo.png").arg(path+QString("/%1").arg(fileInfo.fileName())));
			else
				pix.load(":/image/unType");
			type->setIcon(QIcon(pix));
			type->setIconSize(QSize(200,100));
			m_listType.append(type);
			connect(type, SIGNAL(clicked(bool)), this, SLOT(SlotTypeClick()));

			QLabel *name = new QLabel(fileInfo.fileName());
			name->setObjectName(QString("typeLabel%1").arg(pos));
			name->setStyleSheet(QString("font:%1px;color:#383838;").arg(15));
			name->setAlignment(Qt::AlignCenter);
			vLayout1->addWidget(type,0,Qt::AlignHCenter);
			vLayout1->addWidget(name,0,Qt::AlignHCenter);
			hLayout->addWidget(typeWidget);
		}
		else
		{
			vLayout2 = new QVBoxLayout(typeWidget);
			QPushButton *type = new QPushButton;
			type->setFixedSize(200,100);
			type->setStyleSheet("background:transparent;");
			QPixmap pix;
			if (Common::FileExists(path+QString("/%1").arg(fileInfo.fileName())+"/logo.png"))
				pix.load(tr("%1/logo.png").arg(path+QString("/%1").arg(fileInfo.fileName())));
			else
				pix.load(":/image/unType");
			type->setIcon(QIcon(pix));
			type->setIconSize(QSize(200,100));
			m_listType.append(type);
			connect(type, SIGNAL(clicked(bool)), this, SLOT(SlotTypeClick()));

			QLabel *name = new QLabel(fileInfo.fileName());
			name->setObjectName(QString("typeLabel%1").arg(pos));
			name->setStyleSheet(QString("font:%1px;color:#383838;").arg(15));
			name->setAlignment(Qt::AlignCenter);
			vLayout2->addWidget(type,0,Qt::AlignHCenter);
			vLayout2->addWidget(name,0,Qt::AlignHCenter);
			hLayout->addWidget(typeWidget);
		}

		vLayout->addLayout(hLayout);
		pos++;
	}

	vLayout->addStretch();
	ui.gridLayout_type->addLayout(vLayout,0,0);
}

void CDevType::HmiVisible(bool visible)
{
	ui.btnSelect->setVisible(visible);
	ui.btnAffirm->setVisible(visible);
	ui.btnCancel->setVisible(visible);
	ui.lineEdit_select->setVisible(visible);
	ui.btnNewManufacture->setVisible(!visible);
	ui.btnNewType->setVisible(!visible);
	ui.btnImport->setVisible(!visible);
}