#include <CakeEngine/util/formats/XmlHanddler.hpp>


#define CHAR_ISBLANK(chr) ((chr==' ')||(chr=='\n')||(chr=='\t'))
#define CHAR_ISCHAR(chr, cchar) (chr==cchar)
#define CHAR_ISTEXT(chr) (((chr>='A')&&(chr<='Z'))||((chr>='a')&&(chr<='z'))||(chr=='_'))
#define CHAR_ISDECIMAL(chr) ((chr>='0')&&(chr<='9'))

#define TOKEN_ISBLANK(tk) ((tk.type==Token::TYPE_CHAR)&&((tk.value.chr==' ')||(tk.value.chr=='\n')||(tk.value.chr=='\t')))
#define TOKEN_ISCHAR(tk, cchar) ((tk.type==Token::TYPE_CHAR)&&(tk.value.chr==cchar))
#define TOKEN_ISTEXT(tk) (tk.type==Token::TYPE_TEXT)

#define THROW(error) {collectToken(&tk); std::cout << "Error throwed at program line " << __LINE__ << std::endl; throw 1;}
#define THROW2(error) {collectToken(tk); std::cout << "Error throwed at program line " << __LINE__ << std::endl; throw 1;}



/**
	NODE OBJECT
*/

CKXmlNode::~CKXmlNode(){
	for(CKXmlNode* node:children){
		delete node;
	}
	properties.begin();
	for(;!properties.ended();){
		Char *nextKey = properties.nextKey();
		CKString::unwrap(properties.get(nextKey));
	}
}

std::vector<CKXmlNode*> CKXmlNode::getChildren(){
	std::vector<CKXmlNode*> nodes = std::vector<CKXmlNode*>(0);
	for(CKXmlNode* node:children){
		nodes.push_back(node);
	}
	return nodes;
}

CKXmlNode* CKXmlNode::getFirstChild(){
	if(children.size()>0){
		return children[0];
	}
	return nullptr;
}

std::vector<CKXmlNode*> CKXmlNode::getChildrenByName(Char* name){
	std::vector<CKXmlNode*> nodes = std::vector<CKXmlNode*>(0);
	for(CKXmlNode* node:children){
		if(strcmp(node->name, name)==0){
			nodes.push_back(node);
		}
	}
	return nodes;
}

CKXmlNode* CKXmlNode::getFirstChildByName(Char* name){
	for(CKXmlNode* node:children){
		if(strcmp(node->name, name)==0){
			return node;
		}
	}
	return nullptr;
}

CKXmlNode* CKXmlNode::getFather(){
	return father;
}

std::vector<Char*> CKXmlNode::getProperties(){
	std::vector<Char*> props = std::vector<Char*>(0);
	properties.begin();
	for(;!properties.ended();){
		props.insert(props.begin(), properties.nextKey());
	}
	return props;
}

Char* CKXmlNode::getProperty(Char* name){
	if(properties.has(name)){
		return properties.get(name);
	}
	return nullptr;
}

Char* CKXmlNode::getName(){
	return name;
}

Char* CKXmlNode::getContent(){
	return (Char*)content.data();
}


CKXmlNode* CKXmlNode::createNode(Char* name){
	nocontent = false;
	CKXmlNode *node = new CKXmlNode();
	node->name = name;
	node->nocontent = true;
	children.push_back(node);
	return node;
}

Bool CKXmlNode::removeNode(CKXmlNode* node){
	for(Int ni=0; ni<(Int)children.size(); ni++){
		if(children[ni]==node){
			children.erase(children.begin()+ni);
			return true;
		}
	}
	return false;
}

Bool CKXmlNode::hasNode(CKXmlNode* node){
	for(Int ni=0; ni<(Int)children.size(); ni++){
		if(children[ni]==node){
			return true;
		}
	}
	return false;
}

void CKXmlNode::setProperty(Char* name, Char* value){
	properties.set(name, CKString::wrap(value));
}

void CKXmlNode::setName(Char* name){
	this->name = name;
}

void CKXmlNode::setContent(Char* text){
	nocontent = false;
	content = text;
}



/**
	XML OBJECT
*/




/**
	DECODER
*/

void CKXmlDecoder::collectToken(Token *tk){
	if(tk->type==Token::TYPE_TEXT){
		CKString::unwrap(tk->value.text);
	}
}

