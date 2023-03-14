#include "xmlhanddler.h"


#define CHAR_ISBLANK(chr) ((chr==' ')||(chr=='\n')||(chr=='\t'))
#define CHAR_ISCHAR(chr, cchar) (chr==cchar)
#define CHAR_ISTEXT(chr) (((chr>='A')&&(chr<='Z'))||((chr>='a')&&(chr<='z'))||(chr=='_'))
#define CHAR_ISDECIMAL(chr) ((chr>='0')&&(chr<='9'))

#define TOKEN_ISBLANK(tk) ((tk.type==Token::TYPE_CHAR)&&((tk.value.chr==' ')||(tk.value.chr=='\n')||(tk.value.chr=='\t')))
#define TOKEN_ISCHAR(tk, cchar) ((tk.type==Token::TYPE_CHAR)&&(tk.value.chr==cchar))
#define TOKEN_ISTEXT(tk) (tk.type==Token::TYPE_TEXT)

#define THROW(error) {collectToken(&tk); std::cout << "Error throwed at program line " << __LINE__ << std::endl; throw 1;}
#define THROW2(error) {collectToken(tk); std::cout << "Error throwed at program line " << __LINE__ << std::endl; throw 1;}

std::unordered_map<Char*, Char*> CKXml::dictionary = std::unordered_map<Char*, Char*>();

Char* CKXml::regString(Char* str){
	if(dictionary[str]){
		return dictionary[str];
	}
	Char* nstr = allocString(str);
	
	dictionary[nstr] = nstr;
	return dictionary[nstr];
}

Char* CKXml::allocString(Char* str){
	Int len = strlen(str);
	Char* nstr = new Char[len+1];
	
	Int i = 0;
	do{
		nstr[i] = str[i];
		i++;
		len--;
	}while(len>0);
	nstr[i] = 0;
	
	return nstr;
}

void CKXml::deallocString(Char* str){
	delete[] str;
}


/**
	NODE OBJECT
*/

CKXml::Node::~Node(){
	for(Node* node:children){
		delete node;
	}
	for(auto prop:properties){
		deallocString(prop.second);
	}
}

std::vector<CKXml::Node*> CKXml::Node::getChildren(){
	std::vector<Node*> nodes = std::vector<Node*>(0);
	for(Node* node:children){
		nodes.push_back(node);
	}
	return nodes;
}

CKXml::Node* CKXml::Node::getFirstChild(){
	if(children.size()>0){
		return children[0];
	}
	return nullptr;
}

std::vector<CKXml::Node*> CKXml::Node::getChildrenByName(Char* name){
	std::vector<Node*> nodes = std::vector<Node*>(0);
	for(Node* node:children){
		if(strcmp(node->name, name)==0){
			nodes.push_back(node);
		}
	}
	return nodes;
}

CKXml::Node* CKXml::Node::getFirstChildByName(Char* name){
	for(Node* node:children){
		if(strcmp(node->name, name)==0){
			return node;
		}
	}
	return nullptr;
}

CKXml::Node* CKXml::Node::getFather(){
	return father;
}

std::vector<Char*> CKXml::Node::getProperties(){
	std::vector<Char*> props = std::vector<Char*>(0);
	for(auto prop:properties){
		props.insert(props.begin(), prop.first);
	}
	return props;
}

Char* CKXml::Node::getProperty(Char* name){
	return properties[name];
}

Char* CKXml::Node::getName(){
	return name;
}

Char* CKXml::Node::getContent(){
	return (Char*)content.data();
}


CKXml::Node* CKXml::Node::createNode(Char* name){
	nocontent = false;
	Node *node = new Node();
	node->name = name;
	node->nocontent = true;
	children.push_back(node);
	return node;
}

Bool CKXml::Node::removeNode(Node* node){
	for(Int ni=0; ni<children.size(); ni++){
		if(children[ni]==node){
			children.erase(children.begin()+ni);
			return true;
		}
	}
	return false;
}

Bool CKXml::Node::hasNode(Node* node){
	for(Int ni=0; ni<children.size(); ni++){
		if(children[ni]==node){
			return true;
		}
	}
	return false;
}

void CKXml::Node::setProperty(Char* name, Char* value){
	properties[name] = allocString(value);
}

void CKXml::Node::setName(Char* name){
	this->name = name;
}

void CKXml::Node::setContent(Char* text){
	nocontent = false;
	content = text;
}



/**
	XML OBJECT
*/




/**
	READER
*/

CKXml::Reader::Reader(){
	
}

CKXml::Reader *CKXml::Reader::createFromFile(Char* filepath){
	Reader *reader = new Reader();
	reader->mode = FILE_MODE;
	reader->file = fopen(filepath, "r");
	if(!reader->file){
		delete reader;
		return nullptr;
	}
	return reader;
}

CKXml::Reader *CKXml::Reader::createFromString(Char* src){
	Reader *reader = new Reader();
	reader->mode = STRING_MODE;
	reader->src = src;
	return reader;
}

