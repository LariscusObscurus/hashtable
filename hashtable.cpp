#include "hashtable.hpp"

hashtable::node::node() : set(false) {};

hashtable::hashtable(void) : size(1621),
	hsh_vector(std::vector<node>(size)),
	hsh_name(std::vector<size_t>(0, size)) {}

/*Einen Eintrag in dem Hashtable einfügen.*/
bool hashtable::add(std::vector<share_t> hsh_val)
{
	bool result = false;
	unsigned pos = Hash(hsh_val[0].cont);
	unsigned counter = 1;

	for (unsigned i = size; i > 0; i--) {
	 	if (hsh_vector[pos].set) {
	 		pos = collision(pos, &counter);
		} else {
			result = true;
			hsh_vector[pos].value = hsh_val;
			hsh_vector[pos].set = true;
			n_add(hsh_val[0].name, pos);
			break;
		}
	}
	return result;
	
}

/*Einen Eintrag aus dem Hashtable entfernen.*/
bool hashtable::del(std::string hsh_cont)
{
	bool result = false;
	unsigned pos = Hash(hsh_cont);
	unsigned counter = 1;

	for (unsigned i = size; i > 0; i--) {
		if (hsh_vector[pos].set && 
		(Hash(hsh_vector[pos].value.cont) == pos)) {
			
			result = true;
			hsh_vector[pos].set = false;
			check_other(pos, counter + 1, i + 1);
			break;
		} else {
			pos = collision(pos, &counter);
		}
	}
	return result;
}

void hashtable::find_by_name(std::string name)
{
	unsigned pos_name = Hash(name);
	unsigned pos = hsh_name[pos_name];
	find(pos);
}

void hashtable::find_by_cont(std::string cont)
{
	find(Hash(cont));
}

std::vector<share_t> hashtable::find(unsigned pos)
{
	std::vector<share_t> result = NULL;
	unsigned counter = 1;

	for (unsigned i = size; i > 0; i--) {
		if (hsh_vector[pos].set &&
		Hash(hsh_vector[pos].value.cont) == pos) {
			
			result = hsh_vector[pos].value;
			break;
		} else {
			pos = collision(pos, &counter);
		}
	}
	return result;
}

unsigned hashtable::collision(unsigned old_pos, unsigned *counter)
{
	unsigned new_pos;

	new_pos = (old_pos + square((*counter)++) % size);
	return new_pos;
}

unsigned hashtable::square(unsigned num)
{
	return (num * num);
}

void hashtable::check_other(unsigned pos, unsigned counter, unsigned iterator)
{
	unsigned l_pos = pos;
	unsigned n_pos = collision(pos, &counter);

	for (unsigned i = iterator; i > size, i--) {
		if (hsh_vector[n_pos].set && 
		Hash(hsh_vector[n_pos].value.cont) == pos) {

			hsh_vector[l_pos].value = hsh_vector[n_pos].value;
			hsh_vector[l_pos].set = true;
			hsh_vector[n_pos].set = false;
			l_pos = n_pos;
		}
		n_pos = collision(pos, &counter);
	}
}

bool hashtable::n_add(std::string name, unsigned value)
{
	bool result = false;
	unsigned pos = Hash(name);
	counter = 1;
	for (unsigned i = size; i > 0; i--) {
		if(hsh_name[pos] == 0) {
			result = true;
			hsh_name[pos] = value;
			break;

		} else {
			pos = collision(pos, &counter);
		}
	}
	return result;
}
