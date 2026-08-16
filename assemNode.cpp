#include "assemNode.h"

std::ostream& operator<<(std::ostream& os, AsmOperand& operand) {
    return operand.output(os);
}

std::ostream& AsmRegister::output(std::ostream& os) {
    os << "%eax";
    return os;
}

std::ostream& AsmImmediate::output(std::ostream& os) {
    os << "$" << value;
    return os;
}

void AsmRet::output(std::ostream& os) {
    os << "    " << "ret" << std::endl;
}

void AsmMov::output(std::ostream& os) {
    os << "    movl " << *src << ", " << *dest << std::endl;
}

void AsmFunc::output(std::ostream& os) {
    os << "    " << ".globl " << name << std::endl;
    os << name << ":" << std::endl;
    for (const auto& inst : instructions) {
        inst->output(os);
    }
}

void AsmPrg::output(std::ostream& os) const {
    if (func) {
        func->output(os);
    }
    if (isLinux) {
        os << ".section .note.GNU-stack,\"\",@progbits" << std::endl;
    }
}
