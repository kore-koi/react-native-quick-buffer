#include "NativeQuickBuffer.hpp"

std::vector<jsi::PropNameID> NativeQuickBuffer::getPropertyNames(
    jsi::Runtime &runtime)
{
    std::vector<jsi::PropNameID> propertyNames;
    for (auto field : fields)
    {
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, field.first));
    }
    return propertyNames;
}


jsi::Value NativeQuickBuffer::get(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
    auto name = propNameId.utf8(runtime);
    if (name == "0") {
        return jsi::Value(runtime, 54);
    }
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


NativeQuickBuffer::NativeQuickBuffer(int length): data(length, 0) {
    this->fields.push_back(HOST_LAMBDA("ciao", {
        return jsi::Value(runtime, 12);
    }));
}

