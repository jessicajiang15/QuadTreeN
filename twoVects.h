#ifndef _TWOVECTS_H
#define _TWOVECTS_H 1
#include <vector>
#include "RectangleN.h"
//twovects

/**
 * A class that stores two vectors of type RectangleN. Specifically created to be able to return outboxes
 * and inboxes in one function so that the for loop+tree traversal does not need
 * to run twice for each of inboxes and outboxes.
 **/
class twoVects{

    public:
    /**
     * Constructor.
     **/
     twoVects(std::vector<RectangleN*> v1, std::vector<RectangleN*> v2);
    /**
     * The first vector. Stores the outboxes
     **/
    //outboxes. All the boxes where sand needs to be moved OUT.
    std::vector<RectangleN*> v1;
    /**
     * The second vector. Stores the inboxes
     **/
    //inboxes. All the boxes where sand needs to be moved IN.
    std::vector<RectangleN*> v2;

    //std::vector<double> v3;
    /**
     * Append to the first vector.
     **/
    void appendToV1(std::vector<RectangleN*> t);
    /**
     * Append to the second vector.
     **/
    void appendToV2(std::vector<RectangleN*> t);
    /**
     * Setter
     **/
    void setV1(std::vector<RectangleN*> t);
    /**
     * Setter
     **/
    void setV2(std::vector<RectangleN*> t);
    /**
     * Append one twoVects object to another. Appends v1 from other to this->v1, and appends
     * v2 from other to this->v2.
     **/
    void append(twoVects* other);



};

#endif