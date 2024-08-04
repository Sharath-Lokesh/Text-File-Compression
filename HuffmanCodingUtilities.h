//
// Author: Sharath Lokesh
//
#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <functional>

using namespace std;

// A node in the huffman tree
struct Node
{
    int freq;
    char data;
    Node *left, *right;
    // Constructor for the node
    Node(char data, int freq): data(data), freq(freq), left(NULL), right(NULL) {}
};

class HuffmanCodingUtilities
{
    // Comparison function for the priority queue
    std::function<bool(Node*, Node*)> compare = [](Node* l, Node* r) 
    {
        return (l->freq > r->freq);
    };

public:
    // Utility function to create a huffman tree from a given string
    Node* create_huffman_tree(string input_string)
    {
        priority_queue<Node*, vector<Node*>, decltype(compare)> pq(compare);
        map <char, int> freq;
        // Count the frequency of each character
        for(int i = 0; i < input_string.length(); ++i)
        {
            freq[input_string[i]]++;
        }
        // Create a node for each character and push it into the priority queue
        for(auto it = freq.begin(); it != freq.end(); ++it)
        {
            pq.push(new Node(it->first, it->second));
        }
        // Construct the huffman tree
        while(pq.size() > 1)
        {
            // Get the two nodes with the lowest frequency and remove them from the queue
            Node* left = pq.top();
            pq.pop();
            Node* right = pq.top();
            pq.pop();
            // Create a new internal node with the sum of the frequencies of the two nodes
            Node* parent = new Node('\0', left->freq + right->freq);
            // Set the left and right child of the new node
            parent->left = left;
            parent->right = right;
            // Push the new node into the queue
            pq.push(parent);
        }
        // Return the root of the huffman tree
        return pq.top();
    }

    // Utility function to store the codes of each character in a map
    void store_code(Node* root, string str, map<char, string>& codes)
    {   
        if(NULL == root)
            return;

        // If the node is a leaf node, store the code in the map
        if(root->data != '\0')
            codes[root->data] = str;

        // Recursively store the codes of the left and right sub-trees
        store_code(root->left, str + "0", codes);
        store_code(root->right, str + "1", codes);
    }

    // Utility function to print the codes of each character
    void print_code(Node* root, string str)
    {
        if(NULL == root)
            return;

        // If the node is a leaf node, print the code
        if(root->data != '\0')
            cout << root->data << ": " << str << endl;

        // Recursively print the codes of the left and right sub-trees
        print_code(root->left, str + "0");
        print_code(root->right, str + "1");
    }

    // Utility function to encode the input string
    string encode(string input_string, Node* root)
    {
        // Store the codes of each character in a map
        string encoded_string = "";
        map <char, string> huffman_codes;
        store_code(root, "", huffman_codes);

        // Encode the input string
        for(int i = 0; i < input_string.length(); ++i)
        {
            encoded_string += huffman_codes[input_string[i]];
        }

        // Return the encoded string
        return encoded_string;
    }

    // Utility function to decode the encoded string
    string decode(string encoded_string, Node* root)
    {
        // Decode the encoded string
        string decoded_string = "";
        Node* curr = root;

        // Traverse the encoded string
        for(int i = 0; i < encoded_string.length(); ++i)
        {
            if(encoded_string[i] == '0')
                curr = curr->left;
            else
                curr = curr->right;

            // If the current node is a leaf node,
            if(NULL == curr->left && NULL == curr->right)
            {
                decoded_string += curr->data;
                curr = root;
            }
        }
        // Return the decoded string
        return decoded_string;
    }
};
