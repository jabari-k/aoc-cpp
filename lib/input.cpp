#include "input.h"
#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdexcept>
#include <string>
#include <fstream>

std::string get_aoc_session_key() {
  std::ifstream ifs("../session.txt");
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
  return content;
}

size_t write_cb(void *ptr, size_t size, size_t nmemb, std::string *buf) {
  buf->append((const char*) ptr, size * nmemb);
  return size * nmemb;
}

std::string download_input(const char* year, const char* problem_number) {
  char url[256];
  std::snprintf(url, 256, "https://adventofcode.com/%s/day/%s/input", year, problem_number);

  CURL *curl = curl_easy_init();
  CURLcode res;
  std::string buf;
  if (curl) {
    std::string aoc_session_key = get_aoc_session_key();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
    curl_easy_setopt(curl, CURLOPT_COOKIE, aoc_session_key.c_str());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      throw std::runtime_error("download_input: curl failed");
    }
    curl_easy_cleanup(curl);
  }
  return buf;
}
