#ifndef FIELDFEATURE_H
#define FIELDFEATURE_H

#include "../soccernode/soccernode.h"

class FieldFeature : public SoccerNode
{
public:
    FieldFeature();
    virtual ~FieldFeature();

    salt::Vector3f& Position() { return mPosition; }
    float& Orientation() { return mOrientation; }
    std::string& Type() { return mType; }
    const salt::Vector3f& Position() const { return mPosition; }
    const float& Orientation() const { return mOrientation; }
    const std::string& Type() const { return mType; }

    void setType(std::string type) { mType = type; }

protected:

  salt::Vector3f mPosition;
  float mOrientation;
  std::string mType;
};

DECLARE_CLASS(FieldFeature);

#endif // FIELDFEATURE_H
