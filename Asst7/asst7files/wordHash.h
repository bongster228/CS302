#include <string>

class wordHash {


public:


    wordHash();
    ~wordHash();

    void insert(std::string);                                   // Increment the word count if the item is
                                                                // already in the table and if not, use the private
                                                                // function to insert the word into the table.

    unsigned int getUniqueWordCount() const;                    // Returns the number of unique words in the hash table.
    
    unsigned int getWordCount(std::string) const;               // Looks for the passed in word in the hash table and returns the
                                                                // count of that word.

    bool incCount(std::string);                                 // Search the hash table for the passed string and, if found, 
                                                                // increment the word count associated with that string and return
                                                                // true. If the passed string is not found, then return false.
   
    void getMaxNode (unsigned int&, std::string&) const;        // Search for the word string associated with the largest count and
                                                                // return, via ref, the word string and count.
   
    void printHash() const;                                     // Print all non-empty entries in the hash table.

    void showHashStats() const;                                 // Print the current hash size, hash table resize count,
                                                                // and collision count.

    void printHashInOrder() const;
    


private:


    unsigned int hashSize;
    unsigned int reSizeCount;
    unsigned int collisionCount;
    unsigned int uniqueWordCount;


    std::string *wordList;
    unsigned int *wordCounts;

    static constexpr double loadFactor = 0.65;
    static constexpr int initialHashSize = 30011;

    void insert(std::string, unsigned int);                     // Insert the passed item into the hash table. If the hash
                                                                // table entries exceeds the load factor (count/tableSize),
                                                                // the thable must be rehashed via the private rehash(). The
                                                                // hash() must be used to determine the index of the insert
                                                                // location. If a collision occurs, the collision count should
                                                                // be incremented and the next() function should be called to
                                                                // implement quadratic probing. The appropriate counts should 
                                                                // be updated accordingly which may be called repeatedly. The
                                                                // collision count should be incremented appropriately.
    
    unsigned int hash(std::string) const;                       // Return a hash from the passed string. The returned hash
                                                                // must be mod'ed with the current hash size.


    unsigned int next(unsigned int, unsigned int) const;        // Should be called when there is a collision and should 
                                                                // implement the quadratic probing approach.
    
    void rehash();                                              // Create a new hash table approximately twice the size of the
                                                                // exsisting hash table, extract all entries from the current hash
                                                                // table, insert them into the new table, and delete the old table.
                                                                // The hash table resize counter should be updated. The new entries
                                                                // should be placed with the private insert() into the new hash table.
                                                                // If the resize value exceeds, display error message.



};