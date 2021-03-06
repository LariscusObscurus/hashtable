#ifndef HASHTABLE_H
#define HASHTABLE_H 

#include <vector> 
#include <iostream>
#include "share.hpp" 
#include "hash.hpp" 

#define BOUNDARY		100 

typedef enum { 
	NAME,
	CONT
}omode_t;

class HashFile;

class hashtable {
	friend class HashFile;
	friend class file_handling;
	
	struct node {
		std::vector <share_t> value;
		bool set;
		node();
	};
	
	const unsigned size;
	std::vector<node> hsh_vector; /*1621 Primzahl*/
	std::vector<size_t> hsh_name; 
public:
	hashtable (void);
	~hashtable ();

	bool add(std::vector<share_t> hsh_val);
	bool del(const std::string& in, omode_t mode);
	bool find(const std::string& in, std::vector<share_t> &answer, omode_t mode);

private:
	bool n_add(const std::string& name, unsigned value);
	bool n_del(const std::string& name, unsigned value);
	void n_check_other(unsigned pos, unsigned counter, unsigned iterator);

	unsigned collision(unsigned old_pos, unsigned &counter);
	unsigned square(unsigned num);
	void check_other(unsigned pos, unsigned counter, unsigned iterator);
};
#endif
