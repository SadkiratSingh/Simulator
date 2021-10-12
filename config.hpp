#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
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
                void *elem;
            public:
                template<typename T>int getAttribute(const char* name, T&val) const;
                void setAttribute(const char* name, const char* val);
                void getChildElements(const char* name, vector<Element>& v);
                string tostring();
                void setDomElement (void* e) {elem = e;}
                void*getDomElement(){return elem;}

        };
    public:
        void initialize(const char* filename, const char* decodekey = 0);
        Element* getRoot(){return &root;}
        void setRoot(Element r){root = r;}
        void write(const char* filename);
    private:
        Element root;
};