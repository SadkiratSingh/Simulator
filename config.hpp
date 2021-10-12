#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace xercesc;

class Config{
    public:
        class Element{
            friend class Config;
            private:
                DOMElement *elem;
            public:
                string getAttribute(const char* name);
                void setAttribute(const char* name, const char* val);
                void getChildElements(const char* name, vector<Element>& v);
                string tostring();
                void setDomElement (DOMElement* e);
                Element* getDomElement();

        };
    public:
        void initialize(const char* filename, const char* decodekey = 0);
        Element* getRoot(){return &root;}
        void setRoot(DOMElement* r){
            root.elem = r;
        }
        static void setDocLevel(DOMDocument* doc){
            docLevel = doc;
        }
        void write(const char* filename);
        static DOMDocument* docLevel;
    private:
        Element root;
};
DOMDocument* Config::docLevel = NULL;