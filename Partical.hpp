#ifndef PARTICAL_HPP
#define PARTICAL_HPP

class Partical {
public: //not best to make public, but makes acsessing the many particals more efficient
    double m_xPos;
    double m_yPos;

public:
    Partical();
    virtual ~Partical();

};

#endif