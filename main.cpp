#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWindow>
#include <QMouseEvent>
#include "SimulationController.h"
#include "SimulationModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SimulationModel model;
    SimulationController controller(&model, &engine);

    engine.rootContext()->setContextProperty("simulationModel", &model);
    engine.rootContext()->setContextProperty("simulationController", &controller);

    controller.toggleSimulation(true);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    qmlRegisterUncreatableType<Particle>("Skybox", 1, 0, "Particle", "Use Particle only from C++");
    engine.loadFromModule("Skybox", "Main");

   /* QQmlComponent component( &engine, QUrl::fromLocalFile("Skybox/Planet.qml"));
    QObject *planetTest = component.create();

    planetTest->setProperty("width", 50);
    planetTest->setProperty("height", 50);

    planetTest->setProperty("x", 55);
    planetTest->setProperty("y", 55);
*/
    return app.exec();
}
/*
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("Skybox", "Main");

    if (engine.rootObjects().isEmpty()) {
        qWarning() << "No root objects found!";
        return -1;
    }

    QQuickWindow *window = qobject_cast<QQuickWindow *>(engine.rootObjects().first());
    if (!window) {
        qWarning() << "Root is not a QQuickWindow!";
        return -1;
    }

    QQmlComponent component(&engine, QUrl::fromLocalFile("Skybox/Planet.qml"));
    if (component.status() != QQmlComponent::Ready) {
        qWarning() << "Error loading Planet.qml:" << component.errors();
        return -1;
    }

    QObject *obj = component.create();
    QQuickItem *item = qobject_cast<QQuickItem *>(obj);

    if (item) {


        item->setParentItem(window->contentItem());
        item->setWidth(100);
        item->setHeight(100);
        item->setX(100);
        item->setY(100);
    } else {
        qWarning() << "Could not cast Planet.qml object to QQuickItem";
    }

    return app.exec();
}*/
