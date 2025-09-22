#include "Particle.h"
#include <QDebug>

Particle::Particle(QQuickItem *viewQml, Point _positon, Point _velocity,
                   qreal _mass, QObject *parent)
    : QObject{parent}, m_mass(_mass), position{_positon}, velocity{_velocity}

{
    SetupView(viewQml);
    // ResetPositionMemory();
}

void Particle::SetupView(QQuickItem *viewQml) {
    view = viewQml;
    SetupView();
}

void Particle::SetupView() {
    view->setProperty("width", 32);
    view->setProperty("height", 32);

    view->setX(position.x);
    view->setY(position.y);

    view->setParent(this);
}
qreal Particle::radius() {
    qreal r = (qreal)1 + mass();
    return r;
}
qreal Particle::mass() const { return m_mass; }

void Particle::setMass(qreal newMass) { m_mass = newMass; }

void Particle::setX(qreal newX) {
    position.x = newX;
    view->setX(position.x);
}

void Particle::setY(qreal newY) {
    position.y = newY;
    view->setY(position.y);
}

void Particle::setPosition(Point newPosition) {
    setX(newPosition.x);
    setY(newPosition.y);
}
void Particle::ApplyVelocity(qreal deltaTime) {
    setX(position.x + velocity.x * deltaTime);
    setY(position.y + velocity.y * deltaTime);
}
void Particle::addToPosition(Point moveVector) {
    moveVector.x += position.x;
    moveVector.y += position.y;
    // setPosition(moveVector);
    setX(moveVector.x);
    setY(moveVector.y);
    velocity.x = 0;
    velocity.y = 0;
}

// void Particle::SetPositionMemory(qreal newX, qreal newY)
// {
//     mem_x = newX;
//     mem_y = newY;
// }

// void Particle::AddToPositionMemory(qreal addToX, qreal addToY)
// {
//     mem_x += addToX;
//     mem_y += addToY;
// }

// void Particle::ApplyPositionMemory()
// {
//     setPosition(mem_x, mem_y);
//     ResetPositionMemory();
// }

// void Particle::ResetPositionMemory()
// {
//     mem_x = position.x;
//     mem_y = position.y;
// }
