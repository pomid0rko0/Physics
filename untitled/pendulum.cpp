#include "pendulum.h"
#include <algorithm>

physics::pendulum::pendulum(const float _m, bullet *_B, Qt3DCore::QNode *parent) :
    MaterialPoint(_m, parent), B(_B)
{
}

void physics::pendulum::move(const float t)
{
    if (B->transform()->translation().x() < 100) {
        setMesh(":/res/pendulum_bullet.obj");
        setTexture(":/res/pendulum_bullet.png");
        B->move(1e10f);
    }
    rotate(180.f * asinf(pos(t).x() / l) / PI);
}

QVector3D physics::pendulum::pos(const float t)
{
    A = B->v(0).x() * B->m() / (B->m() + m()) / omega;
    float x = A * sinf(omega * t);
    //return { x, Ep(t) / (B->m() + m()) / g, 0 };
    return { x, sqrtf(l * l - x * x), 0 };
}

QVector3D physics::pendulum::v(const float t)
{
    A = B->v(0).x() * B->m() / (B->m() + m()) / omega;
    float s = sinf(omega * t);
    float c = cosf(omega * t);
    return {
             A * omega * c,
             A * A * omega * s * c / sqrtf(l * l - A * A * s * s),
             0
           };
}

float physics::pendulum::Ek(const float t)
{
    float v_len = v(t).length();
    return (m() + B->m()) * v_len * v_len / 2.f;
}

float physics::pendulum::Ep(const float t)
{
    return Ek(0) - Ek(t);
}
