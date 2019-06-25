#include <napi.h>
#include "xpathParser.h"

class XpathWrapper : public Napi::ObjectWrap<XpathWrapper> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports); 
  XpathWrapper(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  Napi::Value GetNumElems(const Napi::CallbackInfo& info); 
  Napi::Value GetData(const Napi::CallbackInfo& info); 
  Napi::Value Free(const Napi::CallbackInfo& info);
  XpathParser *xpathParser_; 
};