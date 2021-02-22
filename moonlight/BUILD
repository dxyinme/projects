cc_library(
    name = "moonlight",
    srcs = [
        "conn.cpp",
        "conn.h",
        "server.cpp",
        "server.h"
    ],
    hdrs = [
        "server.h"
    ],
    deps = [
        "#pthread",
        "#boost_system",
        "//moonlight:moonlight_request"
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
    name = "moonlight_request",
    srcs = [
        "request.cpp",
        "request.h",
    ],
    hdrs = [
        "request.h"
    ],
    deps = []
)

cc_binary(
    name = "client",
    srcs = [
        "client_main.cpp"
    ],
    deps = [
        "//moonlight:moonlight"
    ]
)

cc_binary(
    name = "test",
    srcs = [
        "test.cpp"
    ],
    deps = []
)