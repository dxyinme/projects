cc_library(
    name = "moonlight",
    srcs = [
        "conn.cpp",
        "conn.h",
        "server.cpp",
        "server.h",
        "client.cpp",
        "client.h"
    ],
    hdrs = [
        "conn.h",
        "server.h",
        "client.h"
    ],
    deps = [
        "#pthread",
        "#boost_system",
        
        "//moonlight:request",
        "//moonlight:response",
        "//moonlight:handler"
    ]
)


cc_library(
    name = "common",
    srcs = [
        "common.h"
    ],
    hdrs = [
        "common.h"
    ],
    deps = []
)

cc_library(
    name = "response",
    srcs = [
        "response.cpp",
        "response.h"
    ],
    hdrs = [
        "response.h"
    ],
    deps = [
        "//moonlight:common"
    ]
)

cc_library(
    name = "handler",
    srcs = [
        "handler.cpp",
        "handler.h"
    ],
    hdrs = [
        "handler.h"
    ],
    deps = [
        "//moonlight:common"
    ]
)

cc_binary(
    name = "server",
    srcs = [
        "server_main.cpp"
    ],
    deps = [
        "//moonlight:moonlight"
    ]
)

cc_library(
    name = "request",
    srcs = [
        "request.cpp",
        "request.h",
    ],
    hdrs = [
        "request.h"
    ],
    deps = [
        "//moonlight:common"
    ]
)

cc_binary(
    name = "client",
    srcs = [
        "client_main.cpp"
    ],
    deps = [
        "//moonlight:moonlight",
        "//moonlight:common"
    ]
)

cc_binary(
    name = "test",
    srcs = [
        "test.cpp"
    ],
    deps = []
)