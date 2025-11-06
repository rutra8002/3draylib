#include "gameobject.h"

GameObject::GameObject() : position({0.0f, 0.0f, 0.0f}), active(true) {
}

GameObject::~GameObject() = default;

Vector3 GameObject::GetPosition() const {
    return position;
}

void GameObject::SetPosition(const Vector3& pos) {
    position = pos;
}
