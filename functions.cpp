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
        break;

    }
    return "Noting";
}

std::string whichRegister(std::string R) {
    int R_num = 0;
    R_num = stoi(R, 0, 2);
    for(int i = 0 ; i < 32 ; i++) {
        if (R_num == i)
            return "R"+std::to_string(i);
    }
    return 0;
}