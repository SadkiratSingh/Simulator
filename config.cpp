#include<config.hpp>

void Config::initialize(const char* filename, const char* decodekey = 0){
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
        parser->parse(filename);
        cout<<"Parsing done";
        DOMDocument* doc = parser->adoptDocument();
        Config::setDocLevel(doc);
        DOMElement* rootElem = doc->getDocumentElement();
        Config* cfg = new Config();
        cfg->setRoot(rootElem);
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
    XMLPlatformUtils::Terminate();
}

void Config::Element::setAttribute(const char* name, const char* val){
    this->elem->setAttribute(XMLString::transcode(name),XMLString::transcode(val));
}

string Config::Element::getAttribute(const char* name){
    return string (XMLString::transcode((this->elem->getAttribute(XMLString::transcode(name)))));
}

void Config::Element::setDomElement(DOMElement* e){
    this->elem = e;
}

Config::Element* Config::Element::getDomElement(){
    return this;
}

string Config::Element::tostring(){
    string s(XMLString::transcode(this->elem->getNodeName()));
    cout<<s;
    return s;
}

void Config::Element::getChildElements(const char* name, vector<Element>& v){
    DOMNodeList* itemList = Config::docLevel->getElementsByTagName(XMLString::transcode(name));
    DOMNode* firstItem = itemList->item(0);
    if(firstItem->hasChildNodes()){
        DOMNodeList* childList = firstItem->getChildNodes();
        for(XMLSize_t j =0;j<childList->getLength();j++){
            Config::Element e;
            e.elem = dynamic_cast<DOMElement*>(childList->item(j));
            v.push_back(e);
        }
    }
}

void Config::write(const char* filename){
    //doubt below
    DOMImplementation* t = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));
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