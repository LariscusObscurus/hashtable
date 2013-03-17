#include "hashtable.hpp"

hashtable::node::node() : set(false) {};

hashtable::hashtable(void) : size(1201), hsh_vector(std::vector<node>(size)) {}

bool hashtable::add(std::vector<share_t> hsh_val)
{
	bool result = false;
	unsigned pos = Hash(hsh_val[0].cont);
	unsigned counter = 1;
	for( unsigned i = size; i > 0; i--)
	{
	 	if (hsh_vector[pos].set) {
	 		pos = collision(pos, &counter);
		} else {
			result = true;
			hsh_vector[pos].value = hsh_val;
			hsh_vector[pos].set = true;
			break;
		}
	}
	return result;
	
}
bool hashtable::del(std::vector<share_t> hsh_val)
{

}
unsigned hashtable::find(std::string hsh_val)
{

}

hashtable::collision(unsigned old_pos, unsigned &counter)
{
	unsigned new_pos;
	new_pos = (old_pos + square((*counter)++) % size;
	return new_pos
}

hashtable::square(unsigned num)
{
	return (num * num);
}
