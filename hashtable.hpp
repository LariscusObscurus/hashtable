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
	//std::vector<node&> hsh_vector; /* reference to node "check & operator"*/
public:
	hashtable (void);
	~hashtable ();

	bool add(std::vector<share_t> hsh_val);
	bool del(std::string hsh_cont);
	unsigned find(std::string hsh_cont);

private:
	unsigned collision(unsigned old_pos, unsigned &counter);
	unsigned square(unsigned num);
	void check_other(unsigned pos, unsigned counter, unsigned iterator);
};
#endif
