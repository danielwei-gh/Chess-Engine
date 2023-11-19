#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Square;

class Observer {
public:
    virtual void update(Square &square) = 0;
    virtual ~Observer() = default;
};

#endif
