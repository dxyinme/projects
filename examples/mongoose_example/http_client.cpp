#include <mongoose/mongoose.h>

static const char *s_url = "http://localhost";

// Print HTTP response and signal that we're done
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_CONNECT) {
        // Connected to server. Extract host name from URL
        struct mg_str host = mg_url_host(s_url);
        // Send request
        mg_printf(c,
                "GET %s HTTP/1.0\r\n"
                "Host: %.*s\r\n"
                "\r\n",
                mg_url_uri(s_url), (int) host.len, host.ptr);
    } else if (ev == MG_EV_HTTP_MSG) {
        // Response is received. Print it
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        printf("%.*s", (int) hm->message.len, hm->message.ptr);
        c->is_closing = 1;
        *(bool *) fn_data = true;
    } else if (ev == MG_EV_ERROR) {
        *(bool *) fn_data = true;
    }
}

int main(int argc, char *argv[]) {
    struct mg_mgr mgr;                        // Event manager
    bool done = false;                        // Event handler flips it to true
    if (argc > 1) s_url = argv[1];            // Use URL from command line
    mg_log_set("3");                          // Set to 0 to disable debug
    mg_mgr_init(&mgr);                        // Initialise event manager
    mg_http_connect(&mgr, s_url, fn, &done);  // Create client connection
    while (!done) mg_mgr_poll(&mgr, 1000);    // Infinite event loop
    mg_mgr_free(&mgr);                        // Free resources
    return 0;
}