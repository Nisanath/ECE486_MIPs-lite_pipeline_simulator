#include <iostream>
#include <vector>

using namespace std;

// Struct to represent an instruction
struct Instruction {
    string opcode;  // Opcode of the instruction
    string operands;  // Operands of the instruction
};

// Function to execute the pipeline
void executePipeline(vector<Instruction>& instructions) {
    const int pipelineStages = 5;  // Number of pipeline stages
    const int bufferSize = 5;  // Size of the circular buffer
    
    vector<Instruction> pipelineBuffer(bufferSize);  // Circular buffer to hold instructions
    vector<int> stageContents(pipelineStages, -1);  // Array to track stage contents
    
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
            pipelineBuffer[stageContents[pipelineStages - 1]] = Instruction();  // Remove instruction from the buffer
            stageContents[pipelineStages - 1] = -1;  // Update stage contents
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
                cout << "Stage " << j << ": " << pipelineBuffer[stageContents[j]].opcode << " " << pipelineBuffer[stageContents[j]].operands << endl;
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
    
    if (haltEncountered) {
        cout << "Halt instruction encountered. Pipeline stopped." << endl;
    } else {
        cout << "End of instructions. Pipeline completed." << endl;
    }
}

int main() {
    // Create a vector of instructions and initialize it using explicit struct creation and push_back()
    vector<Instruction> instructions;
    Instruction instr1 = {"SLL", "R5, R5, #1"};
    instructions.push_back(instr1);
    Instruction instr2 = {"ADDI", "R4, R4, #-1"};
    instructions.push_back(instr2);
    Instruction instr3 = {"ADD", "R5, R5, R6"};
    instructions.push_back(instr3);
    Instruction instr4 = {"BNEZ", "R4, LOOP"};
    instructions.push_back(instr4);
    Instruction instr5 = {"SLL", "R5, R5, #1"};
    instructions.push_back(instr5);
    Instruction instr6 = {"ADDI", "R4, R4, #-1"};
    instructions.push_back(instr6);
    Instruction instr7 = {"HALT", ":"};
    instructions.push_back(instr7);
    Instruction instr8 = {"BNEZ", "R4, LOOP"};
    instructions.push_back(instr8);
    
    // Execute the pipeline
    executePipeline(instructions);
    
    return 0;
}




