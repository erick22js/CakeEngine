#ifndef cakengine_util_xmlhanddler_h
#define cakengine_util_xmlhanddler_h

#include <iostream>
#include <vector>

#include "../../file/Reader.hpp"
#include "../../file/Writer.hpp"
#include <CakeEngine/util/String.hpp>
#include <CakeEngine/util/Dictionary.hpp>


class CKXmlNode{

	friend class CKXmlDecoder;
	friend class CKXmlEncoder;
	
protected:
	Char* name = nullptr;
	
	CKDictionary<Char*> properties = CKDictionary<Char*>();
	std::vector<CKXmlNode*> children = std::vector<CKXmlNode*>();
	std::string content = "";
	Bool nocontent = false;
	CKXmlNode *father = nullptr;
	
	CKXmlNode(){};
	
public:
	~CKXmlNode();
	
	std::vector<CKXmlNode*> getChildren();
	CKXmlNode* getFirstChild();
	std::vector<CKXmlNode*> getChildrenByName(Char* name);
	CKXmlNode* getFirstChildByName(Char* name);
	CKXmlNode* getFather();
	std::vector<Char*> getProperties();
	Char* getProperty(Char* name);
	Char* getName();
	Char* getContent();
	
	CKXmlNode* createNode(Char* name);
	Bool removeNode(CKXmlNode* node);
	Bool hasNode(CKXmlNode* node);
	void setProperty(Char* name, Char* value);
	void setName(Char* name);
	void setContent(Char* data);
	
};

class CKXmlObject: public CKXmlNode{

	friend class CKXmlDecoder;
	friend class CKXmlEncoder;
	
private:
	CKXmlObject(){};
	
public:
	
	
};

class CKXmlDecoder{

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
	static void fetchToken(Token *tk, CKReader *reader);
	static void fetchTokenSupressing(Token *tk, CKReader *reader);
	static void fetchProperty(Token *tk, CKReader *reader);
	
	static CKXmlObject *decode(CKReader *reader);
	static void decodeContent(CKReader *reader, CKXmlNode *owner, Bool root);
	static void decodeNode(CKReader *reader, Char* name, CKXmlNode *father, Bool xmlpref);
	
public:
	static CKXmlObject *decodeFrom(CKReader *reader);
	
};

class CKXmlEncoder{

private:
	static void encodeNode(CKWriter *writer, CKXmlNode *node, Int identAdd, Int identTotal);
	static Int encodeNodeContent(CKWriter *writer, CKXmlNode *owner, Int identAdd, Int identTotal);
	static void encode(CKWriter *writer, CKXmlObject *obj);
	
public:
	static void encodeTo(CKWriter *writer, CKXmlObject *obj);
	
};


#endif // cakengine_util_xmlhanddler_h
