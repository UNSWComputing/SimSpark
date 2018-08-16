#include "fieldfeature.h"

using namespace boost;
using namespace oxygen;
using namespace std;

FUNCTION(FieldFeature,setPosition)
{
  salt::Vector3f& value = obj->Position();

    if (
        (in.GetSize() != 3) ||
        (! in.GetValue(in[0], value[0])) ||
        (! in.GetValue(in[1], value[1])) ||
        (! in.GetValue(in[2], value[2]))
        )
        {
            return false;
        }
    return true;
}

FUNCTION(FieldFeature,setOrientation)
{
  float& value = obj->Orientation();

    if (
        (in.GetSize() != 1) ||
        (! in.GetValue(in[0], value))
        )
        {
            return false;
        }
    return true;
}

FUNCTION(FieldFeature,setType)
{
  std::string& value = obj->Type();

    if (
        (in.GetSize() != 1) ||
        (! in.GetValue(in.begin(), value))
        )
        {
            return false;
        }
    return true;
}

void
CLASS(FieldFeature)::DefineClass()
{
    DEFINE_BASECLASS(SoccerNode);
    DEFINE_FUNCTION(setPosition);
    DEFINE_FUNCTION(setOrientation);
    DEFINE_FUNCTION(setType);
}
