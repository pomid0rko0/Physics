#include "Camera.h"



Camera::Camera(Qt3DCore::QNode *parent) :
    QAbstractCameraController(parent)
{
}


Camera::~Camera()
{
}

void Camera::moveCamera(const InputState & state, float dt)
{
    if (camera() == nullptr) {
        return;
    }
    float d = (camera()->position() - camera()->viewCenter()).length();
    if ((2 <= d && state.tzAxisValue > 0) || (d <= 6 && state.tzAxisValue < 0)) {
        camera()->translate(QVector3D(0, 0, state.tzAxisValue * linearSpeed() * dt), camera()->DontTranslateViewCenter);
    }
    float a = camera()->transform()->rotationX();
    if ((-70 <= a && state.ryAxisValue > 0) || (a <= 70 && state.ryAxisValue < 0)) {
        camera()->tiltAboutViewCenter((state.ryAxisValue * lookSpeed()) * dt);
    }
    camera()->panAboutViewCenter((state.rxAxisValue * lookSpeed()) * dt, QVector3D(0, 1, 0));
}
