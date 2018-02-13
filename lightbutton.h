#ifndef LIGHTBUTTON_H
#define LIGHTBUTTON_H

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT LightButton : public QWidget
#else
class LightButton : public QWidget
#endif

{
	Q_OBJECT
	Q_PROPERTY(QString text READ getText WRITE setText)
	Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

	Q_PROPERTY(QColor borderOutColorStart READ getBorderOutColorStart WRITE setBorderOutColorStart)
	Q_PROPERTY(QColor borderOutColorEnd READ getBorderOutColorEnd WRITE setBorderOutColorEnd)
	Q_PROPERTY(QColor borderInColorStart READ getBorderInColorStart WRITE setBorderInColorStart)
	Q_PROPERTY(QColor borderInColorEnd READ getBorderInColorEnd WRITE setBorderInColorEnd)
	Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)

	Q_PROPERTY(bool canMove READ getCanMove WRITE setCanMove)
	Q_PROPERTY(bool showOverlay READ getShowOverlay WRITE setShowOverlay)
	Q_PROPERTY(QColor overlayColor READ getOverlayColor WRITE setOverlayColor)

public:
	explicit LightButton(QWidget *parent = 0);

protected:
	bool eventFilter(QObject *, QEvent *);
	void paintEvent(QPaintEvent *);
	void drawBorderOut(QPainter *painter);
	void drawBorderIn(QPainter *painter);
	void drawBg(QPainter *painter);
	void drawText(QPainter *painter);
	void drawOverlay(QPainter *painter);

private:
	QString text;                   
	QColor textColor;               

	QColor borderOutColorStart;     
	QColor borderOutColorEnd;       
	QColor borderInColorStart;      
	QColor borderInColorEnd;        
	QColor bgColor;                 

	bool canMove;                   
	bool showOverlay;           
	QColor overlayColor;

public:
	QString getText()               const;
	QColor getTextColor()           const;

	QColor getBorderOutColorStart() const;
	QColor getBorderOutColorEnd()   const;
	QColor getBorderInColorStart()  const;
	QColor getBorderInColorEnd()    const;
	QColor getBgColor()             const;

	bool getCanMove()               const;
	bool getShowOverlay()           const;
	QColor getOverlayColor()        const;

	QSize sizeHint()                const;
	QSize minimumSizeHint()         const;

public Q_SLOTS:
    void setText(const QString &text);
    void setTextColor(const QColor &textColor);

    void setBorderOutColorStart(const QColor &borderOutColorStart);
    void setBorderOutColorEnd(const QColor &borderOutColorEnd);

    void setBorderInColorStart(const QColor &borderInColorStart);
    void setBorderInColorEnd(const QColor &borderInColorEnd);

    void setBgColor(const QColor &bgColor);

	void setCanMove(bool canMove);
	void setShowOverlay(bool showOverlay);
    void setOverlayColor(const QColor &overlayColor);

	void setGreen();
	void setRed();
	void setYellow();
	void setBlack();
	void setGray();
	void setBlue();
	void setLightBlue();
	void setLightRed();
	void setLightGreen();
};

#endif //LIGHTBUTTON_H
