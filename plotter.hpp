#ifndef PLOTTER_HPP
#define PLOTTER_HPP
#include <vector>
#include "share.hpp"

class IPlotter
{
public:
	virtual void plot (const std::vector<Share_t>& shares) = 0;
};

class Plotter : public virtual IPlotter
{
public:
	Plotter (void);
	virtual ~Plotter (void);
	virtual void plot (const std::vector<Share_t>& shares);
private:
	void draw (const std::string& name, const char* drawArea);
};

#endif