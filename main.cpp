#include "config.hpp"


int main(int argc, char*argv[]){
    // newfile.xml contains modified xml code after we change the attribute value of one of the elements.
    char* filename = argv[1];
    char* encoding = argv[2];
    char* elementname = argv[3];
    char* attName= argv[4];
    char* attVal= argv[5];
    char* newfile= argv[6];
    // char* filename;
    // string filename_obj("bigsim.xml");
    // filename = &filename_obj[0];
    // char* encoding;
    // string encoding_obj("...");
    // encoding = &encoding_obj[0];
    // char* elementname;
    // string elementname_obj("Sim");
    // elementname = &elementname_obj[0];
    // char* attName;
    // string attName_obj("weight");
    // attName = &attName_obj[0];
    Config* cfg = new Config();
    cfg->initialize(filename,encoding);
    Config::Element* ele = new Config::Element();
    ele->setDomElement(elementname);
    ele->getDomElement();
    //cfg->initialize(argv[1],argv[2]);
    //Config::Element* root= cfg->getRoot();
    vector<Config::Element>v;
    ele->getChildElements(elementname,v);
    cout<<"current element's "<<attName<<": "<<ele->getAttribute(attName)<<endl;
    ele->setAttribute(attName,attVal);
    // for(int i=0; i<v.size();i++){
    //     //do somethingto test setAttribute and getAttribute.
    // }
    cfg->write(newfile);
}