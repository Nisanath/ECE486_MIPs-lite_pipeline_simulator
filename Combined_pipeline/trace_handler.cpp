#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <bitset>
#include "functions.h"
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int debug = 1;
int counter = 0;
char ** file_name;
string bin_image;

string operations;
string r_source,r_target, r_dest, r_imm;
int R[32] = {0};
/*operations for R-type*/
Instruction operating( std::string& rs, std::string& rt,
                        std::string& rd,std::string& opcode); 
/*operations for I-type*/
I_Instruction I_operating( std::string& rs, std::string& rt,
                        std::string& imm,std::string& opcode);

void output_print(std::string opcode, std::string rd, std::string  rs, std::string rt) {

    std::cout<< opcode <<' ' << rd <<' ' << rs <<' ' << rt << endl;
}

void I_output_print(std::string opcode, std::string rs, std::string  rt, std::string imm) {

    std::cout<< opcode <<' ' << rs <<' ' << rt <<' ' << stoi(imm,0,2) << endl;
}

int main(int argc, char* argv[]) {

   //if (argc != 2 && strcmp(argv[2], "1") == 0 ) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }
   // if(strcmp(argv[2], "1") == 0)
      //  debug = 1;
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
    std::vector<Instruction> instructions;

    while (file >> hexnum) {
        if (hexnum.size() != 8) {
            std::cerr << "Invalid hexadecimal number: " << hexnum << '\n';
            continue;
        }
        cout << "PC:" << counter << '\n';
        counter++;
        unsigned long num = std::stoul(hexnum, nullptr, 16);
        std::bitset<32> binary(num); //convert num and store in binary
        
       
        binum = binary.to_string();

        std::string type_select = binum.substr(0,6);
        Instruction instruction = imageSplitter(hexnum);
        I_Instruction I_instruction = I_imageSplitter(hexnum);

        if (debug == 1) {
            std::cout << "Address: " << hexnum <<'\n';
            std::cout << "Opcode: " << instruction.opcode << '\n';
            std::cout << "Rs: " << instruction.rs << '\n';
            std::cout << "Rt: " << instruction.rt << '\n';
            std::cout << "Rd: " << instruction.rd << '\n';
            //std::cout << "Shamt: " << instruction.shamt << '\n';
           // std::cout << "Func: " << instruction.func << '\n';
        }

        //this check if it's R-type or I-type
        if (stoi(type_select,0,2) >= 0 && stoi(type_select,0,2)  < 13) {
            if (stoi(type_select,0,2) % 2 == 0) {

                std::cout << "R-type" << std::endl;
                operating( instruction.rs, instruction.rt,instruction.rd,
                            instruction.opcode);

                operations = op_directive(instruction.opcode);
                r_dest = whichRegister(instruction.rd);
                r_source = whichRegister(instruction.rs);
                r_target = whichRegister(instruction.rt);
                output_print(operations, r_dest, r_source, r_target);
		instructions.push_back(instruction);
                
            } else {
                
                if (debug == 1) {
                    std::cout << "Address: " << hexnum <<'\n';
                    std::cout << "Opcode: " << I_instruction.opcode << '\n';
                    std::cout << "Rs: " << I_instruction.rs << '\n';
                    std::cout << "Rt: " << I_instruction.rt << '\n';
                    std::cout << "Imm: " << stoi(I_instruction.imm,0,2) << '\n';
                    //std::cout << "Shamt: " << instruction.shamt << '\n';
                // std::cout << "Func: " << instruction.func << '\n';
                }
                std::cout << "I-type" << std::endl;
                I_operating(I_instruction.rs,I_instruction.rt,I_instruction.imm,
                                            I_instruction.opcode);
                operations = op_directive(instruction.opcode);
                r_dest = whichRegister(I_instruction.rs);
                r_source = whichRegister(I_instruction.rt);
                r_imm =I_instruction.imm;
                I_output_print(operations,r_dest,r_source,I_instruction.imm);
            }
        }
    
        
        //std::cout << "Hexadecimal: " << hexnum << ", Binary: " << binum << '\n';
        
    }

    executePipeline(instructions);
    file.close();

    std::cout << "Array ";
    for(int i = 0; i < 32; i++) {
        std::cout << R[i] << " ";
    }
    std::cout << "\n";
    return 0;

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

/**R-type Registers**/
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

/**I-type Registers**/
I_Instruction I_imageSplitter(const std::string& hex) {
    unsigned long num = std::stoul(hex, nullptr, 16);
    std::bitset<32> binary(num);

    I_Instruction I_instruction;
    I_instruction.opcode = binary.to_string().substr(0, 6); //opcode
    I_instruction.rs     = binary.to_string().substr(6, 5); //source register
    I_instruction.rt     = binary.to_string().substr(11, 5); //target register
    I_instruction.imm   = binary.to_string().substr(16, 16); //immidiate value

    return I_instruction;
}
/***Return the register as a string ***/
std::string whichRegister(std::string R/*, std::string R_val*/) {
    int R_num = 0;
    R_num = stoi(R, 0, 2);
    for(int i = 0 ; i < 32 ; i++) {
        if (R_num == i) {
           // R[i] = stoi(R_val/*,0,2*/); //store Value of R
            return "R"+std::to_string(i);
        }
    }
    return 0;
}


Instruction executePipeline(vector<Instruction>& instructions) {
    const int pipelineStages = 5;  // Number of pipeline stages
    const int bufferSize = 5;  // Size of the circular buffer
    
    vector<Instruction> pipelineBuffer(bufferSize);  // Circular buffer to hold instructions
    vector<int> stageContents(pipelineStages, -1);  // Array to track stage contents
    
    std::map<std::string, std::string> opcodeMap = {
        {"000000", "ADD"},
        {"000001", "ADDI"},
	{"000010", "SUB"},
	{"000011", "SUBI"},
	{"000100", "MUL"},
	{"000101", "MULI"},
	{"000110", "OR"},
	{"000101", "ORI"},
	{"001000", "AND"},
	{"001001", "ANDI"},
	{"001010", "XOR"},
	{"001011", "XORI"},
	{"001100", "LDW"},
	{"001101", "STW"},
	{"001110", "BZ"},
	{"001111", "BEQ"},
	{"010000", "JR"},
	{"010001", "HALT"},
        
    };

    int clock = 0;  // Global clock counter
    bool haltEncountered = false;  // Flag to indicate if halt instruction encountered
    
    for (int i = 0; i < instructions.size(); i++) {
        cout << "Clock Cycle " << clock << ":" << endl;
        
        // Check if halt instruction encountered
        if (instructions[i].opcode == "HALT") {
            haltEncountered = true;
            break;
        }
        
        // Normal Operation: Increment the clock and remove instruction in the last stage
        if (stageContents[pipelineStages - 1] != -1) {
            Instruction instruction = pipelineBuffer[stageContents[pipelineStages - 1]];
            pipelineBuffer[stageContents[pipelineStages - 1]] = Instruction();  // Remove instruction from the buffer
            stageContents[pipelineStages - 1] = -1;  // Update stage contents
            
            // Call the operating function for the instruction
            operating(instruction.rs, instruction.rt, instruction.rd, instruction.opcode);
        }
        
        // Update the array contents to reflect the movement of instructions
        for (int j = pipelineStages - 1; j >= 1; j--) {
            stageContents[j] = stageContents[j - 1];
        }
        
        // Fetch the next instruction into the first stage
        if (i < instructions.size()) {
            pipelineBuffer[0] = instructions[i];
            stageContents[0] = i % bufferSize;
        }
        
        // Print the contents of each stage
    	for (int j = 0; j < pipelineStages; j++) {
  	  if (stageContents[j] != -1) {
        	std::string opcode = pipelineBuffer[stageContents[j]].opcode;
        	std::string opcodeStr = opcodeMap[opcode];
        
       		std::cout << "Stage " << j << ": " << opcodeStr << " "
                  	  << pipelineBuffer[stageContents[j]].rs << " "
                  	  << pipelineBuffer[stageContents[j]].rt << " "
                 	  << pipelineBuffer[stageContents[j]].rd << std::endl;
    	  } else {
        	std::cout << "Stage " << j << ": Empty" << std::endl;
   	 	}		
	}

        
        // Increment the clock
        clock++;
        
        // Handle data hazards or branch/jump instructions
        // This part needs to be customized based on specific hazard detection and handling mechanisms
        
        // Stop fetching new instructions during stall duration
        
        // Update the program counter for branch/jump instructions
        
        cout << endl;
    }
    
    if (haltEncountered) {
        cout << "Halt instruction encountered. Pipeline stopped." << endl;
    } else {
        cout << "End of instructions. Pipeline completed." << endl;
    }

 if (!instructions.empty()) {
        return instructions.back();
    } else {
        return Instruction();  // Return a default-constructed Instruction if the instructions vector is empty
    }
}


/*
//operating function

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
        //instruction.rd = std::bitset<5>(result).to_string();
		
	}
return instruction;
	

}*/