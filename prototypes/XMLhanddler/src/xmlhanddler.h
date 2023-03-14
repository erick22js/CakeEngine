#ifndef cakengine_util_xmlhanddler_h
#define cakengine_util_xmlhanddler_h

#include <iostream>
#include <unordered_map>
#include <string>
#include <string.h>
#include <vector>
#include <api.h>


class CKXml{
	
private:
	
	static std::unordered_map<Char*, Char*> dictionary;
	
	/* This function is for avoid allocating multiples instances of a same string form */
	static Char* regString(Char* str);
	/* This function is for generating a new allocated string copied from another one */
	static Char* allocString(Char* str);
	static void deallocString(Char* str);
	
	class Reader;
	
	class Writer;
	
public:
	class Node;
	
	class Object;
	
	class Decoder;
	
	class Encoder;
	
};

class CKXml::Reader{

private:
	enum{
		FILE_MODE,
		STRING_MODE
	}mode;
	
	FILE *file;
	
	Char* src;
	Int src_seek = 0;
	
	Int ended = -1;
	
	Int lchr = 0;
	Bool lbuf = false;
	
	Reader();
	
public:
	static Reader* createFromFile(Char* filepath);
	static Reader* createFromString(Char* src);
	
	Int read();
	
	void unread();
	
};

class CKXml::Writer{
	
private:
	enum{
		FILE_MODE,
		STRING_MODE
	}mode;
	
	FILE *file;
	
	std::string src = "";
	
	Writer();
	
public:
	static Writer* createToFile(Char* filepath);
	static Writer* createToString();
	
	void writeChar(Int chr);
	void writeChar(Int chr, Int times);
	void writeString(Char* cstr);
	void writeString(std::string str);
	
	Char* flush();
	void close();
	
};

class CKXml::Node{

	friend class Decoder;
	friend class Encoder;
	
protected:
	Char* name = nullptr;
	
	std::unordered_map<Char*, Char*> properties = std::unordered_map<Char*, Char*>();
	std::vector<Node*> children = std::vector<Node*>();
	std::string content = "";
	Bool nocontent = false;
	Node *father = nullptr;
	
	Node(){};
	
public:
	~Node();
	
	std::vector<Node*> getChildren();
	Node* getFirstChild();
	std::vector<Node*> getChildrenByName(Char* name);
	Node* getFirstChildByName(Char* name);
	Node* getFather();
	std::vector<Char*> getProperties();
	Char* getProperty(Char* name);
	Char* getName();
	Char* getContent();
	
	Node* createNode(Char* name);
	Bool removeNode(Node* node);
	Bool hasNode(Node* node);
	void setProperty(Char* name, Char* value);
	void setName(Char* name);
	void setContent(Char* data);
	
};

class CKXml::Object: public CKXml::Node{

	friend class Decoder;
	friend class Encoder;
	
private:
	Object(){};
	
public:
	
	
};

class CKXml::Decoder{

private:
	typedef struct{
		enum{
			TYPE_CHAR,
			TYPE_TEXT,
			TYPE_EOF
		}type;
		union{
			Int chr;
			Char* text;
		}value;
	}Token;
	
	static void collectToken(Token *tk);
	static void fetchToken(Token *tk, Reader *reader);
	static void fetchTokenSupressing(Token *tk, Reader *reader);
	static void fetchProperty(Token *tk, Reader *reader);
	
	static Object *decode(Reader *reader);
	static void decodeContent(Reader *reader, Node *owner, Bool root);
	static void decodeNode(Reader *reader, Char* name, Node *father, Bool xmlpref);
	
public:
	static Object *decodeFromFile(Char* filepath);
	static Object *decodeFromString(Char* src);
	
};

class CKXml::Encoder{

private:
	static void encodeNode(Writer *writer, Node *node, Int identAdd, Int identTotal);
	static Int encodeNodeContent(Writer *writer, Node *owner, Int identAdd, Int identTotal);
	static Char* encode(Writer *writer, Object *obj);
	
public:
	static void encodeToFile(Char* filepath, Object *obj);
	static Char* encodeToString(Object *obj);
	
};


#endif // cakengine_util_xmlhanddler_h
