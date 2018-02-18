#ifndef PARTICAL_HPP
#define PARTICAL_HPP

#include <cstdlib>

class Partical {
public: //not best to make public, but makes acsessing the many particals more efficient
    double m_xPos;
    double m_yPos;

    //the speed an individucal  partical will move
    double m_xspeed;
    double m_yspeed;

public:
    Partical();
    virtual ~Partical();
    void update();

};

#endif