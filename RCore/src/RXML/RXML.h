#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "tinyxml2/tinyxml2.h"

namespace RXML
{
	tinyxml2::XMLElement* getUniqueElement(tinyxml2::XMLElement* parent, const char* name);

	class XMLElemObj
	{
		friend class XMLFileObj;
	public:
		tinyxml2::XMLElement* getXmlElement() const { return this->m_xmlElement; }
		int getNumChildElements() const { return this->m_childElements.size(); }
		XMLElemObj* getChildElement(std::string name);
		void addChildElement(std::string name);

		virtual void destroy();
	protected:
		XMLElemObj() {}

		XMLElemObj(tinyxml2::XMLElement* elem) 
		{
			this->m_xmlElement = elem;
		}

		~XMLElemObj() {}

		static XMLElemObj* create(tinyxml2::XMLElement* elem);

		tinyxml2::XMLElement* m_xmlElement = nullptr;

		XMLElemObj* m_parent = nullptr;
		std::vector<XMLElemObj*> m_childElements;
	};

	class XMLFileObj
	{
	public:
		XMLFileObj() 
		{
			this->m_xmlDoc = new tinyxml2::XMLDocument;

			tinyxml2::XMLElement* root = this->m_xmlDoc->NewElement("");
			this->m_xmlDoc->InsertEndChild(root);

			this->m_rootElement = XMLElemObj::create(root);
		}

		XMLFileObj(const char* filename) : XMLFileObj()
		{
			this->setDstFileName(filename);
		}

		std::string getDstFileName() const { return this->m_dstFileName; }
		void setDstFileName(std::string filepath) { this->m_dstFileName = filepath; }

		XMLElemObj* getRootElement() const { return this->m_rootElement; }

		int getNumChildElements() const { return this->m_rootElement->getNumChildElements(); }
		XMLElemObj* getChildElement(std::string name) const { return this->m_rootElement; }
		void addChildElement(std::string name);

		virtual bool save();
		virtual bool load(const char* filename);
		virtual void destroy();
	protected:
		~XMLFileObj() {}

		std::string m_dstFileName = "";
		tinyxml2::XMLDocument* m_xmlDoc = nullptr;
		XMLElemObj* m_rootElement = nullptr;
	};

	tinyxml2::XMLElement* createBoolElement(tinyxml2::XMLElement* parent, std::string name, bool value);
	tinyxml2::XMLElement* createByteElement(tinyxml2::XMLElement* parent, std::string name, INT8 value);
	tinyxml2::XMLElement* createUByteElement(tinyxml2::XMLElement* parent, std::string name, UINT8 value);
	tinyxml2::XMLElement* createShortElement(tinyxml2::XMLElement* parent, std::string name, INT16 value);
	tinyxml2::XMLElement* createUShortElement(tinyxml2::XMLElement* parent, std::string name, UINT16 value);
	tinyxml2::XMLElement* createIntElement(tinyxml2::XMLElement* parent, std::string name, int value);
	tinyxml2::XMLElement* createUIntElement(tinyxml2::XMLElement* parent, std::string name, UINT value);
	tinyxml2::XMLElement* createInt64Element(tinyxml2::XMLElement* parent, std::string name, INT64 value);
	tinyxml2::XMLElement* createUInt64Element(tinyxml2::XMLElement* parent, std::string name, UINT64 value);
	tinyxml2::XMLElement* createFloatElement(tinyxml2::XMLElement* parent, std::string name, float value);
	tinyxml2::XMLElement* createVector3Element(tinyxml2::XMLElement* parent, std::string name, float x, float y, float z);
	tinyxml2::XMLElement* createVector4Element(tinyxml2::XMLElement* parent, std::string name, float x, float y, float z, float w);

	bool getBoolElement(tinyxml2::XMLElement* parent, std::string name);
	INT8 getByteElement(tinyxml2::XMLElement* parent, std::string name);
	UINT8 getUByteElement(tinyxml2::XMLElement* parent, std::string name);
	INT16 getShortElement(tinyxml2::XMLElement* parent, std::string name);
	UINT16 getUShortElement(tinyxml2::XMLElement* parent, std::string name);
	int getIntElement(tinyxml2::XMLElement* parent, std::string name);
	UINT getUIntElement(tinyxml2::XMLElement* parent, std::string name);
	INT64 getInt64Element(tinyxml2::XMLElement* parent, std::string name);
	UINT64 getUInt64Element(tinyxml2::XMLElement* parent, std::string name);
	float getFloatElement(tinyxml2::XMLElement* parent, std::string name);
	void getVector3Element(tinyxml2::XMLElement* parent, std::string name, float* buf);
	void getVector4Element(tinyxml2::XMLElement* parent, std::string name, float* buf);
}