#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "functions.h"
#include <sstream>
#include <vector>
using namespace std;

int debug = 0;
char ** file_name;
string bin_image;

string operations;
string r_source,r_target, r_dest;



Instruction operating( std::string& rs, std::string& rt,std::string& rd,std::string& opcode);
I_Instruction operating_I( std::string& rs, std::string& rt,std::string& imm,std::string& opcode);
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
	  I_Instruction i_instruction = I_imageSplitter(hexnum);
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
        operating( instruction.rs, instruction.rt,instruction.rd,instruction.opcode);
	  operating_I(i_instruction.rs, i_instruction.rt,i_instruction.imm,i_instruction.opcode);
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

//operating function
// for R type
Instruction operating( std::string& rs, std::string& rt,std::string& rd,std::string& opcode){
	Instruction instruction;
	instruction.rs = rs;
 	instruction.rd = rd;
    	instruction.rt = rt;
	instruction.opcode = opcode;
	
	if(stoi(opcode,0,2) == ADD) {

		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int result = rs_val + rt_val;
		cout<< "Result :"<< result<< endl;
        	instruction.rd = std::bitset<5>(result).to_string();
		cout<< "result for storing Rd:" << instruction.rd<<endl;		
	}

	if(stoi(opcode,0,2) == SUB){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int result = rs_val - rt_val;
		cout<< "Result :"<< result<< endl;
		instruction.rd =std::bitset<5>(result).to_string();
		cout<< "Result for storing Rd:" << instruction.rd<<endl;
	}	
	if(stoi(opcode,0,2) == MUL){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int result = rs_val * rt_val;
		cout<< "Result :"<< result<< endl;
		instruction.rd = std:: bitset<5>(result).to_string();
		cout<< "result for storing Rd:" << instruction.rd<<endl;
	}
	if(stoi(opcode,0,2) == OR){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int result = rs_val || rt_val;
		cout<< "Result :"<< result<< endl;
		instruction.rd = std:: bitset<5>(result).to_string();
		cout<< "Result for storing Rd:"<< instruction.rd<<endl;
		
	}
	if(stoi(opcode,0,2) == AND){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int result = rs_val && rt_val;
		cout<< "Result :"<< result<< endl;
		instruction.rd = std:: bitset<5>(result).to_string();
		cout<< "Result for storing Rd:"<< instruction.rd<<endl;
		
	}
	if(stoi(opcode,0,2) == XOR){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int result = rs_val ^ rt_val;
		cout<< "Result :"<< result<< endl;
		instruction.rd = std::bitset<5>(result).to_string();
		cout<< "Result for storing Rd:"<< instruction.rd<<endl;
		
	}
return instruction;
	

}

//for I type
I_Instruction operating_I( std::string& rs, std::string& rt,std::string& imm,std::string& opcode){
	I_Instruction i_instruction;
	i_instruction.rs = rs;
 	i_instruction.rt = rt;
        i_instruction.imm = imm;
	i_instruction.opcode = opcode;
	
	if(stoi(opcode,0,2) == ADDI) {
		
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int result = imm_val + rs_val;
		cout<< "Result :"<< result<< endl;
                i_instruction.rt = std::bitset<5>(result).to_string();
		cout<< "Result for storing Rt:" << i_instruction.rt<<endl;	
	}

	if(stoi(opcode,0,2) == SUBI){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int result = rs_val - imm_val;
		cout<< "Result :"<< result<< endl;
		i_instruction.rt = std:: bitset<5>(result).to_string();
		cout<< "Result for storing Rt:"<< i_instruction.rt<<endl;

	}	

	if(stoi(opcode,0,2) == MULI){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int result = rs_val * imm_val;
		cout<< "Result :"<< result<< endl;
		i_instruction.rt = std:: bitset<5>(result).to_string();
		cout<< "Result for storing Rt:"<<i_instruction.rt<<endl;
	}

	if(stoi(opcode,0,2) == ORI){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int result = rs_val || imm_val;
		cout<< "Result :"<< result<< endl;
		i_instruction.rt = std:: bitset<5>(result).to_string();
		cout<< "Result for storing Rt:"<<i_instruction.rt<<endl;
	}

	if(stoi(opcode,0,2) == ANDI){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int result = rs_val && imm_val;
		cout<< "Result :"<< result<< endl;
		i_instruction.rt = std:: bitset<5>(result).to_string();
		cout<< "Result for storing Rt:"<<i_instruction.rt<<endl;
	}

	if(stoi(opcode,0,2) == XORI){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int result = rs_val ^ imm_val;
		cout<< "Result :"<< result<< endl;
		i_instruction.rt = std:: bitset<5>(result).to_string();
		cout<< "Result for stroing Rt:"<<i_instruction.rt<<endl;
		
	}

	if(stoi(opcode,0,2) == LDW){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int address = rs_val + imm_val;
		//int contents = memory[address]; 
		//rt_val = contents;
		//cout<< "Result :"<< address << endl;
		
	}

	if(stoi(opcode,0,2) == STW){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		int result = rs_val + imm_val;
		cout<< "Result :"<< result<< endl;
		
	}

	if(stoi(opcode,0,2) == BZ){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		if(rs_val == 0){
			cout<< "Result: "<<endl;
		}
	
		
	}

	if(stoi(opcode,0,2) == BEQ){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		if(rs_val == rt_val){
		//need to implement logic branch
		cout<< "Result :"<< endl;
		}
	}

	if(stoi(opcode,0,2) == JR){
		int rs_val = stoi(rs,0,2);
		int rt_val = stoi(rt,0,2);
		int imm_val = stoi(imm,0,2);
		//load PC with the content of register RS
		//need to implement the logic to update program counter (PC)
		//based on the value of rs_val
		
	}

	if(stoi(opcode,0,2) == HALT){
		
		cout<< "Result: HALT!!! "<< endl;
		
	}

return i_instruction;
	

}
