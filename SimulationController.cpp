#include "SimulationController.h"
#include <Particle.h>
#include <QDebug>
#include <QQmlContext>
#include <QTimer>
SimulationController::SimulationController(SimulationModel *model, QQmlApplicationEngine* engine, QObject *parent)
    : QObject{parent}
{
    m_model = model;
    this->engine = engine;
}
void SimulationController::toggleSimulation(bool run) {
    if (run)
        m_model->start();
    else
        m_model->pause();
}

void SimulationController::createPlanet(QObject* parent, qreal x, qreal y )
{
    // Example logic: queue an addPlanet command to the model

    QQuickItem* planet = createQmlObject(parent, "Skybox/Planet.qml","planet_");

    Particle* newPlanet = new Particle(planet, x, y);

    m_model->addNewPlanet(newPlanet);

}

QQuickItem* SimulationController::createQmlObject(QObject* parent,QString path,QString id)
{
    QQmlComponent component(engine, QUrl::fromLocalFile(path));
    QQuickItem * mainObject_;
    if(component.isError())
    {
        qWarning() << "QmlItemCreator::createQmlObject The QMLComponent for "
                   << path << " has errors: " << component.errorString();
    }
    else if (component.isReady())
    {

        mainObject_ = qobject_cast<QQuickItem*>(component.create());
        QQmlEngine::setObjectOwnership(mainObject_, QQmlEngine::CppOwnership);

        mainObject_->setProperty("id", id);

        mainObject_->setParent(m_model);  // SimulationModel instance might be a better parent
        mainObject_->setParentItem(qobject_cast<QQuickItem*>(parent));

        // qDebug()<<mainObject_
         //         <<"\n  property('parent'): " << mainObject_->property("parent")
         //         <<"\n  parentItem()->property(id)(): " << mainObject_->parentItem()->property("id")
         //         <<"\n  parentItem(): " << mainObject_->parentItem()
         //         <<"\n  parent(): " << mainObject_->parent()
         //         <<"\n  id: " << mainObject_->property("id");
    }

    return mainObject_;
}
