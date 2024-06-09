#include "QuickBufferHostObject.hpp"
#include "NativeQuickBuffer.hpp"

std::vector<jsi::PropNameID> QuickBufferHostObject::getPropertyNames(
    jsi::Runtime &runtime)
{
    std::vector<jsi::PropNameID> propertyNames;
    for (auto field : fields)
    {
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, field.first));
    }
    return propertyNames;
}


jsi::Value QuickBufferHostObject::get(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
    auto name = propNameId.utf8(runtime);
    for (auto field : fields)
    {
        auto fieldName = field.first;
        if (fieldName == name)
        {
            return (field.second)(runtime);
        }
    }
    return jsi::Value::undefined();
    }

FieldDefinition buildPair(std::string name, jsi::HostFunctionType &&f) {
      auto valueBuilder = [f, name](jsi::Runtime &runtime) {
        const auto func = f;
        auto propNameID = jsi::PropNameID::forAscii(runtime, name);
        return jsi::Function::createFromHostFunction(runtime, propNameID, 0, func);
      };
    return std::make_pair(name, valueBuilder);
}


QuickBufferHostObject::QuickBufferHostObject() {
    this->fields.push_back(HOST_LAMBDA("createNativeQuickBuffer", {
            
        if (!arguments[0].isNumber()) {
            throw new jsi::JSError(runtime, "missing length param");
        }
        
        int length = (int)arguments[0].asNumber();
        auto o = std::make_shared<NativeQuickBuffer>(length);
        return jsi::Object::createFromHostObject(runtime, o);
    }));
    
    this->fields.push_back(HOST_LAMBDA("getRawBuffer", {
        std::shared_ptr<NativeQuickBuffer> thiz = thisValue.getObject(runtime).getHostObject<NativeQuickBuffer>(runtime);
       
        int length = (int)arguments[0].asNumber();
        auto o = std::make_shared<NativeQuickBuffer>(length);
        return jsi::Object::createFromHostObject(runtime, o);
    }));
}
