cc_binary(
    name = "io_service_test",
    srcs = [
        "io_service_test.cpp"
    ],
    deps = [
        "#boost_system",
        "#pthread"
    ]
)


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
        "//moonlight:handler",
        "//moonlight:moonlight_base"
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
        "//moonlight:tcp_conn",
        "//moonlight:moonlight_base"
    ]
)

cc_binary(
    name = "tcp_server_example",
    srcs = [
        "tcp_server_example.cpp"
    ],
    deps = [
        "//moonlight:tcp_server",
        "//util/flags:flags"
    ]
)

cc_binary(
    name = "tcp_client_example",
    srcs = [
        "tcp_client_example.cpp"
    ],
    deps = [
        "//moonlight:tcp_conn"
    ]
)