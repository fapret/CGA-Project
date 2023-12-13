#include "TransformComponent.h"

glm::vec3 TransformComponent::getPosition()
{
    return glm::vec3(posX, posY, posZ);
}

void TransformComponent::setPosition(glm::vec3 pos)
{
    this->posX = pos.x;
    this->posY = pos.y;
    this->posZ = pos.z;

    btVector3 boxPos = btVector3(pos.x, pos.y, pos.z);
    btTransform transformBt;
    transformBt.setOrigin(boxPos);
    cameraRigidBody->setWorldTransform(transformBt);
    cameraRigidBody->getMotionState()->setWorldTransform(transformBt);

}

glm::vec3 TransformComponent::getScale()
{
    return glm::vec3(scaleX, scaleY, scaleZ);
}

void TransformComponent::setScale(glm::vec3 scale)
{
    this->scaleX = scale.x;
    this->scaleY = scale.y;
    this->scaleZ = scale.z;
}

glm::vec3 TransformComponent::getRotation()
{
    return glm::vec3(rotationX, rotationY, rotationZ);
}

void TransformComponent::setRotation(glm::vec3 rot)
{
    this->rotationX = rot.x;
    this->rotationY = rot.y;
    this->rotationZ = rot.z;
}

TransformComponent::TransformComponent() : EntityComponent("TransformComponent")
{
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
    this->scaleX = 1.0f;
    this->scaleY = 1.0f;
    this->scaleZ = 1.0f;
}

void TransformComponent::setUpCollission()
{
    btVector3 boxSize(1, 1, 1);
    btBoxShape* boxShape = new btBoxShape(boxSize);
    btScalar newMargin = 10.1;
    boxShape->setMargin(newMargin);
    btScalar collisionMargin = boxShape->getMargin();

    // Set the mass of the box
    btScalar boxMass = 10.0; // Adjust the mass as needed

    // Set the initial position and orientation of the box
    btTransform boxTransform;
    boxTransform.setIdentity(); // No initial rotation
    glm::vec3 transformPos = this->getPosition();
    //boxTransform.setOrigin(btVector3(transformPos.x, transformPos.y, transformPos.z)); // Initial position
    boxTransform.setOrigin(btVector3(transformPos.x, transformPos.y, transformPos.z)); // Initial position


    // Create the motion state
    btDefaultMotionState* boxMotionState = new btDefaultMotionState(boxTransform);

    // Create the rigid body construction info
    btVector3 boxInertia(0, 0, 0);
    boxShape->calculateLocalInertia(boxMass, boxInertia);

    this->cameraRigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(boxMass, boxMotionState, boxShape, boxInertia));;

    Hierarchy& hierarchy = Hierarchy::getInstance();
    btDiscreteDynamicsWorld* dynamicsWorld = hierarchy.getDynamicsWorld();
    dynamicsWorld->addRigidBody(this->cameraRigidBody);
}

void TransformComponent::updateRigidBody()
{
   
    // Add the camera rigid body to the dynamics world

    // Update the position of the camera rigid body based on the CameraComponent's position
    btVector3 boxPos = this->getRigidBody()->getWorldTransform().getOrigin();

    btVector3 initPos = cameraRigidBody->getWorldTransform().getOrigin();
    this->setPosition(glm::vec3(boxPos.getX(), boxPos.getY(), boxPos.getZ()));
}

void TransformComponent::draw(float deltaTime)
{
}

btRigidBody* TransformComponent::getRigidBody()
{
    return cameraRigidBody;
}

#ifdef USE_IMGUI
void TransformComponent::EditorPropertyDraw()
{
    EntityComponent::EditorPropertyDraw();
    ImGui::Text("Position");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##X", &posX, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##Y", &posY, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##Z", &posZ, 0.01f, 0.1f, "%.3f");

    ImGui::Separator();
    ImGui::Text("Rotation");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##RX", &rotationX, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##RY", &rotationY, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##RZ", &rotationZ, 0.01f, 0.1f, "%.3f");

    ImGui::Separator();
    ImGui::Text("Scale");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##SX", &scaleX, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##SY", &scaleY, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##SZ", &scaleZ, 0.01f, 0.1f, "%.3f");
}
#endif