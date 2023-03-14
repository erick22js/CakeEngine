#ifndef cakengine_util_dictionary_h
#define cakengine_util_dictionary_h

#include <unordered_map>

#include <CakeEngine/util/String.hpp>


template<typename V> class CKDictionary{
	
	struct Value{
		Char* key;
		V value;
	};
	
	typedef typename std::unordered_map<SizeT, Value>::const_iterator const_iterator;
	
private:
	std::unordered_map<SizeT, Value> map = std::unordered_map<SizeT, Value>();
	const_iterator iter = map.begin();
	
public:
	CKDictionary(){
		
	}
	
	
	void set(Char* key, V value){
		SizeT keyhash = CKString::hash(key);
		map[keyhash] = {key, value};
	}
	
	
	V get(Char* key){
		SizeT keyhash = CKString::hash(key);
		return map[keyhash].value;
	}
	
	
	Bool has(Char* key){
		SizeT keyhash = CKString::hash(key);
		return map.count(keyhash);
	}
	
	
	void remove(Char* key){
		SizeT keyhash = CKString::hash(key);
		if(has(key)){
			map.erase(keyhash);
		}
	}
	
	
	void begin(){
		iter = map.begin();
	}
	
	Char* nextKey(){
		Char* key = iter->second.key;
		iter++;
		return key;
	}
	
	Bool ended(){
		return iter==map.end();
	}
	
};


#endif // cakengine_util_hashmap_h
