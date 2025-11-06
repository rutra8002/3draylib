#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <string>

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void Init() {}
    virtual void Update(float /*deltaTime*/) {}
    virtual void Draw() = 0;
    virtual std::string GetName() const { return "GameObject"; }
};

#endif

