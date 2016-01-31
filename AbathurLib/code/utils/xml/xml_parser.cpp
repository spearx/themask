#include "xml_parser.h"

using namespace tinyxml2;

// CXMLElement 
CXMLElement::CXMLElement( const XMLElement *aelem ) 
: elem(aelem) 
{ 
}

int CXMLElement::getIntAttr( const char *name, int default_value ) const {
	int value = default_value;
	elem->QueryIntAttribute(name, &value);
	return value;
}

float CXMLElement::getFloatAttr( const char *name, float default_value ) const {
	float value = default_value;
	elem->QueryFloatAttribute(name, &value);
	return value;
}

bool CXMLElement::getBoolAttr( const char *name, bool default_value ) const {
	bool value = default_value;
	elem->QueryBoolAttribute(name, &value);
	return value;
}	

const char *CXMLElement::getStrAttr( const char *name) const {
  const char *value = elem->Attribute(name);
  if( value )
	  return value;
  return "";
}

const char* CXMLElement::getText( ) const {
	return elem->GetText( );
}

void CXMLParser::parserElem( const XMLElement *elem ) {		
	const char *name = elem->Name();
	CXMLElement e(elem);
	onStartElement( name, e );
	//childrens parser
	const XMLElement *child = elem->FirstChildElement();
	while( child ) {
		parserElem(child);
		child = child->NextSiblingElement();
	}
	onEndElement( name, e );
}

void CXMLParser::loadFile( const char *filename ) {
	XMLDocument doc;
	doc.LoadFile(filename);
	int ret = doc.ErrorID();
	if( ret == 0 ) {
		XMLElement* root = doc.RootElement( );
		parserElem(root);

	} else {
		printf("XMLParser error!\n");
	}

}