#include "MemoryPool.h"

MemoryPool::MemoryPool(){

}

void MemoryPool::init(int size){
	slot_size=size;
	currentBlock=currentSlot=lastSlot=freeSlot=NULL;
}

MemoryPool::~MemoryPool(){
	printf("Memory release!\n");
	Slot* curr=currentBlock;
	while(curr){
		Slot* prev=curr->next;
		free(reinterpret_cast<void *>(curr));
		//operator delete(reinterpret_cast<void *>(curr));
		curr=prev;
	}
}

inline 
size_t MemoryPool::padPointer(char* p,size_t align){
	uintptr_t result=reinterpret_cast<uintptr_t>(p);
	//printf("align=%lu\n",align);
	return ((align-result)%align);
}

Slot* MemoryPool::allocateBlock(){
	char* newBlock=NULL;
	while(!(newBlock=reinterpret_cast<char *>(malloc(BlockSize))));
	char* body=newBlock+sizeof(Slot);
	//printf("slot_size=%d\n",slot_size);
	size_t bodyPadding=padPointer(body,static_cast<size_t>(slot_size));
	//data_pointer newBlock=reinterpret_cast<data_pointer>(operator new(BlockSize));
	Slot *useSlot;
	{
		MutexLockGuard lock(m_other);
		reinterpret_cast<Slot*>(newBlock)->next=currentBlock;
		currentBlock=reinterpret_cast<Slot*>(newBlock);
		//char* body=newBlock+sizeof(Slot);
		//size_t bodyPadding=padPointer(body,slot_size);
		currentSlot=reinterpret_cast<Slot*>(body+bodyPadding);
		lastSlot=reinterpret_cast<Slot*>(newBlock+BlockSize-slot_size+1);
		useSlot=currentSlot;
    	currentSlot+=(slot_size>>3);
	}
    return useSlot;
}

Slot* MemoryPool::nofree_solve(){
	if(currentSlot>=lastSlot)
		return allocateBlock();
	Slot* useSlot;
	{
		MutexLockGuard lock(m_other);
		useSlot=currentSlot;
		currentSlot+=(slot_size>>3);
	}
	return useSlot;
}

Slot* MemoryPool::allocate(){
	if(freeSlot){
		{
			MutexLockGuard lock(m_freeSlot);
			if(freeSlot){
				Slot *result=freeSlot;
				freeSlot=freeSlot->next;
				return result;
			}
		}
	}
	return nofree_solve();
}

inline void MemoryPool::deallocate(Slot* p){
	if(p){
		MutexLockGuard lock(m_freeSlot);
		p->next=freeSlot;
		freeSlot=p;
	}
}

/*void *operator new(size_t size){
	printf("size=%d\n",size);
	long long *p;
	if(size>128){
		
		//malloc未处理
		return malloc(size);
	}
	return reinterpret_cast<void *>(memorypool[((size+7)>>3)-1].allocate());
}*/

void* use_memory(size_t size){
	if(!size)
		return nullptr;
	if(size>512)
		return malloc(size);
	return reinterpret_cast<void *>(get_memorypool(((size+7)>>3)-1).allocate());
}

void free_memory(size_t size,void *p){
	if(!p)
		return;
	if(size>512){
		free(p);
		return;
	}
	get_memorypool(((size+7)>>3)-1).deallocate(reinterpret_cast<Slot *>(p));
}

/*void operator delete(void *p,size_t size){
	printf("exec delete!\n");
	if(size>128)
		free(p);
	else
		memorypool[((size+7)>>3)-1].deallocate(reinterpret_cast<Slot *>(p));
}*/

void init_memorypool(){
	for(int i=0;i<64;++i)
		get_memorypool(i).init((i+1)<<3);
}

MemoryPool& get_memorypool(int id){
	static MemoryPool memorypool[64];
	return memorypool[id];
}
