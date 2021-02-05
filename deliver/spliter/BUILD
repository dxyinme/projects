cc_library(
    name = "spliter",
    srcs = [
        "spliter.h",
        "spliter.cpp"
    ],
    hdrs = [
        "spliter.h"
    ],
    deps = [
        "//util/md5:md5",
        "//util/string_utils:string_utils"
    ]
)

cc_binary(
    name = "spliter_test",
    srcs = [
        "spliter_test.cpp"
    ],
    deps = [
        "//deliver/spliter:spliter"
    ]
)

cc_binary(
    name = "spliter_client",
    srcs = [
        "spliter_client.cpp"
    ],
    deps = [
        "//deliver/spliter:spliter"
    ]
)