#pragma once
#include <jsi/jsi.h>
#include <vector>
#include "JSIMacros.h"

namespace jsi = facebook::jsi;

typedef std::function<jsi::Value(jsi::Runtime &runtime)> JSIValueBuilder;

typedef std::pair<std::string, JSIValueBuilder> FieldDefinition;

FieldDefinition buildPair(std::string name, jsi::HostFunctionType &&f);


class JSI_EXPORT NativeQuickBuffer: public jsi::HostObject {

public:
    NativeQuickBuffer(int length);
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &runtime);
    jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &propNameId);
    std::vector<std::pair<std::string, JSIValueBuilder>> fields;
    std::vector<size_t> getData;

private:
    std::vector<size_t> data;
    
};
