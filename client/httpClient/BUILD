cc_library(
    name = "httpClient",
    srcs = [
        "httpClient.cpp",
        "httpClient.h"
    ],
    hdrs = [
        "httpClient.h"
    ],
    deps = [
        "//third_party/mongoose:mongoose"
    ]
)

cc_binary(
    name = "httpClient_example",
    srcs = [
        "example.cpp"
    ],
    deps = [
        "//client/httpClient:httpClient"
    ]
)