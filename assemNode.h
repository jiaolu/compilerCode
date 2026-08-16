#ifndef ASSEM_NODE_H
#define ASSEM_NODE_H
#include <vector>
#include <memory>
#include <ostream>

class AsmFunc;
class AsmInst;
class AsmMove;
class AsmOperand;
class AsmRegister;
class AsmImmediate;

class AsmNode {
public:
    virtual ~AsmNode() = default;
};

class AsmOperand : public AsmNode
{
public:
    virtual std::ostream& output(std::ostream& os) = 0;
};

std::ostream& operator<<(std::ostream& os, AsmOperand& operand);

class AsmRegister : public AsmOperand
{
public:
    std::ostream& output(std::ostream& os) override;
};

class AsmImmediate : public AsmOperand {
public:
    explicit AsmImmediate(unsigned v) : value(v) {}
    std::ostream& output(std::ostream& os) override;
    unsigned value;
};

class AsmInst : public AsmNode
{
public:
    virtual void output(std::ostream& os) = 0;
};

class AsmRet : public AsmInst
{
public:
    AsmRet() = default;
    void output(std::ostream& os) override;
};

class AsmMov : public AsmInst
{
public:
    std::unique_ptr<AsmOperand> src;
    std::unique_ptr<AsmOperand> dest;
    AsmMov(std::unique_ptr<AsmOperand> s, std::unique_ptr<AsmOperand> d) : src(std::move(s)), dest(std::move(d)) {}
    void output(std::ostream& os) override;
};

class AsmFunc : public AsmNode
{
public:
    explicit AsmFunc(const char* fname) : name(fname) {}
    void output(std::ostream& os);
    std::vector<std::unique_ptr<AsmInst>> instructions;
    const char* name;
};

class AsmPrg : public AsmNode
{
public:
#ifdef __linux__
    static constexpr bool isLinux = true;
#else
    static constexpr bool isLinux = false;
#endif

    void output(std::ostream& os) const;
    std::unique_ptr<AsmFunc> func;
};

#endif