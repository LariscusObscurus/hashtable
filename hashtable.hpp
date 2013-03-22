#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashFile;

class hashtable {
	friend class HashFile;
	
	struct node {
		std::vector <share_t> value;
		bool set;
		node();
	}
	
	const unsigned size;
	std::vector<node> hsh_vector; /*1201 Primzahl*/
public:
	hashtable (void);
	~hashtable ();

	bool add(std::vector<share_t> hsh_val);
	bool del(std::vector<share_t> hsh_val);
	unsigned find(std::string hsh_val);

private:
	unsigned collision(unsigned old_pos, unsigned &counter);
	unsigned square(unsigned num);
	void check_other(unsigned key, unsigned index, unsigned iterator);
};
#endif
