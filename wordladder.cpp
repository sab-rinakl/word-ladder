#include "MinHeap.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void output(int steps, int expansions);

int get_h(string word2, string curr_word);

int priority(int g, int h, int len);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Incorrect number of arguments given." << endl;
        return 0;
    }

    MinHeap<string> minheap = MinHeap<string>(2);
    vector<string> words;
    map<string, int> g_vals;
    int steps = 0;
    int expansions = 0;
    string word1 = argv[1];
    string word2 = argv[2];
    if (word1.length() != word2.length()) {
        cout << "Starting and ending words are of different lengths." << endl;
        return 0;
    }
    for (size_t i = 0; i < word1.length(); i++) {
        word1[i] = toupper(word1[i]);
        word2[i] = toupper(word2[i]);
    }
    if (word1 == word2) {
        output(steps, expansions);
    }

    string filename = argv[3];
    ifstream ifs;
    ifs.open(filename);
    if (ifs.fail()) {
        cout << "Could not open file." << endl;
        return 0;
    }

    int n;
    ifs >> n;
    string temp;
    for (int i = 0; i < n; i++) {
        ifs >> temp;
        for (size_t i = 0; i < temp.length(); i++) {
            temp[i] = toupper(temp[i]);
        }
        if (temp.length() == word1.length()) {
            words.push_back(temp);
        }
    }

    string curr_word, temp_word;
    minheap.add(word1, priority(steps, get_h(word2, word1), word1.length()));
    g_vals[word1] = steps;
    while (!minheap.isEmpty()) {
        curr_word = minheap.peek();
        minheap.remove();
        if (curr_word == word2) {
            steps = g_vals[curr_word];
            break;
        } else {
            expansions++;
        }
        for (size_t i = 0; i < word1.length(); i++) {
            temp_word = curr_word;
            for (int j = 65; j <= 90; j++) {
                temp_word[i] = (char)j;
                for (size_t k = 0; k < words.size(); k++) {
                    if ((temp_word == words[k]) && (temp_word != curr_word)) {
                        if (g_vals.find(temp_word) == g_vals.end()) {
                            g_vals[temp_word] = g_vals[curr_word] + 1;
                            minheap.add(
                                    temp_word,
                                    priority(g_vals[temp_word], get_h(word2, temp_word), temp_word.length()));
                        } else if (g_vals[temp_word] > g_vals[curr_word]) {
                            g_vals[temp_word] = g_vals[curr_word] + 1;
                            minheap.updatePriority(
                                    temp_word,
                                    priority(g_vals[temp_word], get_h(word2, temp_word), temp_word.length()));
                        }
                    }
                }
            }
        }
    }

    if (curr_word == word2) {
        output(steps, expansions);
    } else {
        cout << "No transformation" << endl;
        cout << expansions << endl;
    }
}

void output(int steps, int expansions) {
    cout << steps << endl;
    cout << expansions << endl;
}

int get_h(string word2, string curr_word) {
    int h = 0;
    for (size_t i = 0; i < curr_word.length(); i++) {
        if (curr_word[i] != word2[i]) {
            h++;
        }
    }
    return h;
}

int priority(int g, int h, int len) { return ((g + h) * (len + 1) + h); }
