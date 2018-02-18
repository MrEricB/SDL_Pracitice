#ifndef PARTICAL_HPP
#define PARTICAL_HPP

#include <cstdlib>

class Partical {
public: //not best to make public, but makes acsessing the many particals more efficient
    double m_xPos;
    double m_yPos;


private:
    //the speed an individucal  partical will move
    double m_speed;
    double m_direction; // [0-365]


private: 
    void init();

public:
    Partical();
    virtual ~Partical();
    void update(int change);

};

#endif