#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"

class GameObject {
public:
    GameObject();
    virtual ~GameObject();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    [[nodiscard]] Vector3 GetPosition() const;
    void SetPosition(const Vector3& pos);

protected:
    Vector3 position;
    bool active;
};

#endif
