#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "functions.h"
#include <sstream>


int debug = 0;
using namespace std;
char ** file_name;
string bin_image;

string operations;
string r_source,r_target, r_dest;

void output_print(std::string opcode, std::string  rs, std::string rt, std::string rd) {

    std::cout<< opcode <<' ' << rd <<' ' << rs <<' ' << rt << '\n';
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }
    if (argc <= 0) {
            cout<< "Please Provide Name of File"<< endl;
            return -1;
        } else {
            //file_name = argv[1];
            //ifstream input_file(argv[1]);
          //  cout << file_name<<endl;
        } 
    //string file_name = argv[1];
    
    //ifstream input_file(file_name);
    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open the file \"" << file_name << "\" for reading." << std::endl;
        return 1;
    }

    std::string line;
    std::string hexnum, binum;

    while (file >> hexnum) {
        if (hexnum.size() != 8) {
            std::cerr << "Invalid hexadecimal number: " << hexnum << '\n';
            continue;
        }

        unsigned long num = std::stoul(hexnum, nullptr, 16);
        std::bitset<32> binary(num);
        binum = binary.to_string();

        Instruction instruction = imageSplitter(hexnum);
        std::cout << "Address: " << hexnum <<'\n';
        std::cout << "Opcode: " << instruction.opcode << '\n';
        std::cout << "Rs: " << instruction.rs << '\n';
        std::cout << "Rt: " << instruction.rt << '\n';
        std::cout << "Rd: " << instruction.rd << '\n';
        std::cout << "Shamt: " << instruction.shamt << '\n';
        std::cout << "Func: " << instruction.func << '\n';

        operations = op_directive(instruction.opcode);
        r_dest = whichRegister(instruction.rd);
        r_source = whichRegister(instruction.rs);
        r_target = whichRegister(instruction.rt);
        //std::cout << "Hexadecimal: " << hexnum << ", Binary: " << binum << '\n';
        output_print(operations, r_dest, r_source, r_target);
    }

}
/*********Functions**********/

/*
**This function convert the data from the tracefile to binary 
**and return the binary value as a string
*/
std::string hex2bin(std::string hexnum) {
    std::string binum;
    unsigned long num = std::stoul(hexnum, nullptr, 16);
    std::bitset<32> binary(num);
    binum = binary.to_string();
    std::cout << "Address: " << hexnum << ", Binary: " << binum << '\n';
    return binum;
}

/**R-type registers**/
Instruction imageSplitter(const std::string& hex) {
    unsigned long num = std::stoul(hex, nullptr, 16);
    std::bitset<32> binary(num);

    Instruction instruction;
    instruction.opcode = binary.to_string().substr(0, 6); //opcode
    instruction.rs     = binary.to_string().substr(6, 5); //source register
    instruction.rt     = binary.to_string().substr(11, 5); //target register
    instruction.rd     = binary.to_string().substr(16, 5); //dest register
    instruction.shamt  = binary.to_string().substr(21, 5); //shift amount
    instruction.func   = binary.to_string().substr(26, 6); //function

    return instruction;
}

//I types Registers
I_Instruction I_imageSplitter(const std::string& hex) {
    unsigned long num = std::stoul(hex, nullptr, 16);
    std::bitset<32> binary(num);

    I_Instruction instruction;
    instruction.opcode = binary.to_string().substr(0, 6); //opcode
    instruction.rs     = binary.to_string().substr(6, 5); //source register
    instruction.rt     = binary.to_string().substr(11, 5); //target register
    instruction.imm   = binary.to_string().substr(16, 16); //immidiate value

    return instruction;
}