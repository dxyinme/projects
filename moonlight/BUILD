cc_library(
    name = "moonlight_base",
    srcs = [
        
    ],
    hdrs = [
    ],
    deps = [
        "#boost_system",
        "#pthread"
    ]
)

cc_library(
    name = "tcp_conn",
    srcs = [
        "tcp_conn.cpp",
        "tcp_conn.h"
    ],
    hdrs = [
        "tcp_conn.h"
    ],
    deps = [
        "//moonlight:moonlight_base"
    ]
)

cc_library(
    name = "tcp_server",
    srcs = [
        "tcp_server.cpp",
        "tcp_server.h"
    ],
    hdrs = [
        "tcp_server.h"
    ],
    deps = [
        "//moonlight:tcp_conn",
    ]
)

cc_binary(
    name = "tcp_server_example",
    srcs = [
        "tcp_server_example.cpp"
    ],
    deps = [
        "//moonlight:tcp_server"
    ]
)