void CKXmlDecoder::fetchToken(Token *tk, CKReader *reader){
	Int chr = reader->readc();
	
	collectToken(tk);
	
	if(chr==EOF){
		//std::cout << "Fetched EOF" << std::endl;
		tk->type = Token::TYPE_EOF;
		tk->value.chr = 0;
		return;
	}
	else if(CHAR_ISTEXT(chr)){
		std::vector<Char> text = std::vector<Char>(0);
		while(CHAR_ISTEXT(chr)||(chr==':')||(CHAR_ISDECIMAL(chr))||(chr=='-')){
			text.push_back((Char)chr);
			chr = reader->readc();
		}
		text.push_back((Char)0);
		reader->unreadc();
		Char* cstr = CKString::wrap(text.data());
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

void CKXmlDecoder::fetchTokenSupressing(Token *tk, CKReader *reader){
	do{
		fetchToken(tk, reader);
	}while(TOKEN_ISBLANK((*tk)));
}

void CKXmlDecoder::fetchProperty(Token *tk, CKReader *reader){
	std::string str = "";
	
	Int chr = reader->readc();
	
	if(chr!='"'){
		/* TODO: Error => expected a string marker */
		THROW2(1);
		throw 1;
	}
	
	while(((chr = reader->readc())!='"')&&(chr!=EOF)){
		str.push_back(chr);
	}
	
	tk->type = Token::TYPE_TEXT;
	tk->value.text = CKString::wrap((Char*)str.data());
}

CKXmlObject *CKXmlDecoder::decode(CKReader *reader){
	CKXmlObject *xml = new CKXmlObject();
	
	try{
		decodeContent(reader, xml, true);
	}
	catch(Int err){
		std::cout << "Have throwed a error!" << std::endl;
		return nullptr;
	}
	
	return xml;
}

void CKXmlDecoder::decodeContent(CKReader *reader, CKXmlNode *owner, Bool root){
	Token tk;
	std::string content = "";
	Bool blankcontent = true;
	
	do{
		fetchToken(&tk, reader);
		
		if(TOKEN_ISCHAR(tk, '<')){
			fetchTokenSupressing(&tk, reader);
			
			if(TOKEN_ISTEXT(tk)){
				/**/content.clear();
				Char* nodename = CKString::record(tk.value.text);
				decodeNode(reader, nodename, owner, false);
				continue;
			}
			else if(TOKEN_ISCHAR(tk, '?')&&root){
				/**/content.clear();
				fetchTokenSupressing(&tk, reader);
				if(TOKEN_ISTEXT(tk)){
					Char* nodename = CKString::record(tk.value.text);
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

void CKXmlDecoder::decodeNode(CKReader *reader, Char* name, CKXmlNode *father, Bool xmlpref){
	CKXmlNode *node = new CKXmlNode();
	node->name = name;
	Token tk;
	
	do{
		fetchTokenSupressing(&tk, reader);
		
		/* Scans for node property */
		if(TOKEN_ISTEXT(tk)){
			Char* propname = CKString::record(tk.value.text);
			fetchTokenSupressing(&tk, reader);
			if(TOKEN_ISCHAR(tk, '=')){
				fetchProperty(&tk, reader);
				Char* propvalue = CKString::wrap(tk.value.text);
				node->properties.set(propname, propvalue);
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

CKXmlObject *CKXmlDecoder::decodeFrom(CKReader *reader){
	if(!reader->isOpen()){
		return nullptr;
	}
	return decode(reader);
}


/**
	ENCODER
*/

void CKXmlEncoder::encodeNode(CKWriter *writer, CKXmlNode *node, Int identAdd, Int identTotal){
	writer->writec('\t', identTotal);
	writer->writec('<');
	writer->write(node->name);
	
	std::vector<Char*> props = node->getProperties();
	
	for(Int pi=0; pi<(Int)props.size(); pi++){
		writer->writec(' ');
		writer->write(props[pi]);
		writer->writec('=');
		writer->writec('"');
		writer->write(node->getProperty(props[pi]));
		writer->writec('"');
	}
	
	if(!node->nocontent){
		writer->writec('>');
		if(encodeNodeContent(writer, node, identAdd, identTotal+identAdd)){
			writer->writec('\n');
			writer->writec('\t', identTotal);
		}
		writer->writec('<');
		writer->writec('/');
		writer->write(node->name);
		writer->writec('>');
	}
	else{
		writer->writec('/');
		writer->writec('>');
	}
}

Int CKXmlEncoder::encodeNodeContent(CKWriter *writer, CKXmlNode *owner, Int identAdd, Int identTotal){
	writer->write((Char*)owner->content.data());
	
	std::vector<CKXmlNode*> children = owner->getChildren();
	for(Int ni=0; ni<(Int)children.size(); ni++){
		writer->writec('\n');
		encodeNode(writer, children[ni], identAdd, identTotal);
	}
	return children.size();
}

void CKXmlEncoder::encode(CKWriter *writer, CKXmlObject *obj){
	try{
		writer->write((Char*)"<?xml version=\"1.0\" encoding=\"utf-8\"?>");
		encodeNodeContent(writer, obj, 1, 0);
	}
	catch(Int err){
		
	}
}


void CKXmlEncoder::encodeTo(CKWriter* writer, CKXmlObject *obj){
	if(!writer->isOpen()){
		return;
	}
	encode(writer, obj);
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


