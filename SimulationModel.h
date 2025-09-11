#ifndef SIMULATIONMODEL_H
#define SIMULATIONMODEL_H

#include <QObject>
#include <QTimer>
#include <Particle.h>
#include <QList>

class SimulationModel : public QObject
{
    Q_OBJECT

public:
    explicit SimulationModel(QObject *parent = nullptr);
    void tick();

    void start(int msecTickInterval = 10);
    void pause();

    void addNewPlanet(Particle *planet);

    qreal timerDeltaTime();
    qreal deltaTime;

private:
    QTimer *m_timer;
    QList<Particle*> queueNewPlanets;
    QList<Particle*> activePlanets;
signals:
};

#endif // SIMULATIONMODEL_H
