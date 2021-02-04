#include "httpClient.h"

#include <cstring>
#include <string>
#include <iostream>
#include <mutex>

namespace client {
namespace httpClient {

std::mutex fn_mu;

static const char* s_s_url = "http://localhost";

std::string s_s_body, s_content_type;

std::string s_r_body ;

static void fn_get(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_CONNECT) {
        // Connected to server. Extract host name from URL
        struct mg_str host = mg_url_host(s_s_url);
        // Send request
        mg_printf(c,
                "GET %s HTTP/1.0\r\n"
                "Host: %.*s\r\n"
                "\r\n",
                mg_url_uri(s_s_url), (int) host.len, host.ptr);
    } else if (ev == MG_EV_HTTP_MSG) {
        // Response is received. Print it
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        // printf("%.*s", (int) hm->message.len, hm->message.ptr);
        s_r_body = std::string(hm->message.ptr, hm->message.len);
        c->is_closing = 1;
        *(bool *) fn_data = true;
    } else if (ev == MG_EV_ERROR) {
        *(bool *) fn_data = true;
    }
}

static void fn_post(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_CONNECT) {
        // Connected to server. Extract host name from URL
        struct mg_str host = mg_url_host(s_s_url);
        // Send request
        mg_printf(c,
                "POST %s HTTP/1.0\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %d\r\n"
                "Host: %.*s\r\n"
                "\r\n"
                "%s\r\n",
                mg_url_uri(s_s_url), s_content_type.c_str(), (int)s_s_body.size(), (int)host.len, host.ptr, s_s_body.c_str());
    } else if (ev == MG_EV_HTTP_MSG) {
        // Response is received. Print it
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        // printf("%.*s", (int) hm->message.len, hm->message.ptr);
        s_r_body = std::string(hm->message.ptr, hm->message.len);
        c->is_closing = 1;
        *(bool *) fn_data = true;
    } else if (ev == MG_EV_ERROR) {
        *(bool *) fn_data = true;
    }
}


http_client::http_client() {
    mg_mgr_init(&mgr);
}

void http_client::HTTP_GET() {
    fn_mu.lock();
    done = false;
    s_s_url = s_url.c_str();
    mg_http_connect(&mgr, s_s_url, fn_get, &done);
    while (!done) mg_mgr_poll(&mgr, 1000);
    r_body = s_r_body;
    fn_mu.unlock();
}

void http_client::HTTP_POST() {
    fn_mu.lock();
    done = false;
    s_s_url = s_url.c_str();
    s_s_body = s_body;
    s_content_type = content_type;
    mg_http_connect(&mgr, s_s_url, fn_post, &done);
    while (!done) mg_mgr_poll(&mgr, 1000);
    r_body = s_r_body;
    fn_mu.unlock();
}


http_client::~http_client() {
    mg_mgr_free(&mgr);
}

};
};