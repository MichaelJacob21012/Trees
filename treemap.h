#ifndef TREEMAP_H
#define TREEMAP_H

#include "tree.h"

template<typename Key, typename Value>
class KeyValuePair {

public:

    const Key k;
    Value v;

    // TODO your code for KeyValuePair goes here
    KeyValuePair(Key key, Value value)
    :k(key),v(value){
    }
    KeyValuePair(Key key)
        :k(key){
    }
    bool operator<(const KeyValuePair & other) const {
    	return (k < other.k);
    }


};



template<typename Key, typename Value>
ostream & operator<< (ostream & o, const KeyValuePair<Key,Value> & kv){
    o << kv.k << "," << kv.v;
    return o;
}



template<typename Key, typename Value>
class TreeMap {

private:
    BinarySearchTree<KeyValuePair<Key,Value> > tree;

public:

    KeyValuePair<Key,Value> * insert(const Key & k, const Value & v) {
        return &(tree.insert(KeyValuePair<Key,Value>(k,v))->data);
    }

    void write(ostream & o) const {
        tree.write(o);
    }

    // TODO your code for TreeMap goes here:

    KeyValuePair<Key,Value> * find(const Key & k)  const{
    	KeyValuePair<Key,Value> pair = KeyValuePair<Key,Value>(k);
    	TreeNode<KeyValuePair<Key,Value>>* node = tree.find(pair);
    	if (node){
    		return &(node->data);
    	}
    	return nullptr;
    }



};


// do not edit below this line

#endif
