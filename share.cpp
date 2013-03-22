#include "share.hpp"

Share::Share (void) : name(""), cont(""), open(.0f), high(.0f), low(.0f), close(.0f), volume(.0f), adjClose(.0f)
{
}

Share::~Share (void)
{
}

Share::Date::Date (void) : day(0), month(0), year(0)
{
}

Share::Date::~Date (void)
{
}