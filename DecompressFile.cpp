//
// Author: Sharath Lokesh
//
#include <fstream>
#include <bitset>
#include "HuffmanCodingUtilities.h"
#include <stack>

using namespace std;

class DecompressFile:public HuffmanCodingUtilities
{
    // Get the Tree String from the compressed file
    string readTreeString(ifstream& inputFile) 
    {
        string treeStringhex;
        getline(inputFile, treeStringhex);
        string treeString;
        treeString.reserve(treeStringhex.length()/2);

        for  (int i = 0; i < treeStringhex.length(); i+=2) 
        {
            string byte_str = treeStringhex.substr(i, 2);
            char byte = (char)strtol(byte_str.c_str(), nullptr, 16);
            treeString.push_back(byte);
        }
        cout << "Tree String:\n" << treeString << endl;
        return treeString;
    }

    // Get the encoded data from the compressed file
    string readEncodedData(ifstream& inputFile) {
        string encodedString;
        char byte;
        while (inputFile.read(&byte, 1)) {
            for (int i = 7; i >= 0; --i) {
                encodedString += ((byte >> i) & 1) ? '1' : '0';
            }
        }
        return encodedString;
    }

    //Recursively prints the data of each node in a binary tree, starting from the root.
    void printTree(Node* root) {
        if (root == nullptr)
            return;

        cout << root->data << " ";
        printTree(root->left);
        printTree(root->right);
    }

    // Calculates the index of the left child of a node in the Huffman tree.
    int leftIdx(int i, int leafNode_count) { return 2 * i + 1 - (2*leafNode_count); }

    // Calculates the index of the right child of a node in the Huffman tree.
    int rightIdx(int i, int leafNode_count) { return 2 * i + 2- (2*leafNode_count); }

    // Create the huffman tree from the tree string
    Node* create_huffman_tree(ifstream& inputFile)
    {
        string tree_string = readTreeString(inputFile);
        vector<Node*> v;
        // Create node for each value - \0 for intermidiate nodes and char for leaf nodes
        for (int i=0; i<tree_string.length(); ++i)
        {
            Node*  node;
            if (tree_string[i] == '$')
                node = new Node('\0', 0);
            else
                node = new Node(tree_string[i], -1);
            v.push_back(node);
        }
        int leaf_count = 0;
        int l_idx, r_idx;
        for (int i=0; i<v.size(); ++i)
        {
            // Skip the leaf nodes
            if(v[i]->freq == -1)
            {
                leaf_count++;
                continue;
            }
            // Set the left and right child of the intermidiate node 
            l_idx = leftIdx(i, leaf_count);
            r_idx = rightIdx(i, leaf_count);
            if (l_idx < v.size())
                v[i]->left = v[l_idx];
            if (r_idx < v.size())
                v[i]->right = v[r_idx];
        }
        // return the root of the huffman tree
        return v[0];
    }
public:
    // Decompresses the data from the input file using Huffman coding and writes the
    // decoded data into a new text file.
    void decompress(string input_file_name, string output_file_name)
    {
        ifstream  in_file(input_file_name, ios::binary);
        if (!in_file) 
        {
            cout << "Error opening file for reading" << endl;
            in_file.close();
            return;
        }
        // Create Huffman Tree
        Node* root = create_huffman_tree(in_file);
        string encoded_data = readEncodedData(in_file);
        // Decode the compressed data against the Huffman Tree
        string decoded_string = decode(encoded_data, root);
        in_file.close();

        ofstream out_file(output_file_name);
        if (!out_file)
        {
            cout << "Error opening file for writing" << endl;
            out_file.close();
            return;
        }
        // Write the decoded data into a new text file
        out_file << decoded_string;
        out_file.close();
        cout << "\nDecompressed data successfully written to " << output_file_name << endl;
    }
};
int main()
{
    string input_file_name = "CompressedFile.bin";
    string output_file_name = "DeCompressedFile.txt";
    DecompressFile df = DecompressFile();
    df.decompress(input_file_name, output_file_name);
    return 0;
}