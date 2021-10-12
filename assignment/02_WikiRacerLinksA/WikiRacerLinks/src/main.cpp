#include <iostream>
#include <fstream>
#include <unordered_set>
#include<algorithm>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;


bool search_pred(char a, char b) {
    if (a == b) {
        return true;
    }
    return false;
}

unordered_set<string> findWikiLinks(const string& page_html) {
    unordered_set<string> result;
    const string& pattern = "<a href=\"/wiki/";
    auto ita = page_html.begin();
    while ((ita = std::search(ita, page_html.end(), pattern.begin(), pattern.end(), search_pred)) != page_html.end()) {
        ita = ita + 15; // pass the pattern string, go to the PAGENAME.
        auto itb = ita;
        string pagename = "";
        bool invalid = false; // if the PAGENAME is valid.
        while ((itb < page_html.end()) && (*itb != '\"')) {
            pagename = pagename + *itb;
            if ((*itb == '#') || (*itb == ':')) {
                invalid = true;
            }
            ++itb;
        }
        if (itb == page_html.end()) {
            break;
        }
        ita = itb;
        if (invalid) {
            continue;
        }
        result.insert(pagename);
    }
    return result;
}

int main() {
    cout << "in main\n";
    std::ifstream in("sking.txt", std::ifstream::in);
    cout << "initialize ifstream";
    string file_content;
    string line;
    while (in) {
        std::getline(in, line);
        file_content = file_content + line;
    }
    unordered_set<string> result = findWikiLinks(file_content);
    for (auto s : result) {
        cout << s << endl;
    }


    /* TODO: Write code here! */

    /* Note if your file reading isn't working, please follow the
     * steps posted on the front page of the CS106L website. Essentially
     * go to the projects tab on the panel on the left, and in the run
     * section, uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */

}
