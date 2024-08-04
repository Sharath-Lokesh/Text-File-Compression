//
// Author: Sharath Lokesh
//
#include "HuffmanCodingUtilities.h"

// Main function
int main()
{
    string input_string = "1. He colored deep space a soft yellow.\n\
2. She learned that water bottles are no longer just to hold liquid, but they're also status symbols.\n\
3. She was disgusted he couldn't tell the difference between lemonade and limeade.\n\
4. He poured rocks in the dungeon of his mind.";

    HuffmanCodingUtilities hf = HuffmanCodingUtilities();

    // Create the huffman tree
    Node* root = hf.create_huffman_tree(input_string);
    // Print the codes of each character
    cout << "Huffman Codes:"<<endl;
    hf.print_code(root, "");

    // Encode the input string
    string encoded_string = hf.encode(input_string, root);
    cout << "\nEncoded string: " << encoded_string << endl;

    // Decode the encoded string
    string decoded_string = hf.decode(encoded_string, root);
    cout << "\nDecoded string:\n" << decoded_string << endl;

    return 0;
}
    