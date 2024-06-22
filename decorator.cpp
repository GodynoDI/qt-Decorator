#include "Decorator.h"

QString ConcreateProcessor::readData(const QString& filename){
    QFile file(filename);
    QString fileText;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        fileText = in.readAll();
        fileText.replace("\n", " ");
        file.close();
    }
    return fileText;
};

QString ConcreateProcessor::process(const QString &data) {
    return readData(data);
}

QString FormulaCalculator::process(const QString& data) {
    QString processedData = Decorator::process(data);
    QRegularExpression formulaRegex("(\\d+)([\\+\\-])(\\d+)");
    QRegularExpressionMatchIterator matchIterator = formulaRegex.globalMatch(processedData);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        int num1 = match.captured(1).toInt();
        int num2 = match.captured(3).toInt();
        QString op = match.captured(2);
        int result = (op == "+") ? num1 + num2 : num1 - num2;
        processedData.replace(match.captured(), QString::number(result));
    }
    return processedData;
}

QString FormulaMarker::process(const QString& data) {
    QString processedData = Decorator::process(data);
    QRegularExpression formulaRegex("(\\d+)([\\+\\-])(\\d+)");
    int formulaCount = 1;
    QRegularExpressionMatchIterator matchIterator = formulaRegex.globalMatch(processedData);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        processedData.replace(match.captured(), match.captured() + " (Формула " + QString::number(formulaCount++) + ")");
    }
    return processedData;
}

QString HexToDecimal::process(const QString& data) {
    QString processedData = Decorator::process(data);
    QRegularExpression hexRegex("\\b0x[0-9a-fA-F]+\\b");
    QRegularExpressionMatchIterator matchIterator = hexRegex.globalMatch(processedData);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString hex = match.captured();
        bool flag;
        int decimal = hex.toInt(&flag, 16);
        if (flag)
            processedData.replace(match.captured(), QString::number(decimal));
    }
    return processedData;
}

QString DecimalToHex::process(const QString& data) {
    QString processedData = Decorator::process(data);
    QRegularExpression decimalRegex("\\b\\d+\\b");
    QRegularExpressionMatchIterator matchIterator = decimalRegex.globalMatch(processedData);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString decimal = match.captured();
        int decValue = decimal.toInt();
        processedData.replace(QRegularExpression("\\b"+decimal+"\\b"), "0x" + QString::number(decValue, 16));
    }
    return processedData;
}

QString RemoveDigits::process(const QString& data) {
    QString processedData = Decorator::process(data);
    processedData.remove(QRegularExpression("[1-9]+"));
    return processedData;
}

QString ReverseText::process(const QString& data) {
    QString baseData = Decorator::process(data);
    QString processedData = "";
    for (int i = baseData.length() - 1; i >= 0; --i) {
        processedData.append(baseData.at(i));
    }
    return processedData;
}
