//
// Author: Sharath Lokesh
//
#include <fstream>
#include <bitset>
#include <sstream>
#include <iomanip>
#include "HuffmanCodingUtilities.h"

using namespace std;

class CompressFile: public HuffmanCodingUtilities
{
    // Writes the compressed data to a file.
    void write_compressed_file(string encoded_string, string output_file_name, Node* root)
    {
        ofstream output_file(output_file_name, ios::binary);
        if (!output_file)
        {
            cout << "Error opening output file " << output_file_name << endl;
            output_file.close();
            return;
        }
        string tree_str;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty())
        {
            Node* curr = q.front();
            q.pop();
            // check for leaf node
            if (curr->data != '\0')
            {
                tree_str += curr->data;
            }
            else
            {
                // add $ for intermidiate nodes
                tree_str += '$';
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        cout << "\nTree string:\n" << tree_str << endl;
        stringstream ss;
        for (char c: tree_str)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
        }
        cout << "\nTree string in hex: " << ss.str() << endl;

        // Write the tree string to the output file
        output_file << ss.str() << endl;

        vector<bool> binary_encoded_data;
        // Convert the encoded string to binary
        for (char c: encoded_string)
        {
            binary_encoded_data.push_back(c == '1');
        }

        // Write the binary encoded data to the output file
        unsigned char byte = 0;
        int bitCount = 0;
        for (bool bit : binary_encoded_data) {
            byte = (byte << 1) | bit;
            bitCount++;
            if (bitCount == 8) {
                output_file.put(byte);
                byte = 0;
                bitCount = 0;
            }
        }
        // Flush any remaining bits
        if (bitCount > 0) {
            byte = byte << (8 - bitCount);
            output_file.put(byte);
        }

        // Close the output file
        output_file.close();
    }
public:
    // Compresses the input file and writes the compressed data to a file.
    void compress(string input_file_name, string output_file_name)
    {
        // Read the input file
        ifstream input_file(input_file_name);
        if (!input_file)
        {
            cout << "Error opening input file " << input_file_name << endl;
            input_file.close();
            return;
        }
        // Read the input string
        string input_string;
        while (input_file)
        {
            string line;
            getline(input_file, line);
            input_string += (line + "\n");
        }
        input_file.close();
        // Create the huffman tree
        Node* root = create_huffman_tree(input_string);
        // Print the codes of each character
        cout << "Huffman Codes:" <<  endl;
        print_code(root, "");
        // Encode the input string
        string encoded_string = encode(input_string, root);
        // Write the compressed data to a file
        write_compressed_file(encoded_string, output_file_name, root);
    }
};
int main()
{
    string input_file_name = "OriginalTextFile.txt";
    string output_file_name = "CompressedFile.bin";
    CompressFile cf = CompressFile();

    // Compresses the input file and writes the compressed data to a file.
    cf.compress(input_file_name, output_file_name);
    return 0;
}