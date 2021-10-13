#include "config.hpp"

DOMDocument* Config::docLevel = NULL;

void Config::initialize(char* filename,char* decodekey){
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
                << message << "\n";
        XMLString::release(&message);
    }
    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    try {
        //t1
        parser->parse(filename);
        cout<<"Parsing done"<<endl;
        
        //t2
        DOMDocument* doc = parser->adoptDocument();
        Config::setDocLevel(doc);
        char* rootNodeName = XMLString::transcode(Config::docLevel->getNodeName());
        cout<<"DocumentLevel: "<<rootNodeName<<endl;
        DOMElement* rootElem = doc->getDocumentElement();
        
        //t3
        setRoot(rootElem);
        char* configRootName = XMLString::transcode(getRoot()->elem->getNodeName());
        cout<<"configRootName: "<<configRootName<<endl;
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
    }
    catch (...) {
        cout << "Unexpected Exception \n" ;
    }
    delete parser;
    delete errHandler;
    //doubt in below line.
    //XMLPlatformUtils::Terminate();
}

void Config::Element::setAttribute(char* name, char* val){
    elem->setAttribute(XMLString::transcode(name),XMLString::transcode(val));
}

string Config::Element::getAttribute(char* name){
    return string(XMLString::transcode(elem->getAttribute(XMLString::transcode(name))));
}

void Config::Element::setDomElement(char* name){
    //cout<<XMLString::transcode(Config::docLevel->getNodeName());
    //cout<<XMLString::transcode(Config::docLevel->getDocumentElement()->getNodeName());
    //cout<<XMLString::transcode(Config::docLevel->getDocumentElement()->getAttribute(XMLString::transcode("logLevel")));
    DOMElement* e = static_cast<DOMElement*>(Config::docLevel->getElementsByTagName(XMLString::transcode(name))->item(0));
    //t4
    char* e_name = XMLString::transcode(e->getNodeName());
    cout<<"current node name: "<<e_name<<endl;
    elem = e;
}

Config::Element* Config::Element::getDomElement(){
    //t5
    char* e_name = XMLString::transcode(elem->getNodeName());
    cout<<"current node name: "<<e_name<<endl;
    return this;
}

string Config::Element::tostring(){
    string s(XMLString::transcode(elem->getNodeName()));
    cout<<"node name: "<<s;
    return s;
}

void Config::Element::getChildElements(char* name, vector<Element>& v){
    // DOMNodeList* itemList = Config::docLevel->getElementsByTagName(XMLString::transcode(name));
    // DOMNode* firstItem = itemList->item(0);
    setDomElement(name);
    if(elem->hasChildNodes()){
        DOMNodeList* childList = elem->getChildNodes();
        for(XMLSize_t j =0;j<childList->getLength();j++){
            //cout<<childList->item(j)<<endl;
            Config::Element e;
            e.elem = static_cast<DOMElement*>(childList->item(j));
            v.push_back(e);
            //cout<<e.elem<<endl;
            //t6
            cout<<j<<". "<<XMLString::transcode(e.elem->getNodeName())<<endl;
        }
    }
}

void Config::write(char* filename){
    //doubt below
    DOMImplementation* t = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
    DOMDocument* d = Config::docLevel;
    DOMLSSerializer *theWriter = ((DOMImplementationLS*)t)->createLSSerializer();
    DOMLSOutput *theOutputDesc = ((DOMImplementationLS*)t)->createLSOutput();
    DOMConfiguration* theWriterConfig = theWriter->getDomConfig();
    theWriterConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint,true);
    XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(filename);
    theOutputDesc->setByteStream(myFormTarget);
    theWriter->write(d,theOutputDesc);
    delete myFormTarget;
    theOutputDesc->release();
    theWriter->release();
}