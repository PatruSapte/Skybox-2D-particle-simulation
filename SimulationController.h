#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>

#include "SimulationModel.h"


class SimulationController : public QObject
{
    Q_OBJECT
public:
    explicit SimulationController(SimulationModel *model, QQmlApplicationEngine *engine, QObject *parent = nullptr);

    QQmlApplicationEngine *engine;
    SimulationModel *m_model;

    void toggleSimulation(bool run);
    Q_INVOKABLE void createPlanet(QObject* parent, qreal x, qreal y, QVector2D velocity);
    QQuickItem *createQmlObject(QObject *parent, QString path, QString id="no_id_provided");

};

#endif // SIMULATIONCONTROLLER_H
