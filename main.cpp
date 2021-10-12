#include<config.hpp>


int main(int argc, char*argv[]){
    char* filename = argv[1];
    char* encoding = argv[2];
    char* childname = argv[3];
    char* newfile= argv[4];
    Config cfg;
    cfg.initialize(argv[1],argv[2]);
    Config::Element* root= cfg.getRoot();
    vector<Config::Element>v;
    root->getChildElements(childname,v);
    for(int i=0; i<v.size();i++){
        //do somethingto test setAttribute and getAttribute.
    }
    cfg.write(newfile);
}