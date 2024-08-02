//
// Author: Sharath Lokesh
//
#include "HuffmanCodingUtilities.h"

// Main function
int main()
{
    string input_string = "He colored deep space a soft yellow.\n\
She learned that water bottles are no longer just to hold liquid, but they're also status symbols.\n\
She was disgusted he couldn't tell the difference between lemonade and limeade.\n\
He poured rocks in the dungeon of his mind.";

    // Create the huffman tree
    Node* root = create_huffman_tree(input_string);
    // Print the codes of each character
    print_code(root, "");

    // Encode the input string
    string encoded_string = encode(input_string, root);
    cout << "Encoded string: " << encoded_string << endl;

    // Decode the encoded string
    string decoded_string = decode(encoded_string, root);
    cout << "Decoded string:\n" << decoded_string << endl;

    return 0;
}
    