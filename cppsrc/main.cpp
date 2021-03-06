/* cppsrc/main.cpp */
#include <napi.h>
#include "xpath/xpathWrapper.h"


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return XpathWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
