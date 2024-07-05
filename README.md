# A Magical Keyboard

#### Contributor: Dumitrascu Filip-Teodor

## General description:
    The program is based on working with strings that have letters stored in a trie. The efficiency of this data structure is to perform operations on words that have a common prefix because in a string the storage of common letters is not done separately. Thus, the following operations are implemented:

## Commands: 

### trie_create() / trie_create_node() 
    Initializes the memory for a new trie/node struct and returns a pointer to it.

### trie_free_subtrie() / trie_free()
    Frees the memory used by a subtire/trie.

### trie_insert()
    Takes letter by letter from the input word and inserts them in the trie creating a node for each one. If the word is already inserted in the trie, increments it s counter by one.

### trie_remove()
    If the word given as input to be deleted is a prefix for anaother word, the function only sets the end_od_word counter to 0. If not, calls the trie_free_subtrie function to remove the word. 

### load_file() 
    Reads word by word from a file and inserts the word in the trie.

### autocorrect(), dfs_autocorrect()
    Within a limit of characters different from the word received as input the function calls a dfs to traverse all nodes and display words with up to k different letters. At each recursion it checks whether the letter matches or not and increments the count of different characters up to that point.

### autocomplete, dfs_lexico(), dfs_shortest(), dfs_frequent()
    If the prefix exists in the trie it can at least be a word in itself, without any other characters in the word in which it is included. Thus, the characters of the prefix are iterated. If the node exists calls a dfs function specific to the autocomplete criterion and if not it means that there is no node that can complete the criterion.

    * lexico - Knowing that all children of a node are in lexicographic order, go through each array of children from 'a' to 'z' and at the first word found, the ok variable takes the value 1 to ignore the other iterations in the recursive calls and to exit the function 

    * shortest - Goes through each subtrie of the root until the whole words are found. Their length is compared each time, the word as output being longer than the prefix but shorter than any other word.

    * frequent - Goes through all the words in the trie and selects the one with the highest number of appearances.


# kNN system

## General description:
    The program is based on working with point's coordinates implementing a k-dimensional system. This data structure is similar with a binary search tree. The only difference is that when comparing the value in the node to insert to the left or to the right this value on the next level, takes into account the current level and choose the specific coordinate for comparison. Thus, the following operations are implemented:

## Commands: 

### bst_create() / bst_create_node() 
    Initializes the memory for a new bst/node struct and returns a pointer to it.

### bst_insert_node()
    With the coordinates received as input creates a node and iterates through them to determine where it is situated (left or right) on the next level. This is how the levels are browsed and the node is inserted as a leaf in the bst.

### bst_free_tree() / bst_free_subtree()
    Frees the memory used by a subtree/tree.

### load_file() 
    Reads coordonate by coordonate from a file and inserts the point in the bst

### distance()
    Calculates the euclidian distance between two nodes.

### closest()
    Returns he node closest to the target node.
    
### nn()
    Selects the subtrie which can have the nearest neighbour
    and finds a temporary nearest node to compare it's distance
    with the previous one. After all the comparisions have been made returns the nearest one.

### is_outside_range()
    Checks if a node coordinates is outside a given range

### rs()
    Prints all the nodes that are in the given range.
