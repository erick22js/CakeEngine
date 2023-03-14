#include <iostream>

#include "src/xmlhanddler.h"



int main(){
	
	CKXml::Object *xml = CKXml::Decoder::decodeFromFile("model.dae");
	
	CKXml::Node *root = xml->getFirstChild();
	
	CKXml::Encoder::encodeToFile("saida.xml", xml);
	
	delete xml;
	
    return 0;
}
