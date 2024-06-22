#ifndef DECORATOR_H
#define DECORATOR_H

#include <QString>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>

class Processor {
public:
    virtual QString process(const QString& data) = 0;
};

class ConcreateProcessor: public Processor {
public:
    QString process(const QString& data) override;
    QString readData(const QString& filename);
};


class Decorator: public Processor {
protected:
    Processor *proc;
public:
    Decorator(Processor *processor): proc(processor){};

    QString process(const QString& data) override{
        return proc? proc->process(data): nullptr;
    };
};

class FormulaCalculator : public Decorator {
public:
    FormulaCalculator(Processor *processor) : Decorator(processor){};
    QString process(const QString& data) override;
};

class FormulaMarker : public Decorator {
public:
    FormulaMarker(Processor *processor) : Decorator(processor){};
    QString process(const QString& data) override;
};

class HexToDecimal : public Decorator {
public:
    HexToDecimal(Processor *processor) : Decorator(processor){};
    QString process(const QString& data) override;
};

class DecimalToHex : public Decorator {
public:
    DecimalToHex(Processor *processor) : Decorator(processor){};
    QString process(const QString& data) override;
};

class RemoveDigits : public Decorator {
public:
    RemoveDigits(Processor *processor) : Decorator(processor){};
    QString process(const QString& data) override;
};

class ReverseText : public Decorator {
public:
    ReverseText(Processor *processor) : Decorator(processor){};
    QString process(const QString& data) override;
};

#endif // DECORATOR_H

