#ifndef INC_XML_PARSER
#define INC_XML_PARSER

#include "utils/xml/tinyxml2.h"

class CXMLElement { 
	const tinyxml2::XMLElement *elem;
public:
	CXMLElement( const tinyxml2::XMLElement *elem );

	int getIntAttr( const char *name, int default_value ) const;
	float getFloatAttr( const char *name, float default_value ) const;
	bool getBoolAttr( const char *name, bool default_value ) const;
	const char *getStrAttr( const char *name) const;
	const char* getText( ) const;
};


class CXMLParser {
	void parserElem( const tinyxml2::XMLElement *elem );

public:
	void loadFile( const char *filename );
	//callbacks function
	virtual void onStartElement( const char *name, const CXMLElement &elem ) { }	
	virtual void onEndElement( const char *name, const CXMLElement &elem ) { }
};


#endif
