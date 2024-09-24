#include "ArduPar3.h"
ArduPar3Collection parameterCollection; // create a collection for parameters so we can conveniently do things with all of them at once

float someFloat=0; // we will controll the value of this number
SingleFloatArduPar3 someFloatParameter;

int32_t someInt=0;// we will controll the value of this number too
SingleInt32ArduPar3 someInt32Parameter;

// A function that can be triggered remotely to print all parameter states
void dumpFunction(){
    parameterCollection.dumpParameterInfos(&Serial);
}
CallbackArduPar3 dumpCallbackParameter;
// A function that can be triggered remotely to load parameter states
void loadFunction(){
    parameterCollection.loadAll();
}
CallbackArduPar3 loadCallbackParameter;

// A function that can be triggered remotely to save parameter states
void saveFunction(){
    parameterCollection.saveAll();
}
CallbackArduPar3 saveCallbackParameter;

void setup(){
    ArduPar3Collection::globalDefaultCollection=&parameterCollection; // use our parameter collection as a default
    // we use our own version of "F()" to work around the inconsistencies of the implementations on Arduino/ESP platforms.
    someFloatParameter.setup(ARDUPAR_F("/someFloat"),ARDUPAR_F("An exquisite float"),0,10,5,&someFloat);
    someInt32Parameter.setup(ARDUPAR_F("/someInt"),ARDUPAR_F("An exquisite integer"),0,10000,100,&someInt);
    dumpCallbackParameter.setup(ARDUPAR_F("/dump"),ARDUPAR_F("Print Parameter Summary"),&dumpFunction);
    loadCallbackParameter.setup(ARDUPAR_F("/load"),ARDUPAR_F("Load Settings."),&loadFunction);
    saveCallbackParameter.setup(ARDUPAR_F("/save"),ARDUPAR_F("Save Settings."),&saveFunction);
    Serial.begin(115200);
    delay(500);
    parameterCollection.dumpParameterInfos(&Serial);
}

void loop(){
    parameterCollection.updateParametersFromStream(&Serial,1000);
}

