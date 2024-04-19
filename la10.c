//Alexander Moreno
//4-19-24
//COP3502

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie Node
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
};

// Initialize a new Trie Node
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;
    node->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    trie->root = createTrieNode();
    return trie;
}

// Inserts the word into the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *current = pTrie->root;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
    current->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct TrieNode *current = pTrie->root;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}

// Helper function to deallocate the trie nodes recursively
void deallocateTrieHelper(struct TrieNode *node) {
    if (node == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        deallocateTrieHelper(node->children[i]);
    }
    free(node);
}

// Deallocate the trie structure
void deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) return;
    deallocateTrieHelper(pTrie->root);
    free(pTrie);
}

// This function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, struct Trie *pTrie, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(1);
    }

    int count = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[count] = strdup(word);
        insert(pTrie, word);
        count++;
    }

    fclose(file);
    return count;
}

int main(void) {
    struct Trie *pTrie = createTrie();
    char *inWords[256];

    //dictionary and insert into Trie.
    int numWords = readDictionary("dictionary.txt", pTrie, inWords);

    //display words from the file.
    for (int i = 0; i < numWords; i++)
    {
        printf("%s\n", inWords[i]);
    }

    //word occurrences.
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    //deallocate the trie.
    deallocateTrie(pTrie);

    return 0;
}
