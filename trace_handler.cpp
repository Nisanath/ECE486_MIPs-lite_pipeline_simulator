#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <bitset>
#include "functions.h"
#include <sstream>
#include <unordered_map>
#include <vector>
#include <map>

using namespace std;
/*Variables*/
int debug = 0;
int verbose = 1;
int counter = 0;
int ins_total = 0;
int ins_ct = 0; //instruction cnt
int logi_ct = 0; //logical cnt
int mem_ac_ct = 0; //mem access cnt
int ctrl_ct = 0; //control transfer instruction
/*Strings*/
std::string line;
std::string hexnum, binum;
char ** file_name;

string bin_image;

string operations;
string r_source,r_target, r_dest, r_imm;
int R[32] = {0}; // initialize to 0 
/*operations for R-type*/
Instruction operating( std::string& rs, std::string& rt,
                        std::string& rd,std::string& opcode); 
/*operations for I-type*/
I_Instruction I_operating( std::string& rs, std::string& rt,
                        std::string& imm,std::string& opcode);

void output_print(std::string opcode, std::string rd, std::string  rs, std::string rt) {
   // if(debug==1)
        std::cout<< opcode <<' ' << rd <<' ' << rs <<' ' << rt << endl;
}

void I_output_print(std::string opcode, std::string rs, std::string  rt, std::string imm) {
    if(debug)
        std::cout<< opcode <<' ' << rs <<' ' << rt <<' ' << stoi(imm,0,2) << endl;
}


void executePipeline(const vector<Instruction>& instructions, const string& opcode, const string& rd, const string& rs, const string& rt) {
    // Execute the instruction based on the opcode, destination, source, and target
    // Add your logic here to handle the execution in the pipeline
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
    
    for (int i = 0; i < instructions.size(); i++) {
        cout << "Clock Cycle " << clock << ":" << endl;
        
        // Normal Operation: Increment the clock and remove instruction in the last stage
        if (stageContents[pipelineStages - 1] != -1) {
            pipelineBuffer[stageContents[pipelineStages - 1]] = Instruction();  // Remove instruction from the buffer
            stageContents[pipelineStages - 1] = -1;  // Update stage contents
        }
        
        // Update the array contents to reflect the movement of instructions
        for (int j = pipelineStages - 1; j >= 1; j--) {
            stageContents[j] = stageContents[j - 1];
        }
        
        // Fetch the next instruction into the first stage
        if (i < instructions.size()) {
            Instruction instr;
            instr.opcode = opcode;
            instr.rs = rs;
            instr.rt = rt;
            instr.rd = rd;
            pipelineBuffer[0] = instr;
            stageContents[0] = i % bufferSize;
        }
        
        // Print the contents of each stage
        for (int j = 0; j < pipelineStages; j++) {
            if (stageContents[j] != -1) {
                const Instruction& currInstr = pipelineBuffer[stageContents[j]];
                cout << "Stage " << j << ": " << opcodeMap[currInstr.opcode] << " " << currInstr.rd << ", " << currInstr.rs << ", " <<currInstr.rt<< endl;
            } else {
                cout << "Stage " << j << ": Empty" << endl;
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
}
void printMap(const std::unordered_map<std::string, int>& myMap) {
    for (std::unordered_map<std::string, int>::const_iterator it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << "\n";
    }
}
void print_image_output()
{
    ins_total = ins_ct+logi_ct+mem_ac_ct+ctrl_ct;
    std::cout<< "Instruction counts: "<<ins_total <<std::endl;
    std::cout<< "\n";
    std::cout<< "Arithmetic instructions: " << ins_ct <<std::endl;
    std::cout<< "Logical instructions: " <<logi_ct << std::endl;
    std::cout<< "Memory access instructions: "<<mem_ac_ct<< std::endl;
    std::cout<< "Control transfer instruction: "<<ctrl_ct<< std::endl;
    std::cout<< "\n";
    std::cout<< "Final register state" <<std::endl;
    std::cout << std::endl;
    std::cout<< "Program counter:"<< counter <<std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 31; i +=2) {
        std::cout << "R" <<std::dec<< (i) << ":"<<std::dec << R[i] << "\t R" <<std::dec<< (i + 1) << ":" <<std::dec<< R[i] <<std::endl;
    }
    std::cout<< "Final memory state" <<std::endl;
    std::cout<< "Address" <<"Contents"<<std::endl;

    /*Printing Final contents*/
    printMap(regi_map);

    
}

int main(int argc, char* argv[]) {

   //if (argc != 2 && strcmp(argv[2], "1") == 0 ) {
   /* if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }*/
   // if(strcmp(argv[2], "1") == 0)
      //  debug = 1;
    for(int i = 0 ; i < argc; i++) {
        if (argc <= 0) {
                cout<< "Please Provide Name of File"<< endl;
                std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
                return -1;
            } else if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--verbose") == 0) ){
                cout<< "Verbose mode"<< endl;
                verbose = 1;
            } else if ((strcmp(argv[i], "-d") == 0) || (strcmp(argv[i], "--debug") == 0)){
                cout<< "Debug mode"<< endl;
                debug = 1;
            } 
    }
    //string file_name = argv[1];
    
    //ifstream input_file(file_name);
    vector<Instruction> instructions;  // Store the instructions
    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open the file \"" << file_name << "\" for reading." << std::endl;
        return 1;
    }

   // while (file >> hexnum) {
    while (getline(file,line)) {
        file >>hexnum;
        if (hexnum.size() != 8) {
            std::cerr << "Invalid hexadecimal number: " << hexnum << '\n';
            continue;
        }
        if(debug)
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
        if (stoi(type_select,0,2) >= 0 && stoi(type_select,0,2)  < 18) {
            if (stoi(type_select,0,2) % 2 == 0) {

                //std::cout << "R-type" << std::endl;
                operating( instruction.rs, instruction.rt,instruction.rd,
                            instruction.opcode);

                operations = op_directive(instruction.opcode);
                r_dest = whichRegister(instruction.rd);
                r_source = whichRegister(instruction.rs);
                r_target = whichRegister(instruction.rt);
                if(verbose) {
                    output_print(operations, r_dest, r_source, r_target);
		    instructions.push_back(instruction);  // Store the instruction in the vector

     		   // Execute the instruction in the pipeline
      			  executePipeline(instructions, instruction.opcode, instruction.rd, instruction.rs, instruction.rt);	
                }
                
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
                //std::cout << "I-type" << std::endl;
                I_operating(I_instruction.rs,I_instruction.rt,I_instruction.imm,
                                            I_instruction.opcode);
                operations = op_directive(instruction.opcode);
                r_dest = whichRegister(I_instruction.rs);
                r_source = whichRegister(I_instruction.rt);
                r_imm =I_instruction.imm;
                if(verbose) {
                    I_output_print(operations,r_dest,r_source,I_instruction.imm);
		 instructions.push_back(instruction);  // Store the instruction in the vector

     		   // Execute the instruction in the pipeline
      			  executePipeline(instructions, I_instruction.opcode, I_instruction.rs, I_instruction.rt, I_instruction.imm);	
                }
            }
        }
    
        
        //std::cout << "Hexadecimal: " << hexnum << ", Binary: " << binum << '\n';
        
    }
    file.close();
    print_image_output();
    /*std::cout << "Array ";
    for(int i = 0; i < 32; i++) {
        std::cout << R[i] << " ";
    }
    std::cout << "\n";/*/
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
