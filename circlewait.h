#ifndef CIRCLEWAIT_H
#define CIRCLEWAIT_H

#include <QWidget>

class CircleWait : public QWidget
{
	Q_OBJECT
public:
	explicit CircleWait(QWidget *parent = 0);

	void setColor(QColor color);
	void setClockwiseRotate(bool clockwise);
	void setRotateDelta(int delta);

protected:
	void paintEvent(QPaintEvent *);
	void drawCircleWait(QPainter& p);

private:
	QColor m_color;
	bool m_clockwiseRotate;
	int m_rotateDelta;
	int m_rotateAngle;

	QTimer* m_timer;
};

#endif // CIRCLEWAIT_H
