#include <string>
#include <unordered_map>
#include <iostream>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
extern int R[];

extern int debug;
extern int verbose;
extern int ins_ct;
extern int logi_ct;
extern int mem_ac_ct;
extern int ctrl_ct;

extern std::unordered_map<std::string, int> regi_map;
//void hextobin(std::string s);
std::string hex2bin(std::string hexnum);

std::string whichRegister(std::string R);
std::string op_directive(std::string opcode);
void print_image_output();

void populateMap(std::string addr, int contents);
template<typename K, typename V>

void printMap(const std::unordered_map<std::string, int>& myMap);
 

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


#endif