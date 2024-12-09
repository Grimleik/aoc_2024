#include <iostream>
#include <string.h>
#include <vector>
#include <assert.h>

class InstructionParser
{
public:
    enum class EInstruction
    {
        EMul,
    };

    // typedef struct binary_instruction_t binary_instruction_t;
    struct binary_instruction_t
    {
        EInstruction instruction;
        int op1, op2;
    };

    int CalculateInstructions();

    bool skipInstruction = false;
    void Parse(std::string &input);

private:
    std::vector<binary_instruction_t> instructions;
};

int InstructionParser::CalculateInstructions()
{
    int result = 0;
    for (auto &inst : instructions)
    {
        switch (inst.instruction)
        {
        case EInstruction::EMul:
            result += inst.op1 * inst.op2;
            break;

        default:
            break;
        }
    }

    return result;
}

void InstructionParser::Parse(std::string &input)
{
    const int inputSize = input.size();
    for (int i = 0; i < inputSize; ++i)
    {
        switch (input[i])
        {
        case 'd':
        {
            if ((i + 3) < inputSize &&
                input[i + 1] == 'o' &&
                input[i + 2] == '(' &&
                input[i + 3] == ')')
            {
                skipInstruction = false;
                i += 3;
            }
            else if ((i + 6) < inputSize &&
                     input[i + 1] == 'o' &&
                     input[i + 2] == 'n' &&
                     input[i + 3] == '\'' &&
                     input[i + 4] == 't' &&
                     input[i + 5] == '(' &&
                     input[i + 6] == ')')
            {
                skipInstruction = true;
                i += 6;
            }
        }
        break;
        case 'm':
        {
            if (skipInstruction)
                continue;

            int end = input.find(')', i);
            // NOTE(pf): Input size is maximum ul( + <3 digits> + , + <3 digits>
            // + ) = 3 + 3 + 1 + 3 + 1 11 chars.
            if (end < inputSize && (end - i) <= 11)
            {
                int sep = input.find(',', i);
                /* NOTE(pf):
                 * What we anticipate: mul([...],[...])
                 * First part ensures mul(
                 * Then that ',' is between '(' and ')'
                 * We then check internally if the operands are < 1000 each.
                 * Edge case example of corruption 1001,10 -> 100,110.
                 */
                if (input[i + 1] == 'u' && input[i + 2] == 'l' && input[i + 3] == '(' &&
                    sep > (i + 3) && sep < end)
                {
                    assert(sep > i && sep < end);
                    int op1 = 0;
                    int op2 = 0;
                    std::string dbgOp1 = std::string(input.begin() + (i + 4),
                                                     input.begin() + sep);
                    std::string dbgOp2 = std::string(input.begin() + sep + 1,
                                                     input.begin() + end);

                    op1 = atoi(dbgOp1.c_str());
                    op2 = atoi(dbgOp2.c_str());
                    // NOTE(pf): Input ensures that inputs are 3 digit numbers.
                    // Assuming corruption if this doesn't hold.
                    if (op1 < 1000 && op1 > 0 && op2 < 1000 && op2 > 0)
                    {
                        instructions.push_back({EInstruction::EMul, op1, op2});
                    }

                    // NOTE(pf): Jump over this instruction.
                    i = end;
                }
            }
        }
        break;

        default:
            break;
        }
    }
}

void part12()
{
    std::string input;
    InstructionParser ip;
    while (std::getline(std::cin, input) && input.size() > 0)
    {
        ip.Parse(input);
    }

    int result = ip.CalculateInstructions();
    std::cout << "Result is: " << result << std::endl;
}

int main(int, char **)
{
    part12();
}
