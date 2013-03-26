#ifndef PLOTTER_HPP
#define PLOTTER_HPP
#include <vector>
#include <cstring>
#include "share.hpp"

class IPlotter
{
public:
	virtual void plot (const std::vector<share_t>& shares) = 0;
};

class Plotter : public virtual IPlotter
{
public:
	Plotter (void) {}
	virtual ~Plotter (void) {}
	virtual void plot (const std::vector<share_t>& shares);
private:
	void draw (const std::string& name, const float* values, const char* drawArea, const int width, const int height);
};

#endif
