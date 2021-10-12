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

    cout<<"Parsing done";

    //initialize members
    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
    if(impl == NULL){
        cout<<"Implementation Error"<<endl;
        return;
    }
    try{
        DOMDocument* doc = impl->createDocument(0,XMLString::transcode("Simulator"),0);
        DOMElement* rootElem = doc->getDocumentElement();
        Config* cfg = new Config();
        cfg->setRoot(rootElem);
    }catch(const XMLException& toCatch){
         char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
    }

    delete parser;
    delete errHandler;
    XMLPlatformUtils::Terminate();
}