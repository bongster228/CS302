#include "wordHash.h"

class wordCount: public wordHash {

public:
    
    wordCount();
    bool getArguments(int, char *[], std::string&, bool&);
    bool readDocument(const std::string);

    std::string wordCheck(std::string);

    void showDocumentFileName() const;

    void showTotalWordCount() const;                    // Display the formatted total word count

    void showUniqueWordCount() const;                   // Show the formatted unique word count by calling
                                                        // the wordHash countNodes() function.

    void showStats() const;                             // Dispaly stats by calling showHashStats() function

    void getMaxWord(unsigned int&, std::string&);       // Return the largest word count and the word by ref.

    void printWordCounts() const;
    
    unsigned int getWordCount(std::string) const;       // Return the count of the passed in word by calling the 
                                                        // base class function. Since the words are all lower case, must
                                                        // search for only lower case words.

private:

    unsigned int totalWordCount;
    std::string docFileName;
};