#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "functions.h"
#include <sstream>


std::string op_directive(std::string opcode)
{
    int opcode_int = 0;
    opcode_int = stoi(opcode, 0, 2);

    switch(opcode_int) {
    case ADD:
        return "ADD";
        break;
    case ADDI:
        return "ADDI";
        break;
    case SUB:
        return "SUB";
        break;
    case SUBI:
        return "SUBI";
        break;
    case MUL:
        return "MUL";
        break;
    case MULI:
        return "MULI";
        break;
    case OR:
        return "OR"; 
        break;
    case ORI:
        return "ORI"; 
        break;
    case AND:
        return "AND";
        break;
    case ANDI:
        return "ANDI";
        break;
    case XOR:
        return "XOR";
        break;
    case XORI:
        return "XORI";
        break;
    case LDW:
        return "LDW";
        break;
    case STW:
        return "STW";
        break;
    case BZ:
        return "BZ";
        break;
    case BEQ:
        return "BEQ";
        break;
    case JR:
        return "JR";
        break;
    case HALT:
        return "HALT";
        break;
        
    default:
        std::cout<<"NOT DEFINED";
        exit(1);
        break;

    }
    return "Noting";
}



/****Operating function for R type ****/
Instruction operating( std::string& rs, std::string& rt,std::string& rd,std::string& opcode){
	Instruction instruction;
	instruction.rs = rs;
 	instruction.rd = rd;
    instruction.rt = rt;
	instruction.opcode = opcode;
	int sr_1 = R[stoi(rs)];
    int sr_2 = R[stoi(rt)];
    int dest_r = 0;

	if(stoi(opcode,0,2) == ADD) {
        std::cout <<"ADD:" <<rt << "RS:"<< rs<<std::endl;

		//int rs_val = stoi(rs,0,2);
		//int rt_val = stoi(rt,0,2);
		//int result = rs_val + rt_val;
        int result = sr_1 + sr_2;
        R[stoi(rd,0,2)] = result;
        std::cout<< "From Arr["<<stoi(rd)<<"]" << R[stoi(rd)]<<std::endl;
		std::cout<< "Result :"<< result<< std::endl;
        //instruction.rd = std::bitset<5>(result).to_string();
		
	}

	if(stoi(opcode,0,2) == SUB){
        std::cout <<"SUB:" <<rt << "RS:"<< rs<<std::endl;
		//int rs_val = stoi(rs,0,2);
		//int rt_val = stoi(rt,0,2);
		//int result = rs_val - rt_val;
        int result = sr_1 + sr_2;
        R[stoi(rd)] = result;
        std::cout<< "From Arr["<<stoi(rd,0,2)<<"]" << R[stoi(rd)]<<std::endl;
		std::cout<< "Result :"<< result<< std::endl;
		
	}	
	if(stoi(opcode,0,2) == MUL){
        std::cout <<"MUL:" <<rt << "RS:"<< rs<<std::endl;
		//int rs_val = stoi(rs,0,2);
		//int rt_val = stoi(rt,0,2);
		//int result = rs_val * rt_val;
        int result = sr_1 + sr_2;
        R[stoi(rd)] = result;
        std::cout<< "From Arr["<<stoi(rd)<<"]" << R[stoi(rd)]<<std::endl;
		std::cout<< "Result :"<< result<< std::endl;
		
	}
	if(stoi(opcode,0,2) == OR){
		//int rs_val = stoi(rs,0,2);
		//int rt_val = stoi(rt,0,2);
		//int result = rs_val || rt_val;
        int result = sr_1 + sr_2;
        R[stoi(rd)] = result;
        std::cout<< "From Arr:" << R[stoi(rd)]<<std::endl;
		std::cout<< "Result :"<< result<< std::endl;
		
	}
	if(stoi(opcode,0,2) == AND){
		//int rs_val = stoi(rs,0,2);
		//int rt_val = stoi(rt,0,2);
		//int result = rs_val && rt_val;
        int result = sr_1 + sr_2;
        R[stoi(rd)] = result;
        std::cout<< "From Arr:" << R[stoi(rd)]<<std::endl;
		std::cout<< "Result :"<< result<< std::endl;
		
	}
	if(stoi(opcode,0,2) == XOR){
		//int rs_val = stoi(rs,0,2);
		//int rt_val = stoi(rt,0,2);
		//int result = rs_val ^ rt_val;
        int result = sr_1 + sr_2;
        R[stoi(rd)] = result;
        std::cout<< "From Arr:" << R[stoi(rd)]<<std::endl;
		std::cout<< "Result :"<< result<< std::endl;
		
	}
return instruction;
	

}

