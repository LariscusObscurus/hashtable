#include "hashtable.hpp"

hashtable::node::node() : set(false) {};

hashtable::hashtable(void) : size(1621),
	hsh_vector(std::vector<node>(size)),
	hsh_name(std::vector<size_t>(0, size)) {}

/*Einen Eintrag in dem hashStringtable einfügen.*/
bool hashtable::add(std::vector<share_t> hsh_val)
{
	bool result = false;
	unsigned pos = hashString(hsh_val[0].cont);
	unsigned counter = 1;

	for (unsigned i = size; i > 0; i--) {
	 	if (hsh_vector[pos].set) {
	 		pos = collision(pos, counter);
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

/*Einen Eintrag aus dem hashStringtable entfernen.*/
bool hashtable::del(const std::string& in, omode_t mode)
{
	bool result = false;
	unsigned pos;
	unsigned temp;
	unsigned counter = 1;

	switch(mode) {
	case NAME:
		temp = hashString(in);
		pos = (unsigned)hsh_name[temp];
		break;
	case CONT:
		pos = hashString(in);
		break;
	}

	for (unsigned i = size; i > 0; i--) {
		if (hsh_vector[pos].set && 
		(hashString(hsh_vector[pos].value[0].cont) == pos)) {
			
			result = true;
			n_del(hsh_vector[pos].value[0].name, pos);
			hsh_vector[pos].set = false;
			check_other(pos, counter + 1, i + 1);
			break;
		} else {
			pos = collision(pos, counter);
		}
	}
	return result;
}

int hashtable::find(const std::string& in, std::vector<share_t> &result, omode_t mode)
{
	unsigned pos = 0;
	unsigned temp = 0;
	unsigned counter = 1;

	switch(mode) {
	case CONT:
		pos = hashString(in);
		break;
	case NAME:
		temp = hashString(in);
		pos = (unsigned)hsh_name[temp];
		break;
	}

	for (unsigned i = size; i > 0; i--) {
		if (hsh_vector[pos].set &&
		hashString(hsh_vector[pos].value[0].cont) == pos) {
			
			result = hsh_vector[pos].value;
			break;
		} else {
			pos = collision(pos, counter);
		}
	}
	return 0;
}

unsigned hashtable::collision(unsigned old_pos, unsigned &counter)
{
	unsigned new_pos;

	new_pos = (old_pos + square(counter++) % size);
	return new_pos;
}

unsigned hashtable::square(unsigned num)
{
	return (num * num);
}

void hashtable::check_other(unsigned pos, unsigned counter, unsigned iterator)
{
	unsigned l_pos = pos;
	unsigned n_pos = collision(pos, counter);

	for (unsigned i = iterator; i > size; i--) {
		if (hsh_vector[n_pos].set && 
		hashString(hsh_vector[n_pos].value[0].cont) == pos) {

			hsh_vector[l_pos].value = hsh_vector[n_pos].value;
			hsh_vector[l_pos].set = true;
			hsh_vector[n_pos].set = false;
			l_pos = n_pos;
		}
		n_pos = collision(pos, counter);
	}
}

bool hashtable::n_add(const std::string& name, unsigned value)
{
	bool result = false;
	unsigned pos = hashString(name);
	unsigned counter = 1;
	for (unsigned i = size; i > 0; i--) {
		if(hsh_name[pos] == 0) {
			result = true;
			hsh_name[pos] = value;
			break;

		} else {
			pos = collision(pos, counter);
		}
	}
	return result;
}

bool hashtable::n_del(const std::string& name, unsigned value)
{
	bool result = false;
	unsigned pos = hashString(name);
	unsigned counter = 1;
	for (unsigned i = size; i > size; i--) {
		if (hsh_name[pos] == value) {
			result = true;
			hsh_name[pos] = 0;
			n_check_other(pos, counter + 1, i + 1);
			break;

		} else {
			pos = collision(pos, counter);
		}
	}
	return result;
}

void hashtable::n_check_other(unsigned pos, unsigned counter, unsigned iterator)
{
	unsigned l_pos = pos;
	unsigned n_pos = collision(pos, counter);

	for (unsigned i = iterator; i > size; i--) {
		if (hsh_name[n_pos] != 0) {
			hsh_name[l_pos] = hsh_name[n_pos];
			hsh_name[n_pos] = 0;
			l_pos = n_pos;
		}
		n_pos = collision(pos, counter);
	}
}
