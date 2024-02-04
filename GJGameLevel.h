#ifndef __GJGAMELEVEL__
#define __GJGAMELEVEL__

// Thank you macro gods 🙏
#define SYNTHESIZE(__NAME__, __TYPE__) private: __TYPE__ __NAME__; public: __TYPE__ get##__NAME__() { return this->##__NAME__; } void set##__NAME__(__TYPE__ __NAME__) { this->##__NAME__ = __NAME__; }


class Level
{
	SYNTHESIZE(objectId, unsigned int);
	SYNTHESIZE(position_x, int);
	SYNTHESIZE(position_y, int);
	SYNTHESIZE(rotation, int);
	SYNTHESIZE(flip_x, bool);
	SYNTHESIZE(flip_y, bool);

	const int LEVEL_LENGTH_LIMIT = 1000 * 30;
};

#endif