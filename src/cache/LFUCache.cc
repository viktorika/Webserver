#include "LFUCache.h"

void KeyList::init(int fq)
{
	freq=fq;
	//head=last=new Node<Key>;
	head=last=newElement<Node<Key>>();
	head->setNext(NULL);
}

void KeyList::destory(){
	while(head){
		key_node pre=head;
		head=head->getNext();
		//delete pre;
		deleteElement(pre);
	}
}

int KeyList::getFreq(){
	return freq;
}

void KeyList::add(key_node &node){
	if(head->getNext()){
		head->getNext()->setPre(node);
		//printf("is not one\n");
	}
	else
		last=node;
	node->setNext(head->getNext());
	node->setPre(head);
	head->setNext(node);
	//printf("last key=%d\n",last->getValue().key);
}

void KeyList::del(key_node &node){
	node->getPre()->setNext(node->getNext());
    if(node->getNext())
        node->getNext()->setPre(node->getPre());
    else
        last=node->getPre();
}

bool KeyList::isEmpty(){
	return head==last;
}

key_node KeyList::getLast(){
	return last;
}

void LFUCache::init(){
	capacity=getconf().getcapacity();
	//head=new Node<KeyList>;
	head=newElement<Node<KeyList>>();
	head->getValue().init(0);
	head->setNext(NULL);
}

LFUCache::~LFUCache(){
	while(head){
		freq_node pre=head;
		head=head->getNext();
		pre->getValue().destory();
		//delete pre;
		deleteElement(pre);
	}
}

void LFUCache::addfreq(key_node &nowk,freq_node &nowf){
	freq_node nxt;
	if(!nowf->getNext()||nowf->getNext()->getValue().getFreq()!=nowf->getValue().getFreq()+1){
		//插入freqnode
		//printf("new freqnode!\n");
		//nxt=new Node<KeyList>;
		nxt=newElement<Node<KeyList>>();
		nxt->getValue().init(nowf->getValue().getFreq()+1);
		if(nowf->getNext())
			nowf->getNext()->setPre(nxt);
		nxt->setNext(nowf->getNext());
		nowf->setNext(nxt);
		nxt->setPre(nowf);
	}
	else
		nxt=nowf->getNext();
	fmap[nowk->getValue().key]=nxt;
	//移动keynode
	if(nowf!=head){
		nowf->getValue().del(nowk);
		//printf("nowf is not head!\n");
	}
	nxt->getValue().add(nowk);
    if(nowf!=head&&nowf->getValue().isEmpty())
		del(nowf);
}

bool LFUCache::get(string &key,string &v){
	if(!capacity)
		return false;
	MutexLockGuard lock(mutex);
	if(fmap.find(key)!=fmap.end()){
		//命中
		key_node nowk=kmap[key];
		freq_node nowf=fmap[key];
		v+=nowk->getValue().value;
		addfreq(nowk,nowf);
		return true;
	}
	return false;
}

void LFUCache::set(string &key,string &v){
	if(!capacity)
		return;
	//printf("kmapsize=%d capacity=%d\n",kmap.size(),capacity);
	MutexLockGuard lock(mutex);
	if(kmap.size()==capacity){
		freq_node headnxt=head->getNext();
		key_node last=headnxt->getValue().getLast();
		headnxt->getValue().del(last);
		//printf("key=%d\n",last->getValue().key);
		kmap.erase(last->getValue().key);
		fmap.erase(last->getValue().key);
		//delete last;
		deleteElement(last);
		if(headnxt->getValue().isEmpty())
			del(headnxt);
	}
	//key_node nowk=new Node<Key>;
	key_node nowk=newElement<Node<Key>>();
	nowk->getValue().key=key;
	nowk->getValue().value=v;
	addfreq(nowk,head);
	kmap[key]=nowk;
}

void LFUCache::del(freq_node &node){
	node->getPre()->setNext(node->getNext());
	if(node->getNext())
    	node->getNext()->setPre(node->getPre());
    node->getValue().destory();
    //delete node;
	deleteElement(node);
}

LFUCache& getCache(){
	static LFUCache cache;
	return cache;
}