//for I type
I_Instruction I_operating( std::string& rs, std::string& rt,std::string& imm,std::string& opcode){
	I_Instruction i_instruction;
	i_instruction.rs = rs;
 	i_instruction.rt = rt;
    i_instruction.imm = imm;
	i_instruction.opcode = opcode;
    int rs_val = R[stoi(rs)];
    int rt_val = R[stoi(rt)];
	
	if(stoi(opcode,0,2) == ADDI) {

		int imm_val = stoi(imm,0,2);
		int result = imm_val + rt_val;
        R[stoi(rs)] = result;
		std::cout<< "Result :"<< result<< std::endl;
        //instruction.rd = std::bitset<5>(result).to_string();
		
	}

	if(stoi(opcode,0,2) == SUBI){
	
		int imm_val = stoi(imm,0,2);
		int result = rt_val - imm_val;
        R[stoi(rs)] = result;
		std::cout<< "Result :"<< result<< std::endl;
		
	}	

	if(stoi(opcode,0,2) == MULI){
	
		int imm_val = stoi(imm,0,2);
		int result = rt_val * imm_val;
        R[stoi(rs)] = result;
		std::cout<< "Result :"<< result<< std::endl;
		
	}

	if(stoi(opcode,0,2) == ORI){
	
		int imm_val = stoi(imm,0,2);
		int result = rt_val || imm_val;
		R[stoi(rs)] = result;
        std::cout<< "Result :"<< result<< std::endl;
		
	}

	if(stoi(opcode,0,2) == ANDI){
	
		int imm_val = stoi(imm,0,2);
		int result = rt_val && imm_val;
        R[stoi(rs)] = result;
		std::cout<< "Result :"<< result<< std::endl;
		
	}

	if(stoi(opcode,0,2) == XORI){
	
		int imm_val = stoi(imm,0,2);
		int result = rt_val ^ imm_val;
        R[stoi(rs)] = result;
		std::cout<< "Result :"<< result<< std::endl;
		
	}

	if(stoi(opcode,0,2) == LDW){
	
		int imm_val = stoi(imm,0,2);
		int address = rt_val + imm_val;
		//int contents = memory[address]; 
		//rt_val = contents;
		//std::cout<< "Result :"<< address << std::endl;
		
	}

	if(stoi(opcode,0,2) == STW){
	
		int imm_val = stoi(imm,0,2);
		int result = rt_val + imm_val;
        R[stoi(rs)] = result;
		std::cout<< "Result :"<< result<< std::endl;
		
	}

	if(stoi(opcode,0,2) == BZ){
	
		int imm_val = stoi(imm,0,2);
		if(rs_val == 0){
			std::cout<< "Result: "<<std::endl;
		}
	
		
	}

	if(stoi(opcode,0,2) == BEQ){
	
		int imm_val = stoi(imm,0,2);
		if(rs_val == rt_val){
		//need to implement logic branch
		std::cout<< "Result :"<< std::endl;
		}
	}

	if(stoi(opcode,0,2) == JR){
		
		int imm_val = stoi(imm,0,2);
		//load PC with the content of register RS
		//need to implement the logic to update program counter (PC)
		//based on the value of rs_val
		
	}

	if(stoi(opcode,0,2) == HALT){
		
		std::cout<< "Result: HALT!!! "<< std::endl;
		
	}

return i_instruction;
	

}