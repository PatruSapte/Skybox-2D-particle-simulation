#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QQuickItem>
#include <QVariant>
#include "Point.h"

class Particle : public QObject
{
    Q_OBJECT


public:
    explicit Particle(QQuickItem* viewQml, qreal _x, qreal _y, qreal _mass = 1, Point _velocity = Point(0, 0), QObject *parent = nullptr);


    QQuickItem* view;

    void SetupView(QQuickItem* viewQml);
    void SetupView();

    Point position;
    Point velocity;
    qreal mass() const;
    qreal radius();
    void setX(qreal newX);
    void setY(qreal newY);

    void setMass(qreal newMass);
    void setPosition(Point newPosition);

    void addToPosition(Point addValue);
    void addToVelocity(Point addValue);

    void ApplyVelocity(qreal deltaTime);
signals:



private:

    qreal m_mass;

    qreal mem_x=0;
    qreal mem_y=0;
};

#endif // PARTICLE_H
