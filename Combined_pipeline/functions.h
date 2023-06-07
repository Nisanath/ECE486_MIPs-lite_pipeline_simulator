#include <string>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>

extern int R[];



//void hextobin(std::string s);
std::string hex2bin(std::string hexnum);

std::string whichRegister(std::string R);
std::string op_directive(std::string opcode);

enum opcode_directive{ADD,ADDI,SUB,SUBI,MUL,MULI,OR,ORI,AND,
                        ANDI,XOR,XORI,LDW,STW,BZ,BEQ,JR,HALT};

//int R[32] = {0}; // Array of registers from 0-31

struct Instruction {
    std::string opcode;
    std::string rs;
    std::string rt;
    std::string rd;
    std::string shamt;
    std::string func;
};

struct I_Instruction {
    std::string opcode;
    std::string rs;
    std::string rt;
    std::string imm;
};

Instruction imageSplitter(const std::string& hex);
I_Instruction I_imageSplitter(const std::string& hex);
Instruction executePipeline(std::vector<Instruction>& Instruction);

#endif