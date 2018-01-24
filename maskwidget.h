#ifndef MASKWIDGET_H
#define MASKWIDGET_H

#include <QWidget>
#include <QMutex>

class MaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MaskWidget(QWidget *parent = 0);
    static MaskWidget *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new MaskWidget;
            }
        }

        return self;
    }

	static void DestoryInstance();

protected:
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    static MaskWidget *self;
    QWidget *mainWidget;
    QStringList dialogNames;

public slots:
    void setMainWidget(QWidget *mainWidget);
    void setDialogNames(const QStringList &dialogNames);
	void appendDialogName(const QString dialogName);
    void setBgColor(const QColor &bgColor);
    void setOpacity(double opacity);
};

#endif // MASKWIDGET_H
