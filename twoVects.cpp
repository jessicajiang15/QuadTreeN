#include "twoVects.h"
//twovects

twoVects::twoVects(std::vector<RectangleN *> v1, std::vector<RectangleN*> v2)
{
    this->v1 = v1;
    this->v2 = v2;
}

void twoVects::appendToV1(std::vector<RectangleN*> t)
{
    v1.insert(v1.end(), t.begin(), t.end());
}
void twoVects::appendToV2(std::vector<RectangleN *> t)
{
    v2.insert(v2.end(), t.begin(), t.end());
}

void twoVects::setV1(std::vector<RectangleN *> t)
{
    this->v1 = t;
}
void twoVects::setV2(std::vector<RectangleN *> t)
{
    this->v2 = t;
}

void twoVects::append(twoVects* other)
{
    appendToV1(other->v1);
    appendToV2(other->v2);
}