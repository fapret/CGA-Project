#pragma once
#include <iostream>
#include <btBulletDynamicsCommon.h>

class MyContactCallback : public btCollisionWorld::ContactResultCallback {
public:
    MyContactCallback() {}

    // This method is called when a contact is detected
    btScalar addSingleResult(btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0Wrap,
        int partId0,
        int index0,
        const btCollisionObjectWrapper* colObj1Wrap,
        int partId1,
        int index1) override {
        // Display some information about the contact
        //std::cout << "Collision detected between objects!" << std::endl;
        btRigidBody* objectWithGravity = nullptr;
        btRigidBody* staticObject = nullptr;

        if (colObj0Wrap->getCollisionShape()->getName() == "Box") {
            objectWithGravity = dynamic_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj0Wrap->getCollisionObject()));
            staticObject = dynamic_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject()));
        }
        if (colObj1Wrap->getCollisionShape()->getName() == "Box") {
            objectWithGravity = dynamic_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject()));
            staticObject = dynamic_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj0Wrap->getCollisionObject()));
        }

        btTransform transform = objectWithGravity->getWorldTransform();
        btVector3 staticObjectPosition = staticObject->getWorldTransform().getOrigin();
        transform.setOrigin(btVector3(transform.getOrigin().getX(), staticObjectPosition.getY(), transform.getOrigin().getZ()));
        objectWithGravity->setWorldTransform(transform);

        // You can access more information about the contact, such as contact points, normals, etc., using the 'cp' parameter

        // Return 0 to continue processing other contacts
        return 0;
    }
};