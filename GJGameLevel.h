#ifndef __GJGAMELEVEL__
#define __GJGAMELEVEL__

#define SYNTHESIZE(__NAME__, __TYPE__) \
private: \
    __TYPE__ __NAME__; \
public: \
    __TYPE__ get##__NAME__() const { return this->__NAME__; } \
    void set##__NAME__(__TYPE__ __NAME__) { this->__NAME__ = __NAME__; } 

class Level {
public:
    // Constructor
    Level() = default; // Default constructor

    // Copy constructor
    void operator=(const Level& other) {
        this->objectId = other.objectId;
        this->position_x = other.position_x;
        this->position_y = other.position_y;
        this->rotation = other.rotation;
        this->flip_x = other.flip_x;
        this->flip_y = other.flip_y;
    }

    // Macro for getter and setter
    SYNTHESIZE(objectId, unsigned int);
    SYNTHESIZE(position_x, int);
    SYNTHESIZE(position_y, int);
    SYNTHESIZE(rotation, int);
    SYNTHESIZE(flip_x, bool);
    SYNTHESIZE(flip_y, bool);

    // Destructor if needed
    //~Level() = default; // Default destructor

private:
    const int LEVEL_LENGTH_LIMIT = 1000 * 30;
};

#endif