Int CKXml::Reader::read(){
	if(lbuf){
		lbuf = false;
		return lchr;
	}
	if(mode==FILE_MODE){
		lchr = fgetc(file);
		return lchr;
	}
	else if(mode==STRING_MODE){
		if(ended){
			return EOF;
		}
		else{
			Int chr = src[src_seek++];
			if(chr==0){
				ended = true;
				return EOF;
			}
			lchr = chr;
			return chr;
		}
	}
	return 0;
}

void CKXml::Reader::unread(){
	lbuf = true;
}


/**
	WRITTER
*/

CKXml::Writer::Writer(){
	
}

CKXml::Writer* CKXml::Writer::createToFile(Char* filepath){
	Writer* writer = new Writer();
	writer->file = fopen(filepath, "w");
	writer->mode = FILE_MODE;
	if(!writer->file){
		delete writer;
		return nullptr;
	}
	return writer;
}

CKXml::Writer* CKXml::Writer::createToString(){
	Writer* writer = new Writer();
	writer->mode = STRING_MODE;
	return writer;
}

void CKXml::Writer::writeChar(Int chr){
	src.push_back(chr);
}

void CKXml::Writer::writeChar(Int chr, Int times){
	while(times){
		src.push_back(chr);
		times--;
	}
}

void CKXml::Writer::writeString(Char* cstr){
	src.append(cstr);
}

void CKXml::Writer::writeString(std::string str){
	src.append(str);
}


Char* CKXml::Writer::flush(){
	if(mode==FILE_MODE){
		fwrite((void*)src.data(), 1, src.size(), file);
	}
	else if(mode==STRING_MODE){
		
	}
	return (Char*)src.data();
}

void CKXml::Writer::close(){
	if(mode==FILE_MODE){
		fclose(file);
	}
	else if(mode==STRING_MODE){
		
	}
}


/**
	DECODER
*/

void CKXml::Decoder::collectToken(Token *tk){
	if(tk->type==Token::TYPE_TEXT){
		deallocString(tk->value.text);
	}
}

void CKXml::Decoder::fetchToken(Token *tk, Reader *reader){
	Int chr = reader->read();
	
	collectToken(tk);
	
	if(chr==EOF){
		//std::cout << "Fetched EOF" << std::endl;
		tk->type = Token::TYPE_EOF;
		tk->value.chr = 0;
		return;
	}
	else if(CHAR_ISTEXT(chr)){
		std::vector<Char> text = std::vector<Char>(0);
		while(CHAR_ISTEXT(chr)||(chr==':')||(CHAR_ISDECIMAL(chr))){
			text.push_back((Char)chr);
			chr = reader->read();
		}
		text.push_back((Char)0);
		reader->unread();
		Char* cstr = allocString(text.data());
		tk->type = Token::TYPE_TEXT;
		tk->value.text = cstr;
		//std::cout << "Fetched Text: " << cstr << std::endl;
		return;
	}
	else{
		//std::cout << "Fetched Char: " << (Char)chr << std::endl;
		tk->type = Token::TYPE_CHAR;
		tk->value.chr = chr;
		return;
	}
}

void CKXml::Decoder::fetchTokenSupressing(Token *tk, Reader *reader){
	do{
		fetchToken(tk, reader);
	}while(TOKEN_ISBLANK((*tk)));
}

void CKXml::Decoder::fetchProperty(Token *tk, Reader *reader){
	std::string str = "";
	
	Int chr = reader->read();
	
	if(chr!='"'){
		/* TODO: Error => expected a string marker */
		THROW2(1);
		throw 1;
	}
	
	while(((chr = reader->read())!='"')&&(chr!=EOF)){
		str.push_back(chr);
	}
	
	tk->type = Token::TYPE_TEXT;
	tk->value.text = allocString((Char*)str.data());
}

CKXml::Object *CKXml::Decoder::decode(Reader *reader){
	Object *xml = new Object();
	
	try{
		decodeContent(reader, xml, true);
	}
	catch(Int err){
		std::cout << "Have throwed a error!" << std::endl;
		return nullptr;
	}
	
	return xml;
}

void CKXml::Decoder::decodeContent(Reader *reader, Node *owner, Bool root){
	Token tk;
	std::string content = "";
	Bool blankcontent = true;
	
	do{
		fetchToken(&tk, reader);
		
		if(TOKEN_ISCHAR(tk, '<')){
			fetchTokenSupressing(&tk, reader);
			
			if(TOKEN_ISTEXT(tk)){
				/**/content.clear();
				Char* nodename = regString(tk.value.text);
				decodeNode(reader, nodename, owner, false);
				continue;
			}
			else if(TOKEN_ISCHAR(tk, '?')&&root){
				/**/content.clear();
				fetchTokenSupressing(&tk, reader);
				if(TOKEN_ISTEXT(tk)){
					Char* nodename = regString(tk.value.text);
					decodeNode(reader, nodename, owner, true);
					continue;
				}
			}
			else if(TOKEN_ISCHAR(tk, '/')){
				fetchTokenSupressing(&tk, reader);
				if(TOKEN_ISTEXT(tk)&&(strcmp(tk.value.text, owner->name)==0)){
					if(blankcontent){
						content.clear();
					}
					owner->content = content;
					
					fetchTokenSupressing(&tk, reader);
					if(TOKEN_ISCHAR(tk, '>')){
						collectToken(&tk);
						return;
					}
				}
			}
			/* TODO: Error => Unexpected symbol */
			THROW(1);
			throw 1;
			
		}
		
		if(tk.type==Token::TYPE_CHAR){
			if(!CHAR_ISBLANK(tk.value.chr)){
				blankcontent = false;
			}
			content.push_back(tk.value.chr);
		}
		else if(tk.type==Token::TYPE_TEXT){
			blankcontent = false;
			content.append(tk.value.text);
		}
	}while((tk.type!=Token::TYPE_EOF));
	
	collectToken(&tk);
}

