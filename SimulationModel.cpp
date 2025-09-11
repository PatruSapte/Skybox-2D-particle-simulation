#include "SimulationModel.h"
#include <QDebug>

SimulationModel::SimulationModel(QObject *parent)
    : QObject{parent},
    m_timer(new QTimer(this))
{
    queueNewPlanets.clear();
    activePlanets.clear();
    connect(m_timer, &QTimer::timeout, this, &SimulationModel::tick);
}

void SimulationModel::start(int msecTickInterval) {
    m_timer->start(msecTickInterval);
    deltaTime = (qreal)1 / ((qreal)1000 / (qreal)msecTickInterval);
}
void SimulationModel::pause() { m_timer->stop(); }



void SimulationModel::addNewPlanet(Particle *planet)
{
    queueNewPlanets.append(planet);
}

bool isTicking=false;
void SimulationModel::tick() {
    // logic loop of simulation
    if(isTicking)
        qDebug()<<"tick";
    isTicking = true;

    while(!queueNewPlanets.isEmpty())
    {
        activePlanets.append(queueNewPlanets.first());
        queueNewPlanets.removeFirst();
    }

    for (int id1 = 0; id1 < activePlanets.size() - 1; id1++)
    {
        //Physics loop
        for (int id2 = id1 + 1; id2 < activePlanets.size(); id2++)
        {
            Particle* A = activePlanets[id1];
            Particle* B = activePlanets[id2];

          //  qreal dx = B->position.x - A->position.x;
          //  qreal dy = B->position.y - A->position.y;
          //  qreal ddistance = std::sqrt(dx * dx + dy * dy);

            Point dirAB = B->position - A->position;
            qreal distance = std::sqrt(dirAB.x * dirAB.x + dirAB.y * dirAB.y);

            if (distance == 0.0f) return; // already at the same point

            qreal G = 9.7;

            // gravity force formula ignoring mass
            qreal F = G / (distance );

            // acc for A
            qreal acc = F * B->mass();
            A->velocity += (dirAB * acc * deltaTime);
            // acc for B
            acc = F * A->mass();
            B->velocity += (dirAB * (-acc) * deltaTime);

                //   acc = (dirAB ) * (F / B->mass());
                //      B->velocity -= acc ;

                    // Normalize direction vector
        //    qreal nx = dx / distance;
           // qreal ny = dy / distance;

            // A->velocity.x += nx*G*0.05;
            // A->velocity.y += ny*G*0.05;
            // B->velocity.x -= nx*G*0.05;
            // B->velocity.y -= ny*G*0.05;
            // Move A and B toward each other
            // Move A and B toward each other
            // A->AddToPositionMemory( nx * G, ny * G);
            // B->AddToPositionMemory( -nx * G, -ny * G);*/
        }
    }
    for (int id = 0; id < activePlanets.size(); id++)
    {
        // activePlanets[id]->addToPosition(activePlanets[id]->velocity);
        activePlanets[id]->ApplyVelocity(deltaTime);
    }

    isTicking = false;
}
