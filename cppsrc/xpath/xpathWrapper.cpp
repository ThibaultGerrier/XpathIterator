#include "xpathWrapper.h"

Napi::FunctionReference XpathWrapper::constructor;

Napi::Object XpathWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "XpathWrapper", {
    InstanceMethod("getNumElems", &XpathWrapper::GetNumElems),
    InstanceMethod("getData", &XpathWrapper::GetData),
    InstanceMethod("free", &XpathWrapper::Free),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("XpathWrapper", func);
  return exports;
}

XpathWrapper::XpathWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<XpathWrapper>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 2 || !info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Invalid Input").ThrowAsJavaScriptException();
  }

  Napi::String xml = info[0].As<Napi::String>();
  Napi::String iterator = info[1].As<Napi::String>();
  this->xpathParser_ = new XpathParser(xml.ToString(), iterator.ToString());
}

Napi::Value XpathWrapper::GetNumElems(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int num = this->xpathParser_->getNumElems();

  return Napi::Number::New(env, num);
}


Napi::Value XpathWrapper::GetData(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 2 || !info[0].IsNumber() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Invalid input").ThrowAsJavaScriptException();
  }

  Napi::Number index = info[0].As<Napi::Number>();
  Napi::String selector = info[1].As<Napi::String>();
  std::vector<std::string> results = this->xpathParser_->getData(index, selector);

  int length = results.size();

  Napi::Array outputArray = Napi::Array::New(env, length);
  for (int i = 0; i < length; i++) {
    outputArray[i] = Napi::String::New(env, results[i]);
  }
  
  return outputArray;
}

Napi::Value XpathWrapper::Free(const Napi::CallbackInfo& info){
  delete this->xpathParser_;
  return Napi::Value();
}