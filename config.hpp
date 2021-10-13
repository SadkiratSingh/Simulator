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
                string getAttribute(char* name);
                void setAttribute(char* name,char* val);
                void getChildElements(char* name, vector<Element>& v);
                string tostring();
                void setDomElement (char* name);
                Element* getDomElement();

        };
    public:
        void initialize(char* filename,char* decodekey);
        Element* getRoot(){return &root;}
        void setRoot(DOMElement* r){
            root.elem = r;
        }
        static void setDocLevel(DOMDocument* doc){
            docLevel = doc;
        }
        static DOMDocument* getDocLevel(){
            return docLevel;
        }
        void write(char* filename);
        static DOMDocument* docLevel;
    private:
        Element root;
};