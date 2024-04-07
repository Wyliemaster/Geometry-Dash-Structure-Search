#ifndef __GJGAMELEVEL__
#define __GJGAMELEVEL__

#define SYNTHESIZE(__NAME__, __TYPE__) \
private: \
    __TYPE__ __NAME__; \
public: \
    __TYPE__ get##__NAME__() const { return this->__NAME__; } \
    void set##__NAME__(__TYPE__ __NAME__) { this->__NAME__ = __NAME__; } 

class Object {
public:
    Object() = default;
    ~Object() = default;

    void operator=(const Object& other) {
        this->objectId = other.objectId;
        this->position_x = other.position_x;
        this->position_y = other.position_y;
        this->rotation = other.rotation;
        this->flip_x = other.flip_x;
        this->flip_y = other.flip_y;
    }

    SYNTHESIZE(objectId, unsigned int);
    SYNTHESIZE(position_x, int);
    SYNTHESIZE(position_y, int);
    SYNTHESIZE(rotation, int);
    SYNTHESIZE(flip_x, bool);
    SYNTHESIZE(flip_y, bool);

};

#endif
