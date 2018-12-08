#pragma once

#include "../MemoryPool/MemoryPool.h"
#include <unordered_map>
#include <string>
#include "../conf/Conf.h"
#include "../Mutex/MutexLock.h"

using std::string;

template<typename T>
class Node{
private:
	T value;
	Node* pre;
	Node* next;

public:
	void setPre(Node *p){
		pre=p;
	}
	void setNext(Node *n){
		next=n;
	}
	Node* getPre(){
		return pre;
	}
	Node* getNext(){
		return next;
	}
	T& getValue(){
		return value;
	}	

};

struct Key{
	string key,value;
};

typedef Node<Key>* key_node;

class KeyList{
private:
	int freq;
	key_node head;
	key_node last;

public:
	void init(int fq);
	void destory();
	int getFreq();
	void add(key_node &node);
	void del(key_node &node);
	bool isEmpty();
	key_node getLast();
};

typedef Node<KeyList>* freq_node;

class LFUCache{
private:
	freq_node head;
	int capacity;
	MutexLock mutex;	

	std::unordered_map<string,key_node> kmap;//key到keynode的映射
	std::unordered_map<string,freq_node> fmap;//key到freqnode的映射
	
	void addfreq(key_node &nowk,freq_node &nowf);	
	void del(freq_node &node);

public:
	void init();
	~LFUCache();
	bool get(string &key,string &value);//通过key返回value并进行LFU操作
	void set(string &key,string &value);//更新LFU缓存
};

LFUCache& getCache();
