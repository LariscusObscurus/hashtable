#include "hashtable.hpp"

hashtable::node::node() : value(std::vector<share_t>(0)), set(false) {};

hashtable::hashtable(void) : size(1621),
	hsh_vector(std::vector<node>(size)),
	hsh_name(std::vector<size_t>(size, 0)) {}

hashtable::~hashtable() {}

/*Einen Eintrag in dem hashtable einfügen.*/
bool hashtable::add(std::vector<share_t> hsh_val)
{
	bool result = false;
	unsigned check = hashString(hsh_val[0].name) % size;
	unsigned pos = hashString(hsh_val[0].cont) % size;
	unsigned counter = 1;

	if ((hsh_vector[hsh_name[check]].value.size() > 0) 
	&& (hsh_vector[hsh_name[check]].value[0].cont != hsh_val[0].cont)) {
			return result;
	}

	for (unsigned i = BOUNDARY; i > 0; i--) {
	 	if (hsh_vector[pos].set) {
			if ((hsh_vector[pos].value[0].name == hsh_val[0].name) 
			&& (hsh_vector[pos].value[0].cont == hsh_val[0].cont)) {

				
				hsh_vector[pos].value.insert(
					hsh_vector[pos].value.begin(), 
					hsh_val.begin(), 
					hsh_val.end());
				result = true;
			} else if (
			(hsh_vector[pos].value[0].name != hsh_val[0].name) 
			&& (hsh_vector[pos].value[0].cont == hsh_val[0].cont)) {
				return result;
			} else {
		 		pos = collision(pos, counter);
			//	std::cout << "coll is: " << pos << std::endl;
			}
		} else {
			if(!(n_add(hsh_val[0].name, pos))) {
				return result;
			}
			result = true;
			hsh_vector[pos].set = true;
			hsh_vector[pos].value = hsh_val;
			break;
		}
	}
	return result;
	
}

/*Einen Eintrag aus dem hashtable entfernen.*/
bool hashtable::del(const std::string& in, omode_t mode)
{
	bool result = false;
	unsigned pos;
	unsigned temp;
	unsigned counter = 1;

	switch(mode) {
	case NAME:
		temp = hashString(in) % size;
		pos = (unsigned)hsh_name[temp];
		break;
	case CONT:
		pos = hashString(in) % size;
		break;
	}

	for (unsigned i = BOUNDARY; i > 0; i--) {
		if (hsh_vector[pos].set && 
		((hashString(hsh_vector[pos].value[0].cont) % size) == pos)) {
			
			result = true;
			if(!(n_del(hsh_vector[pos].value[0].name, pos))) {
				result = false;
			}
			hsh_vector[pos].set = false;
			check_other(pos, counter + 1, i + 1);
			break;
		} else {
			pos = collision(pos, counter);
		}
	}
	return result;
}

bool hashtable::find(const std::string& in, 
			std::vector<share_t> &answer, 
			omode_t mode)
{
	bool result = false;
	unsigned pos = 0;
	unsigned temp = 0;
	unsigned counter = 1;

	switch(mode) {
	case CONT:
		pos = hashString(in) % size;
		break;
	case NAME:
		temp = hashString(in) % size;
		pos = (unsigned)hsh_name[temp];
		break;
	}

	for (unsigned i = BOUNDARY; i > 0; i--) {
		if (hsh_vector[pos].set) {
			
			if ((hsh_vector[pos].value[0].cont == in) 
			|| (hsh_vector[pos].value[0].name == in)) {
				
			answer = hsh_vector[pos].value;
			result = true;
			break;
			} else {
				pos = collision(pos, counter);
			//	std::cout << "coll is: " << pos << std::endl;
			}
		} else {
			pos = collision(pos, counter);
		}
	}
	return result;
}

unsigned hashtable::collision(unsigned old_pos, unsigned &counter)
{
	unsigned new_pos;

	new_pos = ((old_pos + square(counter++)) % size);
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

	for (unsigned i = iterator; i > 0; i--) {
		if (hsh_vector[n_pos].set && 
		(hashString(hsh_vector[n_pos].value[0].cont) % size) == pos) {

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
	unsigned pos = hashString(name) % size;
	unsigned counter = 1;
	for (unsigned i = BOUNDARY; i > 0; i--) {
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
	unsigned pos = hashString(name) % size;
	unsigned counter = 1;
	for (unsigned i = BOUNDARY; i > 0; i--) {
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

	for (unsigned i = iterator; i > 0; i--) {
		if (hsh_name[n_pos] != 0) {
			hsh_name[l_pos] = hsh_name[n_pos];
			hsh_name[n_pos] = 0;
			l_pos = n_pos;
		}
		n_pos = collision(pos, counter);
	}
}
