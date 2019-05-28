#ifndef OBJECT_H
#define OBJECT_H


class Object
{
public:
    Object();
    int x;
    int y;
    enum class Type
    {
        REAL = 1,
        SIMULATED=2
    }type;
};

#endif // OBJECT_H
