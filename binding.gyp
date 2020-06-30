{
    "targets": [{
        "target_name": "xpathWrapper",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "cppsrc/main.cpp",
            "cppsrc/xpath/xpathParser.cpp",
            "cppsrc/xpath/xpathWrapper.cpp",
            "cppsrc/pugixml/src/pugixml.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
        'conditions': [
        [
          'OS=="mac"', {
            'xcode_settings': {
              'OTHER_CFLAGS': [
                '-mmacosx-version-min=10.7',
                '-std=c++11',
                '-stdlib=libc++'
              ],
              'GCC_ENABLE_CPP_RTTI': 'YES',
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
            }
          }
        ]
      ]
    }]
}