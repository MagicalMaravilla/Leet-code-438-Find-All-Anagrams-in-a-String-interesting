#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Function to count characters in a string
std::unordered_map<char, int> countCharacters(const std::string& str) {
    std::unordered_map<char, int> characterCount;
    for (char ch : str) {
        characterCount[ch]++;
    }
    return characterCount;
}

// Function to find all anagrams of p in s
std::vector<int> findAnagrams(const std::string& s, const std::string& p) {
    std::vector<int> anagramStartIndices;
    if (s.length() < p.length()) return anagramStartIndices; // Return empty if p is longer than s

    // Count characters in p and the first window of s
    auto pCount = countCharacters(p);
    auto sCount = countCharacters(s.substr(0, p.length()));

    // Slide the window across s and check for anagrams
    for (size_t i = 0; i <= s.length() - p.length(); ++i) {
        if (i != 0) {
            // Update counts for the new window: add next character, remove the preceding character
            sCount[s[i + p.length() - 1]]++; // Add count for new character entering the window
            sCount[s[i - 1]]--; // Decrement count for character leaving the window
            
            // If the count goes to 0, erase the character to avoid mismatch due to missing keys
            if (sCount[s[i - 1]] == 0) {
                sCount.erase(s[i - 1]);
            }
        }

        // Check if current window is an anagram of p
        if (sCount == pCount) {
            anagramStartIndices.push_back(i);
        }
    }

    return anagramStartIndices;
}

int main() {
    std::string s = "cbaebabacd";
    std::string p = "abc";

    std::vector<int> anagramIndices = findAnagrams(s, p);

    std::cout << "Anagram start indices: ";
    for (int index : anagramIndices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return 0;
}
