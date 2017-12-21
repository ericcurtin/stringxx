#include <string>
#include <functional>
#include <algorithm>

#include <openssl/crypto.h>

using std::string;
using std::ptr_fun;
using std::find_if;

void replace_all(string& str,
                 const string& from,
                 const string& to) {
  // Prevents infinite loops
  if (from.empty()) {
     return;
  }

  for (size_t pos = 0; (pos = str.find(from, pos)) != string::npos;) {
    str.replace(pos, from.length(), to);
    pos += to.length();
  }
}

// Clean C++ string internal buffer
void cleanse(string& str) {
  str.resize(str.capacity(), '\0');
  OPENSSL_cleanse(&str[0], str.size());
  str.clear();
}

void ltrim(string& str) {
  str.erase(str.begin(),
            find_if(str.begin(),
                    str.end(),
                    not1(ptr_fun<int, int>(isspace))));
}

void rtrim(string& str) {
  str.erase(find_if(str.rbegin(),
                    str.rend(),
                    not1(ptr_fun<int, int>(isspace))).base(),
            str.end());
}

void trim(string &str) {
  ltrim(str);
  rtrim(str);
}

void lower(string& str) {
  transform(str.begin(), str.end(), str.begin(), tolower);
}

void upper(string& str) {
  transform(str.begin(), str.end(), str.begin(), toupper);
}

