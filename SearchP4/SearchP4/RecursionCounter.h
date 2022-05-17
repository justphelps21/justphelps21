#ifndef __RECURSIONCOUNTER__
#define __RECURSIONCOUNTER__

class RecursionCounter
{
public:
	RecursionCounter() {
		++currentDepth;
		if (currentDepth > maxDepth)
			maxDepth = currentDepth;
	}
	~RecursionCounter() { --currentDepth; }
	static int currentDepth;
	static int maxDepth;
};

#endif