void CKXml::Decoder::decodeNode(Reader *reader, Char* name, Node *father, Bool xmlpref){
	Node *node = new Node();
	node->name = name;
	Token tk;
	
	do{
		fetchTokenSupressing(&tk, reader);
		
		/* Scans for node property */
		if(TOKEN_ISTEXT(tk)){
			Char* propname = regString(tk.value.text);
			fetchTokenSupressing(&tk, reader);
			if(TOKEN_ISCHAR(tk, '=')){
				fetchProperty(&tk, reader);
				Char* propvalue = allocString(tk.value.text);
				node->properties[propname] = propvalue;
				continue;
			}
		}
		/* Scans for node content filling */
		else if(TOKEN_ISCHAR(tk, '>')){
			decodeContent(reader, node, false);
			break;
		}
		/* Scans for node termination */
		else if(TOKEN_ISCHAR(tk, '/')||TOKEN_ISCHAR(tk, '?')){
			fetchTokenSupressing(&tk, reader);
			if(TOKEN_ISCHAR(tk, '>')){
				collectToken(&tk);
				node->father = father;
				node->nocontent = true;
				if(!xmlpref){
					father->children.push_back(node);
				}
				return;
			}
		}
		/* TODO: Error => Unexpected symbol */
		THROW(1);
		throw 1;
		
	}while(tk.type!=Token::TYPE_EOF);
	
	node->father = father;
	if(!xmlpref){
		father->children.push_back(node);
	}
	collectToken(&tk);
}

CKXml::Object *CKXml::Decoder::decodeFromFile(Char* filepath){
	Reader *reader = Reader::createFromFile(filepath);
	if(!reader){
		return nullptr;
	}
	return decode(reader);
}

CKXml::Object *CKXml::Decoder::decodeFromString(Char* src){
	Reader *reader = Reader::createFromString(src);
	return decode(reader);
}


/**
	ENCODER
*/

void CKXml::Encoder::encodeNode(Writer *writer, Node *node, Int identAdd, Int identTotal){
	writer->writeChar('\t', identTotal);
	writer->writeChar('<');
	writer->writeString(node->name);
	
	std::vector<Char*> props = node->getProperties();
	
	for(Int pi=0; pi<props.size(); pi++){
		writer->writeChar(' ');
		writer->writeString(props[pi]);
		writer->writeChar('=');
		writer->writeChar('"');
		writer->writeString(node->getProperty(props[pi]));
		writer->writeChar('"');
	}
	
	if(!node->nocontent){
		writer->writeChar('>');
		if(encodeNodeContent(writer, node, identAdd, identTotal+identAdd)){
			writer->writeChar('\n');
			writer->writeChar('\t', identTotal);
		}
		writer->writeChar('<');
		writer->writeChar('/');
		writer->writeString(node->name);
		writer->writeChar('>');
	}
	else{
		writer->writeChar('/');
		writer->writeChar('>');
	}
}

Int CKXml::Encoder::encodeNodeContent(Writer *writer, Node *owner, Int identAdd, Int identTotal){
	writer->writeString(owner->content);
	
	std::vector<Node*> children = owner->getChildren();
	for(Int ni=0; ni<children.size(); ni++){
		writer->writeChar('\n');
		encodeNode(writer, children[ni], identAdd, identTotal);
	}
	return children.size();
}

Char* CKXml::Encoder::encode(Writer *writer, Object *obj){
	try{
		writer->writeString("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
		encodeNodeContent(writer, obj, 1, 0);
		return writer->flush();
	}
	catch(Int err){
		
	}
	return nullptr;
}


void CKXml::Encoder::encodeToFile(Char* filepath, Object *obj){
	Writer *writer = Writer::createToFile(filepath);
	encode(writer, obj);
	writer->close();
}

Char* CKXml::Encoder::encodeToString(Object *obj){
	Writer *writer = Writer::createToString();
	return encode(writer, obj);
}


#undef CHAR_ISBLANK
#undef CHAR_ISCHAR
#undef CHAR_ISTEXT
#undef CHAR_ISDECIMAL

#undef TOKEN_ISBLANK
#undef TOKEN_ISCHAR
#undef TOKEN_ISTEXT

#undef THROW
#undef THROW2


