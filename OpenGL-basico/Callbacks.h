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

        if (colObj0Wrap->getCollisionShape()->getName() == "STATICPLANE" || colObj1Wrap->getCollisionShape()->getName() == "STATICPLANE") {
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
            transform.setOrigin(btVector3(transform.getOrigin().getX(), staticObjectPosition.getY() - 200, transform.getOrigin().getZ()));
            objectWithGravity->setWorldTransform(transform);

            // You can access more information about the contact, such as contact points, normals, etc., using the 'cp' parameter

            // Return 0 to continue processing other contacts
        }
        else {
            btRigidBody* box1 = nullptr;
            btRigidBody* box2 = nullptr;

            // Identify the two boxes
            if (colObj0Wrap->getCollisionShape()->getName() == "Box") {
                box1 = static_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj0Wrap->getCollisionObject()));
                box2 = static_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject()));
            }




            // Get the current transforms
            btTransform transform1 = box1->getWorldTransform();
            btTransform transform2 = box2->getWorldTransform();

            // Check for overlap along the X-axis
            btVector3 position1 = transform1.getOrigin();
            btVector3 position2 = transform2.getOrigin();
            btScalar overlapX = - static_cast<float>((box1->getCollisionShape()->getLocalScaling().getX() + box2->getCollisionShape()->getLocalScaling().getX()) / 2.0 - std::abs(position1.getX() - position2.getX()));

            // Check for overlap along the Z-axis
            btScalar overlapZ = - static_cast<float>((box1->getCollisionShape()->getLocalScaling().getZ() + box2->getCollisionShape()->getLocalScaling().getZ()) / 2.0 - std::abs(position1.getZ() - position2.getZ()));

            std::cout << "Overlap X: " << overlapX << std::endl;
            std::cout << "Overlap Z: " << overlapZ << std::endl;
            // Resolve collision along the X-axis
            if (overlapX > 0.0f) {
                btScalar displacement = overlapX / 2.0f;

                if (position1.getX() < position2.getX()) {
                    position1.setX(position1.getX() - displacement);
                    position2.setX(position2.getX() + displacement);
                }
                else {
                    position1.setX(position1.getX() + displacement);
                    position2.setX(position2.getX() - displacement);
                }
            }

            // Resolve collision along the Z-axis
            if (overlapZ > 0.0f) {
                btScalar displacement = overlapZ / 2.0f;

                if (position1.getZ() < position2.getZ()) {
                    position1.setZ(position1.getZ() - displacement);
                    position2.setZ(position2.getZ() + displacement);
                }
                else {
                    position1.setZ(position1.getZ() + displacement);
                    position2.setZ(position2.getZ() - displacement);
                }
            }

            // Update the transforms
            if (box1->getMass() > 0.0f) {
                transform1.setOrigin(position1);
            }
            if (box2->getMass() > 0.0f) {
                transform2.setOrigin(position2);
            }

            box1->setWorldTransform(transform1);
            box2->setWorldTransform(transform2);
        }
        return 0;
    }

    /*
    btScalar addSingleResult(btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0Wrap,
        int partId0,
        int index0,
        const btCollisionObjectWrapper* colObj1Wrap,
        int partId1,
        int index1) override {

        btRigidBody* box1 = nullptr;
        btRigidBody* box2 = nullptr;

        // Identify the two boxes
        if (colObj0Wrap->getCollisionShape()->getName() == "Box") {
            box1 = static_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj0Wrap->getCollisionObject()));
            box2 = static_cast<btRigidBody*>(const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject()));
        }
  


        // Get the current transforms
        btTransform transform1 = box1->getWorldTransform();
        btTransform transform2 = box2->getWorldTransform();

        // Check for overlap along the X-axis
        btVector3 position1 = transform1.getOrigin();
        btVector3 position2 = transform2.getOrigin();
        btScalar overlapX = static_cast<float>((box1->getCollisionShape()->getLocalScaling().getX() + box2->getCollisionShape()->getLocalScaling().getX()) / 2.0 - std::abs(position1.getX() - position2.getX()));

        // Check for overlap along the Z-axis
        btScalar overlapZ = static_cast<float>((box1->getCollisionShape()->getLocalScaling().getZ() + box2->getCollisionShape()->getLocalScaling().getZ()) / 2.0 - std::abs(position1.getZ() - position2.getZ()));

        // Resolve collision along the X-axis
        if (overlapX > 0.0f) {
            btScalar displacement = overlapX / 2.0f;

            if (position1.getX() < position2.getX()) {
                position1.setX(position1.getX() - displacement);
                //position2.setX(position2.getX() + displacement);
            }
            else {
                position1.setX(position1.getX() + displacement);
                //position2.setX(position2.getX() - displacement);
            }
        }

        // Resolve collision along the Z-axis
        if (overlapZ > 0.0f) {
            btScalar displacement = overlapZ / 2.0f;

            if (position1.getZ() < position2.getZ()) {
                position1.setZ(position1.getZ() - displacement);
                //position2.setZ(position2.getZ() + displacement);
            }
            else {
                position1.setZ(position1.getZ() + displacement);
                //position2.setZ(position2.getZ() - displacement);
            }
        }

        // Update the transforms
        transform1.setOrigin(position1);
        transform2.setOrigin(position2);

        box1->setWorldTransform(transform1);
        box2->setWorldTransform(transform2);

        // Return 0 to continue processing other contacts
        return 0;
    }

    */
};